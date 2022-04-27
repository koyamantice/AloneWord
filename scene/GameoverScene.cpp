#include "GameoverScene.h"
#include "Audio.h"
#include "input.h"
#include "DebugText.h"
#include "SceneManager.h"
#include "BossScene.h"
#include "GameoverScene.h"
#include"ImageManager.h"
void GameoverScene::Initialize(DirectXCommon* dxCommon) {

	//背景スプライト生成
	sprite = Sprite::Create(ImageManager::OVER, { 0.0f,0.0f });
	//スプライト生成
}

void GameoverScene::Update(DirectXCommon* dxCommon) {
	Input* input = Input::GetInstance();
	if (input->PushKey(DIK_RETURN) || input->TriggerButton(input->Button_B)) {
		Audio::GetInstance()->PlayWave("Resources/Sound/Button.wav", 0.4f);
		SceneManager::GetInstance()->ChangeScene("TITLE");
	}
	if ( input->TriggerButton(input->Button_X)) {
		Audio::GetInstance()->PlayWave("Resources/Sound/Button.wav", 0.4f);
		SceneManager::GetInstance()->ChangeScene("BOSS");
	}
	//DebugText::GetInstance()->Print("Buttun_B or ENTER to TITLE!!", 200, 100, 1.0f);
}

void GameoverScene::Draw(DirectXCommon* dxCommon) {
	sprite->PreDraw();
	//背景用
	sprite->Draw();
}


void GameoverScene::Finalize() {
	//３ｄのモデルのデリート
	delete sprite;
}

