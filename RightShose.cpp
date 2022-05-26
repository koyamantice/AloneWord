#include "RightShose.h"
#include"Collision.h"
#include<sstream>
#include<iomanip>
#include <Easing.h>
#include"ImageManager.h"
using namespace DirectX;

//こんすとらくた
RightShose::RightShose() {
	model = ModelManager::GetIns()->GetModel(ModelManager::RightShoes);
}

//初期化
void RightShose::Initialize(bool shadow) {
	assert(player);
	this->shadow = shadow;
	IsAlive = 0;
	pos = { 5.0f,0.0f,0.0f };
	rot = { 0,270,0 };
	Afterrot.y = rot.y;

	//敵
	Object3d*enemyobj_ = new Object3d();
	enemyobj_ = Object3d::Create();
	enemyobj_->SetModel(model);
	enemyobj_->SetPosition(pos);
	enemyobj_->SetRotation(rot);
	enemyobj_->SetScale({ 0.3f,0.3f,0.3f });
	enemyobj.reset(enemyobj_);
	//影(今回は使わない)
	texture = Texture::Create(ImageManager::shadow, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	texture->TextureCreate();
	//texture->SetColor({ 1,1,1,1 });
	texture->SetPosition(pos.x, -100, pos.z);
	texture->SetRotation({ 90,0,0 });
	texture->SetScale({ 0.3f,0.3f,0.3f });
	//ぴよぴよ

	for (std::size_t i = 0; i < Stuntexture.size(); i++) {
		Stuntexture[i] = Texture::Create(ImageManager::Stun, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
		Stuntexture[i]->TextureCreate();
		Stuntexture[i]->SetRotation({ 0,0,0 });
		Stuntexture[i]->SetScale({ 0.05f,0.05f,0.05f });
		Stunscale[i] = 1.0f;
		StunSpeed[0] = 0.0f;
		StunSpeed[1] = 90.0f;
		StunSpeed[2] = 180.0f;
		StunSpeed[3] = 270.0f;
		Stunradius[i] = StunSpeed[i] * PI / 180.0f;
		StunCircleX[i] = cosf(Stunradius[i]) * Stunscale[i];
		StunCircleZ[i] = sinf(Stunradius[i]) * Stunscale[i];
		StunPos[i].x = StunCircleX[i] + pos.x;
		StunPos[i].z = StunCircleZ[i] + pos.z;
		StunPos[i].y = pos.y + 3;
		Stuntexture[i]->SetPosition(StunPos[i]);
		Stuntexture[i]->Update();
	}
	InitCommon();
	//当たり判定の大きさ
	hitradius = 0.6f;
}

//開放
void RightShose::Finalize() {
	//delete enemyobj;
	delete texture;
	for (std::size_t i = 0; i < Stuntexture.size(); i++) {
		delete Stuntexture[i];
	}
}

//ボスの行動
void RightShose::Spec() {
	XMFLOAT3 AfterPos{};
	//ここで行動を決める
	if (AttackCount > 150 && pos.y <= 0.1f) {
		if (!active) {
			action = (rand() % 2);
			frame = 0;
			pat = 1;
			active = true;
		}
	}
	//攻撃をするまでのインターバル
	else {
		if (!active) {
			AttackCount++;
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
			Afterrot.x = 0.0f;
			if (!stun) {
				//3回突進する
				if (AttackC < 100) {
					MoveCount++;
				}
				//左足が戻ったら元の位置に戻る
				else {
					AfterPos = {
					5,
					0,
					0
					};
					Afterrot.y = 270;
					if (frame < 0.45f) {
						frame += 0.004f;
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
				//スタン時のぴよぴよ
				for (std::size_t i = 0; i < Stuntexture.size(); i++) {
					Stunradius[i] = StunSpeed[i] * PI / 180.0f;
					StunCircleX[i] = cosf(Stunradius[i]) * Stunscale[i];
					StunCircleZ[i] = sinf(Stunradius[i]) * Stunscale[i];
					StunPos[i].x = StunCircleX[i] + pos.x;
					StunPos[i].z = StunCircleZ[i] + pos.z;
					StunPos[i].y = pos.y + 2;
					Stuntexture[i]->SetPosition(StunPos[i]);
					Stuntexture[i]->Update();
				}

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
			enemyobj->SetPosition(pos);
		}
		//プレイヤーを挟むような攻撃
		if ((action % 2) == 1) {
			if (AttackC < 3) {
				Afterrot.x = 270.0f;
				switch (pat) {
				case 1:
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
					5,
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
void RightShose::App(int Timer) {

	XMFLOAT3 AfterPos{};
	XMFLOAT3 AfterRot{};

	if (Timer == 0) {
		pos = { 13.0f,0.0f,18.0f };
		rot = { 0.0f,315.0f,0.0f };
	}
	
	if (Timer == 150 || Timer == 280 || Timer == 300){
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
		pos = { 5.0f,0.0f,0.0f };
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

	for (std::size_t i = 0; i < Stuntexture.size(); i++) {
		Stunradius[i] = StunSpeed[i] * PI / 180.0f;
		StunCircleX[i] = cosf(Stunradius[i]) * Stunscale[i];
		StunCircleZ[i] = sinf(Stunradius[i]) * Stunscale[i];
		StunPos[i].x = StunCircleX[i] + pos.x;
		StunPos[i].z = StunCircleZ[i] + pos.z;
		StunPos[i].y = pos.y + 2;
		Stuntexture[i]->SetPosition(StunPos[i]);
		Stuntexture[i]->Update();
	}

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
void RightShose::End(int Timer) {
	//ボスを倒したあとの挙動(後で記述)
	XMFLOAT3 scale = {0.5f,0.5f,0.5f};
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
void RightShose::specialDraw() {
	if (stun) {
		for (std::size_t i = 0; i < Stuntexture.size(); i++) {
			Stuntexture[i]->Draw();
		}
	}
}

//左足と行動を合わせる
void RightShose::SetAct(LeftShose* leftshose) {
	int action = leftshose->GetAction();
	int AttackCount = leftshose->GetAttackCount();
	int pat = leftshose->GetPat();
	this->action = action;
	if (leftshose->GetHP() > 0) {
		this->AttackCount = AttackCount;
	}
	if (pat == 5 && pos.y == 0.0f) {
		AttackC = 101;
	}

	LeftAct = leftshose->GetActive();
}

//左足との当たり判定
bool RightShose::HitShose(LeftShose* leftshose) {
	XMFLOAT3 leftpos = leftshose->GetPosition();
	if (Collision::SphereCollision(pos.x, pos.y, pos.z, 1.5f, leftpos.x, leftpos.y, leftpos.z, 1.5f) && (action % 2) == 0
		&& (leftshose->GetHP() > 0)) {
		this->stun = true;
		leftshose->SetStun(true);
		if (pos.z >= leftpos.z) {
			hitpoint = HitUp;
			Deadbound.y = 0.3f;
			Deadbound.z = -0.2f;
		}
		else {
			hitpoint = HitDown;
			Deadbound.y = 0.3f;
			Deadbound.z = 0.2f;
		}
		return true;
	}
	else {
		return false;
	}
}