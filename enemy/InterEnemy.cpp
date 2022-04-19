#include "InterEnemy.h"
#include "Collision.h"
#include <XorShift.h>

void InterEnemy::Pause(const int& Timer) {
	int wait = 0;
	if (wait>=Timer) {
		pause = false;
	} else {
		pause = true;
		wait++;
	}
}
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
//“G‚ÌˆÊ’u‚ð˜r‚Æ“¯‚¶‚É‚·‚é
void InterEnemy::SetEnemy() {
	float armweight = player->GetArmWeight();
	XMFLOAT3 plapos = player->GetPosition();
	if (EnemyCatch == true) {
		radius = speed * PI / 180.0f;
		circleX = cosf(radius) * scale;
		circleZ = sinf(radius) * scale;
		pos.x = circleX + plapos.x;
		pos.z = circleZ + plapos.z;
	}
}

//“G‚ªŽ€‚ñ‚¾‚Æ‚«‚Ì‰‰o
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
		enescale.x -= 0.01f;
		enescale.y -= 0.01f;
		enescale.z -= 0.01f;
		if (enescale.x <= 0.0f && enescale.y <= 0.0f && enescale.z <= 0.0f) {
			DrawExp = true;
			Exp = false;
			IsAlive = false;
		}
	}
}

void InterEnemy::RandDeadPower() {
	Deadbound.x = (float)((int)XorShift::GetInstance()->xor128() % 4 - 2);
	Deadbound.y = 5;
	Deadbound.z = (float)((int)XorShift::GetInstance()->xor128() % 4 - 2);
	Deadbound.x = Deadbound.x / 10;
	Deadbound.y = Deadbound.y / 10;
	Deadbound.z = Deadbound.z / 10;
}

void InterEnemy::Respawn(float speed) {
	if (speed!=0.0f) {
		respawn = true;
	}
	this->speed = speed;
}
//“G’Ç]
void InterEnemy::Follow() {
	XMFLOAT3 position{};
	position.x = (playerpos.x - pos.x);
	position.z = (playerpos.z - pos.z);
	rot.y = (atan2(position.x, position.z) * (180.0f / XM_PI)) - 90;// *(XM_PI / 180.0f);
	pos.x -= sin(-atan2(position.x, position.z)) * 0.2f;
	pos.z += cos(-atan2(position.x, position.z)) * 0.2f;
}

void InterEnemy::Reborn() {
	if (!IsAlive) {
		IsTimer--;
		if (IsTimer == 100) {
			if (!respawn) {
				speed = (float)((int)(XorShift::GetInstance()->xor128())% 360);
				scale = (float)((int)(XorShift::GetInstance()->xor128())% 10 + 10);
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
			enemyobj->SetPosition(pos);
		}
		else if (IsTimer == 0) {
			respawn = false;
			IsAlive = true;
			appearance = true;
			isMove = false;
			IsTimer = 200;
		}
	}

}

bool InterEnemy::CollidePos(XMFLOAT3 pos, float radius) {
	return Collision::SphereCollision(pos.x,pos.y,pos.z,radius, this->pos.x, this->pos.y, this->pos.z, radius);
}
