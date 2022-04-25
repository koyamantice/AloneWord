#include "UI.h"
#include <Easing.h>

UI::UI(Player* player, InterBoss* boss) {
	this->player = player;
	this->boss = boss;
	Sprite::LoadTexture(3, L"Resources/2d/PlayerHP.png");
	Sprite::LoadTexture(4, L"Resources/2d/Arrow.png");
	Sprite::LoadTexture(5, L"Resources/2d/Life.png");
	Sprite::LoadTexture(6, L"Resources/2d/Vignette.png");
	BossHp = Sprite::Create(3, { 0.0f,0.0f });
	BossHp->SetPosition({ 260.0f,20.0f });
	BossHp->SetColor({ 1.0f,0.0f,0.0,1.0 });
	//背景スプライト生成
	PlaHp = Sprite::Create(3, { 0.0f,0.0f });
	PlaHp->SetPosition({ 170.0f,642.0f });
	//背景スプライト生成
	Life = Sprite::Create(5, { 0.0f,0.0f });
	Life->SetPosition({ 20.0f,620.0f });
	Arrow = Sprite::Create(4, { 0.0f,0.0f });
	Arrow->SetPosition({ 0,0 });
	Vignette = Sprite::Create(6, { 0.0f,0.0f });
	Vignette->SetPosition({ 0,0 });
	Vignette->SetColor({ 255,255,255,0.75f });
}
void UI::Update() {
	{//HPˆ—

		AfterPos[1] = { (float)(player->GetHp() * 30),20 };
		plaPos = {
		Ease(In,Quint,0.7f,(float)PlaHp->GetSize().x,(float)AfterPos[1].x),
		Ease(In,Quint,0.7f,(float)PlaHp->GetSize().y,(float)AfterPos[1].y),
		};
		PlaHp->SetSize(plaPos);
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
}

const void UI::Draw() {
	ImGui::Begin("test");
	if (ImGui::TreeNode("Debug")) {
		ImGui::SliderFloat("radius", &radius, 360, -360);
		ImGui::SliderFloat("pos.X", &circle.x, 1280, 0);
		ImGui::SliderFloat("pos.Y", &circle.y, 720, 0);
		//ImGui::Text("Sub %d", invisible);
		//ImGui::Unindent();
		ImGui::TreePop();
	}
	ImGui::End();
	Sprite::PreDraw();
	//Vignette->Draw();
	if (boss) {
		BossHp->Draw();
	}
	PlaHp->Draw();
	Life->Draw();

	if (boss && invisible) {
		Arrow->Draw();
	}
}

void UI::SeachBoss() {
	XMFLOAT3 pla = player->GetPosition();
	XMFLOAT3 bos = boss->GetPosition();
	XMFLOAT3 position{};
	position.x = (pla.x - bos.x);
	position.z = (pla.z - bos.z);

	radius = atan2f(position.x, position.z);// *PI / 180.0f;
	circle.x = (sin(-radius)*150.0f)+WinApp::window_width/2; //*0.2251f;
	circle.y = (cos(-radius)*150.0f)+WinApp::window_height/2; //*0.2251f;

	if (fabs(pos.x) > 15.00f || fabs(pos.z) > 15.00f) {
		invisible = 1;
	}else {
		invisible = 1;
	}

	Arrow->SetPosition(circle);
}
