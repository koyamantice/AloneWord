#include "RightHumanWave.h"
#include "ImageManager.h"
#include"Collision.h"
#include "imgui.h"
void RightHumanWave::Init() {
	wave = Texture::Create(ImageManager::enemy, { 0,0,0 }, { 12,12,12 }, { 1,1,1,0.6f });
	wave->TextureCreate();
	wave->SetPosition({ 0.0f,0.0f,0.0f });
	wave->SetRotation({ 90.0f, 0.0f, 0.0f });
	wave->SetScale(scale);
	//limit->SetScale({ 6,5,5 }); 
}

void RightHumanWave::Upda(RightHand* righthand, Player* player) {
	XMFLOAT3 playerpos = player->GetPosition();
	float playerhp = player->GetHp();
	XMFLOAT3 distance = player->GetDistance();
	float weight = player->GetArmWeight();
	if (CollideWave(player) && !CollideSafeWave(player) && player->GetInterval() == 0 && player->GetPosition().y <= 1.0f) {
		Audio::GetInstance()->PlayWave("Resources/Sound/Damage.wav", 0.4f);
		player->SetHp(playerhp - 1.0f);
		player->SetCharge(0);
		player->SetRotCount(0);
		player->SetInterval(100);
		distance.x = playerpos.x - pos.x;
		distance.z = playerpos.z - pos.z;
		player->SetDistance(distance);
		player->SetJumpG(0.5f);
		player->SetDamageFlag(true);
		player->SetAttackFlag(false);
		if (weight != 0.0f) {
			weight = 0.0f;
			player->SetArmWeight(weight);
		}
	}

	SetWave(righthand);
	wave->Update();
}

void RightHumanWave::Draw() {
	//ImGui::Begin("test");
	///*ImGui::SliderFloat("frame", &frame, 1, 0.0f);
	//ImGui::SliderFloat("frame2", &frame2, 1, 0.0f);
	//ImGui::Text("Move:%d", appearMove);*/
	//ImGui::SliderFloat("damage", &damegeArea, 360, -360);
	//ImGui::SliderFloat("pos.x", &pos.x, 360, -360);
	//ImGui::SliderFloat("pos.y", &pos.y, 360, -360);
	//ImGui::SliderFloat("pos.z", &pos.z, 360, -360);
	//ImGui::End();

	if (expand) {
		wave->Draw();
	}
}

void RightHumanWave::Final() {
	delete wave;
}

//?{?X?ɂ????ďՌ??g??????
void RightHumanWave::SetWave(RightHand* righthand) {
	int action = righthand->GetAction();
	XMFLOAT3 pos = righthand->GetPosition();
	int pat = righthand->GetPat();
	float HP = righthand->GetHP();
	//?Ռ??g?̈ʒu?????߂?
	if (action == 0 && pos.y == 1.5f && pat == 5 && !expand && HP > 0 && righthand->GetCoolT() == 1) {
		this->pos.x = pos.x;
		this->pos.y = pos.y + 1.0f;
		this->pos.z = pos.z - 5.0f;
		expand = true;
	}

	if (expand == true) {
		scale.x += 0.05f;
		scale.y += 0.05f;
		scale.z += 0.05f;

		//?Ռ??g???L????
		damegeArea += 0.12f;

		if (damegeArea >= 0.5f) {
			safeArea += 0.12f;
		}
		if (scale.x >= 2.2f) {
			expand = false;
			scale = { 0.0f,0.0f,0.0f };
			damegeArea = 0.0f;
			safeArea = 0.0f;
		}
	}

	wave->SetPosition(this->pos);
	wave->SetScale(scale);
}

bool RightHumanWave::CollideWave(Player* player) {
	XMFLOAT3 playerpos = player->GetPosition();

	if (Collision::SphereCollision(pos.x, pos.y, pos.z, damegeArea, playerpos.x, playerpos.y, playerpos.z, damegeArea)) {
		return true;
	}
	else {
		return false;
	}
}

bool RightHumanWave::CollideSafeWave(Player* player) {
	XMFLOAT3 playerpos = player->GetPosition();
	if (Collision::SphereCollision(pos.x, pos.y, pos.z, safeArea, playerpos.x, playerpos.y, playerpos.z, safeArea)) {
		return true;
	}
	else {
		return false;
	}
}

