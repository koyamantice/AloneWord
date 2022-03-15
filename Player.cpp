#include "Player.h"
#include "Input.h"
#include"Collision.h"
#include"Easing.h"
#include "DebugText.h"
#include<sstream>
#include<iomanip>
using namespace DirectX;
float easeInSine(float x) {
	return x * x * x;
}
float easeOutBack(float x) {
	return x == 1 ? 1 : 1 - powf(2, -10 * x);
}

float easeInOut(float x) {
	return x < 0.5 ? 2 * x * x : 1 - pow(-2 * x + 2, 2) / 2;
}
Player::Player() {
	model = Model::CreateFromOBJ("chr_knight");
	Armmodel = Model::CreateFromOBJ("Particle");
	object3d = new Object3d();
	Armobj = new Object3d();
	Sprite::LoadTexture(3, L"Resources/2d/gage.png");

}

void Player::Initialize() {
	Sprite::LoadTexture(3, L"Resources/2d/gage.png");
	//îwåiÉXÉvÉâÉCÉgê∂ê¨
	Gauge = Sprite::Create(3, { 0.0f,0.0f });

	object3d = Object3d::Create();
	object3d->SetModel(model);
	object3d->SetPosition(pos);
	object3d->SetScale({ 1,1,1 });

	Armobj = Object3d::Create();
	Armobj->SetModel(Armmodel);
	Armradius = ArmSpeed * PI / 180.0f;
	ArmCircleX = cosf(Armradius) * Armscale;
	ArmCircleZ = sinf(Armradius) * Armscale;
	Armpos.x = ArmCircleX + pos.x;
	Armpos.z = ArmCircleZ + pos.z;
	Armobj->SetPosition(Armpos);

	Armobj->SetScale({ 1,1,1 });

	collider.radius = rad;
}

void Player::Update() {
	Input* input = Input::GetInstance();
	
	XMFLOAT3 rot = this->object3d->GetRotation();
	object3d->Update();
	Armobj->Update();
	/*collider.center = XMVectorSet(pos.x, pos.y, pos.z, 1);*/
	//if ((input->LeftTiltStick(input->Right)) || (input->LeftTiltStick(input->Left)) ||
	//	(input->LeftTiltStick(input->Down)) || (input->LeftTiltStick(input->Up))) {
	//
	//}

	if (AttackFlag == false && ArmMoveNumber == 0 && AttackMoveNumber == 0) {
		if (input->LeftTiltStick(input->Right)) {
			pos.x += PlayerSpeed;
			rot.y = 90;
			ArmSpeed = 0;
		}

		if (input->LeftTiltStick(input->Left)) {
			pos.x -= PlayerSpeed;
			rot.y = 270;
			ArmSpeed = 180;
		}

		if (input->LeftTiltStick(input->Up)) {
			pos.z += PlayerSpeed;
			rot.y = 0;
			ArmSpeed = 90;
		}

		if (input->LeftTiltStick(input->Down)) {
			pos.z -= PlayerSpeed;
			rot.y = 180;
			ArmSpeed = 270;
		}


		if (input->PushButton(input->Button_RB)) {
			ArmMoveNumber = 1;
			initscale = Armscale;
			frame = 0;
		}

		//çUåÇ
		if (input->TriggerButton(input->Button_A)) {
			AttackFlag = true;
			AttackMoveNumber = 1;
			initscale = Armscale;
			initspeed = ArmSpeed;
			initrotation = rot.y;
			frame2 = 0;
			frame3 = 0;
		}
	}

	//òrÇêLÇŒÇ∑
	if (ArmMoveNumber == 1) {
		Armscale = initscale + 3.0f * easeOutBack(frame / frameMax);
		if (frame != frameMax) {
			frame = frame + 1;
		} else {
			ArmMoveNumber = 2;
			frame = 0;
			initscale = Armscale;
		}
	}

	else if (ArmMoveNumber == 2) {
		Armscale = initscale - 3.0f * easeOutBack(frame / frameMax);
		if (frame != frameMax) {
			frame = frame + 1;
		} else {
			ArmMoveNumber = 0;
			initscale = Armscale;
		}
	}

	//çUåÇ
	if (AttackFlag == true) {
		ArmSpeed = initspeed + 360.0f * easeInOut(frame2 / frameMax2);
		rot.y = initrotation - 360.0f * easeInOut(frame2 / frameMax2);
		if (frame2 <= frameMax2) {
			frame2 = frame2 + 1;
		} else {
			AttackFlag = false;
			frameMax2 = 80.0f;
		}
	}

	if (AttackMoveNumber == 1) {
		Armscale = initscale + 3.0f * easeInOut(frame3 / frameMax3);
		if (frame3 <= frameMax3) {
			frame3 = frame3 + 1;
		} else {
			AttackMoveNumber = 2;
			initscale = Armscale;
			frame3 = 0;
			frameMax3 = 20.0f;
		}
	}

	else if (AttackMoveNumber == 2) {
		Armscale = initscale - 3.0f * easeInOut(frame3 / frameMax3);
		if (frame3 <= frameMax3) {
			frame3 = frame3 + 1;
		} else {
			AttackMoveNumber = 0;
			Armscale = 1.0f;
			frameMax3 = 80.0f;
		}
	}

	Armradius = ArmSpeed * PI / 180.0f;
	ArmCircleX = cosf(Armradius) * Armscale;
	ArmCircleZ = sinf(Armradius) * Armscale;
	Armpos.x = ArmCircleX + pos.x;
	Armpos.z = ArmCircleZ + pos.z;
	Armobj->SetPosition(Armpos);
	//à⁄ìÆ
	object3d->SetPosition(pos);
	object3d->SetRotation(rot);
}

void Player::Draw() {
	Sprite::PreDraw();
	//îwåióp
	Gauge->Draw();

	Object3d::PreDraw();
	object3d->Draw();
	Armobj->Draw();
}


