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
	model = Model::CreateFromOBJ("Motti");
	Armmodel = Model::CreateFromOBJ("Particle");
	object3d = new Object3d();
	Armobj = new Object3d();
	Sprite::LoadTexture(3, L"Resources/2d/PlayerHP.png");

}

void Player::Initialize() {
	//îwåiÉXÉvÉâÉCÉgê∂ê¨
	SpritePlayerHP = Sprite::Create(3, { 0.0f,0.0f });
	SpritePlayerHP->SetPosition({ 0.0f,520.0f });
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
	Armobj->SetScale({ 1,1,1 });

	collider.radius = rad;
}

void Player::Update() {
	Input* input = Input::GetInstance();
	XMFLOAT2 AfterPos;
	AfterPos = { (float)(HP * 30),20 };
	PlayerHP = {
	Ease(In,Quint,0.7f,(float)SpritePlayerHP->GetSize().x,(float)AfterPos.x),
	Ease(In,Quint,0.7f,(float)SpritePlayerHP->GetSize().y,(float)AfterPos.y),
	};
	SpritePlayerHP->SetSize(PlayerHP);
	XMFLOAT3 rot = this->object3d->GetRotation();
	//if (!AttackFlag) {
		rot.y = Ease(In, Quad, 0.9f, rot.y, AfterRot);
	//}
	object3d->Update();
	Armobj->Update();
	StickrotX = input->GetPosX();
	StickrotY = input->GetPosY();
	/*collider.center = XMVectorSet(pos.x, pos.y, pos.z, 1);*/
	//if ((input->LeftTiltStick(input->Right)) || (input->LeftTiltStick(input->Left)) ||
	//	(input->LeftTiltStick(input->Down)) || (input->LeftTiltStick(input->Up))) {
	//
	//}

	if (ArmMoveNumber <= 0) {
		if (input->LeftTiltStick(input->Right) && AttackFlag == false && AttackMoveNumber == 0) {
			if (pos.x <= 25.0f) {
				pos.x += PlayerSpeed;
				AfterRot = 90;
			}
		}

		if (input->LeftTiltStick(input->Left) && AttackFlag == false && AttackMoveNumber == 0) {
			if (pos.x >= -25.0f) {
				pos.x -= PlayerSpeed;
				AfterRot = 270;
			}
		}

		if (input->LeftTiltStick(input->Up) && AttackFlag == false && AttackMoveNumber == 0) {
			if (pos.z <= 20.0f) {
				pos.z += PlayerSpeed;
				AfterRot = 0;
				/*	if (ArmSpeed >= 90 && ArmSpeed <= 315 && ArmWeight != 0.0f) {
						ArmSpeed += 3.0f;
					}*/
			}
		}

		if (input->LeftTiltStick(input->Down) && AttackFlag == false && AttackMoveNumber == 0) {
			if (pos.z >= -20) {
				pos.z -= PlayerSpeed;
				AfterRot = 180;
			}
		}
		//òrÇêLÇŒÇ∑
		if (input->PushButton(input->Button_RB) && ArmWeight <= 6.0f && AttackFlag == false && AttackMoveNumber == 0) {
			ArmMoveNumber = 1;
			if (ArmWeight != 0.0f) {
				ArmSpeed = TargetSpeed;
			}
			Armscale = 0.0f;
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

		if (AttackFlag == false && AttackMoveNumber == 0 && ArmMoveNumber == 0) {
			//ÉvÉåÉCÉÑÅ[ÇÃå¸Ç´ê›íË
			if (StickrotY <= -650) {
				if (StickrotX <= 650 && StickrotX >= -650) {
					AfterRot = 180;
					if (ArmWeight == 0.0f) {
						ArmSpeed = 90;
					} else {
						ArmSpeed = 315;
						TargetSpeed = 90;
					}
				} else if (StickrotX > 650) {
					AfterRot = 225;
					if (ArmWeight == 0.0f) {
						ArmSpeed = 45;
					} else {
						ArmSpeed = 275;
						TargetSpeed = 45;
					}
				} else if (StickrotX < -650) {
					AfterRot = 135;
					if (ArmWeight == 0.0f) {
						ArmSpeed = 135;
					} else {
						ArmSpeed = 0;
						TargetSpeed = 135;
					}
				}
			} else if (StickrotY >= 650) {
				if (StickrotX <= 650 && StickrotX >= -650) {
					AfterRot = 0;
					if (ArmWeight == 0.0f) {
						ArmSpeed = 270;
					} else {
						ArmSpeed = 135;
						TargetSpeed = 270;
					}
				} else if (StickrotX > 650) {
					AfterRot = 315;
					if (ArmWeight == 0.0f) {
						ArmSpeed = 315;
					} else {
						ArmSpeed = 180;
						TargetSpeed = 315;
					}
				} else if (StickrotX < -650) {
					AfterRot = 45;
					if (ArmWeight == 0.0f) {
						ArmSpeed = 225;
					} else {
						ArmSpeed = 90;
						TargetSpeed = 225;
					}
				}
			} else {
				if (StickrotX <= -650) {
					AfterRot = 90;
					if (ArmWeight == 0.0f) {
						ArmSpeed = 180;
					} else {
						ArmSpeed = 45;
						TargetSpeed = 180;
					}
				}

				if (StickrotX >= 650) {
					AfterRot = 270;
					if (ArmWeight == 0.0f) {
						ArmSpeed = 0;
					} else {
						ArmSpeed = 225;
						TargetSpeed = 0;
					}
				}
			}
		}
	}

	//òrÇêLÇŒÇ∑
	if (ArmMoveNumber == 1) {
		Armscale = initscale + 5.0f * easeOutBack(frame / frameMax);
		if (frame != frameMax) {
			frame = frame + 1;
		} else {
			ArmMoveNumber = 2;
			frame = 0;
			initscale = Armscale;
		}
	}
	else if (ArmMoveNumber == 2) {
		Armscale = initscale - (5.0f - (ArmWeight - 0.5f)) * easeOutBack(frame / frameMax);
		if (frame != frameMax) {
			frame = frame + 1;
		} else {
			ArmMoveNumber = 0;
			initscale = Armscale;
			//Armscale += ArmWeight;
		}
	}

	//çUåÇ
	if (AttackFlag == true) {
		ArmSpeed = initspeed + 360.0f * easeInOut(frame2 / frameMax2);
		AfterRot = initrotation - 360.0f * easeInOut(frame2 / frameMax2);
		if (frame2 <= frameMax2) {
			frame2 = frame2 + 1;
		} else {
			AttackFlag = false;
			frameMax2 = 80.0f;
		}
	} 

	if (AttackMoveNumber == 1) {
		if (ArmWeight>0) {
			Armscale = initscale + 5.0f * easeInOut(frame3 / frameMax3);
			if (frame3 <= frameMax3) {
				frame3 = frame3 + 1;
			} else {
				AttackMoveNumber = 2;
				initscale = Armscale;
				scaleVel = 5.0f;
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

	else if (AttackMoveNumber == 2) {
		Armscale = initscale - scaleVel * easeInOut(frame3 / frameMax3);
		if (frame3 <= frameMax3) {
			frame3 = frame3 + 1;
		} else {
			AttackMoveNumber = 0;
			//Armscale = 1.0f;
			frameMax3 = 80.0f;
		/*	if (ArmWeight != 0.0f && Armscale != ArmWeight - 0.5) {
				Armscale = ArmWeight - 0.5f;
			}*/
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
	//	ImGui::Begin("test");
	//if (ImGui::TreeNode("Debug"))     {
	//	if (ImGui::TreeNode("Player"))         {
	//		ImGui::SliderFloat("Position.x", &pos.x, 50, -50);
	//		ImGui::SliderFloat("Position.z", &pos.z, 50, -50);
	//		ImGui::SliderFloat("ArmSpeed", &ArmSpeed, 50, -50);
	//		ImGui::SliderFloat("Armscale", &Armscale, 50, -50);
	//		ImGui::SliderFloat("scaleVel", &scaleVel, 50, -50);
	//		ImGui::SliderFloat("Armweight", &ArmWeight, 50, -50);
	//		ImGui::Unindent();
	//		ImGui::TreePop();
	//	}
	//	ImGui::TreePop();
	//}
	//ImGui::End();
	Sprite::PreDraw();
	//îwåióp
	SpritePlayerHP->Draw();

	Object3d::PreDraw();
	object3d->Draw();
	if (Armscale >= 0.2f) {
		Armobj->Draw();
	}
}

void Player::ResetWeight(Enemy *enemy) {
	if (ArmWeight==0.0f) {
		if (enemy->GetEnemyCatch()) {
			enemy->SetEnemyCatch(false);
			enemy->SetIsAlive(0);
		}
	}
}


