#include "LeftHand.h"
#include"Collision.h"
#include<sstream>
#include<iomanip>
#include <Easing.h>
using namespace DirectX;
#include"ImageManager.h"

//コンストラクタ
LeftHand::LeftHand() {
	model = ModelManager::GetIns()->GetModel(ModelManager::LeftHand_Open);
	enemyobj = new Object3d();
	hand_closemodel = ModelManager::GetIns()->GetModel(ModelManager::LeftHand_Close);
}

//初期化
void LeftHand::Initialize(bool shadow) {
	assert(player);
	this->shadow = shadow;
	IsAlive = 0;
	//敵
	enemyobj = Object3d::Create();
	enemyobj->SetModel(model);
	pos = { -10.0f,0.0f,0.0f };
	enemyobj->SetPosition(pos);
	rot = { 0,270,0 };
	Afterrot.y = rot.y;
	//影(このオブジェクトでは使わない)
	enemyobj->SetRotation(rot);
	//hand_closeobj->SetRotation(rot);
	enemyobj->SetScale({ 0.3f,0.3f,0.3f });
	texture = Texture::Create(ImageManager::shadow, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	texture->TextureCreate();
	//texture->SetColor({ 1,1,1,1 });
	texture->SetPosition(pos.x, -100, pos.z);
	texture->SetRotation({ 90,0,0 });
	texture->SetScale({ 0.3f,0.3f,0.3f });

	////スタン時のぴよぴよ

	//for (std::size_t i = 0; i < Stuntexture.size(); i++) {
	//	Stuntexture[i] = Texture::Create(ImageManager::Stun, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	//	Stuntexture[i]->TextureCreate();
	//	Stuntexture[i]->SetRotation({ 0,0,0 });
	//	Stuntexture[i]->SetScale({ 0.05f,0.05f,0.05f });
	//	Stunscale[i] = 1.0f;
	//	StunSpeed[0] = 0.0f;
	//	StunSpeed[1] = 90.0f;
	//	StunSpeed[2] = 180.0f;
	//	StunSpeed[3] = 270.0f;
	//	Stunradius[i] = StunSpeed[i] * PI / 180.0f;
	//	StunCircleX[i] = cosf(Stunradius[i]) * Stunscale[i];
	//	StunCircleZ[i] = sinf(Stunradius[i]) * Stunscale[i];
	//	StunPos[i].x = StunCircleX[i] + pos.x;
	//	StunPos[i].z = StunCircleZ[i] + pos.z;
	//	StunPos[i].y = pos.y + 3;
	//	Stuntexture[i]->SetPosition(StunPos[i]);
	//	Stuntexture[i]->Update();
	//}
}

//開放
void LeftHand::Finalize() {
	//delete enemyobj;
	delete texture;
}

//ボスの行動
void LeftHand::Spec() {
	XMFLOAT3 AfterPos{};
	if (stateNumber == Open) {
		enemyobj->SetModel(model);
	}
	else if (stateNumber == Close) {
		enemyobj->SetModel(hand_closemodel);
	}
	//ここで行動を決める
	if (AttackCount == 180) {
		if (!active) {
			action = (rand() % 2);
			AttackCount = 0;
			frame = 0;
			pat = 1;
			active = true;
		}
	}
	//攻撃をするまでのインターバル
	else {
		if (!active) {
			//AttackCount++;
			/*angle += 2.0f;
			angle2 = angle * (3.14f / 180.0f);
			pos.y = sin(angle2) * 0.5f + 0.5f;
			enemyobj->SetPosition(pos);*/
		}
	}

	//行動開始
	if (active) {
		//スタージを外周する
		if ((action % 2) == 0) {
			stateNumber = Open;
			if (!stun) {
				if (frame < 0.45f) {
					frame += 0.002f;
				}
				else {
					frame = 0;
					pat++;
				}
				if (pat == 1) {
					Afterrot.y = 225;
					AfterPos.x = 19.0f;
					AfterPos.z = -17.0f;
				}
				else if (pat == 2) {
					Afterrot.y = -270;
					AfterPos.x = 19.0f;
					AfterPos.z = 20.0f;

				}
				else if (pat == 3) {
					Afterrot.y = 0;
					AfterPos.x = -19.0f;
					AfterPos.z = 20.0f;
				}
				else if (pat == 4) {
					Afterrot.y = -90;
					AfterPos.x = -19.0f;
					AfterPos.z = -17.0f;
				}
				else if (pat == 5) {
					Afterrot.y = 135;
					AfterPos.x = -10.0f;
					AfterPos.z = 0.0f;
				}
				else {
					Afterrot.y = 270;
					pat = 0;
					AttackCount = 0;
					Effect = true;
					active = false;
					frame = 0;
				}
				pos = {
		Ease(In,Cubic,frame,pos.x,AfterPos.x),
		0,
		Ease(In,Cubic,frame,pos.z,AfterPos.z),
				};
				enemyobj->SetPosition(pos);
				//hand_closeobj->SetPosition(pos);
			}
			else {
				for (std::size_t i = 0; i < Stuntexture.size(); i++) {
					StunSpeed[i] += 2.0f;
				}
				if (stunTimer < 200) {
					stunTimer++;
				}
				else {
					stunTimer = 0;
					stun = false;
				}

				////スタン時のぴよぴよ
				//for (std::size_t i = 0; i < Stuntexture.size(); i++) {
				//	Stunradius[i] = StunSpeed[i] * PI / 180.0f;
				//	StunCircleX[i] = cosf(Stunradius[i]) * Stunscale[i];
				//	StunCircleZ[i] = sinf(Stunradius[i]) * Stunscale[i];
				//	StunPos[i].x = StunCircleX[i] + pos.x;
				//	StunPos[i].z = StunCircleZ[i] + pos.z;
				//	StunPos[i].y = pos.y + 2;
				//	Stuntexture[i]->SetPosition(StunPos[i]);
				//	Stuntexture[i]->Update();
				//}

			}
		}
		//プレイヤーを挟む処理
		else if ((action % 2) == 1) {
			stateNumber = Close;
			if (AttackC < 3) {
				Afterrot.x = 90.0f;
				switch (pat) {
				case 1:
					AfterPos = {
						player->GetPosition().x - 5,
						5,
						player->GetPosition().z
					};
					if (aiming < 180) {
						frame = 0.5f;
						aiming++;
						break;
					}
					else {
						frame = 0;
						targetpos.x = player->GetPosition().x - 0.2;
						aiming = 0;
						pat++;
						break;
					}
				case 2:
					AfterPos = {
						pos.x,
						0,
						pos.z,
					};
					if (frame < 1.0f) {
						frame += 0.02f;
						break;
					}
					else {
						frame = 0;
						pat++;
						break;
					}
				case 3:
					AfterPos = {
						targetpos.x,
						0,
						pos.z,
					};
					if (frame < 1.0f) {
						frame += 0.08f;
						break;
					}
					if (frame >= 1.0f) {
						frame = 1.0f;
						if (coolT < 50) {
							coolT++;
							break;
						}
						else {
							coolT = 0;
							frame = 0;
							pat = 1;
							AttackC++;
							break;
						}
					}
				default:
					AttackC = 0;
					pat = 1;
					break;
				}
			}
			else {
				switch (pat) {
				case 1:
					AfterPos = {
					pos.x,
					pos.y,
					pos.z
					};
					if (frame < 1.0f) {
						frame += 0.01f;
						break;
					}
					else {
						frame = 0;
						pat++;
						break;
					}
				case 2:
					Afterrot.x = 0.0f;
					AfterPos = {
					-10,
					0,
					0
					};
					if (frame < 1.0f) {
						frame += 0.01f;
						break;
					}
					else {
						frame = 0;
						pat = 0;
						AttackC = 0;
						AttackCount = 0;
						Effect = true;
						active = false;
						break;
					}
				default:
					break;
				}
			}
			pos = {
	Ease(In,Cubic,frame,pos.x,AfterPos.x),
	Ease(In,Cubic,frame,pos.y,AfterPos.y),
	Ease(In,Cubic,frame,pos.z,AfterPos.z)
			};
			enemyobj->SetPosition(pos);
			//hand_closeobj->SetPosition(pos);
		}
	}
	rot.y = Ease(In, Quint, 0.7f, rot.y, Afterrot.y);
	rot.x = Ease(In, Quint, 0.7f, rot.x, Afterrot.x);
	enemyobj->SetRotation(rot);
	//hand_closeobj->SetRotation(rot);
}

//導入
void LeftHand::App(int Timer) {

	XMFLOAT3 AfterPos{};
	XMFLOAT3 AfterRot{};
	if (Timer == 0) {
		pos = { -13.0f,0.0f,18.0f };
		rot = { 0.0f,225.0f,0.0f };
	}

	if (Timer == 150 || Timer == 280 || Timer == 300) {
		appearMove++;
		frame = 0.0f;
		frame2 = 0.0f;
	}

	//導入シーンにおいてフレーム数によって行動を決める
	switch (appearMove) {
	case 1:
		AfterPos = {
						0,
						0,
						-8,
		};
		if (frame < 1.0f) {
			frame += 0.005f;
			break;
		}
		else {
			frame = 0.0f;
			break;
		}

	case 2:
		pos = { -10.0f,0.0f,0.0f };
		rot = { 0,270,0 };
	case 3:
		stun = true;
		if (stun) {
			for (std::size_t i = 0; i < Stuntexture.size(); i++) {
				StunSpeed[i] += 2.0f;
			}
		}

		if (Timer == 500) {
			appearMove = 0;
			stun = false;
		}
	}

	//for (std::size_t i = 0; i < Stuntexture.size(); i++) {
	//	Stunradius[i] = StunSpeed[i] * PI / 180.0f;
	//	StunCircleX[i] = cosf(Stunradius[i]) * Stunscale[i];
	//	StunCircleZ[i] = sinf(Stunradius[i]) * Stunscale[i];
	//	StunPos[i].x = StunCircleX[i] + pos.x;
	//	StunPos[i].z = StunCircleZ[i] + pos.z;
	//	StunPos[i].y = pos.y + 2;
	//	Stuntexture[i]->SetPosition(StunPos[i]);
	//	Stuntexture[i]->Update();
	//}

	pos = {
	Ease(In,Cubic,frame,pos.x,AfterPos.x),
	Ease(In,Cubic,frame,pos.y,AfterPos.y),
	Ease(In,Cubic,frame,pos.z,AfterPos.z)
	};


	rot = {
	Ease(In,Cubic,frame2,rot.x,AfterRot.x),
	Ease(In,Cubic,frame2,rot.y,AfterRot.y),
	Ease(In,Cubic,frame2,rot.z,AfterRot.z)
	};
	enemyobj->SetPosition(pos);
	//hand_closeobj->SetPosition(pos);
	enemyobj->SetRotation(rot);
	//hand_closeobj->SetRotation(rot);
}

//撃破
void LeftHand::End(int Timer) {
	//ボスを倒したあとの挙動(後で記述)
	XMFLOAT3 scale = { 0.8f,0.8f,0.8f };
	float RotPower = 0.0f;
	XMFLOAT3 AfterScale{};
	//float endframe = 0.0f;
	//ボスを倒したあとの挙動(後で記述)
	if (Timer == 300) {
		pos = { -5.0f,0.0f,0.0f };
		rot = { 0,270,0 };
	}

	if (Timer == 450) {
		EndMove++;
		endframe = 0.0f;
	}

	switch (EndMove) {
	case 1:
		AfterScale = {
						0.2f,
						0.2f,
						0.2f,
		};

		if (endframe < 1.0f) {
			endframe += 0.005f;
			break;
		}
		else {
			endframe = 1.0f;
			RotPower = 0.0f;
			EndMove++;
			break;
		}

	case 2:
		if (rot.x <= 90) {
			rot.x += 2.0f;
		}

		//case 2:
		//	AfterPos = {
		//				pos.x,
		//				1,
		//				pos.z,
		//	};

		//	if (frame < 1.0f) {
		//		frame += 0.08f;
		//		break;
		//	}
		//	else {
		//		frame = 1.0f;
		//		break;
		//	}
	}

	RotPower = Ease(In, Cubic, endframe, RotPower, 20.0f);
	if (EndMove == 1) {
		rot.y += RotPower;
	}

	scale = {
	Ease(In,Cubic,endframe,scale.x,0.2f),
	Ease(In,Cubic,endframe,scale.y,0.2f),
	Ease(In,Cubic,endframe,scale.z,0.2f),
	};

	enemyobj->SetScale(scale);
	enemyobj->SetPosition(pos);
	//hand_closeobj->SetPosition(pos);
	enemyobj->SetRotation(rot);
	//hand_closeobj->SetRotation(rot);
}

//特別な描画(この場合ぴよぴよ)
void LeftHand::specialDraw() {
	/*if (stun) {
		for (std::size_t i = 0; i < Stuntexture.size(); i++) {
			Stuntexture[i]->Draw();
		}
	}*/
	/*if (stateNumber == Close) {
		hand_closeobj->Draw();
	}*/
}


void LeftHand::SetAct(Human* human) {
	int action = human->GetAction();
	int AttackCount = human->GetAttackCount();

	this->action = action;
	this->AttackCount = AttackCount;
}
