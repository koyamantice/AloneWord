#include "TitleScene.h"
#include"SceneManager.h"
#include "Audio.h"
#include "input.h"
#include "DebugText.h"

void TitleScene::Initialize() {
	// テクスチャ読み込み
	Sprite::LoadTexture(1, L"Resources/2d/title.png");

	//背景スプライト生成
	sprite = Sprite::Create(1, { 0.0f,0.0f });
	//スプライト生成


}

void TitleScene::Finalize() {
	//３ｄのモデルのデリート
	delete sprite;
}

void TitleScene::Update() {
	Input* input = Input::GetInstance();
	if (input->PushKey(DIK_RETURN)) {
		SceneManager::GetInstance()->ChangeScene("GAMEPLAY");
	}
	DebugText::GetInstance()->Print("ENTER to GAMEPLAY!!", 200, 100, 1.0f);
}

void TitleScene::Draw() {
	sprite->PreDraw();
	//背景用
	sprite->Draw();

	//前面用

}

