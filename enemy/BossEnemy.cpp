#include "BossEnemy.h"
#include"Collision.h"
#include<sstream>
#include<iomanip>
#include <Easing.h>
#include"ImageManager.h"
using namespace DirectX;

//こんすとらくた
BossEnemy::BossEnemy() {
	model = ModelManager::GetIns()->GetModel(ModelManager::Fork);
}

//初期化
void BossEnemy::Initialize(bool shadow) {
	assert(player);
	this->shadow = shadow;
	IsAlive = 0;
	pos = { 0.0f,10.0f,0.0f };
	rot = { 0,90,0 };
	//敵
	Object3d* enemyobj_ = new Object3d();
	enemyobj_ = Object3d::Create();
	enemyobj_->SetModel(model);
	enemyobj_->SetPosition(pos);
	enemyobj_->SetRotation(rot);
	enemyobj_->SetScale({ 0.8f,0.8f,0.8f });
	enemyobj.reset(enemyobj_);
	//影(今回は使う)
	texture = Texture::Create(ImageManager::shadow, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	texture->TextureCreate();
	//texture->SetColor({ 1,1,1,1 });
	texture->SetPosition(pos.x, -1, pos.z);
	texture->SetRotation({ 90,0,0 });
	texture->SetScale({ 0.3f,0.3f,0.3f });
	//当たり判定の大きさ
	hitradius = 0.6f;
	InitCommon();
}
//開放
void BossEnemy::Finalize() {
	delete texture;
}

//ボスの行動
void BossEnemy::Spec() {
	XMFLOAT3 AfterPos{};
	//行動を決める
	if (AttackCount > 180 && pos.y <= 0.1f) {
		if (!active) {
			action = (rand() % 2);
			frame = 0;
			pat = 1;
			active = true;
		}
	}
	else {
		//インターバルのもの
		if (!active) {
			AttackCount++;
			angle += 2.0f;
			angle2 = angle * (3.14f / 180.0f);
			pos.y = sin(angle2) * 0.5f + 0.5f;
			enemyobj->SetPosition(pos);
		}
	}

	//行動を回収
	if (active) {
		//ステージを外周する
		if ((action % 2) == 0) {
			if (frame < 0.45f) {
				frame += 0.002f;
			}
			else {
				frame = 0;
				pat++;
			}
			if (pat == 1) {
				Afterrot.y = 45;
				AfterPos.x = 19.0f;
				AfterPos.z = -17.0f;
			}
			else if (pat == 2) {
				Afterrot.y = -90;
				AfterPos.x = 19.0f;
				AfterPos.z = 21.0f;

			}
			else if (pat == 3) {
				Afterrot.y = -225;
				AfterPos.x = -19.0f;
				AfterPos.z = -17.0f;
			}
			else if (pat == 4) {
				Afterrot.y = -90;
				AfterPos.x = -19.0f;
				AfterPos.z = 21.0f;
			}
			else if (pat == 5) {
				Afterrot.y = 45;
				AfterPos.x = 0.0f;
				AfterPos.z = 0.0f;
			}
			else {
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
		}
		else if ((action % 2) == 1) {
			//プレイヤーを突き刺してくる
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
						Afterrot.z += vel;
						if (rot.z > 45) {
							rot.z = 45;
							vel = -vel;
						}
						if (rot.z < -45) {
							rot.z = -45;
							vel = -vel;
						}
						break;
					}
					else {
						Afterrot.z = 0;
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
			rot.y = Ease(In, Quint, 0.7f, rot.y, Afterrot.y);
			enemyobj->SetRotation(rot);
		}
	}
	rot.y = Ease(In, Quint, 0.7f, rot.y, Afterrot.y);
	enemyobj->SetRotation(rot);
}

//導入
void BossEnemy::App(int Timer) {

	XMFLOAT3 AfterPos{};
	if (Timer == 220 || Timer == 400) {
		appearMove++;
		frame = 0.0f;
	}

	//導入シーンにおいてフレーム数によって行動を決める
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

void BossEnemy::Roll(int Timer) {
	XMFLOAT3 AfterPos{};
	if (Timer == 1) {
		pos = { 50.0f,-5.0f,10.0f };
		frame = 0.0f;
	}

	if (Timer == 10) {
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

void BossEnemy::specialDraw() {
}

//撃破
void BossEnemy::End(int Timer) {
	XMFLOAT3 scale = { 0.8f,0.8f,0.8f };
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