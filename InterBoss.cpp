#include "InterBoss.h"
#include<sstream>
#include<iomanip>
#include"Collision.h"
#include <Easing.h>
using namespace DirectX;




void InterBoss::Update() {
	Interval = player->GetInterval();
	FlashCount = player->GetFlashCount();
	{
		rot.y = Ease(In, Quint, 0.7f, rot.y, Afterrot);
		enemyobj->SetRotation(rot);
	}
	collideAttackArm();
	collidePlayer();
	Spec();
	player->SetInterval(Interval);

	enemyobj->Update();
	texture->SetPosition(pos.x, 0, pos.z);
	texture->Update();
}

void InterBoss::Draw() {
	XMFLOAT3 playerpos = player->GetPosition();
	ImGui::Begin("test");
	ImGui::SliderFloat("speed_y", &playerpos.x, 25, -25);
	ImGui::SliderFloat("speed_y", &targetpos.x, 25, -25);
	//ImGui::Text("AttackCount::%d", AttackC);
	////ImGui::Unindent();
	ImGui::End();
	Object3d::PreDraw();
	enemyobj->Draw();
	Texture::PreDraw();
	texture->Draw();
}
//プレイヤーがダメージを食らう
bool InterBoss::collidePlayer() {
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
bool InterBoss::collideAttackArm() {
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
