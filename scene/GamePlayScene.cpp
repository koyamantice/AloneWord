#include "GamePlayScene.h"
#include "Audio.h"
#include "input.h"
#include "DebugText.h"
#include "TitleScene.h"

void GamePlayScene::Initialize() {
	// カメラ生成
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height);

	// 3Dオブジェクトにカメラをセット
	Object3d::SetCamera(camera);
	//オブジェクト初期化
	modelPin=Model::CreateFromOBJ("chr_knight");
	objPin=Object3d::Create();
	objPin->Initialize();
	objPin->SetModel(modelPin);
	objPin->SetPosition({0,0,0});
	//オブジェクト初期化
	modelSkydome = Model::CreateFromOBJ("skydome");
	objSkydome = Object3d::Create();
	objSkydome->Initialize();
	objSkydome->SetModel(modelSkydome);
	objSkydome->SetPosition({ 0,0,0 });
	//オブジェクト初期化
	modelGround = Model::CreateFromOBJ("ground");
	objGround = Object3d::Create();
	objGround->Initialize();
	objGround->SetModel(modelGround);
	objGround->SetPosition({ 0,0,0 });
	// テクスチャ読み込み
	Sprite::LoadTexture(1, L"Resources/2d/title.png");
	Sprite::LoadTexture(2, L"Resources/2d/gameplay.png");

	//背景スプライト生成
	sprite = Sprite::Create(2, { 0.0f,0.0f });
	
	// モデル読み込み
	Audio::GetInstance()->LoadSound(1, "Resources/BGM/NewWorld.wav");
	srand(NULL);
	// ライト生成
	lightGroup = LightGroup::Create();
	// 3Dオブエクトにライトをセット
	Object3d::SetLightGroup(lightGroup);

	// カメラ注視点をセット
	camera->SetTarget({ 0, 1, 0 });
	camera->SetEye({ 0, 3.0f, -20.0f });
}

void GamePlayScene::Finalize() {
	//３ｄのモデルのデリート
	delete objPin;
}

void GamePlayScene::Update() {
	Input* input = Input::GetInstance();
	objPin->Update();
	objSkydome->Update();
	objGround->Update();
	lightGroup->Update();
	camera->Update();
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
	objSkydome->Draw();
	objPin->Draw();
	objGround->Draw();
	//前面用

}

