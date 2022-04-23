#include "LeftShose.h"
#include"Collision.h"
#include<sstream>
#include<iomanip>
#include <Easing.h>
using namespace DirectX;

LeftShose::LeftShose() {
	model = ModelManager::GetIns()->GetModel(ModelManager::LeftShose);
	enemyobj = new Object3d();
}

void LeftShose::Initialize() {
	assert(player);
	IsAlive = 0;
	enemyobj = Object3d::Create();
	enemyobj->SetModel(model);
	pos = { -10.0f,0.0f,0.0f };
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

void LeftShose::Finalize() {
	//delete enemyobj;
	delete texture;
}

//�{�X�̍s��
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
		}
	}

	if (active) {
		if ((action % 2) == 0) {
			if (frame < 0.45f) {
				frame += 0.002f;
			}
			else {
				frame = 0;
				pat++;
			}
			if (pat == 1) {
				Afterrot = 45;
				AfterPos.x = 25.0f;
				AfterPos.z = -20.0f;
			}
			else if (pat == 2) {
				Afterrot = -90;
				AfterPos.x = 25.0f;
				AfterPos.z = 20.0f;

			}
			else if (pat == 3) {
				Afterrot = -180;
				AfterPos.x = -25.0f;
				AfterPos.z = 20.0f;
			}
			else if (pat == 4) {
				Afterrot = -270;
				AfterPos.x = -25.0f;
				AfterPos.z = -20.0f;
			}
			else if (pat == 5) {
				Afterrot = -45;
				AfterPos.x = 0.0f;
				AfterPos.z = 0.0f;
			}
			else {
				Afterrot = 180;
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
		else if ((action % 2) == 1) {

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
					}
					else {
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
					}
					else {
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
					AfterPos = {
					0,
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