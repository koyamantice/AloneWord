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

	//オブジェクト初期化
	/*modelGround = Model::CreateFromOBJ("ground");
	objFloor = Object3d::Create();
	objFloor->Initialize();
	objFloor->SetModel(modelGround);
	objFloor->SetPosition({ 0,-1,0 });*/
	//ステージ床
	objFloor = Object3d::Create();
	modelFloor = Model::CreateFromOBJ("floor");
	objFloor->SetModel(modelFloor);
	objFloor->SetPosition({ 0, -1, 0 });
	objFloor->SetScale({ 4.0f,1.0f,5.0f });

	//ステージマップ
	modelStartMap = Model::CreateFromOBJ("StartMap");
	objStartMap = TouchableObject::Create(modelStartMap);
	objStartMap->SetPosition({ 0,-1,2 });
	objStartMap->SetRotation({ 0, 90, 0 });
	objStartMap->SetScale({ 1.4f,1.5f,1.6f });
	//バリケード
	for (std::size_t i = 0; i < objBlock.size(); i++) {
		objBlock[i] = Object3d::Create();
		modelBlock[i] = Model::CreateFromOBJ("Fork");
		objBlock[i]->SetModel(modelBlock[i]);
		BlockRotation[i] = { 0.0f,90.0f,0.0f };
		objBlock[i]->SetRotation(BlockRotation[i]);
	}
	//バリケード的なやつの各場所設定
	objBlock[0]->SetPosition({ -5.5f,0.0f,-25.0f });
	objBlock[1]->SetPosition({ 3.5f,0.0f,-25.0f });
	objBlock[2]->SetPosition({ -5.5f,0.0f, 25.0f });
	objBlock[3]->SetPosition({ 3.5f,0.0f, 25.0f });

	//普通のテクスチャ(板ポリ)
	warp = new Warp;
	warp->Initialize();
	warp->SetPosition({ 0.0f,10.0f,50.0f });
	/*limit = texture::create(1, { 0,0,0 }, { 12,12,12 }, { 1,1,1,0.6f });
	limit->texturecreate();
	limit->setposition({ 0.0f,0.01f,0.0f });
	limit->setrotation({ 90.0f,0, 0 });
	limit->setscale({ 5.5f, 5.5f,  5.5f});*/
	//背景スプライト生成
	concent = Sprite::Create(ImageManager::concent, { 0.0f,0.0f });
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
	player->SetPosition({ 0.0f,0.0f,-30.0f });
	//player->SetPosition({ 0.0f,0.0f,-30.0f });

	// パーティクルマネージャ生成
	particleMan = ParticleManager::GetInstance();
	particleMan->SetCamera(camera);


	ui = new UI(player);
	spawing = new Spawning();
	spawing->SetPlayer(player);
	spawing->Initialize();

	spawing->SetPosition({ -20.0f,0.0f,-4.0f });
	spawing->SetRotation({ 0,90,0 });

	//spawing[1]->SetPosition({ 0,0.0f,8.0f });
	//spawing[1]->SetRotation({ 0,90,0 });

	//spawing[2]->SetPosition({ 20.0f,0.0f,-4.0f });
	//spawing[2]->SetRotation({ 0,90,0 });

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
	//３ｄのモデルのデリート
	//for (int i = 0; i < StartEnemyMax; i++) {
	//	enemy[i]->Finalize();
	//}
		spawing->Finalize();

	for (std::size_t i = 0; i < objBlock.size(); i++) {
		delete objBlock[i];
		delete modelBlock[i];
	}
	player->Finalize();
	delete modelFloor;
	delete objFloor;
	delete modelStartMap;
	delete objStartMap;
	//delete object1;
	//delete model1;
	warp->Finalize();
}

void StartMap::Update(DirectXCommon* dxCommon) {
	if (pause) {
		particleMan->Update();
		//for (std::size_t i = 0; i < spawing.size(); i++) {
		//	spawing->Update();
		//}
		Pause(set);
		return;
	} else {
		hit = false;
	}
	for (int j = 0; j < spawing->GetEneMax(); j++) {
			if (spawing->GetEnemy(j)->collideAttackArm()) {
				set = 30;
				set = 15;
				pause = true;
				break;
			}
	}
	objFloor->Update();
	objStartMap->Update();
	lightGroup->Update();
	camera->Update();
	player->Update();
	particleMan->Update();
	warp->Update(player);
	for (std::size_t i = 0; i < objBlock.size(); i++) {
		objBlock[i]->SetRotation(BlockRotation[i]);
		objBlock[i]->Update();
	}
		spawing->Update();
		if (spawing->collideAttackArm()&&spawing->GetIsAlive()) {
			hit = true;
			set = spawing->GetStop();
			pause = true;
		}

	if (warp->collidePlayer(player)) {
		SceneManager::GetInstance()->ChangeScene("BOSS");
	}
	for (int j = 0; j < spawing->GetEneMax(); j++) {
		player->ResetWeight(spawing->GetEnemy(j));
		player->Rebound(spawing->GetEnemy(j));
	}

	if (input->TriggerKey(DIK_C || input->TriggerButton(input->Button_X))) {
		Audio::GetInstance()->StopWave(0);
		Audio::GetInstance()->StopWave(1);
		Audio::GetInstance()->LoopWave(1, 0.7f);
	}
	if (input->TriggerKey(DIK_SPACE)) {
		set = 15;
		pause = true;
	}

	////敵同士の当たり判定
	//if (sizeof(enemy) > 2) {//配列のサイズ確認
	//	for (int colA = 0; colA < StartEnemyMax; colA++) {
	//		for (int colB = 1; colB < StartEnemyMax; colB++) {
	//			if (Collision::CheckSphere2Sphere(enemy[colA]->collider, enemy[colB]->collider) == true && colA != colB) {//当たり判定と自機同士の当たり判定の削除
	//				//DebugText::GetInstance()->Print("Hit", 0, 0, 5.0f);
	//				enemy[colA]->SetHit(true);
	//				enemy[colB]->SetHit(false);
	//				break;

	//			}
	//			else {
	//				enemy[colA]->SetHit(false);
	//			}
	//		}
	//	}
	//}
	//for (std::size_t i = 0; i < spawing.size(); i++) {
	//	for (int colA = 0; colA < 5; colA++) {
	//		for (int colB = 1; colB < 5; colB++) {
	//			if (spawing->GetEnemy(colA)->GetIsAlive()) {
	//				if (Collision::CheckSphere2Sphere(spawing->GetEnemy(colA)->collider, spawing->GetEnemy(colB)->collider) == true && colA != colB) {//当たり判定と自機同士の当たり判定の削除
	//					spawing->GetEnemy(colA)->SetHit(true);
	//					spawing->GetEnemy(colB)->SetHit(false);
	//					break;

	//				} else {
	//					spawing->GetEnemy(colA)->SetHit(false);
	//				}
	//			}
	//		}
	//	}
	//}

	//その他シーン移行

	/*if (bossenemy->GetHP() <= 0) {
		SceneManager::GetInstance()->ChangeScene("CLEAR");
	}*/


	Ray ray;
	ray.start = { player->GetPosition().x,player->GetPosition().y + 3,player->GetPosition().z,1 };
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
		Clear = true;
	}

	if (player->GetPosition().z >= -22) {
		start = true;
	}

	if (!Clear) {
		if (player->GetPosition().z >= 23.9f) {
			player->SetPosition({ player->GetPosition().x,0,23.9f });
		}
		if (player->GetPosition().z <= -22 && start) {
			player->SetPosition({ player->GetPosition().x,0,-22 });
		}
		if (start == true) {
			if (BlockRotation[0].x <= 45.0f) {
				BlockRotation[0].x += 4.5f;
				BlockRotation[2].x += 4.5f;
			}

			if (BlockRotation[1].x >= -45.0f) {
				BlockRotation[1].x -= 4.5f;
				BlockRotation[3].x -= 4.5f;
			}
		}
	}
	else {
		if (BlockRotation[0].x >= 0.0f) {
			BlockRotation[0].x -= 4.5f;
			BlockRotation[2].x -= 4.5f;
		}

		if (BlockRotation[1].x <= 0.0f) {
			BlockRotation[1].x += 4.5f;
			BlockRotation[3].x += 4.5f;
		}
	}

	if (player->GetHp() <= 0) {
		SceneManager::GetInstance()->ChangeScene("GAMEOVER");
	}
	ui->Update();
	cameraPos.x = player->GetTargetPosition().x;
	cameraPos.y = player->GetTargetPosition().y + distanceY;
	cameraPos.z = player->GetPosition().z - distanceZ;
	camera->SetTarget(player->GetTargetPosition());
	camera->SetEye(cameraPos);
	if (player->GetArmWeight() > 0) {
		DebugText::GetInstance()->Print("RB or LB :Rotate", 900, 620, 2.0f);
	}
	DebugText::GetInstance()->Print("A         :Hand", 900, 650, 2.0f);
}

void StartMap::Draw(DirectXCommon* dxCommon) {
	ImGui::Begin("test");
	if (ImGui::TreeNode("Debug"))
	{
		if (ImGui::TreeNode("Field"))
		{
			float a = (float)XorShift::GetInstance()->xor128();
			ImGui::SliderFloat("a", &a, 100, 0);
			ImGui::SliderFloat("b", &distanceZ, 50, -50);
			ImGui::Unindent();
			ImGui::TreePop();
		}
		ImGui::TreePop();
	}
	ImGui::End();
	Object3d::PreDraw();
	//objFloor->Draw();
	//objFloor->Draw();
	//objStartMap->Draw();
	for (std::size_t i = 0; i < objBlock.size(); i++) {
		objBlock[i]->Draw();
	}
	Texture::PreDraw();



	warp->Draw();
	Object3d::PreDraw();
	//背景用
	player->Draw(dxCommon);
	spawing->Draw();
	ui->Draw();
	Sprite::PreDraw();
	//背景用
	if (hit) {
		concent->Draw();
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
	player->Pause(Timer);
	spawing->Pause(Timer);
}
