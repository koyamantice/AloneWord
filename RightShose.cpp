#include "RightShose.h"
#include"Collision.h"
#include<sstream>
#include<iomanip>
#include <Easing.h>
using namespace DirectX;

RightShose::RightShose() {
	model = ModelManager::GetIns()->GetModel(ModelManager::RightShose);
	enemyobj = new Object3d();
}

void RightShose::Initialize() {
	assert(player);
	IsAlive = 0;
	enemyobj = Object3d::Create();
	enemyobj->SetModel(model);
	pos = { 10.0f,0.0f,0.0f };
	enemyobj->SetPosition(pos);
	
	rot = { 0,90,0 };
	enemyobj->SetRotation(rot);
	enemyobj->SetScale({ 1.5f,1.5f,1.5f });
	texture = Texture::Create(1, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	texture->TextureCreate();
	//texture->SetColor({ 1,1,1,1 });
	texture->SetPosition(pos.x, -1, pos.z);
	texture->SetRotation({ 90,0,0 });
	texture->SetScale({ 0.3f,0.3f,0.3f });
}

void RightShose::Finalize() {
	//delete enemyobj;
	delete texture;
}

//ボスの行動
void RightShose::Spec() {
	XMFLOAT3 AfterPos{};
	if (AttackCount > 180 && pos.y <= 0.1f) {
		if (!active) {
			action = (rand() % 2);
			frame = 0;
			pat = 1;
			active = true;
		}
	}
	else {
		if (!active) {
			AttackCount++;
			if (State == Up) {
				AfterPos.y = 1.0f;
			}
			else {
				AfterPos.y = 0.0f;
			}
			if (frame <= 0.65) {
				frame += 0.005f;
			}
			else {
				frame = 0.0f;
				if (State == Up) {
					State = Down;
				}
				else {
					State = Up;
				}
			}
			pos.y = Ease(In, Cubic, frame, pos.y, AfterPos.y);
			enemyobj->SetPosition(pos);
		}
	}

	if (active) {
		if ((action % 2) == 0) {
			//3回突進する
			if (AttackC < 4) {
				MoveCount++;
			}
			//4回目は元の位置に戻る
			else {
				AfterPos = {
				10,
				0,
				0
				};
				if (frame < 1.0f) {
					frame += 0.01f;
				}
				else {
					frame = 0;
					AttackC = 0;
					AttackCount = 30;
					active = false;
				}

				pos = {
				Ease(In,Cubic,frame,pos.x,AfterPos.x),
				0,
				Ease(In,Cubic,frame,pos.z,AfterPos.z),
				};
			}
			//プレイヤーの位置をロックオンさせる
			if (MoveCount == 60) {
				if (!Attack) {
					hitpoint = HitNot;
					Check = player->GetPosition().x - pos.x;
					Check2 = player->GetPosition().z - pos.z;
					posR = (pow(Check, 2) + pow(Check2, 2));
					speedX = Check / posR * 8;
					speedZ = Check2 / posR * 8;
					Attack = true;
				}
			}

			if (Attack) {
				//プレイヤーにスピード加算
				pos.x += speedX;
				pos.z += speedZ;
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
					Deadbound.y -= 0.02;
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
					Deadbound.y -= 0.02;
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
					Deadbound.y -= 0.02;
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
					Deadbound.y -= 0.02;
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
		if ((action % 2) == 1) {
			if (AttackC < 4) {
				MoveCount++;
			}
			else {
				AfterPos = {
				0,
				0,
				0
				};
				if (frame < 1.0f) {
					frame += 0.01f;
				}
				else {
					frame = 0;
					AttackC = 0;
					AttackCount = 30;
					active = false;
				}

				pos = {
				Ease(In,Cubic,frame,pos.x,AfterPos.x),
				0,
				Ease(In,Cubic,frame,pos.z,AfterPos.z),
				};
			}
			if (MoveCount == 60) {
				if (!Attack) {
					hitpoint = HitNot;
					Check = player->GetPosition().x - pos.x;
					Check2 = player->GetPosition().z - pos.z;
					posR = (pow(Check, 2) + pow(Check2, 2));
					speedX = Check / posR * 8;
					speedZ = Check2 / posR * 8;
					Attack = true;
				}
			}

			if (Attack) {
				pos.x += speedX;
				pos.z += speedZ;
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

				if (hitpoint == HitRight) {
					Deadbound.y -= 0.02;
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
				}else if (hitpoint == HitLeft) {
					Deadbound.y -= 0.02;
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
				}else if (hitpoint == HitUp) {
					Deadbound.y -= 0.02;
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
				}else if (hitpoint == HitDown) {
					Deadbound.y -= 0.02;
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

	}
}
