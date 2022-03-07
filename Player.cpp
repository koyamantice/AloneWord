#include "Player.h"
#include "Input.h"
#include"Collision.h"
#include"Easing.h"
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
	collider.center = XMVectorSet(pos.x, pos.y, pos.z, 1);
	if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN)) {
		if (!undoPos) {
			if (input->PushKey(DIK_UP)) {
				speed += 2.0f;
			}
			if (input->PushKey(DIK_DOWN)) {
				speed -= 2.0f;
			}
			//プレイヤー
			radius = speed * PI / 180.0f;
			circleX = cosf(radius) * scale;
			circleZ = sinf(radius) * scale;
			pos.x = circleX;
			pos.y = circleZ;
			object3d->SetPosition(pos);
		}
	}
	if (input->TriggerKey(DIK_SPACE)) {
		if (!shadowFlag) {
			shadowSpeed = speed;
			shadowFlag = true;
			if (coolCount <= 90 && CheckCool) {
				coolCount = 0;
				needCool = true;
			}
		} else {
			if (!undoPos) {
				frame = 0;
				undoPos = true;
			}
		}
	}
	if (shadowFlag) {
		if (needCool) {
			posX *= 0.989f;
		} else {
			posX *= 0.999f;
		}
		Gauge->SetSize({ posX,64});
		if (posX <= 2) {
			if (!undoPos) {
				frame = 0;
				undoPos = true;
			}
			posX = 1;
		}
	} else {
		if (posX < 256) {
			posX *= 1.01f;
			Gauge->SetSize({ posX,64 });
		} else {
			posX = 256;
			Gauge->SetSize({ posX,64 });

		}
		if (posX<1) {
			posX = 1;
		}
	}
	//Gauge関連
	if (CheckCool&&!needCool) {
		Gauge->SetColor({255,0,0,255});
		coolCount++;
		if (coolCount>90) {
			CheckCool = false;
			needCool = false;
			coolCount = 0;
		}
	} else {
		Gauge->SetColor({ 255,255,255,255 });
		coolCount = 0;
	}
	if (needCool) {
		Gauge->SetColor({ 0,0,255,255 });
	} else if (posX == 256) {
		Gauge->SetColor({ 0,255,0,255 });

	}
	if (!shadowFlag) {
		shadowSpeed = speed;
	}
	//プレイヤー(幻想)
	shadowRadius = shadowSpeed * PI / 180.0f;
	shadowCircleX = cosf(shadowRadius) * shadowScale;
	shadowCircleZ = sinf(shadowRadius) * shadowScale;
	shadowpos.x = shadowCircleX;
	shadowpos.y = shadowCircleZ;
	shadowObj->SetPosition(shadowpos);
	if (undoPos) {
		if (frame <= 1.0f) {
			frame += 0.04f;
		} else {
			frame = 1.0f;
			speed = shadowSpeed;
			shadowFlag = false;
			undoPos = false;
			needCool = false;
			if (!CheckCool) {
				CheckCool = true;
			}
		}
		pos.x = Ease(In, Exp, frame, pos.x, shadowpos.x);
		pos.y = Ease(In, Exp, frame, pos.y, shadowpos.y);
		object3d->SetPosition(pos);
	}
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


