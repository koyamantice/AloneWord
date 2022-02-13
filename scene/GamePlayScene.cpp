#include "GamePlayScene.h"
#include "Audio.h"
#include "input.h"
#include "DebugText.h"
#include "TitleScene.h"

void GamePlayScene::Initialize() {
	//オブジェクト初期化
	modelPin=Model::CreateFromOBJ("chr_knight");
	objPin=Object3d::Create();
	objPin->Initialize();
	objPin->SetModel(modelPin);
	objPin->SetPosition({0,0,0});
	// テクスチャ読み込み
	Sprite::LoadTexture(1, L"Resources/2d/title.png");
	Sprite::LoadTexture(2, L"Resources/2d/gameplay.png");

	//背景スプライト生成
	sprite = Sprite::Create(2, { 0.0f,0.0f });
	//スプライト生成
	objSkydome = Object3d::Create();
	modelSkydome = Model::CreateFromOBJ("skydome");
	// モデル読み込み
	Audio::GetInstance()->LoadSound(1, "Resources/BGM/NewWorld.wav");
	srand(NULL);
}

void GamePlayScene::Finalize() {
	//３ｄのモデルのデリート
	delete objPin;
}

void GamePlayScene::Update() {
	Input* input = Input::GetInstance();
	objPin->Update();
	if (input->TriggerKey(DIK_Z)) {
		Audio::GetInstance()->StopWave(0);
		Audio::GetInstance()->StopWave(1);
		Audio::GetInstance()->LoopWave(0,0.7f);
	}
	if (input->TriggerKey(DIK_C)) {
		Audio::GetInstance()->StopWave(0);
		Audio::GetInstance()->StopWave(1);
		Audio::GetInstance()->LoopWave(1,0.7f);
	}
	if (input->TriggerKey(DIK_SPACE)) {
		Audio::GetInstance()->StopWave(0);
		Audio::GetInstance()->StopWave(1);
		SceneManager::GetInstance()->ChangeScene("TITLE");
	}
	DebugText::GetInstance()->Print("SPACE to TITLE!!",200, 100,1.0f);
	DebugText::GetInstance()->Print("Z or C to Sound!!", 200, 115, 1.0f);
	objSkydome->Update();
}

void GamePlayScene::Draw() {
	//ImGui::Begin("test");
	//if (ImGui::TreeNode("Debug"))
	//{
	//	if (ImGui::TreeNode("Field"))
	//	{
	//		//ImGui::SliderFloat("Position.x", &s, 50, -50);
	//		ImGui::Unindent();
	//		ImGui::TreePop();
	//	}
	//	ImGui::TreePop();
	//}
	//ImGui::End();
	Sprite::PreDraw();
	//背景用
	//sprite->Draw();


	Object3d::PreDraw();
	//背景用
<<<<<<< HEAD
	objSkydome->Draw();
=======
	objPin->Draw();
>>>>>>> master


	//前面用

}

