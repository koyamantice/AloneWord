#include "InterEnemy.h"

void InterEnemy::Pause(const int& Timer) {
	int wait = 0;
	if (wait>=Timer) {
		pause = false;
	} else {
		pause = true;
	}
}
void InterEnemy::Back() {
	if (hit) {
		pos = oldpos;
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
	Deadbound.x = (float)(rand() % 4 - 2);
	Deadbound.y = 5;
	Deadbound.z = (float)(rand() % 4 - 2);
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

void InterEnemy::Reborn() {
	if (!IsAlive) {
		IsTimer--;
		if (IsTimer == 100) {
			if (!respawn) {
				speed = (float)(rand() % 360);
				scale = (float)(rand() % 10 + 10);
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
		}

		else if (IsTimer == 0) {
			IsAlive = true;
			appearance = true;
			isMove = false;
			IsTimer = 200;
		}
	}

}
