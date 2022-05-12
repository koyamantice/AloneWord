#include "BossEnemy.h"
#include"Collision.h"
#include<sstream>
#include<iomanip>
#include <Easing.h>
#include"ImageManager.h"
using namespace DirectX;

BossEnemy::BossEnemy() {
	model = ModelManager::GetIns()->GetModel(ModelManager::Fork);
	enemyobj = new Object3d();
}

void BossEnemy::Initialize() {
	assert(player);
	IsAlive = 0;
	enemyobj = Object3d::Create();
	enemyobj->SetModel(model);
	pos = { 0.0f,10.0f,0.0f };
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

void BossEnemy::Finalize() {
	//delete enemyobj;
	delete texture;
}

//ボスの行動
void BossEnemy::Spec() {
	XMFLOAT3 AfterPos{};
	if (AttackCount > 180 && pos.y <= 0.1f) {
		if (!active) {
			action = (rand() % 2);
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
			if (frame < 0.45f) {
				frame += 0.002f;
			} else {
				frame = 0;
				pat++;
			}
			if (pat == 1) {
				Afterrot.y = 45;
				AfterPos.x = 25.0f;
				AfterPos.z = -20.0f;
			} else if (pat == 2) {
				Afterrot.y = -90;
				AfterPos.x = 25.0f;
				AfterPos.z = 20.0f;

			} else if (pat == 3) {
				Afterrot.y = -225;
				AfterPos.x = -25.0f;
				AfterPos.z = -20.0f;
			} else if (pat == 4) {
				Afterrot.y = -90;
				AfterPos.x = -25.0f;
				AfterPos.z = 20.0f;
			} else if (pat == 5) {
				Afterrot.y = 45;
				AfterPos.x = 0.0f;
				AfterPos.z = 0.0f;
			} else {
				Afterrot.y = 90;
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

		rot.y = Ease(In, Quint, 0.7f, rot.y, Afterrot.y);
		enemyobj->SetRotation(rot);
	}

	void BossEnemy::App(int Timer) {

		XMFLOAT3 AfterPos{};
		if (Timer == 220 || Timer == 400) {
			appearMove++;
			frame = 0.0f;
		}

		switch (appearMove) {
		case 1:
			AfterPos = {
							pos.x,
							0,
							pos.z,
			};
			if (frame < 1.0f) {
				frame += 0.08f;
				break;
			}
			else {
				frame = 1.0f;
				break;
			}

		case 2:
			AfterPos = {
						pos.x,
						1,
						pos.z,
			};
			
			if (frame < 1.0f) {
				frame += 0.08f;
				break;
			}
			else {
				frame = 1.0f;
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

	void BossEnemy::specialDraw() {
	}
