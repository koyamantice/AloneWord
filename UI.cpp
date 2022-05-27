#include "UI.h"
#include <Easing.h>
#include <ImageManager.h>
#include"Collision.h"
#include <Input.h>
//コンストラクタ
UI::UI(Player* player, InterBoss* boss, InterBoss* boss2) {
	this->player = player;
	this->boss = boss;
	this->boss2 = boss2;
	BossHp[max] = Sprite::Create(ImageManager::Enemyhp3, { 0.0f,0.0f });
	BossHp[max]->SetPosition({ 260.0f,20.0f });

	//BossHp[max]->SetColor({ 1.0f,0.0f,0.0f,1.0f });
	BossHp[damage] = Sprite::Create(ImageManager::Enemyhp2, { 0.0f,0.0f });
	BossHp[damage]->SetPosition({ 260.0f,20.0f });
	//BossHp[damage]->SetColor({ 1.0f,1.0f,0.0f,1.0f });
	BossHp[now] = Sprite::Create(ImageManager::Enemyhp, { 0.0f,0.0f });
	BossHp[now]->SetPosition({ 260.0f,20.0f });
	//BossHp[now]->SetColor({ 0.0f,1.0f,0.0f,1.0f });
	if (boss) {
		BossMaxHp[0] = boss->GetHP();
		AfterPos[0] = { (float)(boss->GetHP() * (800 / BossMaxHp[0])),75 };
	}
	BossHp[max]->SetSize(AfterPos[0]);
	BossHp[damage]->SetSize(AfterPos[0]);
	BossHp[now]->SetSize(AfterPos[0]);
	BossHp2[max] = Sprite::Create(ImageManager::Enemyhp3, { 0.0f,0.0f });
	BossHp2[max]->SetPosition({ 260.0f,70.0f });
	//BossHp2[max]->SetColor({ 1.0f,0.0f,0.0f,1.0f });
	BossHp2[damage] = Sprite::Create(ImageManager::Enemyhp2, { 0.0f,0.0f });
	BossHp2[damage]->SetPosition({ 260.0f,70.0f });
	//BossHp2[damage]->SetColor({ 1.0f,1.0f,0.0f,1.0f });
	BossHp2[now] = Sprite::Create(ImageManager::Enemyhp, { 0.0f,0.0f });
	BossHp2[now]->SetPosition({ 260.0f,70.0f });
	//BossHp2[now]->SetColor({ 0.0f,1.0f,0.0f,1.0f });
	if (boss2) {
		BossMaxHp[1] = boss2->GetHP();
		AfterPos2[0] = { (float)(boss2->GetHP() * (400/ BossMaxHp[1])),75 };
	}
	BossHp2[max]->SetSize(AfterPos2[0]);
	BossHp2[damage]->SetSize(AfterPos2[0]);
	BossHp2[now]->SetSize(AfterPos2[0]);

	//HPスプライト生成
	HpGauge = Sprite::Create(ImageManager::hpGauge, { 0.0f,0.0f });
	HpGauge->SetPosition({ 22.0f,560.0f });
	Mark[energy] = Sprite::Create(ImageManager::energy, { 0.0f,0.0f });
	Mark[energy]->SetPosition({ 30.0f,576.0f });
	Mark[energy]->SetSize({ 120.0f,120.0f });
	Mark[pinch] = Sprite::Create(ImageManager::pinch, { 0.0f,0.0f });
	Mark[pinch]->SetPosition({ 30.0f,576.0f });;
	Mark[weak] = Sprite::Create(ImageManager::weak, { 0.0f,0.0f });
	Mark[weak]->SetPosition({ 30.0f,576.0f });
	PlaHp[max] = Sprite::Create(ImageManager::playerHp, { 0.0f,0.0f });
	PlaHp[max]->SetPosition({ 163.0f,632.0f });
	PlaHp[max]->SetColor({ 1.0f,0.0f,0.0f,1.0f });
	PlaHp[damage] = Sprite::Create(ImageManager::playerHp, { 0.0f,0.0f });
	PlaHp[damage]->SetPosition({ 163.0f,632.0f });
	PlaHp[damage]->SetColor({ 1.0f,1.0f,0.0f,1.0f });
	PlaHp[now] = Sprite::Create(ImageManager::playerHp, { 0.0f,0.0f });
	PlaHp[now]->SetPosition({ 163.0f,632.0f });
	PlaHp[now]->SetColor({ 0.0f,1.0f,0.0f,1.0f });
	
	
	Sprite*SPD_ = Sprite::Create(ImageManager::SPD, { 0.0f,0.0f });
	SPD_->SetPosition({ 30.0f,576.0f });
	SPD_->SetScale(1.3f);
	SPD.reset(SPD_);


	//背景スプライト生成
	Life = Sprite::Create(ImageManager::life, { 0.0f,0.0f });
	Life->SetPosition({ 20.0f,620.0f });
	Arrow = Sprite::Create(ImageManager::arrow, { 0.0f,0.0f });
	Arrow->SetAnchorPoint({ 0.5f,0.5f });
	Arrow->SetIsFlipY(true);
	Arrow->SetPosition({ 0,0 });
	Arrow2 = Sprite::Create(ImageManager::arrow2, { 0.0f,0.0f });
	Arrow2->SetAnchorPoint({ 0.5f,0.5f });
	Arrow2->SetIsFlipY(true);
	Arrow2->SetPosition({ 0,0 });
	bairitu = Sprite::Create(ImageManager::bairitu, { 1240.0f,10.0f });
	bairitu->SetAnchorPoint({ 1.0f,0.0f });
	bairitu->SetScale(0.7f);
	SpinGauge = Sprite::Create(ImageManager::SpinGauge, { 0.0f,0.0f });
	const int w = 54;
	const int h = 60;
	const int l = 10;
	const float onePos = WinApp::window_width - 208.0f;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 10; j++) {
			number[i][j] = Sprite::Create(ImageManager::GetIns()->num, { 0,0 });
			int number_index_y = j / l;
			int number_index_x = j % l;
			number[i][j]->SetTextureRect(
				{ static_cast<float>(number_index_x) * w, static_cast<float>(number_index_y) * h },
				{ static_cast<float>(w), static_cast<float>(h) });
			number[i][j]->SetSize({ w,h });
			if (i > 0) {
				number[i][j]->SetScale(2.4f);
			} else {
				number[i][j]->SetScale(1.6f);
			}
			number[i][j]->SetAnchorPoint({ 0,0 });
		}
	}
	for (int j = 0; j < 10; j++) {
		number[0][j]->SetPosition(pos);
		number[1][j]->SetPosition(pos2);
	}
	for (int i = 0; i < 2; i++) {
		if (i > 0) {
			number[i][0]->SetScale(0.4f);
		} else {
			number[i][0]->SetScale(0.3f);
		}
	}
	SpinPos[0] = { 1200.0f,500.0f };
	SpinPos[1] = { 1200.0f,670.0f };
	for (int i = 0; i < 3; i++) {
		SpinBar[i] = Sprite::Create(ImageManager::SpinBar, { 0.0f,0.0f });
		SpinBar[i]->SetSize({ 60,0 });
		SpinBar[i]->SetAnchorPoint({ 0.5f,1.0f });
		SpinBar[i]->SetScale(1.5f);
		SpinBar[i]->SetPosition(SpinPos[1]);
	}
	SpinBar[0]->SetColor({ 1.0f,1.0f,1.0f,1.0f });
	SpinBar[1]->SetColor({ 1.0f,1.0f,0.0f,1.0f });
	SpinBar[2]->SetColor({ 1.0f,0.0f,0.0f,1.0f });

	SpinGauge->SetScale(1.5f);
	SpinGauge->SetAnchorPoint({ 0.5f,0.5f });
	SpinGauge->SetPosition(SpinPos[0]);
	//
	Skip = Sprite::Create(ImageManager::textSkip, { 0.0f,0.0f });

}
//更新
void UI::Update() {
	{//HP
		AfterPos[1] = { (float)(player->GetHp() * 43),55 };
		plaPos[0] = {
		Ease(In,Quad,0.7f,(float)PlaHp[now]->GetSize().x,(float)AfterPos[1].x),
		Ease(In,Quint,0.7f,(float)PlaHp[now]->GetSize().y,(float)AfterPos[1].y),
		};
		plaPos[1] = {
		Ease(In,Quad,0.2f,(float)PlaHp[damage]->GetSize().x,(float)AfterPos[1].x),
		Ease(In,Quint,0.2f,(float)PlaHp[damage]->GetSize().y,(float)AfterPos[1].y),
		};
		PlaHp[now]->SetSize(plaPos[0]);
		PlaHp[damage]->SetSize(plaPos[1]);
	}
	if (strong != player->GetArmWeight()) {
		if (!Up) {
			Up = true;
		}
	}
	if (Up) {
		EaseScale();
	}
	if (boss&&!boss2) {
		AfterPos[0] = { (float)(boss->GetHP() * (800 / BossMaxHp[0])),75 };
		bossPos[0] = {
		Ease(In,Quint,0.7f,BossHp[now]->GetSize().x,AfterPos[0].x),
		75,
		};
		bossPos[1] = {
		Ease(In,Quint,0.5f,BossHp[damage]->GetSize().x,AfterPos[0].x),
		75,
		};
		BossHp[damage]->SetSize(bossPos[1]);
		BossHp[now]->SetSize(bossPos[0]);
		SeachBoss();
	}
	if (boss2&&boss) {
		AfterPos[0] = { (float)(boss->GetHP() * (400 / BossMaxHp[0])),75 };
		AfterPos2[0] = { (float)(boss2->GetHP() * (400 / BossMaxHp[1])),75 };
		bossPos[0] = {Ease(In,Quint,0.7f,BossHp[now]->GetSize().x,AfterPos[0].x),75,};
		bossPos[1] = {Ease(In,Quint,0.5f,BossHp[damage]->GetSize().x,AfterPos[0].x),75,};
		BossHp[max]->SetSize({ 400,75 });
		BossHp[damage]->SetSize(bossPos[1]);
		BossHp[now]->SetSize(bossPos[0]);
		for (int i = 0; i < now + 1; i++) {
			BossHp[i]->SetPosition({90.0f,20.0f });
		}
		bossPos2[0] = {
		Ease(In,Quint,0.7f,BossHp2[now]->GetSize().x,AfterPos2[0].x),
		75,
		};
		bossPos2[1] = {
		Ease(In,Quint,0.5f,BossHp2[damage]->GetSize().x,AfterPos2[0].x),
		75,
		};
		for (int i = 0; i < now + 1; i++) {
			BossHp2[i]->SetPosition({ 800.0f,20.0f });
		}
		BossHp2[max]->SetSize({ 400,75 });
		BossHp2[damage]->SetSize(bossPos2[1]);
		BossHp2[now]->SetSize(bossPos2[0]);
		SeachBoss();
		SeachBoss2();
	}
	//スタミナ的なやつ
	if (!player->GetAttackFlag()) {
		if (Input::GetInstance()->PushButton(Input::GetInstance()->Button_A)) {
			if (player->GetChargeTimer() <= 100){ nowBar = 0; }
			if (player->GetChargeTimer() > 100) { nowBar = 1; }
			if (player->GetChargeTimer() > 200) { nowBar = 2; }
			convert = (float)player->GetChargeTimer();
			switch (nowBar) {
			case 0:
				AfterSpin[0].y = (convert/100)* 350.0f;
				SpinBar[1]->SetSize({ 60.0f,0.0f });
				AfterSpin[1].y = 0.0f;
				SpinBar[2]->SetSize({ 60.0f,0.0f });
				AfterSpin[2].y = 0.0f;

				break;
			case 1:
				SpinBar[0]->SetSize({ 60.0f,350.0f });
				AfterSpin[0].y = 350.0f;
				AfterSpin[1].y = ((float)((int)convert % 101) / 100) * 350.0f;
				break;
			case 2:
				SpinBar[0]->SetSize({ 60.0f,350.0f });
				AfterSpin[0].y = 350.0f;
				SpinBar[1]->SetSize({ 60.0f,350.0f });
				AfterSpin[1].y = 350.0f;
				if (convert<300) {
					AfterSpin[2].y = ((float)((int)convert % 100) / 100) * 350.0f;
				} else {
					AfterSpin[2].y = 350.0f;
				}
				break;
			default:
				assert("不正なエラー");
				break;
			}
			for (int i = 0; i < nowBar + 1; i++) {
				SpinSize[i] = {
				60,
				Ease(In,Quint,0.7f,SpinBar[i]->GetSize().y,AfterSpin[i].y) };
				SpinBar[i]->SetSize(SpinSize[i]);
			}
		} else {
			for (int i = 0; i < 3; i++) {
				SpinSize[i] = {
				60,
				Ease(In,Quint,0.7f,SpinBar[i]->GetSize().y,0) };
				SpinBar[i]->SetSize(SpinSize[i]);
			}
		}
	} else {
		convert =(float) player->GetRotTimer();
		if (convert <= 600) { nowBar = 2; }
		if (convert <= 400) { nowBar = 1; }
		if (convert <= 200) { nowBar = 0; }
		switch (nowBar) {
		case 0:
			AfterSpin[0].y = (convert / 200) * 350.0f;
			SpinBar[1]->SetSize({ 60.0f,0.0f });
			AfterSpin[1].y = 0.0f;
			break;
		case 1:
			SpinBar[0]->SetSize({ 60.0f,350.0f });
			AfterSpin[0].y = 350.0f;
			AfterSpin[1].y = ((float)((int)convert % 201) / 200) * 350.0f;
			SpinBar[2]->SetSize({ 60.0f,0.0f });
			AfterSpin[2].y = 0.0f;
			break;
		case 2:
			SpinBar[0]->SetSize({ 60.0f,350.0f });
			AfterSpin[0].y = 350.0f;
			SpinBar[1]->SetSize({ 60.0f,350.0f });
			AfterSpin[1].y = 350.0f;
			AfterSpin[2].y = ((float)((int)convert % 200) / 200) * 350.0f;
			break;
		default:
			assert("不正なエラー");
			break;
		}
		for (int i = 0; i < nowBar + 1; i++) {
			SpinSize[i] = {
			60,
			Ease(In,Quint,0.7f,SpinBar[i]->GetSize().y,AfterSpin[i].y) };
			SpinBar[i]->SetSize(SpinSize[i]);
		}
	}
}

//開放
void UI::Finalize() {
	for (int i = 0; i < 3; i++) {
		delete BossHp[i];
		delete BossHp2[i];
		delete PlaHp[i];
		delete Mark[i];
	}
	delete Skip;
	delete HpGauge;
	delete Arrow;
	delete Arrow2;
}

//描画
const void UI::Draw() {

	Sprite::PreDraw();
	if (boss) {
		BossHp[max]->Draw();
		BossHp[damage]->Draw();
		BossHp[now]->Draw();
	}

	if (boss2) {
		BossHp2[max]->Draw();
		BossHp2[damage]->Draw();
		BossHp2[now]->Draw();
	}

	if (!isInvisible) {
		HpGauge->Draw();
		if (player->GetHp() > 7) {
			Mark[energy]->Draw();
		} else if (player->GetHp() > 3) {
			Mark[pinch]->Draw();
		} else {
			Mark[weak]->Draw();
		}
		SPD->Draw();
		PlaHp[max]->Draw();
		PlaHp[damage]->Draw();
		PlaHp[now]->Draw();
	}
	if (boss && invisible[0] && boss->GetHP() >= 1) {
		Arrow->Draw();
	}

	if (boss2 && invisible[1] && boss2->GetHP() >= 1) {
		Arrow2->Draw();
	}
	if (player->GetAttackFlag()) {
		if (power.size() != 0) {
			bairitu->Draw();
			for (int i = 0; i < power.size() && i < 2; i++) {
				number[i][power[i]]->Draw();
			}
		}
		for (int i = 0; i < 3; i++) {
			SpinBar[i]->Draw();
		}
		SpinBar[nowBar]->Draw();
		SpinGauge->Draw();
	}
	if (!player->GetAttackFlag()) {
		if (Input::GetInstance()->PushButton(Input::GetInstance()->Button_A)) {
			for (int i = 0; i < 3; i++) {
				SpinBar[i]->Draw();
			}
			SpinBar[nowBar]->Draw();
			SpinGauge->Draw();
		}
	}
}

void UI::SkipUpda() {
	if (Input::GetInstance()->AllNoPush()) {
		count++;
		if (count>100) {
			Skipframe += 0.03f;
		}
	} else {
		if (!back) {
			back = true;
		}
	}
	if (back) {
		if (Skipframe > 0.0f) {
			Skipframe -= 0.05f;
		} else {
			back = false;
		}
	}
	if (Skipframe>1.0f) {
		Skipframe = 1.0f;
		count = 0;
	}
	if (Skipframe < 0.0f) {
		Skipframe = 0.0f;
	}
	SkipPos.x = Ease(In,Quad,Skipframe,-408,0);
	Skip->SetPosition(SkipPos);
}

const void UI::SkipDraw() {
	Sprite::PreDraw();
	Skip->Draw();
}


void UI::EaseScale() {
	//strong = 2;
	//strong *= 10;
	strong = player->GetArmWeight() * 5;
	power.clear();
	for (int tmp = (int)strong; tmp > 0;) {
		power.push_back(tmp % 10);
		tmp /= 10;
	}
	strong = player->GetArmWeight();
	//pos.x = Ease(In,Quad,frame, (float)WinApp::window_width - 70, (float)WinApp::window_width - 90);
	//pos.y = Ease(In, Quad, frame, 21 + 80, 40 + 80);
	vel = Ease(In, Quad, frame, 1.3f, 1.1f);

	if (frame > 1.2f) {
		frame = 0.0f;
		Up = false;
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 10; j++) {
				number[i][j]->SetSize({ 48,48 });
				if (i > 0) {
					number[i][j]->SetScale(2.4f);
				} else {
					number[i][j]->SetScale(1.6f);
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
	circle.x = (sin(-radius) * 150.0f) + WinApp::window_width / 2; //*0.2251f;
	circle.y = (cos(-radius) * 150.0f) + WinApp::window_height / 2; //*0.2251f;
	if (!Collision::CircleCollision(bos.x, bos.z, 18.0f, pla.x, pla.z, 1.0f)) {
		invisible[0] = 1;
	} else {
		invisible[0] = 0;
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
	circle2.x = (sin(-radius) * 100.0f) + WinApp::window_width / 2; //*0.2251f;
	circle2.y = (cos(-radius) * 100.0f) + WinApp::window_height / 2; //*0.2251f;

	if (!Collision::CircleCollision(bos.x, bos.z, 18.0f, pla.x, pla.z, 1.0f)) {
		invisible[1] = 1;
	} else {
		invisible[1] = 0;
	}
	Arrow2->SetRotation(radius * (180.0f / XM_PI));//-radius * PI / 180.0f);
	Arrow2->SetPosition(circle2);
}
