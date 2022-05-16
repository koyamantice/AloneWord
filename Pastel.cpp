#include "Pastel.h"
#include"Collision.h"
#include<sstream>
#include<iomanip>
#include <Easing.h>
#include"ImageManager.h"
#include "TouchableObject.h"
using namespace DirectX;

Pastel::Pastel() {
	model = ModelManager::GetIns()->GetModel(ModelManager::Pastel);
	enemyobj = new Object3d();
	Millmodel = ModelManager::GetIns()->GetModel(ModelManager::EHub);
	Millobj = new Object3d();
	Platformmodel = ModelManager::GetIns()->GetModel(ModelManager::Platform);
	for (std::size_t i = 0; i < Platformobj.size(); i++) {
		Platformobj[i] = TouchableObject::Create(Platformmodel);
		Plattexture[i] = Texture::Create(ImageManager::shadow, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
		Plattexture[i]->TextureCreate();
	}
}

void Pastel::Initialize(bool shadow) {
	assert(player);
	this->shadow = shadow;
	IsAlive = 0;
	enemyobj = Object3d::Create();
	enemyobj->SetModel(model);
	pos = { 0.0f,5.0f,8.0f };
	enemyobj->SetPosition(pos);
	rot = { 0,270,0 };
	enemyobj->SetRotation(rot);
	enemyobj->SetScale({ 2.0f,2.0f,2.0f });
	Millobj = Object3d::Create();
	Millobj->SetModel(Millmodel);
	Millpos = { 0.0f,-2.0f,0.0f };
	Millobj->SetPosition(Millpos);
	Millobj->SetRotation({0,90,0});
	Millobj->SetScale({ 4.5f,4.5f,4.5f });
	for (std::size_t i = 0; i < Platformobj.size(); i++) {
		Platformobj[i] = TouchableObject::Create(Platformmodel);
		Platformobj[i]->SetModel(Platformmodel);
		Plapos[i] = { 0.0f,-30.0f,0.0f };
		Platformobj[i]->SetScale({ 1.2f,1.2f,1.2f });
		Platformobj[i]->SetPosition(Plapos[i]);
	}
	texture = Texture::Create(ImageManager::shadow, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	texture->TextureCreate();
	//texture->SetColor({ 1,1,1,1 });
	texture->SetPosition(pos.x, -1, pos.z);
	texture->SetRotation({ 90,0,0 });
	texture->SetScale({ 0.3f,0.3f,0.3f });
	for (std::size_t i = 0; i < Platformobj.size(); i++) {
		Platformobj[i] = TouchableObject::Create(Platformmodel);
		//Plattexture[i] = Texture::Create(ImageManager::shadow, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
		Plattexture[i]->SetRotation({90,0,0});
		Plattexture[i]->SetScale({ 0.5f,0.5f,0.5f });
		//Plattexture[i]->TextureCreate();
	}
}

void Pastel::Finalize() {
	//delete enemyobj;
	delete texture;
	for (std::size_t i = 0; i < Platformobj.size(); i++) {
		delete Plattexture[i];
	}
}

//ボスの行動
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
			pos.y = 5.0f;
			AttackCount++;
			/*angle += 2.0f;
			angle2 = angle * (3.14f / 180.0f);
			pos.y = sin(angle2) * 2 + 3;
			enemyobj->SetPosition(pos);*/
		}
	}

	if (Off == false) {
		if (active) {
			switch (action) {
			//その場所まで行く
			case 1:
				if (pat == 0) {
					AfterPos = {
					10.0f,
					5.0f,
					-15.0f
					};
					Afterrot = {
						rot.x,
						180.0f,
						-45.0f,
					};
				}
				else if (pat == 1) {
					AfterPos = {
					10.0f,
					5.0f,
					15.0f
					};
					Afterrot = {
					rot.x,
					180.0f,
					-45.0f,
					};
				}
				else if (pat == 2) {
					AfterPos = {
					-10.0f,
					5.0f,
					15.0f
					};
					Afterrot = {
					rot.x,
					360.0f,
					-45.0f,
					};
				}
				else if (pat == 3) {
					AfterPos = {
					-10.0f,
					5.0f,
					-15.0f
					};
					Afterrot = {
					rot.x,
					360.0f,
					-45.0f,
					};
				}

				if (frame < 1.0f) {
					frame += 0.01f;
					break;
				}
				else {
					//回避ポイントの場所をランダムで決める
					for (std::size_t i = 0; i < Platformobj.size(); i++) {
						//for (std::size_t j = 1; j < Platformobj.size(); j++) {
							//if ((BirthNumber[i] == BirthNumber[j]) && i != j) {
								SetPlatform[i] = true;
								BirthNumber[i] = rand() % 3;
							//}
						//}
					}
					frame = 0;
					action++;
					break;
				}
			case 2:
				//攻撃までの間
				if (aiming < 200) {
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
				//攻撃
				AfterPos = {
					pos.x,
					2,
					pos.z,
				};
				Afterrot = {
					rot.x,
					rot.y,
					45,
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
				for (std::size_t i = 0; i < Platformobj.size(); i++) {
					SetPlatform[i] = false;
				}
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

		rot = {
Ease(In,Cubic,frame,rot.x,Afterrot.x),
Ease(In,Cubic,frame,rot.y,Afterrot.y),
Ease(In,Cubic,frame,rot.z,Afterrot.z)
		};
		enemyobj->SetPosition(pos);
		enemyobj->SetRotation(rot);
	}
	
	if (Off == true && !active) {
		AfterPos.y = 1.0f;
		AfterPos.z = 5.0f;
	
		if (frame < 0.90f && pos.y != 1.0f) {
			frame += 0.004f;
		}
		else {
			frame = 0.0f;
			angle += 2.0f;
			angle2 = angle * (3.14f / 180.0f);
			rot.z = sin(angle2) * 90;
		}

		pos = {
Ease(In,Cubic,frame,pos.x,AfterPos.x),
Ease(In,Cubic,frame,pos.y,AfterPos.y),
Ease(In,Cubic,frame,pos.z,AfterPos.z)
		};
		enemyobj->SetPosition(pos);
		enemyobj->SetRotation(rot);
	}

	if (haveEnemy >= 10.0f && !active) {
		haveTimer++;
		Off = true;
		if (haveTimer == 1000) {
			Off = false;
			haveTimer = 0;
			haveEnemy = 0.0f;
		}
	}

	MillUpdate();
	for (std::size_t i = 0; i < Platformobj.size(); i++) {
		if (SetPlatform[i] == true) {
			if (BirthNumber[i] == 0) {
				Plapos[i].x = 7.0f;
				Plapos[i].z = -7.0f;
			}
			else if (BirthNumber[i] == 1) {
				Plapos[i].x = 7.0f;
				Plapos[i].z = 7.0f;
			}
			else if (BirthNumber[i] == 2) {
				Plapos[i].x = -7.0f;
				Plapos[i].z = 7.0f;
			}
			else if (BirthNumber[i] == 3) {
				Plapos[i].x = -7.0f;
				Plapos[i].z = -7.0f;
			}

			if (Plapos[i].y <= 0.0f) {
				Plapos[i].y += 0.10f;
			}
		}
		else {
			if (Plapos[i].y >= -30.0f) {
				Plapos[i].y -= 0.10f;
			}
			else {
				SetPlatform[i] = false;
			}
		}
		Plattexture[i]->Update();
		Plattexture[i]->SetPosition({Plapos[i].x,0.0f,Plapos[i].z});
		//Plattexture[i]->SetScale({1.0f,1.0f,1.0f});
		Platformobj[i]->SetPosition(Plapos[i]);
		Platformobj[i]->Update();
	}
}

void Pastel::App(int Timer) {

	XMFLOAT3 AfterPos{};
	XMFLOAT3 AfterRot{};

	if (Timer == 1) {
		frame = 0.0f;
		frame2 = 0.0f;
		appearMove++;
	}
	switch (appearMove) {
	case 1:
		frame = 0.0f;
		angle += 3.0f;
		angle2 = angle * (3.14f / 180.0f);
		rot.z = sin(angle2) * 45;

		if ((angle >= 500) && (rot.z >= 44.0f)) {
			rot.z = 45.0f;
			appearMove++;
		}
	case 2:
		AfterRot = {
			rot.x,
			90.0f,
			rot.z,
		};
		if (frame < 1.0f) {
			frame += 0.005f;
			break;
		}
		else {
			frame = 0.0f;
			appearMove++;
			break;
		}
	}

	rot = {
Ease(In,Cubic,frame,rot.x,AfterRot.x),
Ease(In,Cubic,frame,rot.y,AfterRot.y),
Ease(In,Cubic,frame,rot.z,AfterRot.z)
	};

	enemyobj->SetRotation(rot);
}

void Pastel::MillUpdate() {
	Millobj->Update();
}

void Pastel::specialDraw() {
	Millobj->Draw();
	for (std::size_t i = 0; i < Platformobj.size(); i++) {
		Platformobj[i]->Draw();
		Texture::PreDraw();
		if (SetPlatform[i] && Plapos[i].y <= -1.0f) {
			Plattexture[i]->Draw();
		}
	}
}

bool Pastel::collideAttackArm(Player* player) {
	XMFLOAT3 Armpos = player->GetArmPosition();
	bool attackflag = player->GetAttackFlag();
	float weight = player->GetArmWeight();
	if (attackflag && !BossHit) {
		if (Collision::CircleCollision(Armpos.x, Armpos.z, 1.3, Millpos.x, Millpos.z, 1.3)) {
			BossHit = true;
			player->SetAttackFlag(false);
			//餅を臼に入れている
			if (BossHit == true) {
				haveEnemy += weight;
				weight = 0.0f;
				player->SetArmWeight(weight);
				BossHit = false;
			}
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}