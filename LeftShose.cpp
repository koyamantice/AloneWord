#include "LeftShose.h"
#include"Collision.h"
#include<sstream>
#include<iomanip>
#include <Easing.h>
using namespace DirectX;
#include"ImageManager.h"

LeftShose::LeftShose() {
	model = ModelManager::GetIns()->GetModel(ModelManager::LeftShoes);
	enemyobj = new Object3d();
}

void LeftShose::Initialize(bool shadow) {
	assert(player);
	this->shadow = shadow;
	IsAlive = 0;
	enemyobj = Object3d::Create();
	enemyobj->SetModel(model);
	pos = { -10.0f,0.0f,0.0f };
	enemyobj->SetPosition(pos);
	rot = { 0,270,0 };
	Afterrot.y = rot.y;
	enemyobj->SetRotation(rot);
	enemyobj->SetScale({ 0.3f,0.3f,0.3f });
	texture = Texture::Create(ImageManager::shadow, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	texture->TextureCreate();
	//texture->SetColor({ 1,1,1,1 });
	texture->SetPosition(pos.x, -100, pos.z);
	texture->SetRotation({ 90,0,0 });
	texture->SetScale({ 0.3f,0.3f,0.3f });
	shadow = false;
}

void LeftShose::Finalize() {
	//delete enemyobj;
	delete texture;
}

//ボスの行動
void LeftShose::Spec() {
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
					AttackCount = 30;
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
		}
		else if ((action % 2) == 1) {

			if (AttackC < 3) {
				Afterrot.x = 90.0f;
				switch (pat) {
				case 1:
					AfterPos = {
						player->GetPosition().x - 5,
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
	rot.y = Ease(In, Quint, 0.7f, rot.y, Afterrot.y);
	rot.x = Ease(In, Quint, 0.7f, rot.x, Afterrot.x);
	enemyobj->SetRotation(rot);
}

void LeftShose::App(int Timer) {

	XMFLOAT3 AfterPos{};
	XMFLOAT3 AfterRot{};
	if (Timer == 1) {
		pos = { -13.0f,0.0f,18.0f };
		rot = { 0.0f,225.0f,0.0f };
	}
	
	if (Timer == 150 || Timer == 280) {
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

void LeftShose::End(int Timer) {
	//ボスを倒したあとの挙動(後で記述)
}

void LeftShose::specialDraw() {
}
