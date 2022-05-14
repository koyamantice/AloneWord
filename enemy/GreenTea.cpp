#include "GreenTea.h"
#include"Collision.h"
#include<sstream>
#include<iomanip>
#include <Easing.h>
#include"ImageManager.h"
using namespace DirectX;

GreenTea::GreenTea() {
	model = ModelManager::GetIns()->GetModel(ModelManager::Kyusu);
	enemyobj = new Object3d();
	for (int i = 0; i < 50; i++) {
		hotWater[i] = new HotWater;
		hotWater[i]->Init();
	}
}

void GreenTea::Initialize(bool shadow) {
	assert(player);
	this->shadow = shadow;
	pos = { 0.0f,0.0f,0.0f };
	rot = { 0,0,0 };
	IsAlive = true;
	enemyobj = Object3d::Create();
	enemyobj->SetModel(model);
	enemyobj->SetPosition(pos);
	enemyobj->SetRotation(rot);
	enemyobj->SetScale({ 0.5f,0.5f,0.5f });

	texture = Texture::Create(ImageManager::shadow, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	texture->TextureCreate();
	//texture->SetColor({ 1,1,1,1 });
	texture->SetPosition(pos.x, -1, pos.z);
	texture->SetRotation({ 90,0,0 });
	texture->SetScale({ 0.3f,0.3f,0.3f });
	degree = 0.0f;
	scale = 0.0f;
}

void GreenTea::Finalize() {
	for (int i = 0; i < 50; i++) {
		hotWater[i]->Final();
	}
	delete texture;
	delete enemyobj;
	//delete hotWater;
}

//ボスの行動
void GreenTea::Spec() {
	for (int i = 0; i < 50; i++) {
		hotWater[i]->Upda();
		hotWater[i]->SetPlayer(player);
	}
	if (AttackCount > 180 && pos.y <= 0.1f) {
		if (!active) {
			action = 2;// (rand() % 2);
			frame = 0;
			pat = 1;
			StartPos = pos;
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
		count++;
		if (count % 15 == 0) {
			for (int i = 0; i < 50; i++) {
				if (!hotWater[i]->GetIsAlive()) {
					hotWater[i]->Set(pos);
					break;
				}
			}
		}
		if ((action % 3) == 0) {
			if (pat == 1) {
				radius++;
				scale += 0.02f;
				radius = (int)radius % 360;
				if (radius == 0) {
					if (check >= 2) {
						pat++;
						StartPos = pos;
						frame = 0;
						check = 0;
					} else {
						check++;
					}
				}
				//Afterrot = radius;
				degree = radius * PI / 180.0f;
				pos.x = cosf(degree) * scale;
				pos.z = sinf(degree) * scale;
			} else if (pat == 2) {
				if (frame < 1.0f) {
					frame += 0.002f;
				} else {
					//frame = 0;
					pat++;
					radius = 0;
					scale = 0;
				}
				pos = {
			Ease(InOut,Cubic,frame,StartPos.x,0),
			Ease(InOut,Cubic,frame,StartPos.y,0),
			Ease(InOut,Cubic,frame,StartPos.z,0)
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
		} else if ((action % 3) == 1) {
			if (frame < 1.0f) {
				frame += 0.01f;
			} else {
				frame = 0;
				StartPos = AfterPos;
				pat++;
			}
			switch (pat) {
			case 1:
				AfterPos = {
					-20.0f,
					0.0f,
					0.0f
				};
				break;
			case 2:
				AfterPos = {
					-20.0f,
					0.0f,
					20.0f
				};
				break;
			case 3:
				AfterPos = {
				0.0f,
				0.0f,
				20.0f
				};
				break;
			case 4:
				AfterPos = {
				0.0f,
				0.0f,
				0.0f
				};
				break;
			case 5:
				AfterPos = {
				0.0f,
				0.0f,
				-20.0f
				};
				break;
			case 6:
				AfterPos = {
				20.0f,
				0.0f,
				-20.0f
				};
				break;
			case 7:
				AfterPos = {
				20.0f,
				0.0f,
				0.0f
				};
				break;
			case 8:
				AfterPos = {
				0.0f,
				0.0f,
				0.0f
				};
				break;
			default:
				pat = 0;
				AttackCount = 30;
				Effect = true;
				active = false;
				frame = 0;
				break;
			}
			pos = {
Ease(In,Cubic,frame,StartPos.x,AfterPos.x),
Ease(In,Cubic,frame,StartPos.y,AfterPos.y),
Ease(In,Cubic,frame,StartPos.z,AfterPos.z)
			};
		} else if ((action % 3) == 2) {
			if (frame < 1.0f) {
				frame += 0.01f;
			} else {
				frame = 0;
				StartPos = AfterPos;
				pat++;
			}
			switch (pat) {
			case 1:
				AfterPos = {
					20.0f,
					0.0f,
					0.0f
				};
				break;
			case 2:
				AfterPos = {
					20.0f,
					0.0f,
					-20.0f
				};
				break;
			case 3:
				AfterPos = {
				0.0f,
				0.0f,
				-20.0f
				};
				break;
			case 4:
				AfterPos = {
				0.0f,
				0.0f,
				0.0f
				};
				break;
			case 5:
				AfterPos = {
				0.0f,
				0.0f,
				20.0f
				};
				break;
			case 6:
				AfterPos = {
				-20.0f,
				0.0f,
				20.0f
				};
				break;
			case 7:
				AfterPos = {
				-20.0f,
				0.0f,
				0.0f
				};
				break;
			case 8:
				AfterPos = {
				0.0f,
				0.0f,
				0.0f
				};
				break;
			default:
				pat = 0;
				AttackCount = 30;
				Effect = true;
				active = false;
				frame = 0;
				break;
			}
			pos = {
Ease(In,Cubic,frame,StartPos.x,AfterPos.x),
Ease(In,Cubic,frame,StartPos.y,AfterPos.y),
Ease(In,Cubic,frame,StartPos.z,AfterPos.z)
			};
		}

		enemyobj->SetPosition(pos);
	}
}

void GreenTea::App(int Timer) {
	//後に記入
}

void GreenTea::specialDraw() {
	for (int i = 0; i < 50; i++) {
		hotWater[i]->Draw();
	}
}
