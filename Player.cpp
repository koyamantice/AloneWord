#include "Player.h"
#include "Input.h"
#include"Collision.h"
#include"Easing.h"
#include "DebugText.h"
#include<sstream>
#include<iomanip>
#include"Enemy.h"
using namespace DirectX;
float easeInSine(float x) {
	return x * x * x;
}
float easeOutBack(float x) {
	return x == 1 ? 1 : 1 - powf(2, -10 * x);
}

float easeInOut(float x) {
	return x < 0.5 ? 2 * x * x : 1 - powf(-2 * x + 2, 2) / 2;
}
Player::Player() {
	model = Model::CreateFromOBJ("chr_knight");
	Armmodel = Model::CreateFromOBJ("Particle");
	object3d = new Object3d();
	Armobj = new Object3d();
	Sprite::LoadTexture(3, L"Resources/2d/PlayerHP.png");

}

void Player::Initialize() {
	Sprite::LoadTexture(3, L"Resources/2d/PlayerHP.png");
	//îwåiÉXÉvÉâÉCÉgê∂ê¨
	SpritePlayerHP = Sprite::Create(3, { 0.0f,0.0f });
	SpritePlayerHP->SetPosition({ 0.0f,520.0f });
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
	XMFLOAT2 AfterPos;
	AfterPos = { (float)(HP * 30),20 };
	PlayerHP = {
	Ease(In,Quint,0.7f,SpritePlayerHP->GetSize().x,AfterPos.x),
	Ease(In,Quint,0.7f,SpritePlayerHP->GetSize().y,AfterPos.y),
	};
	SpritePlayerHP->SetSize(PlayerHP);


	XMFLOAT3 rot = this->object3d->GetRotation();
	object3d->Update();
	Armobj->Update();
	/*collider.center = XMVectorSet(pos.x, pos.y, pos.z, 1);*/
	//if ((input->LeftTiltStick(input->Right)) || (input->LeftTiltStick(input->Left)) ||
	//	(input->LeftTiltStick(input->Down)) || (input->LeftTiltStick(input->Up))) {
	//
	//}

	if (ArmMoveNumber <= 0) {
		if (input->LeftTiltStick(input->Right) && AttackFlag == false && AttackMoveNumber == 0) {
			pos.x += PlayerSpeed;
			rot.y = 90;
			ArmSpeed = 0;
		}

		if (input->LeftTiltStick(input->Left) && AttackFlag == false && AttackMoveNumber == 0) {
			pos.x -= PlayerSpeed;
			rot.y = 270;
			ArmSpeed = 180;
		}

		if (input->LeftTiltStick(input->Up) && AttackFlag == false && AttackMoveNumber == 0) {
			pos.z += PlayerSpeed;
			rot.y = 0;
			ArmSpeed = 90;
		}

		if (input->LeftTiltStick(input->Down) && AttackFlag == false && AttackMoveNumber == 0) {
			pos.z -= PlayerSpeed;
			rot.y = 180;
			ArmSpeed = 270;
		}


		if (input->PushButton(input->Button_RB) && ArmWeight <= 6.0f && AttackFlag == false && AttackMoveNumber == 0) {
			ArmMoveNumber = 1;
			initscale = Armscale;
			frame = 0;
		}

		//çUåÇ
		if (input->TriggerButton(input->Button_A) && AttackFlag == false && ArmWeight != 0.0f && AttackMoveNumber == 0) {
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
	SpritePlayerHP->Draw();

	Object3d::PreDraw();
	object3d->Draw();
	Armobj->Draw();
}

void Player::ResetWeight(Enemy *enemy) {
	if (ArmWeight==0.0f) {
		if (enemy->GetEnemyCatch()) {
			enemy->SetEnemyCatch(false);
			enemy->SetIsAlive(0);
		}
	}
}


