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
	radius = speed * PI / 180.0f;
	circleX = cosf(radius) * scale;
	circleZ = sinf(radius) * scale;
	pos.x = circleX;
	pos.y = circleZ;
	IsAlive = 0;
	IsTimer = 100;
	object3d = Object3d::Create();
	object3d->SetModel(model);
	object3d->SetPosition(pos);
	object3d->SetScale({ 0.5,0.5,0.5 });
	collider.radius=rad;
}

void Enemy::Update(Player* player) {
	XMFLOAT3 pos = this->object3d->GetPosition();
	object3d->Update();
	collider.center = XMVectorSet(pos.x,pos.y,pos.z,1);

	if (IsAlive == 0) {
		IsTimer--;
		if (IsTimer == 0) {
			IsTimer = 100;
			IsAlive = 1;
			speed = (float)(rand() % 360);
			scale = 0;
			IsMove = rand() % 2;
		}
	} else {
		if (scale != 10.0f) {
			scale += 0.5f;
		} else {
			if (IsMove == 1) {
				speed += 0.5f;
			} else if (IsMove == 0) {
				speed -= 0.5f;
			}
		}
	}
	//プレイヤー
	radius = speed * PI / 180.0f;
	circleX = cosf(radius) * scale;
	circleZ = sinf(radius) * scale;
	pos.x = circleX;
	pos.y = circleZ;
	object3d->SetPosition(pos);
	collidePlayer(player);
}

void Enemy::Draw() {
	Object3d::PreDraw();
	if (IsAlive == 1) {
		object3d->Draw();
	}
}

bool Enemy::collidePlayer(Player* player) {
	XMFLOAT3 pos = player->GetPosition();

	if (collision->CheckSphere2Sphere(collider, player->collider) == true && IsAlive == 1) {
		IsAlive = 0;
		scale = 0.0f;
		return true;
	} else {
		return false;
	}
}

