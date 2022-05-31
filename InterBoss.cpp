#include "InterBoss.h"
#include<sstream>
#include<iomanip>
#include"Collision.h"
#include <Easing.h>
#include"ImageManager.h"

using namespace DirectX;

void InterBoss::InitCommon() {
	Texture* Hit_ = Texture::Create(ImageManager::Hit, { 0,0,-10 }, { 0,0,0 }, { 1, 1, 1,0.5f });
	Hit_->TextureCreate();
	Hit_->SetRotation({ 30.0f,0.0f,0.0f });
	Hit_->SetScale(Hitsca);
	Hit_->SetPosition({ 1.0f,1.0f,1.0f });
	Hit_->Update();
	Hit.reset(Hit_);
	Sprite* hit_ = Sprite::Create(ImageManager::hit,{640,360},{1.0f,1.0f,0.5f,0.5f},{0.5f,0.5f});
	hit_S.reset(hit_);
}

//更新処理
void InterBoss::Update() {
	Interval = player->GetInterval();
	FlashCount = player->GetFlashCount();
	//
	if (attach) {
		if (Hitsca.x < Maxsca.x) {
			hit_S->SetSize({ hit_S-> GetSize().x*1.1f,hit_S->GetSize().y*1.1f});
			Hitsca.x *= 1.1f;
			Hitsca.y *= 1.1f;
			Hitsca.z *= 1.1f;
		} else {
			Hitsca = { 0.5f,0.5f,0.5f };
			hit_S->SetSize({1280, 720});
			attach = false;
		}
		Hit->SetScale(Hitsca);
	}

	//各当たり判定
	collideAttackArm();
	collidePlayer();
	//各ボスの行動
	Spec();
	//HPをマイナスにしない
	if (BossHP <= 0) {
		BossHP = 0;
	}
	//ダメージ時色変更
	if (color && BossHP > 0) {
		enemyobj->SetColor({ 0.0f,1.0f,0.0f,0.0f });
		colorTimer++;
		if (colorTimer == 10) {
			color = false;
			colorTimer = 0;
		}
	}
	else {
		enemyobj->SetColor({ 1.0f,1.0f,1.0f,1.0f });
	}
	player->SetInterval(Interval);
	enemyobj->Update();
	if (shadow) {
		texture->SetPosition(pos.x, 0, pos.z);
		texture->Update();
	}
	Hit->Update();
}

//描画
void InterBoss::Draw() {
	XMFLOAT3 playerpos = player->GetPosition();
	//ImGui::Begin("test");
	////ImGui::Text("RotCount:%d", bubbleC);
	//ImGui::SliderFloat("attackradius", &attackradius, 360, -360);
	////ImGui::SliderFloat("pos.y", &rot.y, 360, -360);
	////ImGui::SliderFloat("pos.z", &rot.z, 360, -360);
	///*ImGui::Text("Count:%d", AttackCount);
	//ImGui::Text("action:%d", action);*/
	//ImGui::End();
	//if (BossHP >= 1) {
		Object3d::PreDraw();
		enemyobj->Draw();
		Texture::PreDraw();
		if (shadow && BossHP > 0) {
			texture->Draw();
		}
		if (attach/*&&BossHP>0*/) {
			Hit->Draw();
			Sprite::PreDraw();
			hit_S->Draw();
		}
	//}
	//それぞれのマップごとの描画
	specialDraw();
}
//プレイヤーがダメージを食らう
bool InterBoss::collidePlayer() {
	XMFLOAT3 playerpos = player->GetPosition();
	float playerhp = player->GetHp();
	XMFLOAT3 distance = player->GetDistance();
	float weight = player->GetArmWeight();
	int NoDamage = player->GetNoDamage();
	Interval = player->GetInterval();
	FlashCount = player->GetFlashCount();

	if (Collision::SphereCollision(pos.x, pos.y, pos.z, hitradius, playerpos.x, playerpos.y, playerpos.z, hitradius)
		&& FlashCount == 0 && Interval == 0 && BossHP > 0 && playerhp > 0 && NoDamage == 0) {
		Audio::GetInstance()->PlayWave("Resources/Sound/Damage.wav", 0.2f);
		player->SetHp(playerhp - 1);
		player->SetCharge(0);
		player->SetRotCount(0);
		Interval = 100;
		if (playerhp > 1) {
			distance.x = playerpos.x - pos.x;
			distance.z = playerpos.z - pos.z;
			player->SetDistance(distance);
			player->SetJumpG(0.5f);
			player->SetDamageFlag(true);
		}
		player->SetAttackFlag(false);
		if (weight != 0.0f) {
			weight = 0.0f;
			player->SetArmWeight(weight);
		}
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
		if (Collision::SphereCollision(pos.x, pos.y, pos.z, attackradius, plapos.x, plapos.y,plapos.z, attackradius) == true && BossHP > 0) {
			player->SetAttackFlag(false);
			player->SetCharge(0);
			player->SetRotCount(0);
			distance.x = plapos.x - pos.x;
			distance.z = plapos.z - pos.z;
			player->SetDistance(distance);
			player->SetJumpG(0.5f);
			player->SetDamageFlag(true);
		/*	if (active) {
				player->SetHp(playerhp - 1);
			}*/
			if (weight != 0.0f) {
				BossHit = true;
				attach = true;
				//Hit->SetRotation(player->GetRotation());
				Hit->SetPosition(player->GetPosition());
				//ついてる敵の数で音が変わる
				if (weight <= 2) {
					Audio::GetInstance()->PlayWave("Resources/Sound/strongL1.wav", 0.2f);
					Maxsca = { 1.5f,1.5f,1.5f };
				}
				else if (weight > 2 && weight <= 5) {
					Audio::GetInstance()->PlayWave("Resources/Sound/strongL2.wav", 0.3f);
					Maxsca = { 2.0f,2.0f,2.0f };
				}
				else if (weight >= 6) {
					Audio::GetInstance()->PlayWave("Resources/Sound/strongL3.wav", 0.3f);
					Maxsca = {2.5f,2.5f,2.5f};
				}
				player->SetNoDamage(20);
			}
			else {
				distance.x = plapos.x - pos.x;
				distance.z = plapos.z - pos.z;
				player->SetDistance(distance);
				player->SetJumpG(0.5f);
				Audio::GetInstance()->PlayWave("Resources/Sound/playerSE/noDamage.wav", 0.2f);
				player->SetDamageFlag(true);
				player->SetHp(playerhp - 1);
			}

			//ボスのHPをへらす
			if (BossHit == true) {
				Effect = true;
				Effect2 = true;
				//enemyobj->SetCollider();
				BossHP -= (power) / Defense;
				color = true;
				weight = 0.0f;
				//boundpower.x = (float)(rand() % 4 - 2);
				//boundpower.y = (float)(rand() % 6);
				//boundpower.z = (float)(rand() % 4 - 2);
				player->SetOldArm(player->GetArmWeight());
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

//導入
void InterBoss::Begin() {
	enemyobj->Update();
}

//導入ムービーのボスの行動
void InterBoss::AppeaMovie(int Timer) {
	App(Timer);
	enemyobj->Update();
}

//導入ムービーのボスの行動
void InterBoss::RollMovie(int Timer) {
	Roll(Timer);
	enemyobj->Update();
}

//撃破ムービーのボスの行動
void InterBoss::EndMovie(int Timer) {
	End(Timer);
	enemyobj->Update();
	if (attach) {
		if (Hitsca.x < Maxsca.x) {
			Hitsca.x *= 1.1f;
			Hitsca.y *= 1.1f;
			Hitsca.z *= 1.1f;
		}
		else {
			Hitsca = { 0.5f,0.5f,0.5f };
			attach = false;
		}
		Hit->SetScale(Hitsca);
	}
	Hit->Update();
}

