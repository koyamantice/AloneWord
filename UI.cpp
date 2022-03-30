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
	XMFLOAT3 pla=player->GetPosition();
	XMFLOAT3 bos=boss->GetPosition();

	XMFLOAT2 pos;
	pos.x = (pla.x - bos.x);
	pos.y = (pla.z - bos.z);
	double posR = sqrt(pow(pla.x, 2) + pow(bos.z, 2));
	double Check = pos.x / posR;
	double Check2 = pos.y / posR;

	pos.x = (float)Check;
	pos.y = (float)Check2;

	Arrow->SetPosition(pos);







}

const void UI::Draw() {
	Sprite::PreDraw();
	BossHp->Draw();
	PlaHp->Draw();
}
