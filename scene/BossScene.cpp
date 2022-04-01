#include "BossScene.h"
#include "Audio.h"
#include "DebugText.h"
#include "TitleScene.h"
#include "FbxLoader.h"
#include"Collision.h"

void BossScene::Initialize(DirectXCommon* dxCommon) {
	Texture::LoadTexture(0, L"Resources/2d/enemy.png");
	Texture::LoadTexture(1, L"Resources/2d/limit.png");
	Texture::LoadTexture(2, L"Resources/2d/shadow.png");
	Texture::LoadTexture(3, L"Resources/2d/Resporn.png");
	Texture::LoadTexture(4, L"Resources/2d/effect2.png");
	// カメラ生成
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height);
	Texture::SetCamera(camera);
	// 3Dオブジェクトにカメラをセット
	Object3d::SetCamera(camera);
	player = new Player();
	player->Initialize();
	player->SetMove(25.0f, 20.0f);

	bossenemy = new BossEnemy();
	bossenemy->SetPlayer(player);
	bossenemy->Initialize();

	for (int i = 0; i < BossEnemyMax; i++) {
		enemy[i] = new Enemy();
		enemy[i]->SetPlayer(player);
		enemy[i]->Initialize();
	}

	modelground = Model::CreateFromOBJ("ground");
	objground = Object3d::Create();
	objground->Initialize();
	objground->SetModel(modelground);
	objground->SetPosition({ 0,-1,2 });
	objground->SetRotation({ 0, 90, 0 });
	objground->SetScale({ 1.4f,1.5f,1.6f });
	//���ʂ̃e�N�X�`��(�|��)
	/*limit = Texture::Create(1, { 0,0,0 }, { 12,12,12 }, { 1,1,1,0.6f });
=======
	objground->SetPosition({ 0,-1,10 });
	objground->SetScale({ 22,1,10 });
	//普通のテクスチャ(板ポリ)
	limit = Texture::Create(1, { 0,0,0 }, { 12,12,12 }, { 1,1,1,0.6f });
>>>>>>> 87afadc362bebdd4edb1f0132e0338e4585dc7db
	limit->TextureCreate();
	limit->SetPosition({ 0.0f,0.01f,0.0f });
	limit->SetRotation({ 90.0f,0, 0 });
	limit->SetScale({ 6,5,5 });*/

	for (int i = 0; i < EffectMax; i++) {
		effect[i] = new Effect();
		effect[i]->Initialize();
	}
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

	ui = new UI(player,bossenemy);
	//ui->Initialize();
}

void BossScene::Finalize() {

	//３ｄのモデルのデリート
	for (int i = 0; i < BossEnemyMax; i++) {
		enemy[i]->Finalize();
	}
	player->Finalize();
	bossenemy->Finalize();
}

void BossScene::Update(DirectXCommon* dxCommon) {
	//objGround->Update();
	objground->Update();
	lightGroup->Update();
	camera->Update();
	player->Update();
	bossenemy->Update();
<<<<<<< HEAD
	//limit->Update();
=======
	limit->Update();
	weight = player->GetArmWeight();
	
	for (int i = 0; i < EffectNum; i++) {
		effect[i]->Update(bossenemy);
	}
>>>>>>> 87afadc362bebdd4edb1f0132e0338e4585dc7db
	ui->Update();
	for (int i = 0; i < BossEnemyMax; i++) {
		enemy[i]->Update();
		
		player->ResetWeight(enemy[i]);
		player->Rebound(enemy[i]);
	}

	for (int i = 0; i < BossEnemyMax; i++) {
		enemy[i]->SetEnemy();
	}

	if (player->GetArmWeight() == 1) {
		EffectNum = 1;
	} else if (player->GetArmWeight() >= 2 && player->GetArmWeight() < 4) {
		EffectNum = 10;
	} else if (player->GetArmWeight() >= 4 && player->GetArmWeight() < 6) {
		EffectNum = 30;
	} else {
		EffectNum = 70;
	}
	
	if (input->TriggerKey(DIK_C || input->TriggerButton(input->Button_X))) {
		Audio::GetInstance()->StopWave(0);
		Audio::GetInstance()->StopWave(1);
		Audio::GetInstance()->LoopWave(1,0.7f);
	}
	if (input->TriggerKey(DIK_SPACE)) {
		int a = 0;
		a += 1;
	}

	//敵同士の当たり判定
	if (sizeof(enemy) > 2) {//配列のサイズ確認
		for (int colA = 0; colA < BossEnemyMax; colA++) {
			for (int colB = 1; colB < BossEnemyMax; colB++) {
				if (Collision::CheckSphere2Sphere(enemy[colA]->collider, enemy[colB]->collider) == true && colA != colB) {//当たり判定と自機同士の当たり判定の削除
					DebugText::GetInstance()->Print("Hit", 0, 0, 5.0f);
					enemy[colA]->SetHit(true);
					enemy[colB]->SetHit(false);
					break;
				} else {
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
	object1->Update();
	camera->SetTarget(player->GetPosition());
	camera->SetEye({ player->GetPosition().x,player->GetPosition().y + 10,player->GetPosition().z - 10 });
	DebugText::GetInstance()->Print("PUSH to RB!!",200, 100,1.0f);
	DebugText::GetInstance()->Print("PUSH to A!!", 200, 115, 1.0f);
}

void BossScene::Draw(DirectXCommon* dxCommon) {
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
	ImGui::Begin("test");
	if (ImGui::TreeNode("Debug"))
	{
		if (ImGui::TreeNode("Joy"))
		{
			ImGui::Text("IY %d", EffectNum);
			ImGui::SliderFloat("PlayerArm", &weight, 50, -50);
			ImGui::Unindent();
			ImGui::TreePop();
		}

		ImGui::TreePop();
	}
	ImGui::End();
	Object3d::PreDraw();
	//objGround->Draw();
	objground->Draw();

	Texture::PreDraw();
	//limit->Draw();
	//Sprite::PreDraw();
	//背景用
	//sprite->Draw();


	//object1->Draw(dxCommon->GetCmdList());
	//背景用

	player->Draw();
	for (int i = 0; i < BossEnemyMax; i++) {
		enemy[i]->Draw();
	}
	bossenemy->Draw();

	for (int i = 0; i < EffectNum; i++) {
		effect[i]->Draw();
	}
	ui->Draw();
}