#include "StageSelect.h"
#include "ImageManager.h"
#include "Input.h"
#include"SceneManager.h"

void StageSelect::Initialize(DirectXCommon* dxCommon) {
	//”wŒiƒXƒvƒ‰ƒCƒg¶¬
	BackGround = Sprite::Create(ImageManager::SELECT, { 0.0f,0.0f });

}

void StageSelect::Finalize() {
	delete BackGround;
}

void StageSelect::Update(DirectXCommon* dxCommon) {
	input = Input::GetInstance();
	if (input->PushKey(DIK_1) || input->PushKey(DIK_RETURN) || input->TriggerButton(input->Button_A)) {
		Audio::GetInstance()->PlayWave("Resources/Sound/Button.wav", 0.4f);
		SceneManager::GetInstance()->ChangeScene("STARTMAP");
	}
	if (input->PushKey(DIK_SPACE) || input->PushKey(DIK_2) || input->TriggerButton(input->Button_X)) {
		SceneManager::GetInstance()->ChangeScene("SECONDBOSS");
	}

	if (input->PushKey(DIK_3)) {
		SceneManager::GetInstance()->ChangeScene("THIRDBOSS");
	}
	if (input->PushKey(DIK_4) || input->TriggerButton(input->Button_Y)) {
		SceneManager::GetInstance()->ChangeScene("FOURTHBOSS");
	}

}

void StageSelect::Draw(DirectXCommon* dxCommon) {
	Sprite::PreDraw();
	BackGround->Draw();

}
