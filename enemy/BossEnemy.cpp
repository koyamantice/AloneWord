#include "BossEnemy.h"
#include "Input.h"
#include"Collision.h"
#include<sstream>
#include<iomanip>
#include "Enemy.h"
#include <Easing.h>
using namespace DirectX;

BossEnemy::BossEnemy() {
	model = Model::CreateFromOBJ("chr_sword");
	object3d = new Object3d();
	Sprite::LoadTexture(4, L"Resources/2d/PlayerHP.png");
}

void BossEnemy::Initialize() {
	SpriteBossHP = Sprite::Create(4, { 0.0f,0.0f });
	SpriteBossHP->SetColor({ 0.0f,1.0f,0.0,1.0 });
	//ƒvƒŒƒCƒ„[
	//radius = speed * PI / 180.0f;
	//circleX = cosf(radius) * scale;
	//circleZ = sinf(radius) * scale;
	//pos.x = circleX + bosspos.x;
	//pos.y = circleZ + bosspos.z;
	IsAlive = 0;
	IsTimer = 100;
	object3d = Object3d::Create();
	object3d->SetModel(model);
	object3d->SetPosition(pos);
	object3d->SetScale({ 3.0f,3.0f,3.0f });
	collider.radius = rad;
}

void BossEnemy::Update(Player* player) {
	
	collider.center = XMVectorSet(pos.x, pos.y, pos.z, 1);
	XMFLOAT2 AfterPos;
	AfterPos = { (float)(BossHP * 20),20 };
	HPPos = {
	Ease(In,Quint,0.7f,SpriteBossHP->GetSize().x,AfterPos.x),
	Ease(In,Quint,0.7f,SpriteBossHP->GetSize().y,AfterPos.y),
	};
	SpriteBossHP->SetSize(HPPos);

	pos = { 0.0f,0.0f,0.0f };
	//collidePlayer(player);
	collideAttackArm(player);
	object3d->SetPosition(pos);
	object3d->Update();
	//bossobj->SetPosition(bosspos);
	//collidePlayer(player);
}

void BossEnemy::Draw() {
	Object3d::PreDraw();

	object3d->Draw();

	Sprite::PreDraw();
	SpriteBossHP->Draw();

	//bossobj->Draw();
}

bool BossEnemy::collidePlayer(Player* player) {
	XMFLOAT3 playerpos = player->GetPosition();
	int playerhp = player->GetHp();
	if (Collision::SphereCollision(pos.x, pos.y, pos.z, 0.5f, playerpos.x, playerpos.y, playerpos.z, 0.5f)) {
		player->SetHp(playerhp - 1);
		return true;
	} else {
		return false;
	}
}

bool BossEnemy::collideAttackArm(Player* player) {
	XMFLOAT3 Armpos = player->GetArmPosition();
	bool attackflag = player->GetAttackFlag();
	int playerhp = player->GetHp();
	float weight = player->GetArmWeight();
	if (attackflag&& !BossHit) {
		if (Collision::SphereCollision(pos.x, pos.y, pos.z, 0.5f, Armpos.x, Armpos.y, Armpos.z, 0.5f) == true) {
			BossHit = true;
			player->SetAttackFlag(false);

			if (BossHit == true) {
				BossHP -= (weight * 2);
				weight = 0.0f;
				player->SetArmWeight(weight);
				BossHit = false;
			}
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}


//bool BossEnemy::collidePlayer(Player* player) {
//	XMFLOAT3 pos = player->GetPosition();
//
//	//if (collision->CheckSphere2Sphere(collider, player->collider) == true && IsAlive == 1) {
//	//	IsAlive = 0;
//	//	scale = 0.0f;
//	//	this->pos = { 0,0,0 };
//	//	return true;
//	//} else {
//	//	return false;
//	//}
//}

