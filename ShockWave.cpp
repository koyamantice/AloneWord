#include "ShockWave.h"
#include "ImageManager.h"
#include"Collision.h"
#include "DebugText.h"
#include "imgui.h"
void ShockWave::Init() {
	wave = Texture::Create(ImageManager::enemy, { 0,0,0 }, { 12,12,12 }, { 1,1,1,0.6f });
	wave->TextureCreate();
	wave->SetPosition({ 0.0f,0.0f,0.0f });
	wave->SetRotation({ 90.0f, 0.0f, 0.0f });
	wave->SetScale(scale);
	//limit->SetScale({ 6,5,5 }); 
}

void ShockWave::Upda(Pastel* pastel,Player* player) {
	Interval = player->GetInterval();
	float playerhp = player->GetHp();
	if (CollideWave(player) && !CollideSafeWave(player) && Interval == 0 && player->GetPosition().y <= 1.0f) {
		Audio::GetInstance()->PlayWave("Resources/Sound/Damage.wav", 0.4f);
		player->SetHp(player->GetHp() - 1);
		Interval = 100;
		player->SetCharge(0);
		player->SetRotCount(0);
	}
	
	player->SetInterval(Interval);
	SetWave(pastel);
	wave->Update();
}

void ShockWave::Draw() {
	//ImGui::Begin("test");
	///*ImGui::SliderFloat("frame", &frame, 1, 0.0f);
	//ImGui::SliderFloat("frame2", &frame2, 1, 0.0f);
	//ImGui::Text("Move:%d", appearMove);*/
	//ImGui::SliderFloat("pos.x", &pos.x, 360, -360);
	//ImGui::SliderFloat("pos.y", &pos.y, 360, -360);
	//ImGui::SliderFloat("pos.z", &pos.z, 360, -360);
	//ImGui::End();
	
	if (expand) {
		wave->Draw();
	}
}

void ShockWave::Final() {
	delete wave;
}

//ボスによって衝撃波が走る
void ShockWave::SetWave(Pastel* pastel) {
	int pat = pastel->GetPat();
	int AttackPoint = pastel->GetAttackPoint();
	int action = pastel->GetAction();
	XMFLOAT3 pos = pastel->GetPosition();
	//衝撃波の位置を決める
	if (pat == 3 && pos.y == 2.0f && !expand && action == 0) {
		if (AttackPoint == 0 || AttackPoint == 1) {
			this->pos.x = pos.x + 7;
			this->pos.y = 0.0f;
			this->pos.z = pos.z;
		}
		else {
			this->pos.x = pos.x - 7;
			this->pos.y = 0.0f;
			this->pos.z = pos.z;
		}
		//this->pos = pos;
		expand = true;
	}

	if (expand == true) {
		scale.x += 0.05f;
		scale.y += 0.05f;
		scale.z += 0.05f;

		//衝撃波が広がる
		damegeArea += 0.12f;

		if (damegeArea >= 0.5f) {
			safeArea += 0.12f;
		}
		if (scale.x >= 20.0f) {
			expand = false;
			scale = { 0.0f,0.0f,0.0f };
			damegeArea = 0.0f;
			safeArea = 0.0f;
		}
	}

	wave->SetPosition(this->pos);
	wave->SetScale(scale);
}

bool ShockWave::CollideWave(Player* player) {
	XMFLOAT3 playerpos = player->GetPosition();
	
	if (Collision::SphereCollision(pos.x, pos.y, pos.z, damegeArea, playerpos.x, playerpos.y, playerpos.z, damegeArea)) {
		//DebugText::GetInstance()->Print("damegeHit", 0, 0, 2.0f);
		return true;
	}
	else {
		return false;
	}
}

bool ShockWave::CollideSafeWave(Player* player) {
	XMFLOAT3 playerpos = player->GetPosition();
	if (Collision::SphereCollision(pos.x, pos.y, pos.z, safeArea, playerpos.x, playerpos.y, playerpos.z, safeArea)) {
		//DebugText::GetInstance()->Print("safeHit", 0, 10, 2.0f);
		return true;
	}
	else {
		return false;
	}
}

