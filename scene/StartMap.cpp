#include "StartMap.h"
#include "Audio.h"
#include "DebugText.h"
#include "TitleScene.h"
#include "FbxLoader.h"
#include"Collision.h"
#include "TouchableObject.h"
#include "MeshCollider.h"
#include "SphereCollider.h"
#include "CollisionManager.h"
#include <XorShift.h>
#include "ImageManager.h"


void StartMap::Initialize(DirectXCommon* dxCommon) {
	collisionManager = CollisionManager::GetInstance();
	// カメラ生成
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height);
	Texture::SetCamera(camera);
	// 3Dオブジェクトにカメラをセット
	Object3d::SetCamera(camera);
	//ステージ床
	objFloor = Object3d::Create();
	modelFloor = Model::CreateFromOBJ("floor");
	objFloor->SetModel(modelFloor);
	objFloor->SetPosition({ 0, -1, 0 });
	objFloor->SetScale({ 6.0f,1.0f,6.0f });

	//ステージマップ
	modelStartMap = Model::CreateFromOBJ("BossMap");
	objStartMap = TouchableObject::Create(modelStartMap);
	objStartMap->SetPosition({ 0,0,4 });
	objStartMap->SetRotation({ 0, 90, 0 });
	objStartMap->SetScale({ 3.0f,1.5f,3.0f });
	//当たり判定確認用です
	// モデル読み込み
	Audio::GetInstance()->LoadSound(1, "Resources/BGM/NewWorld.wav");
	//srand(NULL);
	// ライト生成
	lightGroup = LightGroup::Create();
	// 3Dオブエクトにライトをセット
	Object3d::SetLightGroup(lightGroup);

	//この順番で書かないと例外スローになります
	// デバイスをセット
	FBXObject3d::SetDevice(dxCommon->GetDev());
	// カメラをセット
	FBXObject3d::SetCamera(camera);
	// グラフィックスパイプライン生成
	FBXObject3d::CreateGraphicsPipeline();
	player = new Player();
	player->Initialize();
	player->SetPosition({ 0.0f,0.0f,-10.0f });
	player->SetMove(250.0f, 200.0f);
	// パーティクルマネージャ生成
	particleMan = ParticleManager::GetInstance();
	particleMan->SetCamera(camera);
	for (int i = 0;i<enemy.size(); i++) {
		enemy[i] = new Rice();
		enemy[i]->SetPlayer(player);
		enemy[i]->Initialize();
		enemy[i]->SetLimit({ 22,-22 , 30,-30 });
		enemy[i]->Update();
	}
	ui = new UI(player);
	spawing = new Spawning();
	spawing->SetPlayer(player);
	spawing->Initialize();
	spawing->SetPosition({ 0.0f,0.0f,0.0f });
	spawing->SetRotation({ 0,90,0 });
	spawing->Update();
	cameraPos.x = player->GetPosition().x;
	cameraPos.y = player->GetPosition().y + distanceY;
	cameraPos.z = player->GetPosition().z - distanceZ;
	camera->SetTarget(player->GetPosition());
	camera->SetEye(cameraPos);
	shrinkchange = new ShrinkChange();
	shrinkchange->SetEndChange(true);
	//スプライト生成
	expandchange = new ExpandChange();
}

void StartMap::Finalize() {
	delete camera;
	for (int i = 0; i < enemy.size(); i++) {
		enemy[i]->Finalize();
	}
	spawing->Finalize();
	player->Finalize();
	delete modelFloor;
	delete objFloor;
	delete modelStartMap;
	delete objStartMap;
	expandchange->Finalize();
	shrinkchange->Finalize();
	delete camera;
	ui->Finalize();

}

void StartMap::Update(DirectXCommon* dxCommon) {
	if (pause) {
		Pause(set);
		return;
	} else {
		hit = false;
	}
	if (input->PushButton(input->Select)) {
		int a = 0;
		a++;
	}

	objStartMap->Update();
	objFloor->Update();
	//objSkydome->Update();
	lightGroup->Update();
	camera->Update();
	player->Update();
	spawing->Update();
	particleMan->Update();
	expandchange->Update();
	shrinkchange->Update();
	for (int i = 0; i < enemy.size() - 1; i++) {
		enemy[i]->Demo(i);
		player->ResetWeight(enemy[i]);
	}
	//player->Rebound(spawing);
	if (player->GetHp() <= 0) {
		player->SetHp(10);
	}

	cameraPos.x = player->GetPosition().x;
	cameraPos.y = player->GetPosition().y + distanceY;
	cameraPos.z = player->GetPosition().z - distanceZ;
	camera->SetTarget(player->GetPosition());
	camera->SetEye(cameraPos);
}

void StartMap::Draw(DirectXCommon* dxCommon) {
	objFloor->Draw();
	objStartMap->Draw();

	for (int i = 0; i < enemy.size() - 1; i++) {
		enemy[i]->Draw();
	}
	player->Draw(dxCommon);

	spawing->Draw();
	// パーティクルの描画
	particleMan->Draw(dxCommon->GetCmdList());
	ui->Draw();
	Sprite::PreDraw();
	expandchange->Draw();
	shrinkchange->Draw();
}

void StartMap::Pause(const int& Timer) {
	wait++;
	if (wait >= Timer) {
		pause = false;
		wait = 0;
	}
	else {
		pause = true;
	}
}
