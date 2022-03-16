#include "BossEnemy.h"
#include "Input.h"
#include"Collision.h"
#include<sstream>
#include<iomanip>
using namespace DirectX;

BossEnemy::BossEnemy() {
	model = Model::CreateFromOBJ("chr_sword");
	object3d = new Object3d();
}

void BossEnemy::Initialize() {

	//プレイヤー
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
	object3d->Update();
	collider.center = XMVectorSet(pos.x, pos.y, pos.z, 1);

	//if (IsAlive == 0) {
	//	IsTimer--;
	//}

	//if (IsTimer == 0) {
	//	IsAlive = 1;
	//	IsTimer = 100;
	//	speed = (float)(rand() % 360);
	//	scale = (float)(rand() % 10 + 10);

	//	radius = speed * PI / 180.0f;
	//	circleX = cosf(radius) * scale;
	//	circleZ = sinf(radius) * scale;
	//	pos.x = circleX + bosspos.x;
	//	pos.z = circleZ + bosspos.z;
	//}
	////プレイヤー
	//radius = speed * PI / 180.0f;
	//circleX = cosf(radius) * scale;
	//circleZ = sinf(radius) * scale;
	//pos.x = circleX + bosspos.x;
	//pos.y = circleZ + bosspos.z;
	pos = { 0.0f,0.0f,0.0f };
	object3d->SetPosition(pos);
	//bossobj->SetPosition(bosspos);
	//collidePlayer(player);
}

void BossEnemy::Draw() {
	Object3d::PreDraw();
	if (IsAlive == 1) {
		
	}
	object3d->Draw();
	//bossobj->Draw();
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

