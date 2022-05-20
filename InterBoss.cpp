﻿#include "InterBoss.h"
#include<sstream>
#include<iomanip>
#include"Collision.h"
#include <Easing.h>
using namespace DirectX;

void InterBoss::Update() {
	Interval = player->GetInterval();
	FlashCount = player->GetFlashCount();

	collideAttackArm();
	collidePlayer();
	if (BossHP > 0) {
		Spec();
	}

	if (BossHP <= 0) {
		BossHP = 0;
	}
	player->SetInterval(Interval);

	enemyobj->Update();
	if (shadow) {
		texture->SetPosition(pos.x, 0, pos.z);
		texture->Update();
	}
}

void InterBoss::Draw() {
	XMFLOAT3 playerpos = player->GetPosition();

	ImGui::Begin("test");
	//ImGui::SliderFloat("endframe", &endframe, 1, 0.0f);
	//ImGui::SliderFloat("rot.x", &rot.x, 360, -360);
	//ImGui::SliderFloat("rot.y", &rot.y, 360, -360);
	/*ImGui::SliderFloat("pos.x", &pos.x, 1, 0.0f);
	ImGui::Text("Move:%d", appearMove);*/
	//ImGui::SliderFloat("angle", &angle, 360, -360);
	ImGui::Text("Attack::%d", AttackCount);
	ImGui::End();
	//if (BossHP >= 1) {
		Object3d::PreDraw();
		enemyobj->Draw();
		Texture::PreDraw();
		if (shadow && BossHP > 0) {
			texture->Draw();
		}
	//}
	specialDraw();
}
//プレイヤーがダメージを食らう
bool InterBoss::collidePlayer() {
	XMFLOAT3 playerpos = player->GetPosition();
	float playerhp = player->GetHp();
	if (Collision::SphereCollision(pos.x, pos.y, pos.z, 0.5f, playerpos.x, playerpos.y, playerpos.z, 0.5f) && FlashCount == 0 && Interval == 0 && BossHP > 0) {
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
	XMFLOAT3 plapos = player->GetPosition();
	bool attackflag = player->GetAttackFlag();
	float power = player->GetPower();
	float weight = player->GetArmWeight();
	float playerhp = player->GetHp();
	XMFLOAT3 distance = player->GetDistance();
	if (attackflag && !BossHit) {
		if (Collision::SphereCollision(pos.x, pos.y, pos.z, 1.3f, plapos.x, plapos.y,plapos.z, 1.3f) == true && BossHP > 0) {
			player->SetAttackFlag(false);
			player->SetCharge(0);
			player->SetRotCount(0);
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
				distance.x = plapos.x - pos.x;
				distance.z = plapos.z - pos.z;
				player->SetDistance(distance);
				player->SetJumpG(0.5f);
				Audio::GetInstance()->PlayWave("Resources/Sound/Damage.wav", 0.4f);
				player->SetDamageFlag(true);
				player->SetHp(playerhp - 1);
			}

			//ボスのHPをへらす
			if (BossHit == true) {
				Effect = true;
				BossHP -= ((weight * 2) / 2);
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

void InterBoss::EndMovie(int Timer) {
	End(Timer);
	enemyobj->Update();
}

