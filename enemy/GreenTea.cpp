#include "GreenTea.h"
#include"Collision.h"
#include<sstream>
#include<iomanip>
#include <Easing.h>
#include"ImageManager.h"
using namespace DirectX;

GreenTea::GreenTea() {
	model = ModelManager::GetIns()->GetModel(ModelManager::Demo);
	enemyobj = new Object3d();
}

void GreenTea::Initialize() {
	assert(player);
	pos = { 0.0f,0.0f,0.0f };
	rot = { 0,0,0 };
	IsAlive = true;
	enemyobj = Object3d::Create();
	enemyobj->SetModel(model);
	enemyobj->SetPosition(pos);
	enemyobj->SetRotation(rot);
	enemyobj->SetScale({ 1.0f,1.0f,1.0f });

	texture = Texture::Create(ImageManager::shadow, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	texture->TextureCreate();
	//texture->SetColor({ 1,1,1,1 });
	texture->SetPosition(pos.x, -1, pos.z);
	texture->SetRotation({ 90,0,0 });
	texture->SetScale({ 0.3f,0.3f,0.3f });

	hotWater = new HotWater;
	hotWater->Init();
	degree = 0.0f;
	scale = 0.0f;
}

void GreenTea::Finalize() {
	hotWater->Final();
	delete texture;
	delete enemyobj;
	delete hotWater;
}

//ボスの行動
void GreenTea::Spec() {
	hotWater->Upda();
	XMFLOAT3 AfterPos{};
	if (AttackCount > 180 && pos.y <= 0.1f) {
		if (!active) {
			action = 0;// (rand() % 2);
			frame = 0;
			pat = 1;
			active = true;
		}
	} else {
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
			//if (frame < 1.0f) {
			//	frame += 0.002f;
			//} else {
			//	frame = 0;
			//}
			if (pat == 1) {
				radius++;
				if ((int)radius % 60 == 0) {
					hotWater->Set(pos);
				}
				scale += 0.02f;
				radius = (int)radius % 360;
				if (radius == 0) {
					if (check >= 2) {
						pat++;
						check = 0;
					} else {
						check++;
					}
				}
				Afterrot = radius;
				degree = radius * PI / 180.0f;
				pos.x = cosf(degree) * scale;
				pos.z = sinf(degree) * scale;
			}else if (pat == 2) {
				if (frame < 1.0f) {
					frame += 0.002f;
				} else {
					frame = 0;
					pat++;
				}
				pos = {
			Ease(In,Cubic,frame,pos.x,0),
			Ease(In,Cubic,frame,pos.y,0),
			Ease(In,Cubic,frame,pos.z,0)
				};
				enemyobj->SetPosition(pos);
			} else {
				pat = 0;
				AttackCount = 30;
				Effect = true;
				active = false;
				frame = 0;
			}
			enemyobj->SetPosition(pos);
			enemyobj->SetRotation({ 0,radius,0 });
		} else if ((action % 2) == 1) {
			if (AttackC < 3) {
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
					} else {
						frame = 0;
						pat++;
						break;
					}
				case 2:
					AfterPos = {
						player->GetPosition().x,
					3.0f,
						player->GetPosition().z
					};
					if (aiming < 180) {
						frame = 0.5f;
						aiming++;
						break;
					} else {
						frame = 0;
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
						frame += 0.08f;
						break;
					}
					if (frame >= 1.0f) {
						frame = 1.0f;
						if (coolT < 90) {
							coolT++;
							break;
						} else {
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
			} else {
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
					} else {
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
					} else {
						frame = 0;
						pat++;
						break;
					}
				case 3:
					AfterPos = {
					0,
					0,
					0
					};
					if (frame < 1.0f) {
						frame += 0.01f;
						break;
					} else {
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

void GreenTea::specialDraw() {
	hotWater->Draw();
}
