#include "BossEnemy.h"
#include"Collision.h"
#include<sstream>
#include<iomanip>
#include <Easing.h>
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
	pos = { 0.0f,0.0f,0.0f };
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

void BossEnemy::Finalize() {
	//delete enemyobj;
	delete texture;
}

void BossEnemy::Update() {
	Interval = player->GetInterval();
	FlashCount = player->GetFlashCount();
	{
		rot.y = Ease(In, Quint, 0.7f, rot.y, Afterrot);
		enemyobj->SetRotation(rot);
	}
	Fork();

	collideAttackArm();
	collidePlayer();
	player->SetInterval(Interval);
	enemyobj->SetPosition(pos);
	enemyobj->Update();
	texture->SetPosition(pos.x, 0, pos.z);
	texture->Update();
}

void BossEnemy::Draw() {
//	ImGui::Begin("test");
//	//	if (ImGui::TreeNode("Debug")) {
//	if (ImGui::TreeNode("Rice")) {
//		ImGui::SliderFloat("pos.x", &pos.x, 50, -50);
//		ImGui::SliderFloat("pos.y", &pos.y, 50, -50);
//		ImGui::SliderFloat("pos.z", &pos.z, 50, -50);
//		ImGui::Text("%d", pat);
//		ImGui::Unindent();
//		ImGui::TreePop();
//	}
//	//ImGui::TreePop();
////}
//	ImGui::End();

	Object3d::PreDraw();
	enemyobj->Draw();
	Texture::PreDraw();
	texture->Draw();

	Sprite::PreDraw();

	//bossobj->Draw();
}

//プレイヤーがダメージを食らう
bool BossEnemy::collidePlayer() {
	XMFLOAT3 playerpos = player->GetPosition();
	int playerhp = player->GetHp();
	if (Collision::SphereCollision(pos.x, pos.y, pos.z, 0.5f, playerpos.x, playerpos.y, playerpos.z, 0.5f) && FlashCount == 0 && Interval == 0) {
		Audio::GetInstance()->PlayWave("Resources/Sound/Damage.wav", 0.4f);
		player->SetHp(playerhp - 1);
		Interval = 100;
		return true;
	} else {
		return false;
	}
}

//攻撃関数
bool BossEnemy::collideAttackArm() {
	XMFLOAT3 Armpos = player->GetArmPosition();
	bool attackflag = player->GetAttackFlag();
	float power = player->GetPower();
	float weight = player->GetArmWeight();
	if (attackflag && !BossHit) {
		if (Collision::SphereCollision(pos.x, pos.y, pos.z, 1.0f, Armpos.x, Armpos.y, Armpos.z, 1.0f) == true) {
			BossHit = true;
			player->SetAttackFlag(false);
			//ついてる敵の数で音が変わる
			if (weight <= 3) {
				Audio::GetInstance()->PlayWave("Resources/Sound/strongL1.wav", 0.4f);
			} else if (weight > 3 && weight <= 6) {
				Audio::GetInstance()->PlayWave("Resources/Sound/strongL2.wav", 0.4f);
			} else if (weight >= 7) {
				Audio::GetInstance()->PlayWave("Resources/Sound/strongL3.wav", 0.4f);
			}

			//ボスのHPをへらす
			if (BossHit == true) {
				Effect = true;
				BossHP -= (weight * 2) * power;
				weight = 0.0f;
				boundpower.x = (float)(rand() % 4 - 2);
				boundpower.y = (float)(rand() % 6);
				boundpower.z = (float)(rand() % 4 - 2);
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

//ボスの行動
void BossEnemy::Fork() {
	XMFLOAT3 AfterPos{};
	if (AttackCount > 180) {
		if (!active) {
			action = (rand() % 2);
			frame = 0;
			pat = 1;
			active = true;
		}
	} else {
		if (!active) {
			AttackCount++;
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
				Afterrot = 45;
				AfterPos.x = 25.0f;
				AfterPos.z = -20.0f;
			} else if (pat == 2) {
				Afterrot = -90;
				AfterPos.x = 25.0f;
				AfterPos.z = 20.0f;

			} else if (pat == 3) {
				Afterrot = -225;
				AfterPos.x = -25.0f;
				AfterPos.z = -20.0f;
			} else if (pat == 4) {
				Afterrot = -90;
				AfterPos.x = -25.0f;
				AfterPos.z = 20.0f;
			} else if (pat == 5) {
				Afterrot = 45;
				AfterPos.x = 0.0f;
				AfterPos.z = 0.0f;
			} else {
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
	}