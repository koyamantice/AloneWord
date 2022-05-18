#include "StageSelect.h"
#include "ImageManager.h"
#include "Input.h"
#include"SceneManager.h"
#include "Collision.h"
#include <Easing.h>

void StageSelect::Initialize(DirectXCommon* dxCommon) {
	//背景スプライト生成
	BackGround = Sprite::Create(ImageManager::SELECT, { 0.0f,0.0f });
	select[0] = Sprite::Create(ImageManager::select1, selectP[0]);
	select[0]->SetAnchorPoint({ 1.0f,0.0f });
	select[1] = Sprite::Create(ImageManager::select2, selectP[0]);
	select[1]->SetAnchorPoint({ 1.0f,0.0f });
	select[2] = Sprite::Create(ImageManager::select3, selectP[0]);
	select[2]->SetAnchorPoint({ 1.0f,0.0f });
	select[3] = Sprite::Create(ImageManager::select4, selectP[0]);
	select[3]->SetAnchorPoint({ 1.0f,0.0f });
	select[4] = Sprite::Create(ImageManager::select5, selectP[0]);
	select[4]->SetAnchorPoint({ 1.0f,0.0f });

	plane[0] = Sprite::Create(ImageManager::kitchen, selectP[1]);
	plane[1] = Sprite::Create(ImageManager::genkan, selectP[1]);
	plane[2] = Sprite::Create(ImageManager::niwa, selectP[1]);
	plane[3] = Sprite::Create(ImageManager::washitu, selectP[1]);
	plane[4] = Sprite::Create(ImageManager::wait, selectP[1]);
	// カメラ生成
	//srand(NULL);
	// ライト生成
	lightGroup = LightGroup::Create();
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
	camera->SetEye(XMFLOAT3{ 0,15,-0.5f });
	//camera->SetTarget(XMFLOAT3{ 0,0,0 });
	camera->SetDistance(200.0f);
	ParticleManager::GetInstance()->SetCamera(camera);
	shrinkchange = new ShrinkChange();
	shrinkchange->SetEndChange(true);
	//スプライト生成
	expandchange = new ExpandChange();
}

void StageSelect::Finalize() {
	delete BackGround;
	player->Finalize();
	for (int i = 0; i < 3; i++) {
		delete  select[i];
	}
	for (int i = 0; i < 4; i++) {
		delete  plane[i];
	}
	expandchange->Finalize();
	shrinkchange->Finalize();
}
bool StageSelect::UICheck() {
	if (Collision::CircleCollision(player->GetPosition().x, player->GetPosition().z, 1.0f, 7.0f, -5.0f, 2.0f)) { return false; }
	if (Collision::CircleCollision(player->GetPosition().x, player->GetPosition().z, 1.0f, 7.0f, 3.0f, 2.0f)) { return false; }
	if (Collision::CircleCollision(player->GetPosition().x, player->GetPosition().z, 1.0f, -1.5f, 3.0f, 2.0f)) { return false; }
	if (Collision::CircleCollision(player->GetPosition().x, player->GetPosition().z, 1.0f, -11.0f, 0.0f, 2.0f)) { return false; }
	if (Collision::CircleCollision(player->GetPosition().x, player->GetPosition().z, 1.0f, -2.0f, -4.0f, 2.0f)) { return false; }
	return true;
}
void StageSelect::Update(DirectXCommon* dxCommon) {
	input = Input::GetInstance();
	lightGroup->Update();
	camera->Update();
	player->SelectUp();
	expandchange->Update();
	shrinkchange->Update();
	ParticleManager::GetInstance()->Update();
	if (Collision::CircleCollision(player->GetPosition().x, player->GetPosition().z, 1.0f, 7.0f, -5.0f, 2.0f)) {
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
		if (input->PushKey(DIK_RETURN) || input->TriggerButton(input->Button_A)) {
			Audio::GetInstance()->PlayWave("Resources/Sound/Button.wav", 0.4f);
			SceneManager::GetInstance()->ChangeScene("BOSS");
		}
	}
	if (Collision::CircleCollision(player->GetPosition().x, player->GetPosition().z, 1.0f, 7.0f, 3.0f, 2.0f)) {
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
		select[2]->SetPosition(selectP[0]);
		if (input->PushKey(DIK_RETURN) || input->TriggerButton(input->Button_A)) {
			Audio::GetInstance()->PlayWave("Resources/Sound/Button.wav", 0.4f);
			SceneManager::GetInstance()->ChangeScene("SECONDBOSS");
		}
	}
	if (Collision::CircleCollision(player->GetPosition().x, player->GetPosition().z, 1.0f, -1.5f, 3.0f, 2.0f)) {
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
		if (input->PushKey(DIK_RETURN) || input->TriggerButton(input->Button_A)) {
			Audio::GetInstance()->PlayWave("Resources/Sound/Button.wav", 0.4f);
			SceneManager::GetInstance()->ChangeScene("THIRDBOSS");
		}
	}
	if (Collision::CircleCollision(player->GetPosition().x, player->GetPosition().z, 1.0f, -11.0f, 0.0f, 2.0f)) {
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
		select[1]->SetPosition(selectP[0]);
		if (input->PushKey(DIK_RETURN) || input->TriggerButton(input->Button_A)) {
			Audio::GetInstance()->PlayWave("Resources/Sound/Button.wav", 0.4f);
			SceneManager::GetInstance()->ChangeScene("FOURTHBOSS");
		}
	}
	if (Collision::CircleCollision(player->GetPosition().x, player->GetPosition().z, 1.0f, -2.0f, -4.0f, 2.0f)) {
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
		if (input->PushKey(DIK_RETURN) || input->TriggerButton(input->Button_A)) {
		}
	}
	if (UICheck()) {
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
	}
}

void StageSelect::Draw(DirectXCommon* dxCommon) {
	Sprite::PreDraw();
	BackGround->Draw();
	player->Draw(dxCommon);
	Sprite::PreDraw();
	for (int i = 0; i < 5;i++) {
		select[i]->Draw();
		plane[i]->Draw();
	}
	expandchange->Draw();
	shrinkchange->Draw();
}


