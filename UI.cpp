#include "UI.h"
#include <Easing.h>

UI::UI(Player* player, BossEnemy* boss) {
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
	/*ImGui::Begin("test");
	if (ImGui::TreeNode("Debug")) {
		if (ImGui::TreeNode("UI")) {
			ImGui::SliderFloat("posx", &ArrowPos.x, 50, -50);
			ImGui::SliderFloat("posz", &ArrowPos.y, 50, -50);
			ImGui::Text("Sub %d", invisible);
			ImGui::Unindent();
			ImGui::TreePop();
		}
		ImGui::TreePop();
	}
	ImGui::End();*/
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

	radius = speed * PI / 180.0f;
	circle.x = cosf(radius) * scale;
	circle.y = sinf(radius) * scale;
	/*ArrowPos.x = circle.x + basePos.x;
	ArrowPos.y = circle.y + basePos.y;
	speed++;*/

	XMFLOAT3 pla = player->GetPosition();
	XMFLOAT3 bos = boss->GetPosition();
	//aX2bX = (aX - bX);
	//aY2bY = (aY - bY);
	//aR2bR = sqrt((aX2bX * aX2bX) + (aY2bY * aY2bY));
	//bX += aX2bX / aR2bR * speed;
	//bY += aY2bY / aR2bR * speed;
	pos.x = (bos.x - pla.x);
	pos.z = (bos.z - pla.z);
	posR = sqrt(pow(pos.x, 2) + pow(pos.z, 2));
	Check = pos.x / posR;
	Check2 = pos.z / posR;

	if (fabs(pos.x) > 15.00f || fabs(pos.z) > 15.00f) {
		invisible = 1;
	}

	else {
		invisible = 0;
	}

	if (Check > 0.3) {
		if (Check2 > 0.3) {
			ArrowPos.y = 200;
			ArrowPos.x = 700;
		} else if(Check2 < -0.3) {
			ArrowPos.y = 400;
			ArrowPos.x = 700;
		}
		else {
			ArrowPos.y = 300;
			ArrowPos.x = 700;
		}
	} else if(Check < -0.3) {
		if (Check2 > 0.3) {
			ArrowPos.y = 200;
			ArrowPos.x = 500;
		}
		else if (Check2 < -0.3) {
			ArrowPos.y = 400;
			ArrowPos.x = 500;
		}
		else {
			ArrowPos.y = 300;
			ArrowPos.x = 500;
		}
	}
	else {
		if (Check2 > 0.3) {
			ArrowPos.y = 200;
			ArrowPos.x = 600;
		}
		else if (Check2 < -0.3) {
			ArrowPos.y = 400;
			ArrowPos.x = 600;
		}
		else {
			ArrowPos.y = 300;
			ArrowPos.x = 600;
		}
	}

	Arrow->SetPosition(ArrowPos);
}
