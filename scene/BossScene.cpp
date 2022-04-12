#include "BossScene.h"
#include "Audio.h"
#include "DebugText.h"
#include "TitleScene.h"
#include "FbxLoader.h"
#include"Collision.h"
#include "TouchableObject.h"
#include "MeshCollider.h"
#include "SphereCollider.h"
#include "CollisionManager.h"
void BossScene::Initialize(DirectXCommon* dxCommon) {
	Texture::LoadTexture(0, L"Resources/2d/enemy.png");
	Texture::LoadTexture(1, L"Resources/2d/limit.png");
	Texture::LoadTexture(2, L"Resources/2d/shadow.png");
	Texture::LoadTexture(3, L"Resources/2d/Resporn.png");
	Texture::LoadTexture(4, L"Resources/2d/effect2.png");
	//インスタンス取得
	collsionManager = CollisionManager::GetInstance();
	// カメラ生成
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height);
	Texture::SetCamera(camera);
	// 3Dオブジェクトにカメラをセット
	Object3d::SetCamera(camera);
	//各オブジェクトの初期化
	//プレイヤー
	player = new Player();
	player->Initialize();
	player->SetMove(250.0f, 200.0f);

	//ボス
	bossenemy = new BossEnemy();
	bossenemy->SetPlayer(player);
	bossenemy->Initialize();

	//敵
	for (int i = 0; i < BossEnemyMax; i++) {
		enemy[i] = new Rice();
		enemy[i]->SetPlayer(player);
		enemy[i]->Initialize();
	}

	//ステージ床
	objFloor = Object3d::Create();
	modelFloor = Model::CreateFromOBJ("floor");
	objFloor->SetModel(modelFloor);
	objFloor->SetPosition({ 0, -1, 0 });
	objFloor->SetScale({ 3.0f,1.0f,3.0f });

	//ステージマップ
	modelBossMap = Model::CreateFromOBJ("BossMap");
	objBossMap = TouchableObject::Create(modelBossMap);
	objBossMap->SetPosition({ 0,-1,2 });
	objBossMap->SetRotation({ 0, 90, 0 });
	objBossMap->SetScale({ 1.4f,1.5f,1.6f });
	/*objBossMap->SetModel(modelBossMap);
	objBossMap->SetPosition({ 0,-1,2 });
	objBossMap->SetRotation({ 0, 90, 0 });
	objBossMap->SetScale({ 1.4f,1.5f,1.6f });
	*/
	//当たり判定確認用です

	objSphere = Object3d::Create();
	modelSphere = Model::CreateFromOBJ("sphere");
	objSphere->SetModel(modelSphere);
	objSphere->SetPosition({ -10, 1, 0 });
	// コライダーの追加
	//objSphere->SetCollider(new SphereCollider);

	//普通のテクスチャ(板ポリ)
	/*limit = Texture::Create(1, { 0,0,0 }, { 12,12,12 }, { 1,1,1,0.6f });
	objBossMap->SetPosition({ 0,-1,10 });
	objBossMap->SetScale({ 22,1,10 });
	//譎ｮ騾壹・繝・け繧ｹ繝√Ε(譚ｿ繝昴Μ)
	limit = Texture::Create(1, { 0,0,0 }, { 12,12,12 }, { 1,1,1,0.6f });
	limit->TextureCreate();
	limit->SetPosition({ 0.0f,0.01f,0.0f });
	limit->SetRotation({ 90.0f,0, 0 });
	limit->SetScale({ 6,5,5 });*/

	for (int i = 0; i < EffectMax; i++) {
		effect[i] = new Effect();
		effect[i]->Initialize();
	}

	for (int i = 0; i < ExpMax; i++) {
		for (int j = 0; j < BossEnemyMax; j++) {
			exp[i][j] = new Exp();
			exp[i][j]->Initialize();
		}
	}

	Audio::GetInstance()->LoadSound(1, "Resources/BGM/NewWorld.wav");
	//srand(NULL);
	// ライト生成
	lightGroup = LightGroup::Create();
	// 3Dオブジェクトにライトをセット
	Object3d::SetLightGroup(lightGroup);

	// カメラ注視点をセット
	camera->SetTarget(player->GetTargetPosition());
	camera->SetEye({ player->GetTargetPosition().x,player->GetTargetPosition().y + 10,player->GetTargetPosition().z - 10 });
	// モデル名を指定してファイル読み込み
	model1 = FbxLoader::GetInstance()->LoadModelFromFile("bonetest");

	// デバイスをセット
	FBXObject3d::SetDevice(dxCommon->GetDev());
	// カメラをセット
	FBXObject3d::SetCamera(camera);
	// グラフィックスパイプライン生成
	FBXObject3d::CreateGraphicsPipeline();
	// パーティクルマネージャ生成
	particleMan = ParticleManager::GetInstance();
	particleMan->SetCamera(camera);


	object1 = new FBXObject3d;
	object1->Initialize();
	object1->SetModel(model1);
	object1->SetScale({ 3.0f,3.0f,3.0f });

	ui = new UI(player, bossenemy);
	//ui->Initialize();
}

void BossScene::Finalize() {

	//3dのモデルのデリート
	for (int i = 0; i < BossEnemyMax; i++) {
		enemy[i]->Finalize();
	}
	player->Finalize();
	bossenemy->Finalize();
	delete objBossMap;
	delete objFloor;
	delete modelBossMap;
	delete modelFloor;
	for (int i = 0; i < EffectMax; i++) {
		effect[i]->Finalize();
	}
	for (int i = 0; i < ExpMax; i++) {
		for (int j = 0; j < BossEnemyMax; j++) {
			exp[i][j]->Finalize();
		}
	}
	delete camera;
	delete object1;
	delete model1;
}

void BossScene::Update(DirectXCommon* dxCommon) {
	//objBossMap->Update();
	//各オブジェクトの更新
	objBossMap->Update();
	objFloor->Update();
	lightGroup->Update();
	camera->Update();
	player->Update();
	bossenemy->Update();
	particleMan->Update();
	//objSphere->Update();
	ui->Update();
	for (int i = 0; i < BossEnemyMax; i++) {
		enemy[i]->Update();
		enemy[i]->SetEnemy();
		player->ResetWeight(enemy[i]);
		player->Rebound(enemy[i]);
	}


	for (int i = 0; i < ExpMax; i++) {
		for (int j = 0; j < BossEnemyMax; j++) {
			exp[i][j]->Update(player, enemy[j]);
		}
	}

	for (int i = 0; i < EffectMax; i++) {
		effect[i]->Update(bossenemy);
	}

	if (input->TriggerKey(DIK_C || input->TriggerButton(input->Button_X))) {
		Audio::GetInstance()->StopWave(0);
		Audio::GetInstance()->StopWave(1);
		Audio::GetInstance()->LoopWave(1, 0.7f);
	}
	if (input->TriggerKey(DIK_SPACE)) {
		int a = 0;
		a += 1;
	}

	//敵同士の当たり判定
	if (sizeof(enemy) > 2) {//配列のサイズ確認
		for (int colA = 0; colA < BossEnemyMax; colA++) {
			for (int colB = 1; colB < BossEnemyMax; colB++) {
				if (Collision::CheckSphere2Sphere(enemy[colA]->collider, enemy[colB]->collider) == true && colA != colB) {//蠖薙◆繧雁愛螳壹→閾ｪ讖溷酔螢ｫ縺ｮ蠖薙◆繧雁愛螳壹・蜑企勁
					//DebugText::GetInstance()->Print("Hit", 0, 0, 5.0f);
					enemy[colA]->SetHit(true);
					enemy[colB]->SetHit(false);
					break;
				}
				else {
					enemy[colA]->SetHit(false);
				}
			}
		}
	}

	//その他シーン移行
	if (bossenemy->GetHP() <= 0) {
		SceneManager::GetInstance()->ChangeScene("CLEAR");
	}

	if (player->GetHp() <= 0) {
		SceneManager::GetInstance()->ChangeScene("GAMEOVER");
	}
	//object1->Update();
		// カメラ注視点をセット
	camera->SetTarget(player->GetTargetPosition());
	camera->SetEye({ player->GetTargetPosition().x,player->GetTargetPosition().y + 10,player->GetTargetPosition().z - 10 });
	// 全ての衝突をチェック
	//collsionManager->CheckAllCollisions();
	/*DebugText::GetInstance()->Print("PUSH to RB!!",200, 100,1.0f);
	DebugText::GetInstance()->Print("PUSH to A!!", 200, 115, 1.0f);*/
	DebugText::GetInstance()->Print("RB or LB :Rotate", 900, 620, 2.0f);
	DebugText::GetInstance()->Print("A         :Hand", 900, 650, 2.0f);
	//DebugText::GetInstance()->Print("PUSH to RB!!", 1040, 620, 2.0f);
	//DebugText::GetInstance()->Print("PUSH to A!!", 1040, 660, 2.0f);
}

void BossScene::Draw(DirectXCommon* dxCommon) {
	//各オブジェクトの描画
	Object3d::PreDraw();
	//objBossMap->Draw();
	//objSphere->Draw();
	objBossMap->Draw();
	objFloor->Draw();

	Texture::PreDraw();
	//limit->Draw();
	//Sprite::PreDraw();
	//sprite->Draw();

	//object1->Draw(dxCommon->GetCmdList());

	player->Draw();
	for (int i = 0; i < BossEnemyMax; i++) {
		enemy[i]->Draw();
	}
	bossenemy->Draw();

	for (int i = 0; i < EffectMax; i++) {
		effect[i]->Draw();
	}

	for (int i = 0; i < ExpMax; i++) {
		for (int j = 0; j < BossEnemyMax; j++) {
			exp[i][j]->Draw();
		}
	}

	ui->Draw();
	// パーティクルの描画
	particleMan->Draw(dxCommon->GetCmdList());
}