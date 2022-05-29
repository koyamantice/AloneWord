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
	hand_closemodel = ModelManager::GetIns()->GetModel(ModelManager::LeftHand_Close);
	Mottimodel = ModelManager::GetIns()->GetModel(ModelManager::Motti_Bullet);
	Mottiobj = new Object3d();
	Mottiobj = Object3d::Create();
	Mottiobj->SetModel(Mottimodel);
}

//初期化
void RightHand::Initialize(bool shadow) {
	assert(player);
	this->shadow = shadow;
	IsAlive = 0;
	pos = { 10.0f,1.0f,0.0f };
	rot = { 0,90,0 };
	//Afterrot.y = rot.y;

	//敵
	Object3d*enemyobj_ = new Object3d();
	enemyobj_ = Object3d::Create();
	enemyobj_->SetModel(model);
	enemyobj_->SetPosition(pos);
	enemyobj_->SetRotation(rot);
	enemyobj_->SetScale({ 1.2f,1.2f,1.2f });
	enemyobj.reset(enemyobj_);
	//影(今回は使わない)
	texture = Texture::Create(ImageManager::shadow, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	texture->TextureCreate();
	//texture->SetColor({ 1,1,1,1 });
	texture->SetPosition(pos.x, -100, pos.z);
	texture->SetRotation({ 90,0,0 });
	texture->SetScale({ 0.3f,0.3f,0.3f });
	//投げる用の餅
	Mottipos = { 0.0f,50.0f,0.0f };
	Mottiobj->SetPosition(Mottipos);
	Mottiobj->SetScale({ 1.0f,1.0f,1.0f });
	InitCommon();
	//当たり判定の大きさ
	hitradius = 0.6f;
	//防御力
	Defense = 1.5f;
}

//開放
void RightHand::Finalize() {
	//delete enemyobj;
	delete texture;
}

//ボスの行動
void RightHand::Spec() {
	shadow = false;
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
			hitradius = 0.6f;
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
		//衝撃波
		if (action == 0) {
			hitradius = 0.6f;
			if (AttackC < 5) {
				switch (pat) {
				case 1:
					AfterPos = {
					pos.x,
					15.0f,
					pos.z
					};
					if (frame < 0.45f) {
						frame += 0.002f;
						break;
					}
					else {
						stateNumber = Close;
						frame = 0;
						pat++;
						break;
					}
				case 2:
					Afterrot.z = 90;
					AfterPos.y = 1.0f;
					if (frame < 0.45f) {
						frame += 0.002f;
					}
					else {
						frame = 0.45f;
						count++;
						if (count == 50) {
							pat++;
							count = 0;
							frame = 0.0f;
						}
					}
					pos.y = Ease(In, Cubic, frame, pos.y, AfterPos.y);
				case 3:
					AfterPos = {
					pos.x,
					5.0f,
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
				case 4:
					AfterPos = {
						player->GetPosition().x,
					7.0f,
						player->GetPosition().z
					};
					if (aiming < 20) {
						frame = 0.5f;
						aiming++;
						break;
					}
					else {
						frame = 0;
						aiming = 0;
						pat++;
						break;
					}
				case 5:
					AfterPos = {
						pos.x,
						1.5,
						pos.z,
					};
					if (frame < 1.0f) {
						frame += 0.08f;
						if (rot.z > 45) {
							rot.z = 45;
							//vel = -vel;
						}
						if (rot.z < -45) {
							rot.z = -45;
							//vel = -vel;
						}
						break;

					}
					else {
						//Afterrot.z = 0;
						frame = 1.0f;
						if (coolT < 20) {
							coolT++;
							break;
						}
						else {
							damageCount = 0;
							coolT = 0;
							frame = 0;
							pat = 3;
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
					3.0f,
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
					AfterPos = {
					0,
					3.0f,
					0
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
				case 3:
					Afterrot = {
						0,
						0,
						0
					};
					AfterPos = {
					10,
					1,
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
						if (BossHP > 0) {
							Effect = true;
						}
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
			rot = {
				Ease(In,Cubic,frame,rot.x,Afterrot.x),
				Ease(In,Cubic,frame,rot.y,Afterrot.y),
				Ease(In,Cubic,frame,rot.z,Afterrot.z)
			};
			enemyobj->SetRotation(rot);

		}
		//プレイヤーを挟むような攻撃
		else if (action == 1) {
		hitradius = 1.5f;
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
						targetpos.x = player->GetPosition().x + 0.2f;
						aiming = 0;
						pat++;
						break;
					}
				case 3:
					AfterPos = {
						pos.x,
						2,
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
						2,
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
					1,
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
						if (BossHP > 0) {
							Effect = true;
						}
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

		//突進攻撃
		else if (action == 2) {
		hitradius = 2.4f;
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
				AfterPos.y = 2.6f;
				Afterrot.y = 0;
				Afterrot.x = 0;
				if (frame < 0.45f) {
					frame += 0.002f;
				}
				else {
					frame = 0;
					pat++;
				}
				//Afterrot.z = -90.0f;
				pos.y = Ease(In, Cubic, frame, pos.y, AfterPos.y);
			}
			else if (pat == 3) {
				Afterrot.x = -90.0f;
				if (!stun) {
					//3回突進する
					if (AttackC < 5) {
						MoveCount++;
					}
					//左足が戻ったら元の位置に戻る
					else {
						AfterPos = {
						10,
						1,
						0
						};
						Afterrot.y = 0;
						Afterrot.x = 0;
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
						Afterrot.y = (atan2(position.x, position.z) * (180.0f / XM_PI)) - 180;// *(XM_PI / 180.0f);
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
						if (pos.x >= 20) {
							hitpoint = HitRight;
							Deadbound.y = 0.5f;
							Deadbound.x = 0.2f;
							speedX = 0.0f;
							speedZ = 0.0f;
						}
						else if (pos.x <= -18) {
							hitpoint = HitLeft;
							Deadbound.y = 0.5f;
							Deadbound.x = 0.2f;
							speedX = 0.0f;
							speedZ = 0.0f;
						}
						else if (pos.z >=20) {
							hitpoint = HitUp;
							Deadbound.y = 0.5f;
							Deadbound.z = 0.2f;
							speedX = 0.0f;
							speedZ = 0.0f;
						}
						else if (pos.z <= -15) {
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
							if (pos.y > 2.6f) {
								pos.x -= Deadbound.x;
							}
							else {
								pos.y = 2.6f;
							}

							if (pos.y == 2.6f) {
								MoveCount = 0;
								Attack = false;
								hitpoint = HitNot;
								AttackC++;
							}
						}
						else if (hitpoint == HitLeft) {
							Deadbound.y -= 0.02f;
							pos.y += Deadbound.y;
							if (pos.y > 2.6f) {
								pos.x += Deadbound.x;
							}
							else {
								pos.y = 2.6f;
							}

							if (pos.y == 2.6f) {
								MoveCount = 0;
								Attack = false;
								hitpoint = HitNot;
								AttackC++;
							}
						}
						else if (hitpoint == HitUp) {
							Deadbound.y -= 0.02f;
							pos.y += Deadbound.y;
							if (pos.y > 2.6f) {
								pos.z -= Deadbound.z;
							}
							else {
								pos.y = 2.6f;
							}

							if (pos.y == 2.6f) {
								MoveCount = 0;
								Attack = false;
								hitpoint = HitNot;
								AttackC++;
							}
						}
						else if (hitpoint == HitDown) {
							Deadbound.y -= 0.02f;
							pos.y += Deadbound.y;
							if (pos.y > 2.6f) {
								pos.z += Deadbound.z;
							}
							else {
								pos.y = 2.6f;
							}

							if (pos.y == 2.6f) {
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
		}//投げる攻撃
		//投げる攻撃
		else if (action == 3) {
		hitradius = 0.6f;
		if (AttackC != 4) {
			if (pat == 1) {
				AfterPos.y = 15.0f;
				if (pos.y >= 14) {
					stateNumber = Open;
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
				AfterPos.y = 1.0f;
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
				AfterPos = {
				19,
				pos.y,
				19
				};
				if (frame < 1.0f) {
					frame += 0.01f;
				}
				else {
					frame = 0;
					pat++;
					Mottipos = { pos.x,15,pos.z };
				}

				pos = {
				Ease(In,Cubic,frame,pos.x,AfterPos.x),
				0,
				Ease(In,Cubic,frame,pos.z,AfterPos.z),
				};

				Mottiobj->SetPosition(Mottipos);

			}
			else if (pat == 4) {
				/*if (AttackC == 2) {
					frame = 0.0f;
					pat = 7;
				}*/
				AfterMottipos = {
				Mottipos.x,
				2,
				Mottipos.z,
				};

				Afterrot = {
					rot.x,
					90,
					90
				};

				if (frame < 1.0f) {
					frame += 0.01f;
				}
				else {
					frame = 0;
					pat++;
				}

				Mottipos = {
				Ease(In,Cubic,frame,Mottipos.x,AfterMottipos.x),
				Ease(In,Cubic,frame,Mottipos.y,AfterMottipos.y),
				Ease(In,Cubic,frame,Mottipos.z,AfterMottipos.z),
				};

				rot = {
				Ease(In,Cubic,frame,rot.x,Afterrot.x),
				Ease(In,Cubic,frame,rot.y,Afterrot.y),
				Ease(In,Cubic,frame,rot.z,Afterrot.z),
				};

				Mottiobj->SetPosition(Mottipos);
			}

			else if (pat == 5) {
				if (AttackC < 4) {
					MoveCount++;
				}
				if (MoveCount == 30) {
					XMFLOAT3 position{};
					position.x = (player->GetPosition().x - Mottipos.x);
					position.z = (player->GetPosition().z - Mottipos.z);
					Afterrot.y = (atan2(position.x, position.z) * (180.0f / XM_PI)) + 270;
				}

				//プレイヤーの位置をロックオンさせる
				if (MoveCount == 60) {
					double sb, sbx, sbz;
					if (!Attack) {
						hitpoint = HitNot;
						sbx = player->GetPosition().x - Mottipos.x;
						sbz = player->GetPosition().z - Mottipos.z;
						sb = sqrt(sbx * sbx + sbz * sbz);
						speedX = sbx / sb * 0.8;
						speedZ = sbz / sb * 0.8;
						pat++;
					}
				}
			}
			else if (pat == 6) {
				//プレイヤーにスピード加算
				Mottipos.x += (float)speedX;
				Mottipos.z += (float)speedZ;

				//敵の位置が壁まで行ったら戻る
				if (Mottipos.x >= x_max) {
					hitpoint = HitRight;
					Deadbound.y = 0.5f;
					Deadbound.x = 0.2f;
					speedX = 0.0f;
					speedZ = 0.0f;
				}
				else if (Mottipos.x <= x_min) {
					hitpoint = HitLeft;
					Deadbound.y = 0.5f;
					Deadbound.x = 0.2f;
					speedX = 0.0f;
					speedZ = 0.0f;
				}
				else if (Mottipos.z >= z_max) {
					hitpoint = HitUp;
					Deadbound.y = 0.5f;
					Deadbound.z = 0.2f;
					speedX = 0.0f;
					speedZ = 0.0f;
				}
				else if (Mottipos.z <= z_min) {
					hitpoint = HitDown;
					Deadbound.y = 0.5f;
					Deadbound.z = 0.2f;
					speedX = 0.0f;
					speedZ = 0.0f;
				}

				//跳ねるような感じで戻る(戻りきったら攻撃回数が加算される)
				if (hitpoint == HitRight) {
					Deadbound.y -= 0.02f;
					Mottipos.y += Deadbound.y;
					if (Mottipos.y > -10.0f) {
						Mottipos.x -= Deadbound.x;
					}
					else {
						Mottipos.y = -10.0f;
					}

					if (Mottipos.y == -10.0f) {
						MoveCount = 0;
						pat = 4;
						AttackC++;
						Mottipos = { pos.x,15,pos.z };
						hitpoint = HitNot;

						frame = 0.0f;
					}
				}
				else if (hitpoint == HitLeft) {
					Deadbound.y -= 0.02f;
					Mottipos.y += Deadbound.y;
					if (Mottipos.y > -10.0f) {
						Mottipos.x += Deadbound.x;
					}
					else {
						Mottipos.y = -10.0f;
					}

					if (Mottipos.y == -10.0f) {
						MoveCount = 0;
						pat = 4;
						AttackC++;
						Mottipos = { pos.x,15,pos.z };
						hitpoint = HitNot;
						frame = 0.0f;
					}
				}
				else if (hitpoint == HitUp) {
					Deadbound.y -= 0.02f;
					Mottipos.y += Deadbound.y;
					if (Mottipos.y > -10.0f) {
						Mottipos.z -= Deadbound.z;
					}
					else {
						Mottipos.y = -10.0f;
					}

					if (Mottipos.y == -10.0f) {
						MoveCount = 0;
						pat = 4;
						AttackC++;
						Mottipos = { pos.x,15,pos.z };
						hitpoint = HitNot;
						frame = 0.0f;
					}
				}
				else if (hitpoint == HitDown) {
					Deadbound.y -= 0.02f;
					Mottipos.y += Deadbound.y;
					if (Mottipos.y > -10.0f) {
						Mottipos.z += Deadbound.z;
					}
					else {
						Mottipos.y = -10.0f;
					}

					if (Mottipos.y == -10.0f) {
						MoveCount = 0;
						pat = 4;
						AttackC++;
						Mottipos = { pos.x,15,pos.z };
						hitpoint = HitNot;

						frame = 0.0f;
					}
				}
				Afterrot = {
					rot.x,
					rot.y,
					-90
				};

				if (frame < 1.0f) {
					frame += 0.1f;
				}
				else {
					frame = 1.0f;
				}

				rot = {
				Ease(In,Cubic,frame,rot.x,Afterrot.x),
				Ease(In,Cubic,frame,rot.y,Afterrot.y),
				Ease(In,Cubic,frame,rot.z,Afterrot.z),
				};

				Mottiobj->SetPosition(Mottipos);
			}
		}
		else {
			Afterrot.x = 0.0f;
			Afterrot.z = 0.0f;
			Afterrot.y = 90.0f;
			AfterPos = {
			10,
			1,
			0
			};
			if (frame < 1.0f) {
				frame += 0.01f;
			}
			else {
				frame = 0;
				pat = 0;
				AttackC = 0;
				AttackCount = 0;
				if (BossHP > 0) {
					Effect = true;
				}
				active = false;
			}

			pos = {
				Ease(In,Cubic,frame,pos.x,AfterPos.x),
				Ease(In,Cubic,frame,pos.y,AfterPos.y),
				Ease(In,Cubic,frame,pos.z,AfterPos.z),
			};

			rot = {
				Ease(In,Cubic,frame,rot.x,Afterrot.x),
				Ease(In,Cubic,frame,rot.y,Afterrot.y),
				Ease(In,Cubic,frame,rot.z,Afterrot.z),
			};
		}
		/*else if (pat == 7) {
			Afterrot.x = 0.0f;
			Afterrot.y = 90.0f;
			AfterPos = {
			-10,
			1,
			0
			};
			if (frame < 1.0f) {
				frame += 0.01f;
			}
			else {
				frame = 0;
				pat = 0;
				AttackC = 0;
				AttackCount = 0;
				Effect = true;
				active = false;
			}
		}*/

		enemyobj->SetPosition(pos);
		}
	}
	Mottiobj->Update();
	rot.y = Ease(In, Quint, 0.7f, rot.y, Afterrot.y);
	rot.x = Ease(In, Quint, 0.7f, rot.x, Afterrot.x);
	enemyobj->SetRotation(rot);
}
//導入
void RightHand::App(int Timer) {

	XMFLOAT3 AfterPos{};
	XMFLOAT3 AfterRot{};

	if (Timer == 0) {
		pos = { 5.0f,1.0f,5.0f };
		rot = { 0,90,0 };
	}

	if (Timer == 360 || Timer == 600 || Timer == 750) {
		appearMove++;
		frame = 0.0f;
		frame2 = 0.0f;
	}

	//導入シーンにおいてフレーム数によって行動を決める
	switch (appearMove) {
	case 1:
		AfterPos = {
						0.5,
						1,
						3,
		};
		AfterRot = {
			45,
			180,
			rot.z,
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
		AfterPos = {
					2,
					1,
					3,
		};

		AfterRot = {
			0,
			90,
			rot.z,
		};
		if (frame < 1.0f) {
			frame += 0.005f;
			break;
		}
		else {
			frame = 0.0f;
			break;
		}
	case 3:
		AfterPos = {
				10,
				1,
				0,
		};
		AfterRot = {
			rot.x,
			rot.y,
			rot.z
		};
		if (frame < 1.0f) {
			frame += 0.005f;
			break;
		}
		else {
			frame = 0.0f;
			break;
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
	Ease(In,Cubic,frame,rot.x,AfterRot.x),
	Ease(In,Cubic,frame,rot.y,AfterRot.y),
	Ease(In,Cubic,frame,rot.z,AfterRot.z)
	};
	enemyobj->SetPosition(pos);
	enemyobj->SetRotation(rot);
}

void RightHand::Roll(int Timer) {
	XMFLOAT3 AfterPos{};
	XMFLOAT3 AfterRot{};
	if (Timer == 1) {
		pos = { 50.0f,-14.0f,10.0f };
		rot.y = 90;
		frame = 0.0f;
	}

	if (Timer == 2900 || Timer == 3100 || Timer == 3300) {
		frame = 0.0f;
		rollMove++;
	}

	//導入シーンにおいてフレーム数によって行動を決める
	switch (rollMove) {
	case 1:
		AfterPos = {
						10,
						pos.y,
						pos.z,
		};
		AfterRot = {
			rot.x,
			rot.y,
			rot.z
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
		AfterPos = {
						0.5,
						-9.5,
						3,
		};
		AfterRot = {
			45,
			180,
			rot.z,
		};
		if (frame < 1.0f) {
			frame += 0.005f;
			break;
		}
		else {
			frame = 0.0f;
			break;
		}
	case 3:
		AfterPos = {
				50,
				pos.y,
				10,
		};

		AfterRot = {
			0,
			90,
			rot.z,
		};
		if (frame < 1.0f) {
			frame += 0.005f;
			break;
		}
		else {
			frame = 0.0f;
			break;
		}
	}
	pos = {
Ease(In,Cubic,frame,pos.x,AfterPos.x),
Ease(In,Cubic,frame,pos.y,AfterPos.y),
Ease(In,Cubic,frame,pos.z,AfterPos.z)
	};


	rot = {
	Ease(In,Cubic,frame,rot.x,AfterRot.x),
	Ease(In,Cubic,frame,rot.y,AfterRot.y),
	Ease(In,Cubic,frame,rot.z,AfterRot.z)
	};
	//pos = {
	//Ease(In,Cubic,frame,pos.x,AfterPos.x),
	//Ease(In,Cubic,frame,pos.y,AfterPos.y),
	//Ease(In,Cubic,frame,pos.z,AfterPos.z)
	//};
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
	if (Timer == 250) {
		pos = { 5.0f,0.0f,0.0f };
		rot = { 0,270,0 };
	}

	if (Timer == 350) {
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
		rot.y -= RotPower;
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
//特別な描画(今回の場合ぴよぴよ)
void RightHand::specialDraw() {
	if (BossHP > 0 && action == 3) {
		Mottiobj->Draw();
	}
}

//左足と行動を合わせる
void RightHand::SetAct(Human* human) {
	int action = human->GetAction();
	int AttackCount = human->GetAttackCount();
	this->action = action;
	this->AttackCount = AttackCount;
}

bool RightHand::collideMottiPlayer(Player* player) {
	XMFLOAT3 playerpos = player->GetPosition();
	float playerhp = player->GetHp();
	XMFLOAT3 distance = player->GetDistance();
	float weight = player->GetArmWeight();
	if (Collision::SphereCollision(Mottipos.x, Mottipos.y, Mottipos.z, 1.5f, playerpos.x, playerpos.y, playerpos.z, 1.5f) 
		&& FlashCount == 0 && Interval == 0 && BossHP > 0 && action == 3 && hitpoint == HitNot) {
		Audio::GetInstance()->PlayWave("Resources/Sound/Damage.wav", 0.4f);
		player->SetHp(playerhp - 1);
		player->SetCharge(0);
		player->SetRotCount(0);
		player->SetInterval(100);
		distance.x = playerpos.x - Mottipos.x;
		distance.z = playerpos.z - Mottipos.z;
		player->SetDistance(distance);
		player->SetJumpG(0.5f);
		player->SetDamageFlag(true);
		player->SetAttackFlag(false);
		if (weight != 0.0f) {
			weight = 0.0f;
			player->SetArmWeight(weight);
		}
		return true;
	}
	else {
		return false;
	}
}

