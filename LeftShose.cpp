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

void LeftShose::Initialize() {
	assert(player);
	IsAlive = 0;
	enemyobj = Object3d::Create();
	enemyobj->SetModel(model);
	pos = { -10.0f,0.0f,0.0f };
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

void LeftShose::Finalize() {
	//delete enemyobj;
	delete texture;
}

//ƒ{ƒX‚Ìs“®
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
					AfterPos.x = -10.0f;
					AfterPos.z = 0.0f;
				}
				else {
					Afterrot = 270;
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
}

void LeftShose::App(int Timer) {

}

void LeftShose::specialDraw() {
}
