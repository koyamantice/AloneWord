#include "UI.h"
#include <Easing.h>


UI::UI(Player* player, BossEnemy* boss) {
	this->player = player;
	this->boss = boss;
	Sprite::LoadTexture(3, L"Resources/2d/PlayerHP.png");
	Sprite::LoadTexture(4, L"Resources/2d/Arrow.png");
	BossHp = Sprite::Create(3, { 0.0f,0.0f });
	BossHp->SetColor({ 0.0f,1.0f,0.0,1.0 });
	//背景スプライト生成
	PlaHp = Sprite::Create(3, { 0.0f,0.0f });
	PlaHp->SetPosition({ 0.0f,520.0f });
	Arrow = Sprite::Create(4, { 0.0f,0.0f });
	Arrow->SetPosition({0,0});
}
void UI::Update() {
	{//HPˆ—
		AfterPos[0] = { (float)(boss->GetHP() * 20),30 };
		bossPos = {
		Ease(In,Quint,0.7f,BossHp->GetSize().x,AfterPos[0].x),
		Ease(In,Quint,0.7f,BossHp->GetSize().y,AfterPos[0].y),
		};
		BossHp->SetSize(bossPos);
		AfterPos[1] = { (float)(player->GetHp() * 30),20 };
		plaPos = {
		Ease(In,Quint,0.7f,(float)PlaHp->GetSize().x,(float)AfterPos[1].x),
		Ease(In,Quint,0.7f,(float)PlaHp->GetSize().y,(float)AfterPos[1].y),
		};
		PlaHp->SetSize(plaPos);
	}




	if (boss) {
		SeachBoss();
	}


}

const void UI::Draw() {
	ImGui::Begin("test");
	if (ImGui::TreeNode("Debug")) {
		if (ImGui::TreeNode("UI")) {
			ImGui::SliderFloat("power1", &Check, 50, -50);
			ImGui::SliderFloat("power2", &Check2, 50, -50);
			ImGui::SliderFloat("power3", &pos.x, 50, -50);
			ImGui::SliderFloat("power4", &pos.y, 50, -50);
			ImGui::SliderFloat("power5", &pos.z, 50, -50);

			//ImGui::Text("Sub %d", SpeedSub);

			ImGui::Unindent();
			ImGui::TreePop();
		}
		ImGui::TreePop();
	}
	ImGui::End();
	Sprite::PreDraw();
	BossHp->Draw();
	PlaHp->Draw();
	if (invisible) {
		Arrow->Draw();
	}
}

void UI::SeachBoss() {

	radius = speed * PI / 180.0f;
	circle.x = cosf(radius) * scale;
	circle.y = sinf(radius) * scale;
	ArrowPos.x = circle.x + basePos.x;
	ArrowPos.y = circle.y + basePos.y;
	speed++;

	XMFLOAT3 pla = player->GetPosition();
	XMFLOAT3 bos = boss->GetPosition();

	pos.x = (pla.x - bos.x);
	pos.z = (pla.z - bos.z);
	pos.y = sqrt(pow(pla.x, 2) + pow(bos.z, 2));
	Check = pos.x / pos.y;
	Check2 = pos.z / pos.y;
	a = (float)Check;
	b = (float)Check2;

	if (fabs(Check)>3||fabs(Check2)>0.4f) {
		invisible = true;
	} else {
		invisible = false;

	}


	//if (Check > 0) {
	//	if (Check2 > 0) {
	//		ArrowPos.y = 400;
	//		ArrowPos.x = 700;
	//	} else {
	//		ArrowPos.y = 200;
	//		ArrowPos.x = 700;
	//	}
	//} else {
	//	if (Check2 > 0) {
	//		ArrowPos.y = 400;
	//		ArrowPos.x = 600;
	//	} else {
	//		ArrowPos.y = 200;
	//		ArrowPos.x = 600;
	//	}

	//}

	Arrow->SetPosition(ArrowPos);
}
