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
	plane[0] = Sprite::Create(ImageManager::kitchen, selectP[1]);
	plane[0]->SetAnchorPoint({ 0.0f,0.0f });
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
}

void StageSelect::Finalize() {
	delete BackGround;
	player->Finalize();

}
bool StageSelect::UICheck() {
	if (Collision::CircleCollision(player->GetPosition().x, player->GetPosition().z, 1.0f, 9.0f, -2.0f, 1.0f)) { return false; }
	if (Collision::CircleCollision(player->GetPosition().x, player->GetPosition().z, 1.0f, 3.0f, 2.0f, 1.0f)) { return false; }
	if (Collision::CircleCollision(player->GetPosition().x, player->GetPosition().z, 1.0f, -5.0f, 5.0f, 1.0f)) { return false; }
	if (Collision::CircleCollision(player->GetPosition().x, player->GetPosition().z, 1.0f, -11.0f, 0.0f, 1.0f)) { return false; }
	if (Collision::CircleCollision(player->GetPosition().x, player->GetPosition().z, 1.0f, -5.0f, -5.0f, 1.0f)) { return false; }
	return true;
}
void StageSelect::Update(DirectXCommon* dxCommon) {
	input = Input::GetInstance();
	lightGroup->Update();
	camera->Update();
	player->SelectUp();


	if (Collision::CircleCollision(player->GetPosition().x, player->GetPosition().z, 1.0f, 9.0f, -2.0f, 1.0f)) {
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
			SceneManager::GetInstance()->ChangeScene("STARTMAP");
		}
	}
	if (Collision::CircleCollision(player->GetPosition().x, player->GetPosition().z, 1.0f, 3.0f, 2.0f, 1.0f)) {
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
			SceneManager::GetInstance()->ChangeScene("SECONDBOSS");
		}
	}
	if (Collision::CircleCollision(player->GetPosition().x, player->GetPosition().z, 1.0f, -5.0f, 5.0f, 1.0f)) {
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
			SceneManager::GetInstance()->ChangeScene("THIRDBOSS");
		}
	}
	if (Collision::CircleCollision(player->GetPosition().x, player->GetPosition().z, 1.0f, -11.0f, 0.0f, 1.0f)) {
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
			SceneManager::GetInstance()->ChangeScene("FOURTHBOSS");
		}
	}
	if (Collision::CircleCollision(player->GetPosition().x, player->GetPosition().z, 1.0f, -5.0f, -5.0f, 1.0f)) {

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
		plane[0]->SetPosition(selectP[1]);
	}
}

void StageSelect::Draw(DirectXCommon* dxCommon) {
	Sprite::PreDraw();
	BackGround->Draw();
	player->Draw(dxCommon);
	Sprite::PreDraw();
	select[0]->Draw();
	plane[0]->Draw();
}


