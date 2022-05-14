#include "UI.h"
#include <Easing.h>
#include <ImageManager.h>
UI::UI(Player* player, InterBoss* boss, InterBoss* boss2) {
	this->player = player;
	this->boss = boss;
	this->boss2 = boss2;
	BossHp = Sprite::Create(ImageManager::playerHp, { 0.0f,0.0f });
	BossHp->SetPosition({ 260.0f,20.0f });
	BossHp->SetColor({ 1.0f,0.0f,0.0,1.0 });
	BossHp2 = Sprite::Create(ImageManager::playerHp, { 0.0f,0.0f });
	BossHp2->SetPosition({ 260.0f,80.0f });
	BossHp2->SetColor({ 1.0f,0.0f,0.0,1.0 });
	//HPスプライト生成
	HpGauge = Sprite::Create(ImageManager::hpGauge, { 0.0f,0.0f });
	HpGauge->SetPosition({ 22.0f,560.0f });
	Mark1 = Sprite::Create(ImageManager::energy, { 0.0f,0.0f });
	Mark1->SetPosition({ 30.0f,576.0f });
	Mark1->SetSize({ 120.0f,120.0f });
	Mark2 = Sprite::Create(ImageManager::pinch, { 0.0f,0.0f });
	Mark2->SetPosition({ 0.0f,642.0f });
	Mark3 = Sprite::Create(ImageManager::weak, { 0.0f,0.0f });
	Mark3->SetPosition({ 0.0f,642.0f });
	PlaHp = Sprite::Create(ImageManager::playerHp, { 0.0f,0.0f });
	PlaHp->SetPosition({ 163.0f,632.0f });
	//背景スプライト生成
	Life = Sprite::Create(ImageManager::life, { 0.0f,0.0f });
	Life->SetPosition({ 20.0f,620.0f });
	Arrow = Sprite::Create(ImageManager::arrow, { 0.0f,0.0f });
	Arrow->SetAnchorPoint({ 0.5f,0.5f });
	Arrow->SetIsFlipY(true);
	Arrow->SetPosition({ 0,0 });
	Arrow2 = Sprite::Create(ImageManager::arrow, { 0.0f,0.0f });
	Arrow2->SetIsFlipY(true);
	Arrow2->SetPosition({ 0,0 });
	Vignette = Sprite::Create(ImageManager::vignette, { 0.0f,0.0f });
	Vignette->SetPosition({ 0,0 });
	Vignette->SetColor({ 255,255,255,0.75f });
	bairitu = Sprite::Create(ImageManager::bairitu, { 1240.0f,10.0f });
	bairitu->SetAnchorPoint({ 1.0f,0.0f });
	bairitu->SetScale(0.7f);
	const int w = 48;
	const int h = 80;
	const int l = 10;
	const float onePos = WinApp::window_width - 208.0f;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 10; j++) {
			number[i][j] = Sprite::Create(ImageManager::GetIns()->num,{ 0,0});
			int number_index_y = j / l;
			int number_index_x = j % l;
			number[i][j]->SetTextureRect(
				{ static_cast<float>(number_index_x) * w, static_cast<float>(number_index_y) * h },
				{ static_cast<float>(w), static_cast<float>(h) });
			number[i][j]->SetSize({ w,h });
			if (i>0) {
				number[i][j]->SetScale(1.0f);
			}
			else {
				number[i][j]->SetScale(0.8f);
			}
			number[i][j]->SetAnchorPoint({ 0,0 });
		}
	}
	for (int j = 0; j < 10; j++) {
		number[0][j]->SetPosition(pos);
		number[1][j]->SetPosition(pos2);
	}
}
void UI::Update() {
	{//HP
		AfterPos[1] = { (float)(player->GetHp() * 43),55 };
		plaPos = {
		Ease(In,Quad,0.7f,(float)PlaHp->GetSize().x,(float)AfterPos[1].x),
		Ease(In,Quint,0.7f,(float)PlaHp->GetSize().y,(float)AfterPos[1].y),
		};
		PlaHp->SetSize(plaPos);
	}
	if (Up) {
		EaseScale();
	}
	if (boss) {
		AfterPos[0] = { (float)(boss->GetHP() * 20),30 };
		bossPos = {
		Ease(In,Quint,0.7f,BossHp->GetSize().x,AfterPos[0].x),
		Ease(In,Quint,0.7f,BossHp->GetSize().y,AfterPos[0].y),
		};
		BossHp->SetSize(bossPos);
		SeachBoss();
	}
	if (boss2) {
		AfterPos2[0] = { (float)(boss2->GetHP() * 20),30 };
		bossPos2 = {
		Ease(In,Quint,0.7f,BossHp2->GetSize().x,AfterPos2[0].x),
		Ease(In,Quint,0.7f,BossHp2->GetSize().y,AfterPos2[0].y),
		};
		BossHp2->SetSize(bossPos2);
		SeachBoss2();
	}
}

void UI::Finalize() {
	delete BossHp;
	delete BossHp2;
	delete HpGauge;
	delete Mark1;
	delete PlaHp;
	delete Arrow;
	delete Arrow2;
}

const void UI::Draw() {
	ImGui::Begin("test");
	ImGui::SliderFloat("rot.x", &pos.x, 270, -90);
	ImGui::SliderFloat("rot.y", &pos.y, 270, -90);
	//ImGui::SliderInt("dir", &dir, 360, -360);
	////ImGui::SliderFloat("speed_y", &speed_y, 360, 0);
	ImGui::SliderFloat("scale", &vel, 360, 0);
	////ImGui::Text("Count::%d", moveCount);
	////ImGui::Text("Move::%d", isMove);
	////ImGui::Text("Hit::%d", hit);
	////ImGui::Unindent();
	ImGui::End();
	Sprite::PreDraw();
	//Vignette->Draw();
	if (boss) {
		BossHp->Draw();
	}
	if (boss2) {
		BossHp2->Draw();
	}
	HpGauge->Draw();
	Mark1->Draw();
	PlaHp->Draw();
	//Life->Draw();

	if (boss && invisible && boss->GetHP() >= 1) {
		Arrow->Draw();
	}

	if (boss2 && invisible && boss2->GetHP() >= 1) {
		Arrow2->Draw();
	}
	for (int i = 0; i < power.size() && i < 2; i++) {
		number[i][power[i]]->Draw();
	}
	bairitu->Draw();
}

void UI::EaseScale() {
	//strong = 2;
	//strong *= 10;
	strong = strong;
	power.clear();
	for (int tmp = strong; tmp > 0;) {
		power.push_back(tmp % 10);
		tmp /= 10;
	}
	//pos.x = Ease(In,Quad,frame, (float)WinApp::window_width - 70, (float)WinApp::window_width - 90);
	//pos.y = Ease(In, Quad, frame, 21 + 80, 40 + 80);
	vel = Ease(In, Quad, frame, 1.3f, 1.1f);

	if (frame > 1.2f) {
		frame = 0.0f;
		Up = false;
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 10; j++) {
				number[i][j]->SetSize({ 48,80 });
				if (i > 0) {
					number[i][j]->SetScale(1.0f);
				} else {
					number[i][j]->SetScale(0.8f);
				}
			}
		}
	} else {
		frame += 0.3f;
	}

	for (int i = 0; i < power.size() && i < 2; i++) {
		number[i][power[i]]->SetScale(vel);
	}
}

void UI::SeachBoss() {
	XMFLOAT3 pla = player->GetPosition();
	XMFLOAT3 bos = boss->GetPosition();
	XMFLOAT3 position{};
	float radius = 0;
	XMFLOAT2 rot{};
	position.x = (pla.x - bos.x);
	position.z = (pla.z - bos.z);

	radius = atan2f(position.x, position.z);// *PI / 180.0f;
	circle.x = (sin(-radius)*150.0f)+WinApp::window_width/2; //*0.2251f;
	circle.y = (cos(-radius)*150.0f)+WinApp::window_height/2; //*0.2251f;
	if ((boss->GetPosition().x > player->GetPosition().x+8.0f||
		boss->GetPosition().x < player->GetPosition().x - 8.0f)||
		(boss->GetPosition().z > player->GetPosition().z + 8.0f ||
		boss->GetPosition().z < player->GetPosition().z - 8.0f)){
		invisible = 1;
	} else {
		invisible = 0;
	}
	Arrow->SetRotation(radius * (180.0f / XM_PI));//-radius * PI / 180.0f);
	Arrow->SetPosition(circle);
}

void UI::SeachBoss2() {
	XMFLOAT3 pla = player->GetPosition();
	XMFLOAT3 bos = boss2->GetPosition();
	XMFLOAT3 position{};
	float radius = 0;
	XMFLOAT2 rot{};
	position.x = (pla.x - bos.x);
	position.z = (pla.z - bos.z);

	radius = atan2f(position.x, position.z);// *PI / 180.0f;
	circle2.x = (sin(-radius) * 150.0f) + WinApp::window_width / 2; //*0.2251f;
	circle2.y = (cos(-radius) * 150.0f) + WinApp::window_height / 2; //*0.2251f;

	if ((boss->GetPosition().x > player->GetPosition().x + 10.0f ||
		boss->GetPosition().x < player->GetPosition().x - 10.0f) ||
		(boss->GetPosition().z > player->GetPosition().z + 10.0f ||
		boss->GetPosition().z < player->GetPosition().z - 10.0f)) {
		invisible = 0;
	}
	else {
		invisible = 1;
	}
	Arrow2->SetRotation(radius * (180.0f / XM_PI));//-radius * PI / 180.0f);
	Arrow2->SetPosition(circle2);
}
