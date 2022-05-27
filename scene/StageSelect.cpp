#include "StageSelect.h"
#include "ImageManager.h"
#include "Input.h"
#include"SceneManager.h"
#include "Collision.h"
#include "imgui.h"
#include <Easing.h>
//静的メンバ変数の実態

void StageSelect::Initialize(DirectXCommon* dxCommon) {
	//背景スプライト生成
	DarkBackGround = Texture::Create(ImageManager::SELECTTex, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	DarkBackGround->TextureCreate();
	DarkBackGround->SetRotation({ 90,0,0 });
	DarkBackGround->SetPosition({ 0.0f,0.0f,0.5f });
	DarkBackGround->SetScale({ 3.2f,1.8f,1.0f });
	DarkBackGround->Update();
	LightBackGround = Texture::Create(ImageManager::SELECTTex2, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	LightBackGround->TextureCreate();
	LightBackGround->SetRotation({ 90,0,0 });
	LightBackGround->SetPosition({ 0.0f,0.0f,0.5f });
	LightBackGround->SetScale({ 3.2f,1.8f,1.0f });
	LightBackGround->Update();
	//マップのUI的なやつの場所
	StageP[0] = { -6.2f,0.0f,3.0f };
	StageP[1] = { 1.3f,0.0f,3.0f };
	StageP[2] = { 8.1f,0.0f,3.0f };
	StageP[3] = { -6.2f,0.0f,-3.2f };
	StageP[4] = { 1.3f,0.0f,-3.2f };

	//各スプライトの宣言
	select[0] = Sprite::Create(ImageManager::select2, selectP[0]);
	select[0]->SetAnchorPoint({ 1.0f,0.0f });
	select[1] = Sprite::Create(ImageManager::select1, selectP[0]);
	select[1]->SetAnchorPoint({ 1.0f,0.0f });
	select[2] = Sprite::Create(ImageManager::select3, selectP[0]);
	select[2]->SetAnchorPoint({ 1.0f,0.0f });
	select[3] = Sprite::Create(ImageManager::select4, selectP[0]);
	select[3]->SetAnchorPoint({ 1.0f,0.0f });
	select[4] = Sprite::Create(ImageManager::select5, selectP[0]);
	select[4]->SetAnchorPoint({ 1.0f,0.0f });
	BlackFilter = Sprite::Create(ImageManager::BlackFilter, { 0.0f,0.0f });
	plane[0] = Sprite::Create(ImageManager::kitchen, selectP[1]);
	plane[1] = Sprite::Create(ImageManager::genkan, selectP[1]);
	plane[2] = Sprite::Create(ImageManager::niwa, selectP[1]);
	plane[3] = Sprite::Create(ImageManager::washitu, selectP[1]);
	plane[4] = Sprite::Create(ImageManager::shinshitu, selectP[1]);
	for (int i = 0; i < 5; i++) {
		no_select[i] = Sprite::Create(ImageManager::noBoss_Select, selectP[0]);
		no_select[i]->SetAnchorPoint({ 1.0f,0.0f });
		no_plane[i] = Sprite::Create(ImageManager::noBoss_Sname, selectP[1]);
	}
	//クリアした時
	Stage1[0] = Texture::Create(ImageManager::clearStage1, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	Stage1[0]->TextureCreate();
	Stage2[0] = Texture::Create(ImageManager::clearStage2, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	Stage2[0]->TextureCreate();
	Stage3[0] = Texture::Create(ImageManager::clearStage3, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	Stage3[0]->TextureCreate();
	Stage4[0] = Texture::Create(ImageManager::clearStage4, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	Stage4[0]->TextureCreate();
	Stage5[0] = Texture::Create(ImageManager::clearStage5, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	Stage5[0]->TextureCreate();
	
	//開放していない時
	Stage1[1] = Texture::Create(ImageManager::onStage1, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	Stage1[1]->TextureCreate();
	Stage2[1] = Texture::Create(ImageManager::onStage2, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	Stage2[1]->TextureCreate();
	Stage3[1] = Texture::Create(ImageManager::onStage3, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	Stage3[1]->TextureCreate();
	Stage4[1] = Texture::Create(ImageManager::onStage4, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	Stage4[1]->TextureCreate();
	Stage5[1] = Texture::Create(ImageManager::onStage5, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	Stage5[1]->TextureCreate();

	//クリアしていない時
	Stage1[2] = Texture::Create(ImageManager::offStage1, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	Stage1[2]->TextureCreate();
	Stage2[2] = Texture::Create(ImageManager::offStage2, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	Stage2[2]->TextureCreate();
	Stage3[2] = Texture::Create(ImageManager::offStage3, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	Stage3[2]->TextureCreate();
	Stage4[2] = Texture::Create(ImageManager::offStage4, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	Stage4[2]->TextureCreate();
	Stage5[2] = Texture::Create(ImageManager::offStage5, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	Stage5[2]->TextureCreate();

	// カメラ生成
	//srand(NULL);
	// ライト生成
	lightGroup = LightGroup::Create();
	//サウンド宣言&プレイ
	Audio::GetInstance()->LoadSound(4, "Resources/Sound/selectBGM.wav");
	Audio::GetInstance()->LoopWave(4, 0.2f);
	// 3Dオブジェクトにライトをセット
	Object3d::SetLightGroup(lightGroup);

	camera = new DebugCamera(WinApp::window_width, WinApp::window_height);
	Texture::SetCamera(camera);
	// 3Dオブジェクトにカメラをセット
	Object3d::SetCamera(camera);
	// デバイスをセット
	FBXObject3d::SetDevice(dxCommon->GetDev());
	// カメラをセット
	FBXObject3d::SetCamera(camera);
	// グラフィックスパイプライン生成
	FBXObject3d::CreateGraphicsPipeline();
	//各オブジェクトの初期化
	//プレイヤー
	player = new Player();
	player->Initialize();
	player->SetRotation({ 0.0f,0.0f,0.0f });
	player->SetPosition({ 0.0f,0.0f,0.0f });
	player->SetMove(10.0f, 10.0f);

	
	//camera->SetEye(XMFLOAT3{ 0,15,-0.5f });
	////camera->SetTarget(XMFLOAT3{ 0,0,0 });
	//camera->SetDistance(200.0f);
	ParticleManager::GetInstance()->SetCamera(camera);

	//カメラポジション
	cameraPos.x = 0;
	cameraPos.y = 15;
	cameraPos.z = -0.5f;
	// カメラ注視点をセット
	cameratargetPos = { 0.0f,0.0f,0.0f };
	camera->SetTarget(cameratargetPos);
	camera->SetEye(cameraPos);
	shrinkchange = new ShrinkChange();
	shrinkchange->SetEndChange(true);
	//スプライト生成
	expandchange = new ExpandChange();
	save = new Save();
}
//開放
void StageSelect::Finalize() {
	delete DarkBackGround;
	delete LightBackGround;
	delete camera;
	player->Finalize();
	for (int i = 0; i < 3; i++) {
		delete  select[i];
	}
	for (int i = 0; i < 4; i++) {
		delete  plane[i];
	}
	for (int i = 0; i < 5; i++) {
		delete no_plane[i];
		delete no_select[i];
	}
	expandchange->Finalize();
	shrinkchange->Finalize();
}
//どのマップに行くかを決める
bool StageSelect::UICheck() {
	if (Collision::CircleCollision(player->GetPosition().x, player->GetPosition().z, 1.0f, -6.2f, 3.0f, 1.5f)) { return false; }
	if (Collision::CircleCollision(player->GetPosition().x, player->GetPosition().z, 1.0f, 1.3f, 3.0f, 1.5f)) { return false; }
	if (Collision::CircleCollision(player->GetPosition().x, player->GetPosition().z, 1.0f, 8.1f, 3.0f, 1.5f)) { return false; }
	if (Collision::CircleCollision(player->GetPosition().x, player->GetPosition().z, 1.0f, -6.2f, -3.2f, 1.5f)) { return false; }
	if (Collision::CircleCollision(player->GetPosition().x, player->GetPosition().z, 1.0f, 1.0f, -3.2f, 1.5f)) { return false; }
	return true;
}
void StageSelect::SinMove(int selectNum, int planeNum) {
	if (frame >= 1.0f) {
		sinFrame += vel;
		if (sinFrame <= 0.0f) {
			sinFrame = 0.0f;
			vel *= -1.0f;
		}
		if (sinFrame >= 1.0f) {
			sinFrame = 1.0f;
			vel *= -1.0f;
		}
		selectP[0] = {
		640,
		Ease(In,Quad,sinFrame,-10,10),
		};
		selectP[1] = {
		640,
		Ease(In,Quad,sinFrame,470,490),
		};
		select[selectNum]->SetPosition(selectP[0]);
		plane[planeNum]->SetPosition(selectP[1]);
		no_select[selectNum]->SetPosition(selectP[0]);
		no_plane[planeNum]->SetPosition(selectP[1]);
	}

}
//更新
void StageSelect::Update(DirectXCommon* dxCommon) {
	int ClearCount = save->GetClearCount();
	input = Input::GetInstance();
	lightGroup->Update();
	player->SelectUp();
	DarkBackGround->Update();
	LightBackGround->Update();
	for (int i = 0; i < 3; i++) {
		Stage1[i]->Update();
		Stage2[i]->Update();
		Stage3[i]->Update();
		Stage4[i]->Update();
		Stage5[i]->Update();
		//
		Stage1[i]->SetRotation({90,0,0});
		Stage2[i]->SetRotation({ 90,0,0 });
		Stage3[i]->SetRotation({ 90,0,0 });
		Stage4[i]->SetRotation({ 90,0,0 });
		Stage5[i]->SetRotation({ 90,0,0 });
		//
		Stage1[i]->SetScale({ 0.2f,0.2f,0.2f });
		Stage2[i]->SetScale({ 0.2f,0.2f,0.2f });
		Stage3[i]->SetScale({ 0.2f,0.2f,0.2f });
		Stage4[i]->SetScale({ 0.2f,0.2f,0.2f });
		Stage5[i]->SetScale({ 0.2f,0.2f,0.2f });
	}
	expandchange->Update();
	shrinkchange->Update();
	ParticleManager::GetInstance()->Update();
	//選ばれる場所によってカメラが寄る場所が変わる
	if (Collision::CircleCollision(player->GetPosition().x, player->GetPosition().z, 1.0f, -6.2f, 3.0f, 1.5f)) {
		if (frame >= 1.0f) {
			frame = 1.0f;
		} else {
			frame += 0.06f;
		}
		selectP[0] = {
			Ease(In,Quad,frame,0,640),
			0
		};
		selectP[1] = {
		Ease(In,Quad,frame,1280,640),
		480
		};
		plane[0]->SetPosition(selectP[1]);
		select[0]->SetPosition(selectP[0]);
		no_select[0]->SetPosition(selectP[0]);
		no_plane[0]->SetPosition(selectP[1]);
		SinMove(0, 0);
		if (input->PushKey(DIK_RETURN) || input->TriggerButton(input->Button_A)) {
			Audio::GetInstance()->PlayWave("Resources/Sound/Button.wav", 0.4f);

			StageSelectNumber = fork;
			/*Aftertargetpos = player->GetPosition();
			Aftereyepos = player->GetPosition();*/
			Aftereyepos = {
					player->GetPosition().x,
					player->GetPosition().y,
					player->GetPosition().z,
			};

			Aftertargetpos = {
				player->GetPosition().x,
				player->GetPosition().y - 5,
				player->GetPosition().z,
			};
		}
	}
	if (Collision::CircleCollision(player->GetPosition().x, player->GetPosition().z, 1.0f, 8.2f, 3.0f, 1.5f)) {
		if (frame >= 1.0f) {
			frame = 1.0f;
		} else {
			frame += 0.06f;
		}
		selectP[0] = {
			Ease(In,Quad,frame,0,640),
			0
		};
		selectP[1] = {
		Ease(In,Quad,frame,1280,640),
		480
		};
		plane[1]->SetPosition(selectP[1]);
		select[1]->SetPosition(selectP[0]);
		no_select[1]->SetPosition(selectP[0]);
		no_plane[1]->SetPosition(selectP[1]);
		SinMove(1, 1);
		if (input->PushKey(DIK_RETURN) || input->TriggerButton(input->Button_A)/* && (ClearCount >= 2)*/) {
			Audio::GetInstance()->PlayWave("Resources/Sound/Button.wav", 0.4f);
			//SceneManager::GetInstance()->ChangeScene("SECONDBOSS");
			StageSelectNumber = boots;
			Aftereyepos = {
					player->GetPosition().x,
					player->GetPosition().y,
					player->GetPosition().z,
			};

			Aftertargetpos = {
				player->GetPosition().x,
				player->GetPosition().y - 5,
				player->GetPosition().z,
			};
			//Aftereyepos = player->GetPosition();
		}
	}
	if (Collision::CircleCollision(player->GetPosition().x, player->GetPosition().z, 1.0f, 1.3f, 3.0f, 1.5f)) {
		if (frame >= 1.0f) {
			frame = 1.0f;
		} else {
			frame += 0.06f;
		}
		selectP[0] = {
			Ease(In,Quad,frame,0,640),
			0
		};
		selectP[1] = {
		Ease(In,Quad,frame,1280,640),
		480
		};
		plane[3]->SetPosition(selectP[1]);
		select[3]->SetPosition(selectP[0]);
		no_select[3]->SetPosition(selectP[0]);
		no_plane[3]->SetPosition(selectP[1]);
		SinMove(3, 3);
		if (input->PushKey(DIK_RETURN) || input->TriggerButton(input->Button_A)/* && (ClearCount >= 1)*/) {
			Audio::GetInstance()->PlayWave("Resources/Sound/Button.wav", 0.4f);
			//SceneManager::GetInstance()->ChangeScene("THIRDBOSS");
			StageSelectNumber = Tea;
			/*Aftertargetpos = player->GetPosition();
			Aftereyepos = player->GetPosition();*/
			Aftereyepos = {
					player->GetPosition().x,
					player->GetPosition().y,
					player->GetPosition().z,
			};

			Aftertargetpos = {
				player->GetPosition().x,
				player->GetPosition().y - 5,
				player->GetPosition().z,
			};
		}
	}
	if (Collision::CircleCollision(player->GetPosition().x, player->GetPosition().z, 1.0f, -6.2f, -3.2f, 1.5f)) {
		if (frame >= 1.0f) {
			frame = 1.0f;
		} else {
			frame += 0.06f;
		}
		selectP[0] = {
			Ease(In,Quad,frame,0,640),
			0
		};
		selectP[1] = {
		Ease(In,Quad,frame,1280,640),
		480
		};
		plane[2]->SetPosition(selectP[1]);
		select[2]->SetPosition(selectP[0]);
		no_select[3]->SetPosition(selectP[0]);
		no_plane[3]->SetPosition(selectP[1]);
		SinMove(2, 2);
		if (input->PushKey(DIK_RETURN) || input->TriggerButton(input->Button_A)/* && (ClearCount >= 3)*/) {
			Audio::GetInstance()->PlayWave("Resources/Sound/Button.wav", 0.4f);
			//SceneManager::GetInstance()->ChangeScene("FOURTHBOSS");
			StageSelectNumber = Pastel;
			/*Aftertargetpos = player->GetPosition();
			Aftereyepos = player->GetPosition();*/
			Aftereyepos = {
					player->GetPosition().x,
					player->GetPosition().y,
					player->GetPosition().z,
			};

			Aftertargetpos = {
				player->GetPosition().x,
				player->GetPosition().y - 5,
				player->GetPosition().z,
			};
		}
	}
	if (Collision::CircleCollision(player->GetPosition().x, player->GetPosition().z, 1.0f, 1.3f, -3.2f, 1.5f)) {
		if (frame >= 1.0f) {
			frame = 1.0f;
		} else {
			frame += 0.06f;
		}
		selectP[0] = {
		Ease(In,Quad,frame,0,640),
		0
		};
		selectP[1] = {
		Ease(In,Quad,frame,1280,640),
		480
		};
		plane[4]->SetPosition(selectP[1]);
		select[4]->SetPosition(selectP[0]);
		no_select[4]->SetPosition(selectP[0]);
		no_plane[4]->SetPosition(selectP[1]);
		SinMove(4, 4);
		if (input->PushKey(DIK_RETURN) || input->TriggerButton(input->Button_A)/* && (ClearCount >= 4)*/) {
			Audio::GetInstance()->PlayWave("Resources/Sound/Button.wav", 0.4f);
			//SceneManager::GetInstance()->ChangeScene("FOURTHBOSS");
			StageSelectNumber = human;
			/*Aftertargetpos = player->GetPosition();
			Aftereyepos = player->GetPosition();*/
			Aftereyepos = {
					player->GetPosition().x,
					player->GetPosition().y,
					player->GetPosition().z,
			};

			Aftertargetpos = {
				player->GetPosition().x,
				player->GetPosition().y - 5,
				player->GetPosition().z,
			};
		}
	}

	//選択した場合カメラが寄る
	if (StageSelectNumber != No) {
		if (selectframe <= 1.0f) {
			selectframe += 0.005f;
		}
		else {
			selectframe = 1.0f;
		}


		cameraPos = {
	Ease(In,Cubic,selectframe,cameraPos.x,Aftereyepos.x),
	Ease(In,Cubic,selectframe,cameraPos.y,Aftereyepos.y),
	Ease(In,Cubic,selectframe,cameraPos.z,Aftereyepos.z)
		};

		cameratargetPos = {
Ease(In,Cubic,selectframe,cameratargetPos.x,Aftertargetpos.x),
Ease(In,Cubic,selectframe,cameratargetPos.y,Aftertargetpos.y),
Ease(In,Cubic,selectframe,cameratargetPos.z,Aftertargetpos.z)
		};

		camera->SetTarget(cameratargetPos);
		camera->SetEye(cameraPos);
	}
	
	if (UICheck()) {
		dark = false;
		frame = 0.0f;
		selectP[0] = {
		Ease(In,Quad,frame,0,640),
		0
		};
		select[0]->SetPosition(selectP[0]);
		selectP[1] = {
		Ease(In,Quad,frame,1280,640),
		480
		};
		for (int i = 0;i<5; i++) {
			select[i]->SetPosition(selectP[0]);
			plane[i]->SetPosition(selectP[1]);
		}
		for (int i = 0; i < 5; i++) {
			no_select[i]->SetPosition(selectP[0]);
			no_plane[i]->SetPosition(selectP[1]);
		}
	}
	else {
		dark = true;
	}

	//シーンがここで変わる
	if (cameraPos.y <= 2.6f) {
		frame = 0.0f;
		selectframe = 0.0f;
		cameraPos = { 0.0f,0.0f,0.0f };
		if (StageSelectNumber == fork) {
			Audio::GetInstance()->StopWave(4);
			SceneManager::GetInstance()->ChangeScene("BOSS");
		}
		else if (StageSelectNumber == boots) {
			Audio::GetInstance()->StopWave(4);
			SceneManager::GetInstance()->ChangeScene("SECONDBOSS");
		}
		else if (StageSelectNumber == Tea) {
			Audio::GetInstance()->StopWave(4);
			SceneManager::GetInstance()->ChangeScene("THIRDBOSS");
		}
		else if (StageSelectNumber == Pastel) {
			Audio::GetInstance()->StopWave(4);
			SceneManager::GetInstance()->ChangeScene("FOURTHBOSS");
		}
		else if (StageSelectNumber == human) {
			Audio::GetInstance()->StopWave(4);
			SceneManager::GetInstance()->ChangeScene("FIFTHBOSS");
		}
		StageSelectNumber = No;
	}
	camera->Update();
	for (int i = 0; i < 3; i++) {
		Stage1[i]->SetPosition(StageP[0]);
		Stage2[i]->SetPosition(StageP[1]);
		Stage3[i]->SetPosition(StageP[2]);
		Stage4[i]->SetPosition(StageP[3]);
		Stage5[i]->SetPosition(StageP[4]);
	}
}

//描画
void StageSelect::Draw(DirectXCommon* dxCommon) {
	int ClearCount = save->GetClearCount();
	XMFLOAT3 pos = player->GetPosition();
	bool SecondClear = save->GetSecondClear();
	ImGui::Begin("test");
	ImGui::SliderFloat("position.x", &pos.x, 100, -100);
	ImGui::SliderFloat("position.y", &pos.y, 100, -100);
	ImGui::SliderFloat("position.z", &pos.z, 100, -100);
	ImGui::Text("clearCount::%d", ClearCount);
	ImGui::Text("Second::%d", SecondClear);
	ImGui::Unindent();
	ImGui::End();

	Texture::PreDraw();
	if (dark) {
		DarkBackGround->Draw();
	}
	else {
		LightBackGround->Draw();
	}
	//クリア状況ごとにマップの色が変わる
	//一ステージ目
	if (save->GetFirstClear()) {
		Stage1[0]->Draw();
	}
	else {
		Stage1[1]->Draw();
	}

	//2ステージ目
	if (save->GetSecondClear()) {
		Stage2[0]->Draw();
	}
	else {
		if (save->GetClearCount() == 1) {
			Stage2[1]->Draw();
		}
		else {
			Stage2[2]->Draw();
		}
	}

	//3ステージ目
	if (save->GetThirdClear()) {
		Stage3[0]->Draw();
	}
	else {
		if (save->GetClearCount() == 2) {
			Stage3[1]->Draw();
		}
		else {
			Stage3[2]->Draw();
		}
	}

	//4ステージ目
	if (save->GetFouthClear()) {
		Stage4[0]->Draw();
	}
	else {
		if (save->GetClearCount() == 3) {
			Stage4[1]->Draw();
		}
		else {
			Stage4[2]->Draw();
		}
	}

	//5ステージ目
	if (save->GetFifthClear()) {
		Stage5[0]->Draw();
	}
	else {
		if (save->GetClearCount() == 4) {
			Stage5[1]->Draw();
		}
		else {
			Stage5[2]->Draw();
		}
	}
	
	
	Sprite::PreDraw();
	player->Draw(dxCommon);
	Sprite::PreDraw();
	select[0]->Draw();
	plane[0]->Draw();
	//2ステージ目
	if (save->GetSecondClear()) {
		plane[3]->Draw();
		select[3]->Draw();
	}
	else {
		if (save->GetClearCount() == 1) {
			plane[3]->Draw();
			select[3]->Draw();
		}
		else {
			no_plane[3]->Draw();
			no_select[3]->Draw();
		}
	}

	//3ステージ目
	if (save->GetThirdClear()) {
		plane[1]->Draw();
		select[1]->Draw();
	}
	else {
		if (save->GetClearCount() == 2) {
			plane[1]->Draw();
			select[1]->Draw();
		}
		else {
			no_plane[1]->Draw();
			no_select[1]->Draw();
		}
	}

	//4ステージ目
	if (save->GetFouthClear()) {
		plane[2]->Draw();
		select[2]->Draw();
	}
	else {
		if (save->GetClearCount() == 3) {
			plane[2]->Draw();
			select[2]->Draw();
		}
		else {
			no_plane[2]->Draw();
			no_select[2]->Draw();
		}
	}

	//5ステージ目
	if (save->GetFifthClear()) {
		plane[4]->Draw();
		select[4]->Draw();
	}
	else {
		if (save->GetClearCount() == 4) {
			plane[4]->Draw();
			select[4]->Draw();
		}
		else {
			no_plane[4]->Draw();
			no_select[4]->Draw();
		}
	}

	expandchange->Draw();
	shrinkchange->Draw();
	if (cameraPos.y <= 0.5) {
		BlackFilter->Draw();
	}
}


