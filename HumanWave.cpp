#include "HumanWave.h"
#include "ImageManager.h"
#include"Collision.h"
#include "DebugText.h"
#include "imgui.h"
void HumanWave::Init() {
	wave = Texture::Create(ImageManager::enemy, { 0,0,0 }, { 12,12,12 }, { 1,1,1,0.6f });
	wave->TextureCreate();
	wave->SetPosition({ 0.0f,0.0f,0.0f });
	wave->SetRotation({ 90.0f, 0.0f, 0.0f });
	wave->SetScale(scale);
	//limit->SetScale({ 6,5,5 }); 
}

void HumanWave::Upda() {
	/*Interval = player->GetInterval();
	float playerhp = player->GetHp();
	if (CollideWave() && !CollideSafeWave() && Interval == 0 && player->GetPosition().y <= 1.0f) {
		player->SetHp(player->GetHp() - 1);
		Interval = 100;
	}

	player->SetInterval(Interval);*/
	wave->Update();
}

void HumanWave::Draw() {
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

void HumanWave::Final() {
	delete wave;
}

//ÕŒ‚”g‚ÌêŠŒˆ‚ß
void HumanWave::Set(const XMFLOAT3& pos) {
	this->pos = pos;
	wave->SetPosition(this->pos);
	if (!expand) {
		expand = true;
	}
}

//ƒ{ƒX‚É‚æ‚Á‚ÄÕŒ‚”g‚ª‘–‚é
void HumanWave::SetWave() {
	//ÕŒ‚”g‚ÌˆÊ’u‚ªŒˆ‚Ü‚Á‚Ä‚©‚ç
	if (expand == true) {
		scale.x += 0.05f;
		scale.y += 0.05f;
		scale.z += 0.05f;

		//ÕŒ‚”g‚ªL‚ª‚é
		damegeArea += 0.12f;

		if (damegeArea >= 0.5f) {
			safeArea += 0.12f;
		}
		if (scale.x >= 5.0f) {
			expand = false;
			scale = { 0.0f,0.0f,0.0f };
			damegeArea = 0.0f;
			safeArea = 0.0f;
		}
	}

	wave->SetPosition(this->pos);
	wave->SetScale(scale);
}


bool HumanWave::CollideWave() {
	XMFLOAT3 playerpos = player->GetPosition();

	if (Collision::SphereCollision(pos.x, pos.y, pos.z, damegeArea, playerpos.x, playerpos.y, playerpos.z, damegeArea)) {
		//DebugText::GetInstance()->Print("damegeHit", 0, 0, 2.0f);
		return true;
	}
	else {
		return false;
	}
}

bool HumanWave::CollideSafeWave() {
	XMFLOAT3 playerpos = player->GetPosition();
	if (Collision::SphereCollision(pos.x, pos.y, pos.z, safeArea, playerpos.x, playerpos.y, playerpos.z, safeArea)) {
		//DebugText::GetInstance()->Print("safeHit", 0, 10, 2.0f);
		return true;
	}
	else {
		return false;
	}
}

