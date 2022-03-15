#include "Enemy.h"
#include "Input.h"
#include"Collision.h"
#include<sstream>
#include<iomanip>
using namespace DirectX;

Enemy::Enemy() {
	model = Model::CreateFromOBJ("chr_sword");
	bossmodel = Model::CreateFromOBJ("chr_sword");
	object3d = new Object3d();
	bossobj = new Object3d();
}

void Enemy::Initialize() {

	//プレイヤー
	radius = speed * PI / 180.0f;
	circleX = cosf(radius) * scale;
	circleZ = sinf(radius) * scale;
	pos.x = circleX + bosspos.x;
	pos.y = circleZ + bosspos.z;
	IsAlive = 0;
	IsTimer = 100;
	object3d = Object3d::Create();
	object3d->SetModel(model);
	object3d->SetPosition(pos);
	bossobj = Object3d::Create();
	bossobj->SetModel(bossmodel);
	bossobj->SetPosition(bosspos);
	bossobj->SetScale({ 3.5,3.5,3.5 });
	collider.radius=rad;
}

void Enemy::Update(Player* player) {
	object3d->Update();
	bossobj->Update();
	collider.center = XMVectorSet(pos.x,pos.y,pos.z,1);

	if (IsAlive == 0) {
		IsTimer--;
	}

	if (IsTimer == 0) {
		IsAlive = 1;
		IsTimer = 100;
		speed = (float)(rand() % 360);
		scale = (float)(rand() % 10 + 10);

		radius = speed * PI / 180.0f;
		circleX = cosf(radius) * scale;
		circleZ = sinf(radius) * scale;
		pos.x = circleX + bosspos.x;
		pos.z = circleZ + bosspos.z;
	}
	//プレイヤー
	radius = speed * PI / 180.0f;
	circleX = cosf(radius) * scale;
	circleZ = sinf(radius) * scale;
	pos.x = circleX + bosspos.x;
	pos.y = circleZ + bosspos.z;
	pos = { 0.0f,0.0f,0.0f };
	object3d->SetPosition(pos);
	bossobj->SetPosition(bosspos);
	collidePlayer(player);
}

void Enemy::Draw() {
	Object3d::PreDraw();
	if (IsAlive == 1) {
		object3d->Draw();
	}

	bossobj->Draw();
}

bool Enemy::collidePlayer(Player* player) {
	XMFLOAT3 pos = player->GetPosition();

	if (collision->CheckSphere2Sphere(collider, player->collider) == true && IsAlive == 1) {
		IsAlive = 0;
		scale = 0.0f;
		this->pos = { 0,0,0 };
		return true;
	} else {
		return false;
	}
}

