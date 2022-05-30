#include "TitleScene.h"
#include"SceneManager.h"
#include "Audio.h"
#include "input.h"
#include "DebugText.h"
#include"ImageManager.h"
#include <TisGame.h>
void TitleScene::Initialize(DirectXCommon* dxCommon) {
	// カメラ生成
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height);
	Texture::SetCamera(camera);
	// 3Dオブジェクトにカメラをセット
	Object3d::SetCamera(camera);
	// モデル読み込み
	Audio::GetInstance()->LoadSound(1, "Resources/Sound/titleBGM.wav");
	Audio::GetInstance()->LoopWave(1, 0.1f);
	//srand(NULL);
	// ライト生成
	lightGroup = LightGroup::Create();
	// 3Dオブエクトにライトをセット
	Object3d::SetLightGroup(lightGroup);

	//この順番で書かないと例外スローになります
	// デバイスをセット
	FBXObject3d::SetDevice(dxCommon->GetDev());
	// カメラをセット
	FBXObject3d::SetCamera(camera);
	// グラフィックスパイプライン生成
	FBXObject3d::CreateGraphicsPipeline();
	Player* player_ = new Player();
	player_->Initialize();
	player_->SetMove(50.0f, 50.0f);
	player_->SetPosition({ 0.0f,5.0f,-10.0f });
	player.reset(player_);
	//背景スプライト生成
	sprite[back] = Sprite::Create(ImageManager::TITLE, { 0.0f,0.0f });
	sprite[button] = Sprite::Create(ImageManager::button, buttonPos[0]);
	sprite[button]->SetAnchorPoint({ 0.5f,0.5f });
	//sprite[button]->SetScale(0.4f);
	sprite[select] = Sprite::Create(ImageManager::Tselect, { 76.0f,418.0f });
	//スプライト生成
	expandchange = new ExpandChange();
	shrinkchange = new ShrinkChange();
	shrinkchange->SetEndChange(true);
	save = new Save();
}
//開放処理
void TitleScene::Finalize() {
	//３ｄのモデルのデリート
	for (int i = 0; i < 4;i++) {
		delete sprite[i];
	}
	expandchange->Finalize();
	delete WhiteFilter;
	delete BlackFilter;
	delete GameOverSprite;
	delete bossName;
	delete SkipSprite;
	delete GameClearSprite;
	delete save;
}
//更新
void TitleScene::Update(DirectXCommon* dxCommon) {
	Input* input = Input::GetInstance();
	shrinkchange->Update();
	//どの選択をするかでどのシーンに行くか変わる
	if (expandchange->GetScale() == 1.0f) {
		if (input->LeftTriggerStick(input->Down) && (SelectNumber <= 1)) {
			Audio::GetInstance()->PlayWave("Resources/Sound/cursorMove.wav", 0.2f);
			SelectNumber++;
		}
		if (input->LeftTriggerStick(input->Up) && (SelectNumber >= 1)) {
			Audio::GetInstance()->PlayWave("Resources/Sound/cursorMove.wav", 0.2f);
			SelectNumber--;
		}
	}
	switch (SelectNumber) {
	case Start:
		buttonPos[0] = { 320.0f,465.0f };
		buttonPos[1] = { 440.0f,465.0f };
		break;
	case Select:
		buttonPos[0] = { 320.0f,543.0f };
		buttonPos[1] = { 440.0f,543.0f };
		break;
	case Exit:
		buttonPos[0] = { 320.0f,620.0f };
		buttonPos[1] = { 440.0f,620.0f };

		break;
	default:
		if (SelectNumber > Exit) {
			SelectNumber = Exit;
		}
		if (SelectNumber < Start) {
			SelectNumber = Start;
		}
		break;
	}
	if (input->TriggerButton(input->Button_A)) {
		Audio::GetInstance()->PlayWave("Resources/Sound/Button.wav", 0.4f);
		Audio::GetInstance()->StopWave(1);
		expandchange->SetStartChange(true);
	}

	/*if (input->TriggerButton(input->Button_Y)) {
		SceneManager::GetInstance()->ChangeScene("CLEAR");
	}*/

	if (expandchange->GetTimer() >= 58) {
		if (SelectNumber == Start) {
			SceneManager::GetInstance()->ChangeScene("STARTMAP");
		} 
		if (SelectNumber == Select){
			SceneManager::GetInstance()->ChangeScene("StageSelect");
		}
		if (SelectNumber == Exit) {
			SceneManager::GetInstance()->SetEnd(true);
		}
	}
	sprite[button]->SetPosition(buttonPos[0]);

	player->TitleUp();
	expandchange->Update();
	camera->Update();
	cameraPos.x = player->GetPosition().x;
	cameraPos.y = player->GetPosition().y + 4.0f;
	cameraPos.z = player->GetPosition().z - 6.0f;
	camera->SetTarget({0,0,0});
	camera->SetEye(cameraPos);
}
//描画
void TitleScene::Draw(DirectXCommon* dxCommon) {
	bool P = save->GetPerfectClear();
	//ImGui::Begin("test");
	////ImGui::SliderFloat("cameraPos.y", &cameraPos.y, 30, 0);
	//ImGui::Text("P::%d", P);
	//ImGui::Unindent();
	//ImGui::End();
	Sprite::PreDraw();
	//背景用
	sprite[back]->Draw();
	sprite[select]->Draw();
	sprite[select]->Draw();
	sprite[button]->Draw();

	player->Draw(dxCommon);

	Sprite::PreDraw();
	//前面用
	expandchange->Draw();
	if (save->GetPerfectClear() == true) {
		shrinkchange->Draw();
	}
}

