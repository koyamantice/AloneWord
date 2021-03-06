#include "InterEnemy.h"
#include "Collision.h"
#include <XorShift.h>

//ポーズが入ったら止まる
void InterEnemy::Pause(const int& Timer) {
	int wait = 0;
	if (wait>=Timer) {
		pause = false;
	} else {
		pause = true;
		wait++;
	}
}
//hitした場合元の場所に戻る
void InterEnemy::Back() {
	if (hit) {
		XMFLOAT3 setpos{};
		if (oldpos.z>pos.z) {
			setpos.z=oldpos.z-pos.z;
			pos.z += setpos.z * 1.5f;
		} else {
			setpos.z = pos.z - oldpos.z;
			pos.z -= setpos.z * 1.5f;
		}
		if (oldpos.x > pos.x) {
			setpos.x = oldpos.x - pos.x;
			pos.x += setpos.x * 1.5f;
		} else {
			setpos.x = pos.x - oldpos.x;
			pos.x -= setpos.x * 1.5f;
		}
		hit = false;
	}
}
void InterEnemy::Stop() {


}
//敵の位置を腕と同じにする
void InterEnemy::SetEnemy() {
	float armweight = player->GetArmWeight();
	XMFLOAT3 plapos = player->GetPosition();
	if (EnemyCatch == true) {
		radius = speed * PI / 180.0f;
		circleX = cosf(radius) * scale;
		circleZ = sinf(radius) * scale;
		pos.x = circleX + plapos.x;
		pos.y = plapos.y;
		pos.z = circleZ + plapos.z;
	}
}

//敵が死んだときの演出
void InterEnemy::DeadEnemy() {
	Deadbound.y -= 0.02f;
	pos.y += Deadbound.y;
	if (pos.y > 0.0f) {
		pos.x += Deadbound.x;
		pos.z += Deadbound.z;
	} else {
		pos.y = 0.0f;
	}
	if (pos.y == 0.0f) {
		enescale.x -= 0.02f;
		enescale.y -= 0.02f;
		enescale.z -= 0.02f;
		if (enescale.x <= 0.0f && enescale.y <= 0.0f && enescale.z <= 0.0f) {
			DrawExp = true;
			Exp = false;
			IsAlive = false;
			nocatch = false;
		}
	}
}

//ここで死んだときに加算する力を決める
void InterEnemy::RandDeadPower() {
	Deadbound.x = (float)((int)XorShift::GetInstance()->xor128() % 4 - 2);
	Deadbound.y = 5;
	Deadbound.z = (float)((int)XorShift::GetInstance()->xor128() % 4 - 2);
	Deadbound.x = Deadbound.x / 10;
	Deadbound.y = Deadbound.y / 10;
	Deadbound.z = Deadbound.z / 10;
}

//リスポーン
void InterEnemy::Respawn(float speed) {
	if (speed!=0.0f) {
		respawn = true;
	}
	this->speed = speed;
}
//敵追従
void InterEnemy::Follow() {
	XMFLOAT3 position{};
	position.x = (playerpos.x - pos.x);
	position.z = (playerpos.z - pos.z);
	rot.y = (atan2f(position.x, position.z) * (180.0f / XM_PI)) - 90;// *(XM_PI / 180.0f);
	//NextP.x -= sin(-atan2f(position.x, position.z)) * 0.2251f;
	//NextP.z += cos(-atan2f(position.x, position.z)) * 0.2251f;
	vel.x=sin(-atan2f(position.x, position.z)) * 0.2251f;
	vel.y=cos(-atan2f(position.x, position.z)) * 0.2251f;
	pos.x -= vel.x;
	pos.z += vel.y;
}

//リスポーンしたときの場所ぎめ
void InterEnemy::Reborn() {
	if (!IsAlive) {
		IsTimer--;
		if (IsTimer == 90) {
			if (!respawn) {
				speed = (float)((int)rand()% 360);
				scale = (float)((int)rand()% 20 + 10);
			} else {
				scale = 10.0f;
			}
			StartPos = pos;
			frame = 0;
			radius = speed * PI / 180.0f;
			circleX = cosf(radius) * scale;
			circleZ = sinf(radius) * scale;
			pos.x = circleX + basePos.x;
			pos.z = circleZ + basePos.z;
			dir=(rand() % 360);
			rot.y = (float)(dir-90);// *(XM_PI / 180.0f);
			enemyobj->SetRotation(rot);
			enemyobj->SetPosition(pos);
		}
		else if (IsTimer == 0) {
			respawn = false;
			IsAlive = true;
			appearance = true;
			isMove = false;
			followed = false;
			IsTimer = 100;
		}
	}

}

//あたってるかどうかの判定(よくわからない)
bool InterEnemy::CollidePos(XMFLOAT3 pos, float radius) {
	if (Collision::SphereCollision(pos.x, pos.y, pos.z, radius, NextP.x, NextP.y, NextP.z, radius)) {
		this->pos = this->pos;
		NextP = pos;
		return true;
	} else {
		return false;
	}
}
