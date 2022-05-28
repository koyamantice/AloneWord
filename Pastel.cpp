#include "Pastel.h"
#include"Collision.h"
#include<sstream>
#include<iomanip>
#include <Easing.h>
#include"ImageManager.h"
#include "TouchableObject.h"
#include "ParticleManager.h"
using namespace DirectX;

//コンストラクタ
Pastel::Pastel() {
	model = ModelManager::GetIns()->GetModel(ModelManager::Pastel);
	Millmodel = ModelManager::GetIns()->GetModel(ModelManager::Mill);
	Millobj = TouchableObject::Create(Millmodel);
	Mottimodel = ModelManager::GetIns()->GetModel(ModelManager::SiroMotti);
	Mottiobj = new Object3d();
	Mottiobj = Object3d::Create();
	Mottiobj->SetModel(Mottimodel);
	Platformmodel = ModelManager::GetIns()->GetModel(ModelManager::Platform);
	for (std::size_t i = 0; i < Platformobj.size(); i++) {
		Platformobj[i] = TouchableObject::Create(Platformmodel);
		Plattexture[i] = Texture::Create(ImageManager::shadow, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
		Plattexture[i]->TextureCreate();
		attensiontexture[i] = Texture::Create(ImageManager::Attension, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
		attensiontexture[i]->TextureCreate();
	}

	//影(今回は使う)
	texture = Texture::Create(ImageManager::shadow, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	texture->TextureCreate();
	//防御力
	Defense = 1.4f;
}

//初期化
void Pastel::Initialize(bool shadow) {
	assert(player);
	this->shadow = shadow;
	IsAlive = 0;
	//敵
	pos = { 0.0f,5.0f,7.5f };
	rot = { 0,270,0 };
	Object3d*enemyobj_ = new Object3d();
	enemyobj_ = Object3d::Create();
	enemyobj_->SetModel(model);
	enemyobj_->SetPosition(pos);
	enemyobj_->SetRotation(rot);
	enemyobj_->SetScale({ 2.0f,2.0f,2.0f });
	enemyobj.reset(enemyobj_);
	//ステージのオブジェクト
	//Millobj = Object3d::Create();
	//Millobj->SetModel(Millmodel);
	
	Millpos = { 0.0f,-2.0f,0.0f };
	Millobj->SetPosition(Millpos);
	Millobj->SetRotation({0,90,0});
	Millobj->SetScale({ 1.0f,1.0f,1.0f });
	
	Mottiobj->SetPosition({ 0.0f,1.0f,0.0f });
	Mottiobj->SetScale(MottiScale);
	for (std::size_t i = 0; i < Platformobj.size(); i++) {
		Platformobj[i]->SetModel(Platformmodel);
		Plapos[i] = { 0.0f,-30.0f,0.0f };
		Platformobj[i]->SetScale({ 1.2f,1.2f,1.2f });
		Platformobj[i]->SetPosition(Plapos[i]);
	}

	//texture->SetColor({ 1,1,1,1 });
	texture->SetPosition(pos.x, -1, pos.z);
	texture->SetRotation({ 90,0,0 });
	texture->SetScale({ 0.3f,0.3f,0.3f });
	for (std::size_t i = 0; i < Platformobj.size(); i++) {
		//Plattexture[i] = Texture::Create(ImageManager::shadow, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
		Plattexture[i]->SetRotation({90,0,0});
		Plattexture[i]->SetScale({ 0.5f,0.5f,0.5f });
		attensiontexture[i]->SetRotation({ 0,0,0 });
		attensiontexture[i]->SetScale({ 0.2f,0.2f,0.2f });
	}
	InitCommon();
	//当たり判定の大きさ
	hitradius = 0.6f;
}

//開放
void Pastel::Finalize() {
	delete Mottiobj;
	delete Millobj;
	delete texture;
	for (std::size_t i = 0; i < Platformobj.size(); i++) {
		delete Plattexture[i];
	}
	for (std::size_t i = 0; i < Platformobj.size(); i++) {
		delete Platformobj[i];
	}
}

//ボスの行動
void Pastel::Spec() {
	XMFLOAT3 AfterPos{};
	//行動を決める
	if (AttackCount > 180) {
		if (!active) {
			hitradius = 0.6f;
			AttackPoint = (rand() % 3);
			frame = 0;
			active = true;
			action = (rand() % 2);
			pat = 1;
		}
	}
	//インターバル
	else {
		if (!active && !Off) {
			AttackCount++;
			AfterPos = {
				pos.x,
				5.0f,
				pos.z
			};

			if (frame < 1.0f) {
				frame += 0.01f;
			}
			else {
				frame = 1.0f;
			}

			pos = {
	Ease(In,Cubic,frame,pos.x,AfterPos.x),
	Ease(In,Cubic,frame,pos.y,AfterPos.y),
	Ease(In,Cubic,frame,pos.z,AfterPos.z)
			};
			
			enemyobj->SetPosition(pos);
		}
	}

	//行動開始
	if (Off == false) {
		if (active) {
			//衝撃は
			if ((action % 2) == 0) {
				hitradius = 0.6f;
				switch (pat) {
					//その場所まで行く
				case 1:
					if (AttackPoint == 0) {
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
					else if (AttackPoint == 1) {
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
					else if (AttackPoint == 2) {
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
					else if (AttackPoint == 3) {
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
						pat++;
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
						pat++;
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

						if (coolT < 150) {
							coolT++;
							break;
						}
						else {
							coolT = 0;
							frame = 0;
							pat++;
							/*if (BossHP >= 20) {
								action++;
							}
							else {
								AttackC++;
								oldAttackPoint = AttackPoint;
								if (AttackC < 2) {
									AttackC++;
									if (oldAttackPoint == AttackPoint) {
										AttackPoint = (rand() % 3);
									}
									action = 1;
								}
								else {
									AttackC = 0;
									action++;
								}
							}*/
							break;
						}
					}
				case 4:
					for (std::size_t i = 0; i < Platformobj.size(); i++) {
						SetPlatform[i] = false;
					}
					//空に戻ります
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
						pat++;
						break;
					}
				case 5:
					//元の位置に戻ります
					AfterPos = {
						0.0f,
						5.0f,
						8.5f,
					};
					Afterrot = {
						0.0f,
						90.0f,
						0.0f,
					};
					if (frame < 1.0f) {
						frame += 0.01f;
						break;
					}
					else {
						frame = 0;
						pat = 0;
						active = false;
						//HPによってインターバルが決まる
						if (BossHP >= 20) {
							AttackCount = 0;
						}
						else {
							AttackCount = 150;
						}
						break;
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
			//回転攻撃
			else if ((action % 2) == 1) {
				switch (pat) {
					//その場所まで行く
				case 1:
					AfterPos = {
					14.0f,
					2.0f,
					12.0f
					};
					Afterrot = {
						90.0f,
						rot.y,
						45.0f,
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
					14.0f,
					2.0f,
					-12.0f
					};
					Afterrot = {
						90.0f,
						rot.y,
						1845.0f,
					};

					if (frame < 1.0f) {
						frame += 0.01f;
						hitradius = 4.0f;
						break;
					}
					else {
						frame = 0;
						hitradius = 1.0f;
						pat++;
						rot.z = 45.0f;
						break;
					}
				case 3:
					AfterPos = {
						-14.0f,
						2.0f,
						-12.0f
					};
					Afterrot = {
						90.0f,
						rot.y,
						1845.0f
					};

					if (frame < 1.0f) {
						frame += 0.01f;
						hitradius = 4.0f;
						break;
					}
					else {
						hitradius = 1.0f;
						frame = 0;
						pat++;
						rot.z = 45.0f;
						break;
					}
				case 4:
					AfterPos = {
					-14.0f,
					2.0f,
					12.0f
					};
					Afterrot = {
						90.0f,
						rot.y,
						1845.0f
					};

					if (frame < 1.0f) {
						frame += 0.01f;
						hitradius = 4.0f;
						break;
					}
					else {
						hitradius = 1.0f;
						frame = 0;
						pat++;
						rot.z = 45.0f;
						break;
					}
				case 5:
					AfterPos = {
					14.0f,
					2.0f,
					12.0f
					};
					Afterrot = {
						90.0f,
						rot.y,
						1845.0f
					};

					if (frame < 1.0f) {
						frame += 0.01f;
						hitradius = 4.0f;
						break;
					}
					else {
						hitradius = 1.0f;
						frame = 0;
						pat++;
						rot.z = 45.0f;
						break;
					}
					
				case 6:
					//元の位置に戻ります
					AfterPos = {
						0.0f,
						5.0f,
						8.5f,
					};
					Afterrot = {
						0.0f,
						90.0f,
						0.0f,
					};
					if (frame < 1.0f) {
						frame += 0.01f;
						break;
					}
					else {
						hitradius = 0.6f;
						frame = 0;
						pat = 0;
						AttackCount = 0;
						active = false;
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
		}
	}
	
	//餅が集まったら餅を付き始める
	if (Off == true && !active) {
		AfterPos.y = 2.0f;
		AfterPos.z = 8.5f;
		hitradius = 0.6f;
		Afterrot = {
			rot.x,
			270.0f,
			rot.z,
		};
		if (frame < 0.90f && pos.y != 2.0f) {
			frame += 0.004f;
		}
		else {
			frame = 0.0f;
			angle += 3.0f;
			angle2 = angle * (3.14f / 180.0f);
			rot.z = sin(angle2) * 30;
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

	if (haveEnemy >= 10.0f && !active) {
		haveTimer++;
		Off = true;
		if (rot.z >= 29.900) {
			MottiScale.x -= 0.06f;
			MottiScale.y -= 0.06f;
			MottiScale.z -= 0.06f;
		}
		if (haveTimer == 600) {
			Off = false;
			haveTimer = 0;
			haveEnemy = 0.0f;
			MottiScale = { 0.0f,0.0f,0.0f };
		}
	}

	MillUpdate();
	
	//回避場所が出現する
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
				Plapos[i].y += 0.20f;
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
		attensiontexture[i]->Update();
		attensiontexture[i]->SetPosition({ Plapos[i].x,3.0f,Plapos[i].z });
		//Plattexture[i]->SetScale({1.0f,1.0f,1.0f});
		Platformobj[i]->SetPosition(Plapos[i]);
		Platformobj[i]->Update();
		Mottiobj->SetScale(MottiScale);
		Mottiobj->Update();
		if (SetPlatform[i] && Plapos[i].y <= -1.0f) {
			FlashTimer++;

			if (FlashTimer % 50) {
				FlashCount++;
			}
		}
		else {
			FlashTimer = 0;
			FlashCount = 0;
		}

	}

	BirthParticle();
}

//導入
void Pastel::App(int Timer) {

	XMFLOAT3 AfterPos{};
	XMFLOAT3 AfterRot{};

	if (Timer == 1) {
		frame = 0.0f;
		frame2 = 0.0f;
		appearMove++;
	}

	//導入シーンにおいてフレーム数によって行動を決める
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

void Pastel::Roll(int Timer) {
	XMFLOAT3 AfterPos{};
	if (Timer == 1) {
		pos = { 50.0f,-5.0f,10.0f };
		frame = 0.0f;
	}

	if (Timer == 300) {
		rollMove++;
	}

	//導入シーンにおいてフレーム数によって行動を決める
	switch (rollMove) {
	case 1:
		pos.x -= 0.1f;
	}

	//pos = {
	//Ease(In,Cubic,frame,pos.x,AfterPos.x),
	//Ease(In,Cubic,frame,pos.y,AfterPos.y),
	//Ease(In,Cubic,frame,pos.z,AfterPos.z)
	//};
	enemyobj->SetPosition(pos);
}

//撃破
void Pastel::End(int Timer) {
	//ボスを倒したあとの挙動(後で記述)
	XMFLOAT3 scale = { 2.0f,2.0f,2.0f };
	float RotPower = 0.0f;
	XMFLOAT3 AfterScale{};
	//float endframe = 0.0f;
	//ボスを倒したあとの挙動(後で記述)
	if (Timer == 250) {
		pos = { 0.0f,0.0f,0.0f };
		rot = { 0,90,0 };
	}

	if (Timer == 350) {
		EndMove++;
		endframe = 0.0f;
	}

	switch (EndMove) {
	case 1:
		AfterScale = {
						0.2f,
						0.2f,
						0.2f,
		};

		if (endframe < 1.0f) {
			endframe += 0.005f;
			break;
		}
		else {
			endframe = 1.0f;
			RotPower = 0.0f;
			EndMove++;
			break;
		}

	case 2:
		if (rot.x <= 90) {
			rot.x += 2.0f;
		}

		//case 2:
		//	AfterPos = {
		//				pos.x,
		//				1,
		//				pos.z,
		//	};

		//	if (frame < 1.0f) {
		//		frame += 0.08f;
		//		break;
		//	}
		//	else {
		//		frame = 1.0f;
		//		break;
		//	}
	}

	RotPower = Ease(In, Cubic, endframe, RotPower, 20.0f);
	if (EndMove == 1) {
		rot.y += RotPower;
	}

	scale = {
	Ease(In,Cubic,endframe,scale.x,0.2f),
	Ease(In,Cubic,endframe,scale.y,0.2f),
	Ease(In,Cubic,endframe,scale.z,0.2f),
	};

	enemyobj->SetScale(scale);
	enemyobj->SetPosition(pos);
	enemyobj->SetRotation(rot);
}

//臼の更新
void Pastel::MillUpdate() {
	Millobj->Update();
}

//特別な描画(うすと回避のものと影)
void Pastel::specialDraw() {
	if (BossHP > 0) {
		Millobj->Draw();
		Mottiobj->Draw();
		for (std::size_t i = 0; i < Platformobj.size(); i++) {
			Platformobj[i]->Draw();
			Texture::PreDraw();
			if (SetPlatform[i] && Plapos[i].y <= -1.0f) {
				Plattexture[i]->Draw();
				if (FlashCount % 2 == 0) {
					attensiontexture[i]->Draw();
				}
			}
		}
	}
}

bool Pastel::collideAttackArm(Player* player) {
	XMFLOAT3 plapos = player->GetPosition();
	bool attackflag = player->GetAttackFlag();
	float weight = player->GetArmWeight();
	if (attackflag && !BossHit) {
		if (Collision::CircleCollision(plapos.x, plapos.z, 2.0f, Millpos.x, Millpos.z, 2.0f)) {
			BossHit = true;
			player->SetRotTimer(0);
			player->SetRotCount(0);
			player->SetChargeTimer(0);
			player->SetAttackFlag(false);
			//餅を臼に入れている
			if (BossHit == true) {
				Audio::GetInstance()->PlayWave("Resources/Sound/strongL2.wav", 0.4f);
				haveEnemy += weight;
				if (haveEnemy < 11.0f) {
					MottiScale.x += (weight / 10);
					MottiScale.y += (weight / 10);
					MottiScale.z += (weight / 10);
				}
				else {
					MottiScale = {1.0f,1.0f,1.0f};
				}
				weight = 0.0f;
				player->SetOldArm(player->GetArmWeight());
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

//パーティクルが出てくる
void Pastel::BirthParticle() {
	if (action == 1 && (pat == 2 || pat == 3 || pat == 4 || pat == 5)) {
		for (int i = 0; i < 3; ++i) {
			const float rnd_vel = 0.1f;
			XMFLOAT3 vel{};
			vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
			vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
			vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
			//const float rnd_sca = 0.1f;
			//float sca{};
			//sca = (float)rand() / RAND_MAX*rnd_sca;
			ParticleManager::GetInstance()->Add(30, { pos.x + vel.x,pos.y,pos.z + vel.z }, vel, XMFLOAT3(), 1.2f, 0.6f);
		}
	}
}