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
	return x < 0.5 ? 8 * x * x * x * x : 1 - pow(-2 * x + 2, 4) / 2;
}
float easeBack(float x) 
{
const float c1 = 1.70158f;
const float c3 = c1 + 1;

return c3 * x * x * x - c1 * x * x;
}
Player::Player() {
	model = Model::CreateFromOBJ("Motti");
	Armmodel = Model::CreateFromOBJ("Arm");
	object3d = new Object3d();
	Armobj = new Object3d();

}

void Player::Initialize() {
	object3d = Object3d::Create();
	object3d->SetModel(model);
	object3d->SetPosition(pos);
	object3d->SetScale({ 0.7f,0.7f,0.7f });

	Armobj = Object3d::Create();
	Armobj->SetModel(Armmodel);
	Armradius = ArmSpeed * PI / 180.0f;
	ArmCircleX = cosf(Armradius) * Armscale;
	ArmCircleZ = sinf(Armradius) * Armscale;
	Armpos.x = ArmCircleX + pos.x;
	Armpos.z = ArmCircleZ + pos.z;
	Armobj->SetPosition(Armpos);
	Armobj->SetScale({ 1.4f,1.4f,1.4f });
	//effecttexture = Texture::Create(4, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	//effecttexture->TextureCreate();
	////effecttexture->SetRotation({ 90,0,0 });
	//effecttexture->SetScale({ 0.2f,0.2f,0.2f });
	collider.radius = rad;
}

void Player::Finalize() {
	delete object3d;
	delete Armobj;
}

void Player::Update() {
	Input* input = Input::GetInstance();
	XMFLOAT3 rot = this->object3d->GetRotation();
	//if (!AttackFlag) {
		rot.y = Ease(In, Quad, 0.9f, rot.y, AfterRot);
	//}
	object3d->Update();
	Armobj->Update();
	StickrotX = input->GetPosX();
	StickrotY = input->GetPosY();
	//effecttexture->Update();
	
	if (ArmMoveNumber == 0 && AttackMoveNumber == 0 && AttackFlag == false) {
		if (input->LeftTiltStick(input->Right)) {
			if (pos.x <= XMax) {
				pos.x += PlayerSpeed;
				AfterRot = 90;
			}
		}

		if (input->LeftTiltStick(input->Left)) {
			if (pos.x >= -XMax) {
				pos.x -= PlayerSpeed;
				AfterRot = 270;
			}
		}

		if (input->LeftTiltStick(input->Up)) {
			if (pos.z <= ZMax) {
				pos.z += PlayerSpeed;
				AfterRot = 0;
			}
		}

		if (input->LeftTiltStick(input->Down)) {
			if (pos.z >= -ZMax) {
				pos.z -= PlayerSpeed;
				AfterRot = 180;
			}
		}
		
		//攻撃右回り
		if (input->PushButton(input->Button_RB) && ArmWeight != 0.0f) {
			AttackFlag = true;
			AttackMoveNumber = 1;
			initscale = Armscale;
			initspeed = ArmSpeed;
			initrotation = rot.y;
			initArmRotation = ArmRot.y;
			frame2 = 0;
			frame3 = 0;
			if (ArmMoveNumber != 0) {
				ArmMoveNumber = 0;
			}
		}

		//左回り
		if (input->PushButton(input->Button_LB) && ArmWeight != 0.0f) {
			AttackFlag = true;
			AttackMoveNumber = 3;
			initscale = Armscale;
			initspeed = ArmSpeed;
			initrotation = rot.y;
			initArmRotation = ArmRot.y;
			frame2 = 0;
			frame3 = 0;
			if (ArmMoveNumber != 0) {
				ArmMoveNumber = 0;
			}
		}

		//腕のばす
		if (input->TriggerButton(input->Button_A) && ArmWeight <= 6.0f) {
			ArmMoveNumber = 1;
			initscale = Armscale;
			frame = 0;
			if (AttackMoveNumber != 0 || AttackFlag == true) {
				AttackMoveNumber = 0;
				AttackFlag = false;
			}
		}

		//プレイヤーの向き設定
		if (StickrotY <= -650) {
			if (StickrotX <= 650 && StickrotX >= -650) {		//上
				AfterRot = 270;
				ArmSpeed = 90;
				ArmRot.y = 270;
			} else if (StickrotX > 650) {	//右上
				AfterRot = 225;
				ArmSpeed = 45;
				ArmRot.y = 315;
			} else if (StickrotX < -650) {	//左上
				AfterRot = 315;
				ArmSpeed = 135;
				ArmRot.y = 225;
			}
		} else if (StickrotY >= 650) {
			if (StickrotX <= 650 && StickrotX >= -650) {	//下
				AfterRot = 90;
				ArmSpeed = 270;
				ArmRot.y = 90;
			} else if (StickrotX > 650) {	//右下
				AfterRot = 45;
				ArmSpeed = 315;
				ArmRot.y = 45;
			} else if (StickrotX < -650) {	//左下
				AfterRot = 135;
				ArmSpeed = 225;
				ArmRot.y = 135;
			}
		} else {
			if (StickrotX <= -650) {	//左
				AfterRot = 180;
				ArmSpeed = 180;
				ArmRot.y = 180;
			}

			if (StickrotX >= 650) {	//右
				AfterRot = 0;
				ArmSpeed = 0;
				ArmRot.y = 0;
			}
		}
	}

	//腕を伸ばす
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
			//Armscale += ArmWeight;
		}
	}

	//攻撃
	if (AttackFlag == true) {
		if (AttackMoveNumber == 1 || AttackMoveNumber == 2) {
			ArmSpeed = initspeed - 360.0f * easeBack(frame2 / frameMax2);
			AfterRot = initrotation + 360.0f * easeBack(frame2 / frameMax2);
			ArmRot.y = initArmRotation + 360.0f * easeBack(frame2 / frameMax2);
		} else {
			ArmSpeed = initspeed + 360.0f * easeBack(frame2 / frameMax2);
			AfterRot = initrotation - 360.0f * easeBack(frame2 / frameMax2);
			ArmRot.y = initArmRotation - 360.0f * easeBack(frame2 / frameMax2);
		}
		
		SpeedSub =(int)( initspeed - ArmSpeed);
		//どれくらい大振りしたかみたいなやつ
		if (SpeedSub <= 90) {
			power = 0.25;
		} else if (SpeedSub > 90 && SpeedSub <= 180) {
			power = 0.5;
		} else if (SpeedSub > 180 && SpeedSub <= 270) {
			power = 0.75;
		} else {
			power = 1.0;
		}
		if (frame2 <= frameMax2) {
			frame2 = frame2 + 1;
		} else {
			AttackFlag = false;
			frameMax2 = 80.0f;
		}
	} 

	//攻撃時に腕を伸ばしている
	if (AttackMoveNumber == 1 || AttackMoveNumber == 3) {
		if (ArmWeight>0) {
			Armscale = initscale + 3.0f * easeInOut(frame3 / frameMax3);
			if (frame3 <= frameMax3) {
				frame3 = frame3 + 1;
			} else {
				if (AttackMoveNumber == 1) {
					AttackMoveNumber = 2;
				} else if (AttackMoveNumber == 3) {
					AttackMoveNumber = 4;
				}
				initscale = Armscale;
				scaleVel = 3.0f;
				frame3 = 0;
				frameMax3 = 20.0f;
			}
		} else {
			AttackMoveNumber = 2;
			scaleVel = Armscale - initscale;
			initscale = Armscale;
			frame3 = 0;
			frameMax3 = 20.0f;
		}
	}

	else if (AttackMoveNumber == 2 || AttackMoveNumber == 4) {
		Armscale = initscale - scaleVel * easeInOut(frame3 / frameMax3);
		if (frame3 <= frameMax3) {
			frame3 = frame3 + 1;
		} else {
			AttackMoveNumber = 0;
			frameMax3 = 80.0f;
		}
	}

	//FlashCount == 4までプレイヤーがダメージを食らったあとの判定
	if (Interval != 0 && FlashCount <= 5) {
		Interval--;
	}

	if (Interval == 1) {
		FlashCount++;
		Interval = 20;
	}

	if (FlashCount == 4) {
		FlashCount = 0;
		Interval = 0;
	}

	Armradius = ArmSpeed * PI / 180.0f;
	ArmCircleX = cosf(Armradius) * Armscale;
	ArmCircleZ = sinf(Armradius) * Armscale;
	Armpos.x = ArmCircleX + pos.x;
	Armpos.z = ArmCircleZ + pos.z;
	Armobj->SetPosition(Armpos);
	//移動
	object3d->SetPosition(pos);
	object3d->SetRotation(rot);
	Armobj->SetRotation(ArmRot);
}

//描画
void Player::Draw() {
	/*ImGui::Begin("test");
	if (ImGui::TreeNode("Debug")) {
		if (ImGui::TreeNode("Player")) {
			ImGui::SliderFloat("power", &power, 50, -50);
			ImGui::Text("Sub %d", SpeedSub);

			ImGui::Unindent();
			ImGui::TreePop();
		}
		ImGui::TreePop();
	}
	ImGui::End();*/

	Object3d::PreDraw();
	if (FlashCount % 2 == 0) {
		object3d->Draw();
		Armobj->Draw();
	}
	
	
}

//敵が腕から離れる
void Player::ResetWeight(Enemy *enemy) {
	XMFLOAT3 boundpower = enemy->GetBoundPower();
	XMFLOAT3 enepos = enemy->GetPosition();
	if (ArmWeight==0.0f) {
		if (enemy->GetEnemyCatch()) {
			enemy->SetBound(true);
			enemy->SetEnemyCatch(false);
		}
		enemy->Setboundpower(boundpower);
	}
}

//ダメージ食らったときにプレイヤーが飛ばされる
void Player::Rebound(Enemy* enemy) {
	XMFLOAT3 enepos = enemy->GetPosition();
	
	distance.x = pos.x - enepos.x;
	distance.z = pos.z - enepos.z;

	if (DamageFlag == true) {
		
		if (distance.x <= 0) {
			rebound.x = -2.0f;
		} else {
			rebound.x = 2.0f;
		}

		if (distance.z <= 0) {
			rebound.z = -2.0f;
		} else {
			rebound.z = 2.0f;
		}
		DamageFlag = false;
	}

	if (rebound.x != 0.0) {
		if (rebound.x > 0) {
			rebound.x *= 0.4f;
		} else {
			rebound.x *= 0.4f;
		}
	}

	if (rebound.z != 0.0) {
		if (rebound.z > 0) {
			rebound.z *= 0.4f;
		} else {
			rebound.z *= 0.4f;
		}
	}

	if (pos.x <= 25.0f && pos.x >= -25.0f) {
		pos.x += rebound.x;
	}
	if (pos.z <= 20.0f && pos.z >= -20.0f) {
		pos.z += rebound.z;
	}
}
