#include "Pastel.h"
#include"Collision.h"
#include<sstream>
#include<iomanip>
#include <Easing.h>
#include"ImageManager.h"
using namespace DirectX;

Pastel::Pastel() {
	model = ModelManager::GetIns()->GetModel(ModelManager::Fork);
	enemyobj = new Object3d();
}

void Pastel::Initialize() {
	assert(player);
	IsAlive = 0;
	enemyobj = Object3d::Create();
	enemyobj->SetModel(model);
	pos = { 0.0f,5.0f,0.0f };
	enemyobj->SetPosition(pos);
	rot = { 0,90,0 };
	enemyobj->SetRotation(rot);
	enemyobj->SetScale({ 1.5f,1.5f,1.5f });
	texture = Texture::Create(ImageManager::shadow, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	texture->TextureCreate();
	//texture->SetColor({ 1,1,1,1 });
	texture->SetPosition(pos.x, -1, pos.z);
	texture->SetRotation({ 90,0,0 });
	texture->SetScale({ 0.3f,0.3f,0.3f });
}

void Pastel::Finalize() {
	//delete enemyobj;
	delete texture;
}

//�{�X�̍s��
void Pastel::Spec() {
	XMFLOAT3 AfterPos{};
	if (AttackCount > 180) {
		if (!active) {
			pat = (rand() % 3);
			frame = 0;
			active = true;
			action = 1;
		}
	}
	else {
		if (!active && !Off) {
			AttackCount++;
			//angle += 2.0f;
			//angle2 = angle * (3.14f / 180.0f);
			//pos.y = sin(angle2) * 0.5f + 0.5f;
			//enemyobj->SetPosition(pos);
		}
	}

	if (Off == false) {
		if (active) {
			switch (action) {
			case 1:
				if (pat == 0) {
					AfterPos = {
					20.0f,
					5.0f,
					-15.0f
					};
				}
				else if (pat == 1) {
					AfterPos = {
					20.0f,
					5.0f,
					15.0f
					};
				}
				else if (pat == 2) {
					AfterPos = {
					-20.0f,
					5.0f,
					15.0f
					};
				}
				else if (pat == 3) {
					AfterPos = {
					-20.0f,
					5.0f,
					-15.0f
					};
				}

				if (frame < 1.0f) {
					frame += 0.01f;
					break;
				}
				else {
					frame = 0;
					action++;
					break;
				}
			case 2:
				if (aiming < 50) {
					aiming++;
					break;
				}
				else {
					frame = 0;
					aiming = 0;
					action++;
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
					if (coolT < 350) {
						coolT++;
						break;
					}
					else {
						coolT = 0;
						frame = 0;
						if (BossHP >= 20) {
							action++;
						}
						else {
							AttackC++;
							oldpat = pat;
							if (AttackC < 2) {
								AttackC++;
								if (oldpat == pat) {
									pat = (rand() % 3);
								}
								action = 1;
							}
							else {
								AttackC = 0;
								action++;
							}
						}
						break;
					}
				}
			case 4:
				AfterPos = {
					pos.x,
					5.0f,
					pos.z,
				};
				if (frame < 1.0f) {
					frame += 0.01f;
					break;
				}
				else {
					frame = 0;
					action++;
					break;
				}
			case 5:
					AfterPos = {
						0.0f,
						5.0f,
						5.0f,
					};
					if (frame < 1.0f) {
						frame += 0.01f;
						break;
					}
					else {
						frame = 0;
						action = 0;
						active = false;
						AttackCount = 0;
						break;
					}
			}
		}
		pos = {
Ease(In,Cubic,frame,pos.x,AfterPos.x),
Ease(In,Cubic,frame,pos.y,AfterPos.y),
Ease(In,Cubic,frame,pos.z,AfterPos.z)
		};
		enemyobj->SetPosition(pos);
	}
	
	if (Off == true && !active) {
		AfterPos.y = 1.0f;
		AfterPos.z = 8.0f;
	
		if (frame < 0.90f && pos.y != 1.0f) {
			frame += 0.004f;
		}
		else {
			frame = 0.0f;
			angle += 2.0f;
			angle2 = angle * (3.14f / 180.0f);
			rot.z = sin(angle2) * 90;
		}

		//if (pos.y <= 2.0f) {
		//
		//}
		//
		pos = {
Ease(In,Cubic,frame,pos.x,AfterPos.x),
Ease(In,Cubic,frame,pos.y,AfterPos.y),
Ease(In,Cubic,frame,pos.z,AfterPos.z)
		};
		enemyobj->SetPosition(pos);
		enemyobj->SetRotation(rot);
	}

}

void Pastel::specialDraw() {
}

void Pastel::GetOff(Mill* mill) {
	float haveEnemy = mill->GetHaveEnemy();
	int haveTimer = mill->GetHaveTimer();
	if (haveTimer != 0) {
		if (Off == false && !active) {
			frame = 0.0f;
			Off = true;
		}
	}
	else {
		rot.z = 0.0f;
		Off = false;
		enemyobj->SetRotation(rot);
	}

}