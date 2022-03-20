#include "Enemy.h"
#include "Input.h"
#include"Collision.h"
#include "BossEnemy.h"
#include<sstream>
#include<iomanip>
#include <Easing.h>
using namespace DirectX;

Enemy::Enemy() {
	model = Model::CreateFromOBJ("chr_sword");
	object3d = new Object3d();

}

void Enemy::Initialize() {

	//プレイヤー
	IsAlive = false;
	IsTimer = 100;
	object3d = Object3d::Create();
	object3d->SetModel(model);
	object3d->SetPosition(pos);
	texture = Texture::Create(0, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	texture->TextureCreate();
	texture->SetPosition(pos);
	texture->SetRotation({ 90,0,0 });
	texture->SetScale({ 0.2f,0.2f,0.2f });
	collider.radius = rad;
}

void Enemy::Update(Player* player, BossEnemy* bossenemy) {
	collider.center = XMVectorSet(pos.x, pos.y, pos.z, 1);
	XMFLOAT3 bosspos = bossenemy->GetPosition();
	playerpos = player->GetPosition();
	if (!IsAlive) {
		IsTimer--;
		speed = (float)(rand() % 360);
		scale = (float)(rand() % 10 + 10);
	}

	if (IsTimer <= 0) {
		IsAlive = true;
		isMove = false;
		frame = 0;
		radius = speed * PI / 180.0f;
		circleX = cosf(radius) * scale;
		circleZ = sinf(radius) * scale;
		pos.x = circleX + bosspos.x;
		pos.z = circleZ + bosspos.z;
		IsTimer = 100;
	}
	////スポーン位置
	//radius = speed * PI / 180.0f;
	//circleX = cosf(radius) * scale;
	//circleZ = sinf(radius) * scale;
	//pos.x = circleX + bosspos.x;
	//pos.z = circleZ + bosspos.z;
	collideArm(player);
	collidePlayer(player);
	collideAttackArm(player);
	if (IsAlive && !EnemyCatch) {
		if (LockOn(player)) {
			Follow(player);
		} else {
			Move();
		}
	}
	object3d->SetPosition(pos);
	texture->SetPosition(pos);
	object3d->Update();
	texture->Update();
}

void Enemy::Draw() {
	if (IsAlive) {
		Object3d::PreDraw();
		object3d->Draw();
	}
	if (IsAlive && !EnemyCatch) {
		Texture::PreDraw();
		texture->Draw();

	}
}

bool Enemy::collideArm(Player* player) {
	XMFLOAT3 Armpos = player->GetArmPosition();
	float armweight = player->GetArmWeight();
	int armMove = player->GetArmMoveNumber();
	if (IsAlive && armMove >= 1 && !EnemyCatch) {
		if (Collision::SphereCollision(pos.x, pos.y, pos.z, 0.5f, Armpos.x, Armpos.y, Armpos.z, 0.5f) == true) {
			EnemyCatch = true;
			armweight += 1.0f;
			player->SetArmWeight(armweight);
		}
	}
	if (EnemyCatch == true) {
		pos = Armpos;
		return true;
	} else {
		return false;
	}
}

bool Enemy::collidePlayer(Player* player) {
	XMFLOAT3 Armpos = player->GetArmPosition();
	int playerhp = player->GetHp();
	if (IsAlive && !EnemyCatch) {
		if (Collision::SphereCollision(pos.x, pos.y, pos.z, 0.5f, playerpos.x, playerpos.y, playerpos.z, 0.5f) == true) {
			IsAlive = 0;
			player->SetHp(playerhp - 1);
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Enemy::collideAttackArm(Player* player) {
	XMFLOAT3 Armpos = player->GetArmPosition();
	bool attackflag = player->GetAttackFlag();
	int playerhp = player->GetHp();
	float armweight = player->GetArmWeight();
	if (IsAlive && !EnemyCatch && attackflag) {
		if (Collision::SphereCollision(pos.x, pos.y, pos.z, 0.5f, Armpos.x, Armpos.y, Armpos.z, 0.5f) == true) {
			IsAlive = 0;//持たれててない方
			player->SetAttackFlag(false);
			if (armweight != 0.0f) {//持ってる方
				armweight = 0.0f;
				player->SetArmWeight(armweight);
			}
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Enemy::LockOn(Player* player) {
		if (Collision::CircleCollision(playerpos.x, playerpos.z, 5.0,
			pos.x, pos.z, 3.0)) {
			return true;
		} else {
			return false;
		}
}

void Enemy::Follow(Player* player) {
	XMFLOAT3 position{};
	position.x = (playerpos.x - pos.x);
	position.z = (playerpos.z - pos.z);
	double posR = sqrt(pow(pos.x, 2) + pow(pos.z, 2));
	double Check = position.x / posR;
	double Check2 = position.z / posR;

	if (hit == false) {
		pos.x += Check * 0.08f;
		pos.z += Check2 * 0.08f;
	}
}

void Enemy::Move() {
	if (moveCount == 0&&!isMove) {
		StartPos = pos;
		if (dir % 4 == 0) {
			EndPos.x = StartPos.x + 2.5f;
		} else if (dir % 4 == 1) {
			EndPos.x = StartPos.x - 2.5f;
		} else if (dir % 4 == 2) {
			EndPos.z = StartPos.z - 2.5f;
			zmove = true;
		} else{
			EndPos.z = StartPos.z + 2.5f;
			zmove=true;
		}
		frame = 0;
		isMove = true;
	} else {
		moveCount--;
		dir= (rand() % 40);
	}
	if (isMove && hit == false) {
		if (frame<=1.0f) {
			frame += 0.01f;
		} else {
			frame = 1.0f;
			moveCount = (rand() % 60) +30;
			dir=0;
			isMove = false;
		}
		if (zmove) {
			pos.z = Ease(In, Quad, frame, pos.z, EndPos.z);
		} else {
			pos.x = Ease(In, Quad, frame, pos.x, EndPos.x);
		}

		object3d->SetPosition(pos);

	}
}
