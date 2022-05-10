#include "TitleScene.h"
#include"SceneManager.h"
#include "Audio.h"
#include "input.h"
#include "DebugText.h"
#include"ImageManager.h"
void TitleScene::Initialize(DirectXCommon* dxCommon) {

	//背景スプライト生成
	sprite = Sprite::Create(ImageManager::TITLE, { 0.0f,0.0f });
	//スプライト生成


}

void TitleScene::Finalize() {
	//３ｄのモデルのデリート
	delete sprite;
}

void TitleScene::Update(DirectXCommon* dxCommon) {
	Input* input = Input::GetInstance();
	if (input->PushKey(DIK_RETURN) || input->TriggerButton(input->Button_X)) {
		Audio::GetInstance()->PlayWave("Resources/Sound/Button.wav", 0.4f);
		SceneManager::GetInstance()->ChangeScene("StageSelect");
	}
	else if (input->TriggerButton(input->Button_A)) {
		Audio::GetInstance()->PlayWave("Resources/Sound/Button.wav", 0.4f);
		SceneManager::GetInstance()->ChangeScene("STARTMAP");
	}
	//if (input->PushKey(DIK_SPACE) || input->TriggerButton(input->Button_X)) {
	//	SceneManager::GetInstance()->ChangeScene("SECONDBOSS");
	//}
	//if (input->PushKey(DIK_SPACE) || input->TriggerButton(input->Button_Y)) {
	//	SceneManager::GetInstance()->ChangeScene("FOURTHBOSS");
	//}
	//if (input->PushKey(DIK_3)) {
	//	SceneManager::GetInstance()->ChangeScene("THIRDBOSS");
	//}
	//DebugText::GetInstance()->Print("Button_A to STARTMAP!!", 100, 100, 1.5f);
	//DebugText::GetInstance()->Print("SPACE to BOSS!!", 100, 130, 1.5f);

}

void TitleScene::Draw(DirectXCommon* dxCommon) {
	sprite->PreDraw();
	//背景用
	sprite->Draw();

	//前面用

}

