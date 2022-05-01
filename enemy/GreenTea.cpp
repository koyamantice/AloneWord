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

	hotWater=new HotWater;
	hotWater->Init();
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
	hotWater->Set(pos);
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
				scale += 0.02f;
				if (radius>=360) {
					if (check) {
						pat++;
						check = false;
					} else {
						check = true;
					}
				} 
				radius = (int)radius % 360;
			} else if (pat == 2) {
				AfterPos.x = 25.0f;
				AfterPos.y = 3.0f;
				AfterPos.z = 20.0f;
			} else if (pat == 3) {
				AfterPos.x = -25.0f;
				AfterPos.y = 3.0f;
				AfterPos.z = -20.0f;
			} else if (pat == 4) {
				AfterPos.x = -25.0f;
				AfterPos.y = 3.0f;
				AfterPos.z = 20.0f;
			} else if (pat == 5) {
				AfterPos.x = 0.0f;
				AfterPos.y = 3.0f;
				AfterPos.z = 0.0f;
			} else {
				pat = 0;
				AttackCount = 30;
				Effect = true;
				active = false;
				frame = 0;
			}
			Afterrot = radius;
			degree = radius * PI / 180.0f;
			pos.x = cosf(degree) * scale;
			pos.z = sinf(degree) * scale;
	//		pos = {
	//Ease(In,Cubic,frame,pos.x,AfterPos.x),
	//Ease(In,Cubic,frame,pos.y,AfterPos.y),
	//Ease(In,Cubic,frame,pos.z,AfterPos.z),
	//		};
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
