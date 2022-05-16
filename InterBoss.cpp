#include "InterBoss.h"
#include<sstream>
#include<iomanip>
#include"Collision.h"
#include <Easing.h>
using namespace DirectX;

void InterBoss::Update() {
	Interval = player->GetInterval();
	FlashCount = player->GetFlashCount();

	collideAttackArm();
	//collidePlayer();
	Spec();
	player->SetInterval(Interval);

	enemyobj->Update();
	texture->SetPosition(pos.x, 0, pos.z);
	texture->Update();
}

void InterBoss::Draw() {
	XMFLOAT3 playerpos = player->GetPosition();

	ImGui::Begin("test");
	/*ImGui::SliderFloat("frame", &frame, 1, 0.0f);
	ImGui::SliderFloat("frame2", &frame2, 1, 0.0f);
	ImGui::Text("Move:%d", appearMove);*/
	ImGui::SliderFloat("frame", &frame, 360, -360);
	ImGui::SliderFloat("pos.y", &pos.y, 360, -360);
	ImGui::SliderFloat("rot.z", &rot.z, 360, -360);
	ImGui::End();
	if (BossHP >= 1) {
		Object3d::PreDraw();
		enemyobj->Draw();
		Texture::PreDraw();
		if (shadow) {
			texture->Draw();
		}
	}
	specialDraw();
}
//プレイヤーがダメージを食らう
bool InterBoss::collidePlayer() {
	XMFLOAT3 playerpos = player->GetPosition();
	int playerhp = player->GetHp();
	if (Collision::SphereCollision(pos.x, pos.y, pos.z, 0.5f, playerpos.x, playerpos.y, playerpos.z, 0.5f) && FlashCount == 0 && Interval == 0 && BossHP >= 1) {
		Audio::GetInstance()->PlayWave("Resources/Sound/Damage.wav", 0.4f);
		player->SetHp(playerhp - 1);
		Interval = 100;
		return true;
	} else {
		return false;
	}
}

//攻撃関数
bool InterBoss::collideAttackArm() {
	XMFLOAT3 Armpos = player->GetArmPosition();
	bool attackflag = player->GetAttackFlag();
	float power = player->GetPower();
	float weight = player->GetArmWeight();
	if (attackflag && !BossHit) {
		if (Collision::SphereCollision(pos.x, pos.y, pos.z, 1.3f, Armpos.x, Armpos.y, Armpos.z, 1.3f) == true && BossHP > 0) {
			player->SetAttackFlag(false);
			player->SetCharge(0);
			if (weight != 0.0f) {
				BossHit = true;
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
			}
			else {
				Audio::GetInstance()->PlayWave("Resources/Sound/Damage.wav", 0.4f);
				player->SetDamageFlag(true);
			}

			//ボスのHPをへらす
			if (BossHit == true) {
				Effect = true;
				BossHP -= (weight * 2);
				weight = 0.0f;
				//boundpower.x = (float)(rand() % 4 - 2);
				//boundpower.y = (float)(rand() % 6);
				//boundpower.z = (float)(rand() % 4 - 2);
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

void InterBoss::Begin() {
	enemyobj->Update();
}

void InterBoss::AppeaMovie(int Timer) {
	App(Timer);
	enemyobj->Update();
}
