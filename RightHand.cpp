#include "RightHand.h"
#include"Collision.h"
#include<sstream>
#include<iomanip>
#include <Easing.h>
#include"ImageManager.h"
using namespace DirectX;

//こんすとらくた
RightHand::RightHand() {
	model = ModelManager::GetIns()->GetModel(ModelManager::RightHand_Open);
	hand_closemodel = ModelManager::GetIns()->GetModel(ModelManager::RightHand_Close);
	enemyobj = new Object3d();
}

//初期化
void RightHand::Initialize(bool shadow) {
	assert(player);
	this->shadow = shadow;
	IsAlive = 0;
	//敵
	enemyobj = Object3d::Create();
	enemyobj->SetModel(model);
	pos = { 10.0f,0.0f,0.0f };
	enemyobj->SetPosition(pos);

	rot = { 0,270,0 };
	Afterrot.y = rot.y;
	enemyobj->SetRotation(rot);
	enemyobj->SetScale({ 0.8f,0.8f,0.8f });
	//影(今回は使わない)
	texture = Texture::Create(ImageManager::shadow, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	texture->TextureCreate();
	//texture->SetColor({ 1,1,1,1 });
	texture->SetPosition(pos.x, -100, pos.z);
	texture->SetRotation({ 90,0,0 });
	texture->SetScale({ 0.3f,0.3f,0.3f });
	////ぴよぴよ

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
void RightHand::Finalize() {
	//delete enemyobj;
	delete texture;
}

//ボスの行動
void RightHand::Spec() {
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
			frame = 0;
			pat = 1;
			active = true;
			AttackCount = 0;
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
		//突進攻撃
		if ((action % 2) == 0) {
			if (pat == 1) {
				AfterPos.y = 15.0f;
				if (pos.y >= 14) {
					stateNumber = Close;
				}
				if (frame < 0.45f) {
					frame += 0.002f;
				}
				else {
					frame = 0;
					pat++;
				}
				pos.y = Ease(In, Cubic, frame, pos.y, AfterPos.y);
			}
			else if (pat == 2) {
				AfterPos.y = 0.0f;
				if (frame < 0.45f) {
					frame += 0.002f;
				}
				else {
					frame = 0;
					pat++;
				}
				pos.y = Ease(In, Cubic, frame, pos.y, AfterPos.y);
			}
			else if (pat == 3) {
				Afterrot.x = 0.0f;
				if (!stun) {
					//3回突進する
					if (AttackC < 3) {
						MoveCount++;
					}
					//左足が戻ったら元の位置に戻る
					else {
						AfterPos = {
						10,
						0,
						0
						};
						Afterrot.y = 270;
						if (frame < 1.0f) {
							frame += 0.01f;
						}
						else {
							frame = 0;
							AttackC = 0;
							AttackCount = 0;
							active = false;
						}

						pos = {
						Ease(In,Cubic,frame,pos.x,AfterPos.x),
						0,
						Ease(In,Cubic,frame,pos.z,AfterPos.z),
						};
					}
					//プレイヤーーの位置に向かって回転する
					if (MoveCount == 80) {
						XMFLOAT3 position{};
						position.x = (player->GetPosition().x - pos.x);
						position.z = (player->GetPosition().z - pos.z);
						Afterrot.y = (atan2(position.x, position.z) * (180.0f / XM_PI)) - 270;// *(XM_PI / 180.0f);
					}
					//プレイヤーの位置をロックオンさせる
					if (MoveCount == 100) {
						double sb, sbx, sbz;
						if (!Attack) {
							hitpoint = HitNot;
							sbx = player->GetPosition().x - pos.x;
							sbz = player->GetPosition().z - pos.z;

							sb = sqrt(sbx * sbx + sbz * sbz);
							speedX = sbx / sb * 0.5;
							speedZ = sbz / sb * 0.5;
							Attack = true;
						}
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

					if (Attack) {
						//プレイヤーにスピード加算
						pos.x += (float)speedX;
						pos.z += (float)speedZ;

						//敵の位置が壁まで行ったら戻る
						if (pos.x >= x_max) {
							hitpoint = HitRight;
							Deadbound.y = 0.5f;
							Deadbound.x = 0.2f;
							speedX = 0.0f;
							speedZ = 0.0f;
						}
						else if (pos.x <= x_min) {
							hitpoint = HitLeft;
							Deadbound.y = 0.5f;
							Deadbound.x = 0.2f;
							speedX = 0.0f;
							speedZ = 0.0f;
						}
						else if (pos.z >= z_max) {
							hitpoint = HitUp;
							Deadbound.y = 0.5f;
							Deadbound.z = 0.2f;
							speedX = 0.0f;
							speedZ = 0.0f;
						}
						else if (pos.z <= z_min) {
							hitpoint = HitDown;
							Deadbound.y = 0.5f;
							Deadbound.z = 0.2f;
							speedX = 0.0f;
							speedZ = 0.0f;
						}

						//跳ねるような感じで戻る(戻りきったら攻撃回数が加算される)
						if (hitpoint == HitRight) {
							Deadbound.y -= 0.02f;
							pos.y += Deadbound.y;
							if (pos.y > 0.0f) {
								pos.x -= Deadbound.x;
							}
							else {
								pos.y = 0.0f;
							}

							if (pos.y == 0.0f) {
								MoveCount = 0;
								Attack = false;
								hitpoint = HitNot;
								AttackC++;
							}
						}
						else if (hitpoint == HitLeft) {
							Deadbound.y -= 0.02f;
							pos.y += Deadbound.y;
							if (pos.y > 0.0f) {
								pos.x += Deadbound.x;
							}
							else {
								pos.y = 0.0f;
							}

							if (pos.y == 0.0f) {
								MoveCount = 0;
								Attack = false;
								hitpoint = HitNot;
								AttackC++;
							}
						}
						else if (hitpoint == HitUp) {
							Deadbound.y -= 0.02f;
							pos.y += Deadbound.y;
							if (pos.y > 0.0f) {
								pos.z -= Deadbound.z;
							}
							else {
								pos.y = 0.0f;
							}

							if (pos.y == 0.0f) {
								MoveCount = 0;
								Attack = false;
								hitpoint = HitNot;
								AttackC++;
							}
						}
						else if (hitpoint == HitDown) {
							Deadbound.y -= 0.02f;
							pos.y += Deadbound.y;
							if (pos.y > 0.0f) {
								pos.z += Deadbound.z;
							}
							else {
								pos.y = 0.0f;
							}

							if (pos.y == 0.0f) {
								MoveCount = 0;
								Attack = false;
								hitpoint = HitNot;
								AttackC++;
							}
						}
					}
				}
			}
			enemyobj->SetPosition(pos);
		}
		//プレイヤーを挟むような攻撃
		if ((action % 2) == 1) {
			if (AttackC < 3) {
				switch (pat) {
				case 1:
					AfterPos = {
					pos.x,
					15.0f,
					pos.z
					};
					if (frame < 1.0f) {
						frame += 0.01f;
						break;
					}
					else {
						Afterrot.x = 90.0f;
						Afterrot.y = 180.0f;
						stateNumber = Open;
						frame = 0;
						pat++;
						break;
					}
				case 2:
					AfterPos = {
						player->GetPosition().x + 5,
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
						targetpos.x = player->GetPosition().x + 0.2;
						aiming = 0;
						pat++;
						break;
					}
				case 3:
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
				case 4:
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
							pat = 2;
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
					Afterrot.y = 90.0f;
					AfterPos = {
					10,
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
		}
	}

	rot.y = Ease(In, Quint, 0.7f, rot.y, Afterrot.y);
	rot.x = Ease(In, Quint, 0.7f, rot.x, Afterrot.x);
	enemyobj->SetRotation(rot);
}
//導入
void RightHand::App(int Timer) {

	XMFLOAT3 AfterPos{};
	XMFLOAT3 AfterRot{};

	if (Timer == 0) {
		pos = { 13.0f,0.0f,18.0f };
		rot = { 0.0f,315.0f,0.0f };
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
		pos = { 10.0f,0.0f,0.0f };
		rot = { 0,270,0 };
	case 3:
		//ぴよぴよが浮かぶ
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

	/*for (std::size_t i = 0; i < Stuntexture.size(); i++) {
		Stunradius[i] = StunSpeed[i] * PI / 180.0f;
		StunCircleX[i] = cosf(Stunradius[i]) * Stunscale[i];
		StunCircleZ[i] = sinf(Stunradius[i]) * Stunscale[i];
		StunPos[i].x = StunCircleX[i] + pos.x;
		StunPos[i].z = StunCircleZ[i] + pos.z;
		StunPos[i].y = pos.y + 2;
		Stuntexture[i]->SetPosition(StunPos[i]);
		Stuntexture[i]->Update();
	}*/

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
	enemyobj->SetRotation(rot);
}

//撃破
void RightHand::End(int Timer) {
	//ボスを倒したあとの挙動(後で記述)
	XMFLOAT3 scale = { 0.8f,0.8f,0.8f };
	float RotPower = 0.0f;
	XMFLOAT3 AfterScale{};
	//float endframe = 0.0f;
	//ボスを倒したあとの挙動(後で記述)
	if (Timer == 300) {
		pos = { 5.0f,0.0f,0.0f };
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
		if (rot.x >= -90) {
			rot.x -= 2.0f;
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
		rot.y -= RotPower;
	}

	scale = {
	Ease(In,Cubic,endframe,scale.x,0.2f),
	Ease(In,Cubic,endframe,scale.y,0.2f),
	Ease(In,Cubic,endframe,scale.z,0.2f),
	};

	enemyobj->SetScale(scale);
	enemyobj->SetPosition(pos);
	enemyobj->SetRotation(rot);
}
//特別な描画(今回の場合ぴよぴよ)
void RightHand::specialDraw() {
	/*if (stun) {
		for (std::size_t i = 0; i < Stuntexture.size(); i++) {
			Stuntexture[i]->Draw();
		}
	}*/
}

//左足と行動を合わせる
void RightHand::SetAct(Human* human) {
	int action = human->GetAction();
	int AttackCount = human->GetAttackCount();
	this->action = action;
	this->AttackCount = AttackCount;
}
