#include "StartMap.h"
#include "Audio.h"
#include "DebugText.h"
#include "TitleScene.h"
#include "FbxLoader.h"
void StartMap::Initialize(DirectXCommon* dxCommon) {
	Texture::LoadTexture(0, L"Resources/2d/enemy.png");
	Texture::LoadTexture(1, L"Resources/2d/limit.png");
	Texture::LoadTexture(2, L"Resources/2d/shadow.png");
	Texture::LoadTexture(3, L"Resources/2d/Resporn.png");
	Texture::LoadTexture(4, L"Resources/2d/effect2.png");
	Texture::LoadTexture(5, L"Resources/2d/PlayerHP.png");
	// カメラ生成
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height);
	Texture::SetCamera(camera);
	// 3Dオブジェクトにカメラをセット
	Object3d::SetCamera(camera);
	player = new Player();
	player->Initialize();
	player->SetMove(50.0f, 50.0f);

	for (int i = 0; i < StartEnemyMax; i++) {
		enemy[i] = new Enemy();
		enemy[i]->SetPlayer(player);
		enemy[i]->Initialize();
		enemy[i]->SetLimit({100,-100,100,-100});
	}
	for (int i = 0; i < 3; i++) {
		spawing[i] = new Spawning();
		spawing[i]->SetPosition({ -15.0f+i*15.0f,0,30 });
		spawing[i]->Initialize();
		spawing[i]->SetPlayer(player);
	}
	for (int i = 0; i < StartEnemyMax; i++) {
		spawing[0]->SetEnemy(i, enemy[i]);
	}
	//オブジェクト初期化
	/*modelGround = Model::CreateFromOBJ("ground");
	objGround = Object3d::Create();
	objGround->Initialize();
	objGround->SetModel(modelGround);
	objGround->SetPosition({ 0,-1,0 });*/

	modelground = Model::CreateFromOBJ("ground");
	objground = Object3d::Create();
	objground->Initialize();
	objground->SetModel(modelground);
	objground->SetPosition({ 0,-1,0 });
	objground->SetScale({ 0.1f,1.0f,0.1f });

	modeltree = Model::CreateFromOBJ("StartMap");
	objtree = Object3d::Create();
	objtree->Initialize();
	objtree->SetModel(modeltree);
	objtree->SetPosition({ 0,-5,50 });
	objtree->SetRotation({ 0,90,0 });
	objtree->SetScale({ 1.8f,1.8f,1.8f });
	//普通のテクスチャ(板ポリ)

	/*limit = Texture::Create(1, { 0,0,0 }, { 12,12,12 }, { 1,1,1,0.6f });
	limit->TextureCreate();
	limit->SetPosition({ 0.0f,0.01f,0.0f });
	limit->SetRotation({ 90.0f,0, 0 });
	limit->SetScale({ 6,5,5 });*/

	//背景スプライト生成

	// モデル読み込み
	Audio::GetInstance()->LoadSound(1, "Resources/BGM/NewWorld.wav");
	//srand(NULL);
	// ライト生成
	lightGroup = LightGroup::Create();
	// 3Dオブエクトにライトをセット
	Object3d::SetLightGroup(lightGroup);

	// カメラ注視点をセット
	camera->SetTarget(player->GetPosition());
	camera->SetEye({ player->GetPosition().x,player->GetPosition().y + 10,player->GetPosition().z - 10 });
	// モデル名を指定してファイル読み込み
	model1 = FbxLoader::GetInstance()->LoadModelFromFile("boneTest");

	// デバイスをセット
	FBXObject3d::SetDevice(dxCommon->GetDev());
	// カメラをセット
	FBXObject3d::SetCamera(camera);
	// グラフィックスパイプライン生成
	FBXObject3d::CreateGraphicsPipeline();

	object1 = new FBXObject3d;
	object1->Initialize();
	object1->SetModel(model1);
}

void StartMap::Finalize() {

	//３ｄのモデルのデリート
	for (int i = 0; i < StartEnemyMax; i++) {
		enemy[i]->Finalize();
	}
	//player->Finalize();

	//bossenemy->Finalize();

}

void StartMap::Update(DirectXCommon* dxCommon) {
	//objGround->Update();
	objground->Update();
	objtree->Update();
	lightGroup->Update();
	camera->Update();
	player->Update();
	for (int i = 0; i < StartEnemyMax; i++) {
		spawing[1]->SetEnemy(i, enemy[i]);
	}
	for (int i = 0; i < 3; i++) {
		spawing[i]->Update();
	}
	//bossenemy->Update();
	//limit->Update();

	for (int i = 0; i < StartEnemyMax; i++) {
		//enemy[i]->Update();

		//player->ResetWeight(enemy[i]);
		//player->Rebound(enemy[i]);
	}

	for (int i = 0; i < StartEnemyMax; i++) {
		enemy[i]->SetEnemy();
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
		for (int colA = 0; colA < StartEnemyMax; colA++) {
			for (int colB = 1; colB < StartEnemyMax; colB++) {
				if (Collision::CheckSphere2Sphere(enemy[colA]->collider, enemy[colB]->collider) == true && colA != colB) {//当たり判定と自機同士の当たり判定の削除
					DebugText::GetInstance()->Print("Hit", 0, 0, 5.0f);
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

	/*if (bossenemy->GetHP() <= 0) {
		SceneManager::GetInstance()->ChangeScene("CLEAR");
	}*/


	if (player->GetHp() <= 0) {
		SceneManager::GetInstance()->ChangeScene("GAMEOVER");
	}
	object1->Update();
	camera->SetTarget(player->GetPosition());
	camera->SetEye({ player->GetPosition().x,player->GetPosition().y + 10,player->GetPosition().z - 10 });
	DebugText::GetInstance()->Print("PUSH to RB!!", 200, 100, 1.0f);
	DebugText::GetInstance()->Print("PUSH to A!!", 200, 115, 1.0f);
}

void StartMap::Draw(DirectXCommon* dxCommon) {
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
	Object3d::PreDraw();
	//objGround->Draw();
	//objground->Draw();
	objtree->Draw();
	Texture::PreDraw();
	//limit->Draw();


	//Sprite::PreDraw();
	//背景用
	//sprite->Draw();


	Object3d::PreDraw();
	//object1->Draw(dxCommon->GetCmdList());
	//背景用
	player->Draw();
	for (int i = 0; i < StartEnemyMax; i++) {
		enemy[i]->Draw();
	}
	for (int i = 0; i < 3; i++) {
		spawing[i]->Draw();
	}
	//bossenemy->Draw();

}