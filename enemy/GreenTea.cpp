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
	if (AttackCount > 180) {
		if (!active) {
			pos.y = 0.0f;
			pos.x = 0.0f;
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
			if (AttackCount<=90) {
				pos.y = sin(angle2) * 0.5f + 0.5f;
			} else {
				pos.x = sin(angle2);
			}
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
				radius = (float)((int)radius % 360);
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
				rot.y+= (rand() % 10)+1;
				enemyobj->SetRotation(rot);
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
			rot.z += vel;
			if (rot.z>Zma) {
				rot.z = Zma;
				vel = -vel;
			}
			if (rot.z < Zmi) {
				rot.z = Zmi;
				vel = -vel;
			}

			rot.y += (rand() % 10) + 1;
			enemyobj->SetRotation(rot);
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
					-17.0f,
					0.0f,
					0.0f
				};
				break;
			case 2:
				AfterPos = {
					-17.0f,
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
				-17.0f
				};
				break;
			case 6:
				AfterPos = {
				17.0f,
				0.0f,
				-17.0f
				};
				break;
			case 7:
				AfterPos = {
				17.0f,
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
			rot.z += vel;
			if (rot.z > Zma) {
				rot.z = Zma;
				vel = -vel;
			}
			if (rot.z < Zmi) {
				rot.z = Zmi;
				vel = -vel;
			}
			rot.y += (rand() % 10) + 1;
			enemyobj->SetRotation(rot);
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
					17.0f,
					0.0f,
					0.0f
				};
				break;
			case 2:
				AfterPos = {
					17.0f,
					0.0f,
					-17.0f
				};
				break;
			case 3:
				AfterPos = {
				0.0f,
				0.0f,
				-17.0f
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
				17.0f
				};
				break;
			case 6:
				AfterPos = {
				-17.0f,
				0.0f,
				17.0f
				};
				break;
			case 7:
				AfterPos = {
				-17.0f,
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
	hotWater[0]->Upda();
	hotWater[0]->SetPlayer(player);
	if (Timer == 1) {
		appearMove++;
		pos = { 13.0f,0.0f,18.0f };
		//rot = { 0.0f,315.0f,0.0f };
	}

	if (Timer == 40 || Timer == 120) {
		Audio::GetInstance()->PlayWave("Resources/Sound/Damage.wav", 0.4f);
	}

	if (AttackC <= 1) {
		if (AttackC == 0) {
			AttackPos = {
							-18,
							pos.y,
							8,
			};
		}
		else if (AttackC == 1) {
			AttackPos = {
							18,
							pos.y,
							8,
			};
		}
		if (!Attack) {
			MoveCount++;
			if (MoveCount == 1) {
				XMFLOAT3 position{};
				position.x = (AttackPos.x - pos.x);
				position.z = (AttackPos.z - pos.z);
				//Afterrot.y = (atan2(position.x, position.z) * (180.0f / XM_PI)) - 270;// *(XM_PI / 180.0f);
			}
			else if (MoveCount == 2) {
				double sb, sbx, sbz;
				if (!Attack) {
					hitpoint = HitNot;
					sbx = AttackPos.x - pos.x;
					sbz = AttackPos.z - pos.z;

					sb = sqrt(sbx * sbx + sbz * sbz);
					speedX = sbx / sb * 1.0f;
					speedZ = sbz / sb * 1.0f;
					Attack = true;
				}
			}
		}

		if (Attack) {
			rot.y += (rand() % 10) + 1;
			//プレイヤーにスピード加算
			pos.x += (float)speedX;
			pos.z += (float)speedZ;

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

			//跳ねるような感じで戻る(戻りきったら攻撃回数が加算される)
			if (hitpoint == HitRight) {
				Deadbound.y -= 0.02f;
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

				Deadbound.y -= 0.02f;
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
		}
	}
	else {
		AfterPos = {
			0,
			pos.y,
			0,
		};
		Afterrot = {
			rot.x,
			900,
			rot.z,
		};
		if (frame < 1.0f) {
			frame += 0.01f;
		}
		else {
			frame = 1.0f;
		}
	}

	if (Timer == 200 || Timer == 220) {
		hotWater[0]->AppeaSet(pos);
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

void GreenTea::End(int Timer) {
	//ボスを倒したあとの挙動(後で記述)
}

void GreenTea::specialDraw() {
	for (int i = 0; i < 50; i++) {
		hotWater[i]->Draw();
	}
}

void GreenTea::AppearDraw() {
	hotWater[0]->Draw();
}
