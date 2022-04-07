#include "InterMob.h"

void InterMob::Pause(const int& Timer) {
	int stop = 0;
	stop++;
	if (stop>=Timer) {
		pause = false;
	} else {
		pause = true;
	}
}
//“G‚ÌˆÊ’u‚ð˜r‚Æ“¯‚¶‚É‚·‚é
void InterMob::SetEnemy() {
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
void InterMob::DeadEnemy() {
	Deadbound.y -= 0.02f;
	pos.y += Deadbound.y;
	if (pos.y > 0.0f) {
		pos.x += Deadbound.x;
		pos.z += Deadbound.z;
	} 	else {
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

void InterMob::RandDeadPower() {
	Deadbound.x = (float)(rand() % 4 - 2);
	Deadbound.y = 5;
	Deadbound.z = (float)(rand() % 4 - 2);
	Deadbound.x = Deadbound.x / 10;
	Deadbound.y = Deadbound.y / 10;
	Deadbound.z = Deadbound.z / 10;
}