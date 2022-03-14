#include "Player.h"
#include "Input.h"
#include"Collision.h"
#include"Easing.h"
#include "DebugText.h"
#include<sstream>
#include<iomanip>
using namespace DirectX;

Player::Player() {
	model = Model::CreateFromOBJ("chr_knight");
	object3d = new Object3d();
	shadowObj = new Object3d();
	Sprite::LoadTexture(3, L"Resources/2d/gage.png");
}

void Player::Initialize() {
	Sprite::LoadTexture(3, L"Resources/2d/gage.png");
	//背景スプライト生成
	Gauge = Sprite::Create(3, { 0.0f,0.0f });

	//プレイヤー
	radius = speed * PI / 180.0f;
	circleX = cosf(radius) * scale;
	circleZ = sinf(radius) * scale;
	pos.x = circleX;
	pos.y = circleZ;

	//プレイヤー(幻想)
	shadowRadius = shadowSpeed * PI / 180.0f;
	shadowCircleX = cosf(shadowRadius) * shadowScale;
	shadowCircleZ = sinf(shadowRadius) * shadowScale;
	shadowpos.x = shadowCircleX;
	shadowpos.y = shadowCircleZ;

	object3d = Object3d::Create();
	object3d->SetModel(model);
	object3d->SetPosition(pos);
	object3d->SetScale({ 1,1,1 });

	shadowObj = Object3d::Create();
	shadowObj->SetModel(model);
	shadowObj->SetPosition(shadowpos);
	shadowObj->SetScale({ 1,1,1 });

	collider.radius = rad;
}

void Player::Update() {
	Input* input = Input::GetInstance();
	XMFLOAT3 pos = this->object3d->GetPosition();
	object3d->Update();
	shadowObj->Update();
	/*collider.center = XMVectorSet(pos.x, pos.y, pos.z, 1);*/
	//if ((input->LeftTiltStick(input->Right)) || (input->LeftTiltStick(input->Left)) ||
	//	(input->LeftTiltStick(input->Down)) || (input->LeftTiltStick(input->Up))) {
	//
	//}

	if (input->LeftTiltStick(input->Right)) {

		pos.x += PlayerSpeed;
	}

	if (input->LeftTiltStick(input->Left)) {
		pos.x -= PlayerSpeed;
	}

	if (input->LeftTiltStick(input->Up)) {
		pos.z += PlayerSpeed;
	}

	if (input->LeftTiltStick(input->Down)) {
		pos.z -= PlayerSpeed;
	}
	//移動


	object3d->SetPosition(pos);
}

void Player::Draw() {
	Sprite::PreDraw();
	//背景用
	Gauge->Draw();

	Object3d::PreDraw();
	object3d->Draw();
	if (shadowFlag) {
		shadowObj->Draw();
	}
}

