#include "RightShose.h"
#include"Collision.h"
#include<sstream>
#include<iomanip>
#include <Easing.h>
#include"ImageManager.h"
using namespace DirectX;

RightShose::RightShose() {
	model = ModelManager::GetIns()->GetModel(ModelManager::RightShoes);
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
	enemyobj->SetScale({ 0.7f,0.7f,0.7f });
	texture = Texture::Create(ImageManager::shadow, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
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
			angle += 2.0f;
			angle2 = angle * (3.14f / 180.0f);
			pos.y = sin(angle2) * 0.5f + 0.5f;
			enemyobj->SetPosition(pos);
		}
	}

	if (active) {
		if ((action % 2) == 0) {
			if (!stun) {
				//3回突進する
				if (AttackC < 100) {
					MoveCount++;
				}
				//左足が戻ったら元の位置に戻る
				else {
					AfterPos = {
					10,
					0,
					0
					};
					if (frame < 0.45f) {
						frame += 0.004f;
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
				if (MoveCount == 100) {
					double sb, sbx, sbz;
					if (!Attack) {
						hitpoint = HitNot;
						sbx = player->GetPosition().x - pos.x;
						sbz = player->GetPosition().z - pos.z;
						//rot.y = (atan2f(position.x, position.z) * (180.0f / XM_PI)) - 90;
						sb = sqrt(sbx * sbx + sbz * sbz);
						speedX = sbx / sb * 0.5;
						speedZ = sbz / sb * 0.5;
						Attack = true;
					}
				}
			}
			else {
				if (stunTimer < 200) {
					stunTimer++;
				}
				else {
					stunTimer = 0;
					stun = false;
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

			if (AttackC < 3) {
				switch (pat) {
				case 1:
					AfterPos = {
						player->GetPosition().x + 5,
						pos.y,
						player->GetPosition().z
					};
					if (aiming < 180) {
						frame = 0.5f;
						aiming++;
						break;
					}
					else {
						frame = 0;
						targetpos.x = player->GetPosition().x;
						aiming = 0;
						pat++;
						break;
					}
				case 2:
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
						if (coolT < 90) {
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
						AttackCount = 30;
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
}

void RightShose::App() {

}
void RightShose::specialDraw() {
}

void RightShose::SetAct(LeftShose* leftshose) {
	int action = leftshose->GetAction();
	int AttackCount = leftshose->GetAttackCount();
	int pat = leftshose->GetPat();
	this->action = action;
	this->AttackCount = AttackCount;
	if (pat == 5 && pos.y == 0.0f) {
		AttackC = 101;
	}

	LeftAct = leftshose->GetActive();
}

bool RightShose::HitShose(LeftShose* leftshose) {
	XMFLOAT3 leftpos = leftshose->GetPosition();
	if (Collision::SphereCollision(pos.x, pos.y, pos.z, 1.5f, leftpos.x, leftpos.y, leftpos.z, 1.5f) && (action % 2) == 0) {
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