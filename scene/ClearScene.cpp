#include "ClearScene.h"
#include "Audio.h"
#include "input.h"
#include "DebugText.h"
#include "SceneManager.h"
#include "GamePlayScene.h"
#include "ClearScene.h"

void ClearScene::Initiallize(DirectXCommon* dxCommon) {
	// �e�N�X�`���ǂݍ���
	Sprite::LoadTexture(1, L"Resources/180_20220130123604.png");

	//�w�i�X�v���C�g����
	sprite = Sprite::Create(1, { 0.0f,0.0f });
	//�X�v���C�g����
}

void ClearScene::Update(DirectXCommon* dxCommon) {
	Input* input = Input::GetInstance();
	if (input->PushKey(DIK_RETURN) || input->TriggerButton(input->Button_B)) {
		SceneManager::GetInstance()->ChangeScene("TITLE");
	}
	DebugText::GetInstance()->Print("ENTER to TITLE!!", 200, 100, 1.0f);
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

