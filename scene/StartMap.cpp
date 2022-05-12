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

StartMap::~StartMap() {
	//Finalize();
}

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
	objFloor->SetScale({ 4.0f,1.0f,5.0f });

	//ステージマップ
	modelStartMap = Model::CreateFromOBJ("BossMap");
	objStartMap = TouchableObject::Create(modelStartMap);
	objStartMap->SetPosition({ 0,-1,2 });
	objStartMap->SetRotation({ 0, 90, 0 });
	objStartMap->SetScale({ 1.2f,1.2f,1.2f });

	/*limit = texture::create(1, { 0,0,0 }, { 12,12,12 }, { 1,1,1,0.6f });
	limit->texturecreate();
	limit->setposition({ 0.0f,0.01f,0.0f });
	limit->setrotation({ 90.0f,0, 0 });
	limit->setscale({ 5.5f, 5.5f,  5.5f});*/
	//背景スプライト生成
	concent = Sprite::Create(ImageManager::concent, { 0.0f,0.0f });
	//背景スプライト生成
	concent2 = Sprite::Create(ImageManager::concent2, { 0.0f,0.0f });
	//背景スプライト生成
	concent3 = Sprite::Create(ImageManager::concent3, { 0.0f,0.0f });
	//背景スプライト生成
	concent4 = Sprite::Create(ImageManager::concent4, { 0.0f,0.0f });
	//背景スプライト生成
	concent5 = Sprite::Create(ImageManager::concent5, { 0.0f,0.0f });

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
	player->SetMove(50.0f, 50.0f);
	player->SetPosition({ 0.0f,5.0f,-10.0f });
	//player->SetPosition({ 0.0f,0.0f,-30.0f });

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
	//カメラポジション
	cameraPos.x = player->GetTargetPosition().x;
	cameraPos.y = player->GetTargetPosition().y + 10;
	cameraPos.z = player->GetTargetPosition().z - 10;
	// カメラ注視点をセット
	camera->SetTarget(player->GetTargetPosition());
	camera->SetEye(cameraPos);
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
}

void StartMap::Update(DirectXCommon* dxCommon) {
	if (pause) {
		Pause(set);
		return;
	} else {
		hit = false;
	}
	if (tutorial%2==1) {
		switch (tutorial) {
		case 1:
			if (input->TriggerButton(input->Button_A)) {
				tutorial++;
			}
		break;
		case 3:
			if (input->TriggerButton(input->Button_A)) {
				tutorial++;
			}
			break;
		case 5:
			if (input->TriggerButton(input->Button_A)) {
				tutorial++;
			}
			break;
		case 7:
			if (input->TriggerButton(input->Button_A)) {

				SceneManager::GetInstance()->ChangeScene("StageSelect");
			}
			break;
		default:
			break;
		}
		return;
	}
	if (player->GetPosition().y<=0 && tutorial == 0) {
		tutorial=1;
	}
	if (tutorial == 2) {
		enemy[0]->Demo();
		if (enemy[0]->GetFollowed()&& enemy[0]->GetStart()) {
			tutorial = 3;
		}
	}
	if (tutorial == 4) {
		enemy[0]->Demo();
		if (enemy[0]->GetEnemyCatch()) {
			tutorial = 5;
		}
	}
	if (tutorial==6) {
		for (int j = 0; j < enemy.size(); j++) {
			enemy[j]->Demo(j);
		}
		if (!spawing->GetIsAlive()) {
			tutorial = 7;
		}
	}
	if (spawing->collideAttackArm()&&spawing->GetIsAlive()) {
		hit = true;
		set = spawing->GetStop();
		pause = true;
	}
	////敵同士の当たり判定
	if (sizeof(enemy) > 2) {//配列のサイズ確認
		for (int colA = 0; colA < enemy.size(); colA++) {
			for (int colB = 1; colB < enemy.size(); colB++) {
				if (!enemy[colA]->GetEnemyCatcth()&& !enemy[colB]->GetEnemyCatcth()) {
					if (Collision::CircleCollision(enemy[colA]->GetPosition().x, enemy[colA]->GetPosition().z, 1.0f, enemy[colB]->GetPosition().x, enemy[colB]->GetPosition().z, 1.0f) && colA != colB) {//当たり判定と自機同士の当たり判定の削除
						if (!enemy[colA]->GetHit()) {
							enemy[colA]->SetHit(true);
							enemy[colA]->SetExP(enemy[colB]->GetPosition());
						}
						if (!enemy[colB]->GetHit()) {
							enemy[colB]->SetHit(true);
							enemy[colB]->SetExP(enemy[colA]->GetPosition());
						}
						break;
					}
				}
			}
		}
	}
	Ray ray;
	ray.start = { player->GetPosition().x,player->GetPosition().y + 1,player->GetPosition().z,1 };
	ray.dir = { 0.0f,0.28f,-1.0f,0.0f };
	RaycastHit raycastHit;
	if (!collisionManager->Raycast(ray, &raycastHit)) {
		if (distanceZ <= 10.0f) {
			distanceZ += 0.25f;
		}

		if (distanceY >= 10.0f) {
			distanceY -= 0.25f;
		}
	}
	else {
		if (distanceZ >= 6.0f) {
			distanceZ -= 0.4f;
		}

		if (distanceY <= 18.0f) {
			distanceY += 0.25f;
		}
	}

	if (input->TriggerKey(DIK_C)) {
		SceneManager::GetInstance()->ChangeScene("CLEAR");
	}
	if (player->GetHp() <= 0) {
		SceneManager::GetInstance()->ChangeScene("GAMEOVER");
	}
	ui->Update();
	objFloor->Update();
	objStartMap->Update();
	lightGroup->Update();
	camera->Update();
	player->Update();
	spawing->Update();
	particleMan->Update();
	for (int j = 0; j < enemy.size(); j++) {
		player->ResetWeight(enemy[j]);
		player->Rebound(enemy[j]);
	}
	cameraPos.x = player->GetTargetPosition().x;
	cameraPos.y = player->GetTargetPosition().y +( distanceY-2);
	cameraPos.z = player->GetPosition().z - distanceZ;
	camera->SetTarget(player->GetTargetPosition());
	camera->SetEye(cameraPos);
}

void StartMap::Draw(DirectXCommon* dxCommon) {
	objFloor->Draw();
	objStartMap->Draw();

	enemy[0]->Draw();
	enemy[1]->Draw();
	enemy[2]->Draw();
	spawing->Draw();
	player->Draw(dxCommon);
	ui->Draw();
	Sprite::PreDraw();
	//背景用
	switch (tutorial) {
	case 1:
		concent2->Draw();
		break;
	case 3:
		concent3->Draw();
		break;
	case 5:
		concent4->Draw();
		break;
	case 7:
		concent5->Draw();
		break;

	default:
		break;
	}
	// パーティクルの描画
	particleMan->Draw(dxCommon->GetCmdList());
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
