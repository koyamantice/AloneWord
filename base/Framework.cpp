#include "Framework.h"

void Framework::Run() {
	//初期化
	Initialize();
	while (true)//ゲームループ
	{
		//毎フレーム更新
		Update();

		//終了リクエストが来たら抜ける
		if (IsEndRequst()) {
			break;
		}

		//描画
		Draw();
	}
	//ゲームの終了
	Finalize();

}

void Framework::Initialize() {
	winApp = new WinApp();
	winApp->Initialize();
	dxCommon = new DirectXCommon();
	dxCommon->Initialize(winApp);
	// 入力の初期化
	input = Input::GetInstance();
	input->Initialize(winApp);

	audio = Audio::GetInstance();
	audio->Initialize();	
	
	
	//スプライト関係
	// スプライト静的初期化
	Sprite::StaticInitialize(dxCommon->GetDev(), dxCommon->GetCmdList(),WinApp::window_width, WinApp::window_height);

	const int debugTextTexNumber = 0;
	// デバッグテキスト用テクスチャ読み込み
	if (!Sprite::LoadTexture(debugTextTexNumber, L"Resources/2d/debugfont.png")) {
		assert(0);
		return;
	}
	// デバッグテキスト初期化
	debugText = DebugText::GetInstance();
	debugText->Initialize(debugTextTexNumber);



	Object3d::StaticInitialize(dxCommon->GetDev(), dxCommon->GetCmdList(), WinApp::window_width, WinApp::window_height);
	// マウスカーソルの非表示
	ShowCursor(TRUE);
	//シーンマネージャー

}

void Framework::Finalize() {
	delete sceneFactory_;
	delete dxCommon;
	winApp->Finalize();
	delete winApp;

}

void Framework::Update() {
	input->Update(winApp);
	if (winApp->ProcessMessage() || input->TriggerKey(DIK_ESCAPE)) {
		endResquest_ = true;
		return;
	}
	SceneManager::GetInstance()->Update();
}

void Framework::Draw() {
	dxCommon->PreDraw();

	SceneManager::GetInstance()->Draw();

	debugText->DrawAll();
	dxCommon->PostDraw();

}
