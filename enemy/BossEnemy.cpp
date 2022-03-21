#include "BossEnemy.h"
#include "Input.h"
#include"Collision.h"
#include<sstream>
#include<iomanip>
#include <Easing.h>
using namespace DirectX;

BossEnemy::BossEnemy() {
	model = Model::CreateFromOBJ("chr_sword");
	enemyobj = new Object3d();
	Sprite::LoadTexture(4, L"Resources/2d/PlayerHP.png");
}

void BossEnemy::Initialize() {
	assert(player);
	SpriteBossHP = Sprite::Create(4, { 0.0f,0.0f });
	SpriteBossHP->SetColor({ 0.0f,1.0f,0.0,1.0 });
	IsAlive = 0;
	IsTimer = 100;
	enemyobj = Object3d::Create();
	enemyobj->SetModel(model);
	pos = { 0.0f,0.0f,0.0f };
	enemyobj->SetPosition(pos);
	enemyobj->SetScale({ 3.0f,3.0f,3.0f });
	texture = Texture::Create(2, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	texture->TextureCreate();
	texture->SetPosition(pos.x,0,pos.z);
	texture->SetRotation({ 90,0,0 });
	texture->SetScale({ 0.3f,0.3f,0.3f });
	collider.radius = rad;
}

void BossEnemy::Finalize() {
}

void BossEnemy::Update() {
	collider.center = XMVectorSet(pos.x, pos.y, pos.z, 1);
	{//HPˆ—
		XMFLOAT2 AfterPos;
		AfterPos = { (float)(BossHP * 20),20 };
		HPPos = {
		Ease(In,Quint,0.7f,SpriteBossHP->GetSize().x,AfterPos.x),
		Ease(In,Quint,0.7f,SpriteBossHP->GetSize().y,AfterPos.y),
		};
		SpriteBossHP->SetSize(HPPos);
	}
	{
		rot.y =Ease(In, Quint, 0.7f, rot.y, Afterrot);
		enemyobj->SetRotation(rot);
	}
	Fork();

	collideAttackArm();
	enemyobj->SetPosition(pos);
	enemyobj->Update();
	texture->SetPosition(pos.x, 0, pos.z);
	texture->Update();
}

void BossEnemy::Draw() {
	ImGui::Begin("test");
	if (ImGui::TreeNode("Debug")) {
		if (ImGui::TreeNode("Player")) {
			ImGui::SliderFloat("Position.x", &pos.x, 20, -20);
			ImGui::SliderFloat("Position.y", &pos.y, 20, -20);
			ImGui::SliderFloat("Position.z", &pos.z, 20, -20);
			ImGui::Unindent();
			ImGui::TreePop();
		}
		ImGui::TreePop();
	}
	ImGui::End();

	Object3d::PreDraw();

	enemyobj->Draw();
	Texture::PreDraw();
	texture->Draw();

	Sprite::PreDraw();
	SpriteBossHP->Draw();

	//bossobj->Draw();
}

bool BossEnemy::collidePlayer() {
	XMFLOAT3 playerpos = player->GetPosition();
	int playerhp = player->GetHp();
	if (Collision::SphereCollision(pos.x, pos.y, pos.z, 0.5f, playerpos.x, playerpos.y, playerpos.z, 0.5f)) {
		player->SetHp(playerhp - 1);
		return true;
	} else {
		return false;
	}
}

bool BossEnemy::collideAttackArm() {
	XMFLOAT3 Armpos = player->GetArmPosition();
	bool attackflag = player->GetAttackFlag();
	int playerhp = player->GetHp();
	float weight = player->GetArmWeight();
	if (attackflag && !BossHit) {
		if (Collision::SphereCollision(pos.x, pos.y, pos.z, 0.5f, Armpos.x, Armpos.y, Armpos.z, 0.5f) == true) {
			BossHit = true;
			player->SetAttackFlag(false);

			if (BossHit == true) {
				BossHP -= (weight * 2);
				weight = 0.0f;
				player->SetArmWeight(weight);
				BossHit = false;
			}
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

void BossEnemy::Fork() {
	XMFLOAT3 AfterPos{};
	if (AttackCount > 40) {
		if (!active) {
			action =(rand()%2);
			frame = 0;
			pat = 1;
			active = true;
		}
	} else {
		if (!active) {
			//pat = 0;
			AttackCount++;
			action++;
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
				Afterrot = 115;
				AfterPos.x = 25.0f;
				AfterPos.z = -20.0f;

			} else if (pat == 2) {
				Afterrot = 0;
				AfterPos.x = 25.0f;
				AfterPos.z = 20.0f;

			} else if (pat == 3) {
				Afterrot = 225;
				AfterPos.x = -25.0f;
				AfterPos.z = -20.0f;
			} else if (pat == 4) {
				Afterrot = 360;
				AfterPos.x = -25.0f;
				AfterPos.z = 20.0f;
			} else if (pat == 5) {
				Afterrot = 360+115;
				AfterPos.x = 0.0f;
				AfterPos.z = 0.0f;
			} else {
				rot.y = 360 + 115+180;
				pat = 0;
				AttackCount = 0;
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
			if (!already&& !finish) {
				AfterPos.y = 3.0f;
				pos.y = Ease(In, Cubic, 0.3f, pos.y, AfterPos.y);
				if (pos.y >= AfterPos.y - 0.05f) {
					Standby++;
					pos = {
			Ease(In,Cubic,0.5f,pos.x,player->GetPosition().x),
			Ease(In, Cubic, 0.3f, pos.y, AfterPos.y),
			Ease(In,Cubic,0.5f,pos.z,player->GetPosition().z),
					};
					if (Standby>=180) {
						already = true;
					}
				}
			} else {
				AfterPos.y = 0.0f;
				pos = {
					pos.x,
					Ease(In, Cubic, 0.6f, pos.y, AfterPos.y),
					pos.z
				};
				if (pos.y <= AfterPos.y + 0.05f) {
					already = false;
					Standby = 0;
					times++;
					if (times >= 3) {
						finish = true;
					} else {
						AfterPos.y = 3.0f;
					}
				}
			}
			if (finish) {
				AfterPos.x = 0.0f;
				AfterPos.y = 0.0f;
				AfterPos.z = 0.0f;
				pos = {
Ease(In,Cubic,0.5f,pos.x, AfterPos.x),
Ease(In, Cubic, 0.5f, pos.y, AfterPos.y),
Ease(In,Cubic,0.5f,pos.z, AfterPos.z),
				};
				if ((fabs(pos.x - AfterPos.x) <= DBL_EPSILON * fmax(1, fmax(fabs(pos.x), fabs(AfterPos.x)))) &&
					(fabs(pos.y - AfterPos.y) <= DBL_EPSILON * fmax(1, fmax(fabs(pos.y), fabs(AfterPos.y)))) &&
					(fabs(pos.z - AfterPos.z) <= DBL_EPSILON * fmax(1, fmax(fabs(pos.z), fabs(AfterPos.z))))) {
					finish = false;
					active = false;
					action = 0;
					AttackCount = 0;
					times = 0;
				}

			}
			enemyobj->SetPosition(pos);

		}
	}




}

//bool BossEnemy::collidePlayer(Player* player) {
//	XMFLOAT3 pos = player->GetPosition();
//
//	//if (collision->CheckSphere2Sphere(collider, player->collider) == true && IsAlive == 1) {
//	//	IsAlive = 0;
//	//	scale = 0.0f;
//	//	this->pos = { 0,0,0 };
//	//	return true;
//	//} else {
//	//	return false;
//	//}
//}

