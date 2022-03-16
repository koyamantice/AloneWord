#include "Enemy.h"
#include "Input.h"
#include"Collision.h"
#include<sstream>
#include<iomanip>
using namespace DirectX;

Enemy::Enemy() {
	model = Model::CreateFromOBJ("chr_sword");
	object3d = new Object3d();
}

void Enemy::Initialize() {

	//プレイヤー
	
	IsAlive = 0;
	IsTimer = 100;
	object3d = Object3d::Create();
	object3d->SetModel(model);
	object3d->SetPosition(pos);

	collider.radius=rad;
}

void Enemy::Update(Player* player,BossEnemy* bossenemy) {
	
	collider.center = XMVectorSet(pos.x,pos.y,pos.z,1);
	XMFLOAT3 bosspos = bossenemy->GetPosition();
	XMFLOAT3 playerpos = player->GetPosition();

	if (IsAlive == 0) {
		IsTimer--;
	}

	if (IsTimer == 0) {
		IsAlive = 1;
		IsTimer = 100;
		speed = (float)(rand() % 360);
		scale = (float)(rand() % 10 + 10);

		//radius = speed * PI / 180.0f;
		//circleX = cosf(radius) * scale;
		//circleZ = sinf(radius) * scale;
		//pos.x = circleX + bosspos.x;
		//pos.z = circleZ + bosspos.z;
	}
	//プレイヤー
	radius = speed * PI / 180.0f;
	circleX = cosf(radius) * scale;
	circleZ = sinf(radius) * scale;
	pos.x = circleX + bosspos.x;
	pos.z = circleZ + bosspos.z;
	
	//bossobj->SetPosition(bosspos);
	collideArm(player);
	collidePlayer(player);
	collideAttackArm(player);
	object3d->SetPosition(pos);
	object3d->Update();
}

void Enemy::Draw() {
	Object3d::PreDraw();
	if (IsAlive == 1) {
		object3d->Draw();
	}

	//bossobj->Draw();
}

bool Enemy::collideArm(Player* player) {
	XMFLOAT3 playerpos = player->GetPosition();
	XMFLOAT3 Armpos = player->GetArmPosition();
	int armMove = player->GetArmMoveNumber();
	if (collision->SphereCollision(pos.x, pos.y, pos.z, 0.5f, Armpos.x, Armpos.y, Armpos.z, 0.5f) == true && IsAlive == 1
		&&armMove >= 1 && EnemyCatch == false) {
		EnemyCatch = true;
		EnemyWeight += 1.0f;
	}

	if (EnemyCatch == true) {
		pos = Armpos;
		return true;
	} else {
		return false;
	}
}

bool Enemy::collidePlayer(Player* player) {
	XMFLOAT3 playerpos = player->GetPosition();
	XMFLOAT3 Armpos = player->GetArmPosition();
	int playerhp = player->GetHp();
	if (collision->SphereCollision(pos.x, pos.y, pos.z, 0.5f, playerpos.x, playerpos.y, playerpos.z, 0.5f) == true && IsAlive == 1
		&& EnemyCatch == false) {
		IsAlive = 0;
		player->SetHp(playerhp - 1);
		return true;
	} else {
		return false;
	}
}

bool Enemy::collideAttackArm(Player* player) {
	XMFLOAT3 Armpos = player->GetArmPosition();
	bool attackflag = player->GetAttackFlag();
	int playerhp = player->GetHp();
	if (collision->SphereCollision(pos.x, pos.y, pos.z, 0.5f, Armpos.x, Armpos.y, Armpos.z, 0.5f) == true && IsAlive == 1
		&& EnemyCatch == false && attackflag == true) {
		IsAlive = 0;
		player->SetAttackFlag(false);
		if (EnemyWeight != 0.0f) {
			EnemyWeight = 0.0f;
		}

		if (EnemyCatch == true) {
			IsAlive = false;
		}
		return true;
	} else {
		return false;
	}
}

