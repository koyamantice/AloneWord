#include "BossEnemy.h"
#include "Input.h"
#include"Collision.h"
#include<sstream>
#include<iomanip>
#include <Easing.h>
using namespace DirectX;

BossEnemy::BossEnemy() {
	model = Model::CreateFromOBJ("Fork");
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
	rot = { 0,90,0 };
	enemyobj->SetRotation(rot);
	enemyobj->SetScale({ 1.5f,1.5f,1.5f });
	texture = Texture::Create(2, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	texture->TextureCreate();
	texture->SetColor({ 1,1,1,0 });
	texture->SetPosition(pos.x, -1, pos.z);
	texture->SetRotation({ 90,0,0 });
	texture->SetScale({ 0.3f,0.3f,0.3f });
	collider.radius = rad;
}

void BossEnemy::Finalize() {
	delete enemyobj;
	delete texture;
}

void BossEnemy::Update() {
	collider.center = XMVectorSet(pos.x, pos.y, pos.z, 1);
	Interval = player->GetInterval();
	FlashCount = player->GetFlashCount();
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
	ImGui::Begin("test");
if (ImGui::TreeNode("Debug")) {
	if (ImGui::TreeNode("Enemy")) {
		ImGui::SliderFloat("bound.x", &pos.x, 50, -50);
		ImGui::SliderFloat("bound.y", &pos.y, 50, -50);
		ImGui::SliderFloat("pos.y", &pos.z, 50, -50);
		ImGui::Text("%d", IsAlive);
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

//プレイヤーがダメージを食らう
bool BossEnemy::collidePlayer() {
	XMFLOAT3 playerpos = player->GetPosition();
	int playerhp = player->GetHp();
	if (Collision::SphereCollision(pos.x, pos.y, pos.z, 0.5f, playerpos.x, playerpos.y, playerpos.z, 0.5f) && FlashCount == 0 && Interval == 0) {
		player->SetHp(playerhp - 1);
		Interval = 20;
		return true;
	}
	else {
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
		if (Collision::SphereCollision(pos.x, pos.y, pos.z, 0.5f, Armpos.x, Armpos.y, Armpos.z, 0.5f) == true) {
			BossHit = true;
			player->SetAttackFlag(false);
		
			//ついてる敵の数で音が変わる
			if (weight <= 3) {
				Audio::GetInstance()->PlayWave("Resources/Sound/strongL1.wav", 0.4f);
			}
			else if (weight > 3 && weight <= 6) {
				Audio::GetInstance()->PlayWave("Resources/Sound/strongL2.wav", 0.4f);
			}
			else if (weight >= 7) {
				Audio::GetInstance()->PlayWave("Resources/Sound/strongL3.wav", 0.4f);
			}

			//ボスのHPをへらす
			if (BossHit == true) {
				BossHP -= (weight * 2) * power;
				weight = 0.0f;
				boundpower.x = (float)(rand() % 4 - 2);
				boundpower.y = (float)(rand() % 6);
				boundpower.z = (float)(rand() % 4 - 2);
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

//ボスの行動
void BossEnemy::Fork() {
	XMFLOAT3 AfterPos{};
	if (AttackCount > 40) {
		if (!active) {
			action = 1;//(rand() % 2);
			frame = 0;
			pat = 1;
			active = true;
		}
	}
	else {
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
				Afterrot = -225;
				AfterPos.x = -25.0f;
				AfterPos.z = -20.0f;
			}
			else if (pat == 4) {
				Afterrot = -90;
				AfterPos.x = -25.0f;
				AfterPos.z = 20.0f;
			}
			else if (pat == 5) {
				Afterrot = 45;
				AfterPos.x = 0.0f;
				AfterPos.z = 0.0f;
			}
			else {
				rot.y = 360 + 115 + 180;
				pat = 0;
				AttackCount = 30;
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
			if (!already && !finish) {
				AfterPos.y = 3.0f;
				Afterrot= 90;
				pos.y = Ease(In, Cubic, 0.3f, pos.y, AfterPos.y);
				if (pos.y >= AfterPos.y - 0.05f) {
					Standby++;
					pos = {
				Ease(In,Cubic,0.5f,pos.x,player->GetPosition().x),
				Ease(In, Cubic, 0.3f, pos.y, AfterPos.y),
				Ease(In,Cubic,0.5f,pos.z,player->GetPosition().z),
					};
					if (Standby >= 180) {
						already = true;
					}
				}
			}
			else {
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
					}
					else {
						AfterPos.y = 3.0f;
					}
				}
			}
			if (finish) {
				coolT++;
				if (bossUp == false && coolT > 180) {
					//if (coolT > 480) {
						bossUp = true;
					//}
				}
				if (bossUp == true) {
					AfterPos.y = 3.0f;
					AfterPos.x = 0.0f;
					AfterPos.z = 0.0f;
					pos = {
	Ease(In,Cubic,0.34f,pos.x, AfterPos.x),
	Ease(In, Cubic, 0.34f, pos.y, AfterPos.y),
	Ease(In,Cubic,0.34f,pos.z, AfterPos.z),
					};
					if ((fabs(pos.x - AfterPos.x) <= DBL_EPSILON * fmax(1, fmax(fabs(pos.x), fabs(AfterPos.x)))) &&
						(fabs(pos.z - AfterPos.z) <= DBL_EPSILON * fmax(1, fmax(fabs(pos.z), fabs(AfterPos.z))))) {
						finish = false;
						active = false;
						bossUp = false;
						coolT = 0;
						action = 0;
						AttackCount = 30;
						AfterPos.y = 0.0f;
						times = 0;
					}

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
