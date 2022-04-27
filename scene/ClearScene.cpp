#include "ClearScene.h"
#include "Audio.h"
#include "input.h"
#include "DebugText.h"
#include "SceneManager.h"
#include "BossScene.h"
#include "ClearScene.h"
#include"ImageManager.h"
void ClearScene::Initialize(DirectXCommon* dxCommon) {
	//�w�i�X�v���C�g����
	sprite = Sprite::Create(ImageManager::CLEAR, { 0.0f,0.0f });
	//�X�v���C�g����
}

void ClearScene::Update(DirectXCommon* dxCommon) {
	Input* input = Input::GetInstance();
	if (input->PushKey(DIK_RETURN) || input->TriggerButton(input->Button_B)) {
		Audio::GetInstance()->PlayWave("Resources/Sound/Button.wav", 0.4f);
		SceneManager::GetInstance()->ChangeScene("TITLE");
	}
	//DebugText::GetInstance()->Print("Buttun_B or ENTER to TITLE!!", 200, 100, 1.0f);
}

void ClearScene::Draw(DirectXCommon* dxCommon) {
	sprite->PreDraw();
	//�w�i�p
	sprite->Draw();
}


void ClearScene::Finalize() {
	//�R���̃��f���̃f���[�g
	delete sprite;
}

