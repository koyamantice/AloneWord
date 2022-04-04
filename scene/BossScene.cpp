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
	// 繧ｫ繝｡繝ｩ逕滓・
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height);
	Texture::SetCamera(camera);
	// 3D繧ｪ繝悶ず繧ｧ繧ｯ繝医↓繧ｫ繝｡繝ｩ繧偵そ繝・ヨ
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
	objground = TouchableObject::Create(modelground);
	objground->SetPosition({ 0,-1,2 });
	objground->SetRotation({ 0, 90, 0 });
	objground->SetScale({ 1.4f,1.5f,1.6f });
	/*objground->SetModel(modelground);
	objground->SetPosition({ 0,-1,2 });
	objground->SetRotation({ 0, 90, 0 });
	objground->SetScale({ 1.4f,1.5f,1.6f });
	*/
	//当たり判定確認用です
	objSphere = Object3d::Create();
	modelSphere = Model::CreateFromOBJ("sphere");
	objSphere->SetModel(modelSphere);
	objSphere->SetPosition({ -10, 1, 0 });
	// コライダーの追加
	objSphere->SetCollider(new SphereCollider);

	//普通のテクスチャ(板ポリ)
	/*limit = Texture::Create(1, { 0,0,0 }, { 12,12,12 }, { 1,1,1,0.6f });
	objground->SetPosition({ 0,-1,10 });
	objground->SetScale({ 22,1,10 });
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
	// 繝ｩ繧､繝育函謌・
	lightGroup = LightGroup::Create();
	// 3D繧ｪ繝悶お繧ｯ繝医↓繝ｩ繧､繝医ｒ繧ｻ繝・ヨ
	Object3d::SetLightGroup(lightGroup);

	// 繧ｫ繝｡繝ｩ豕ｨ隕也せ繧偵そ繝・ヨ
	camera->SetTarget(player->GetPosition());
	camera->SetEye({ player->GetPosition().x,player->GetPosition().y + 10,player->GetPosition().z - 10 });
	// 繝｢繝・Ν蜷阪ｒ謖・ｮ壹＠縺ｦ繝輔ぃ繧､繝ｫ隱ｭ縺ｿ霎ｼ縺ｿ
	model1 = FbxLoader::GetInstance()->LoadModelFromFile("boneTest");

	// 繝・ヰ繧､繧ｹ繧偵そ繝・ヨ
	FBXObject3d::SetDevice(dxCommon->GetDev());
	// 繧ｫ繝｡繝ｩ繧偵そ繝・ヨ
	FBXObject3d::SetCamera(camera);
	// 繧ｰ繝ｩ繝輔ぅ繝・け繧ｹ繝代う繝励Λ繧､繝ｳ逕滓・
	FBXObject3d::CreateGraphicsPipeline();

	object1 = new FBXObject3d;
	object1->Initialize();
	object1->SetModel(model1);

	ui = new UI(player,bossenemy);
	//ui->Initialize();
}

void BossScene::Finalize() {

	//・難ｽ・・繝｢繝・Ν縺ｮ繝・Μ繝ｼ繝・
	for (int i = 0; i < BossEnemyMax; i++) {
		enemy[i]->Finalize();
	}
	//player->Finalize();
	bossenemy->Finalize();
}

void BossScene::Update(DirectXCommon* dxCommon) {
	//objGround->Update();
	objground->Update();
	lightGroup->Update();
	camera->Update();
	player->Update();
	bossenemy->Update();
	objSphere->Update();

	ui->Update();
	for (int i = 0; i < BossEnemyMax; i++) {
		enemy[i]->Update();
		enemy[i]->SetEnemy();
		/*player->ResetWeight(enemy[i]);
		player->Rebound(enemy[i]);*/
	}


	for (int i = 0; i < ExpMax; i++) {
		for(int j = 0; j < BossEnemyMax;j++){
			exp[i][j]->Update(player, enemy[j]);
		}
	}

	for (int i = 0; i < EffectMax; i++) {
		effect[i]->Update(bossenemy);
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

	//謨ｵ蜷悟｣ｫ縺ｮ蠖薙◆繧雁愛螳・
	if (sizeof(enemy) > 2) {//驟榊・縺ｮ繧ｵ繧､繧ｺ遒ｺ隱・
		for (int colA = 0; colA < BossEnemyMax; colA++) {
			for (int colB = 1; colB < BossEnemyMax; colB++) {
				if (Collision::CheckSphere2Sphere(enemy[colA]->collider, enemy[colB]->collider) == true && colA != colB) {//蠖薙◆繧雁愛螳壹→閾ｪ讖溷酔螢ｫ縺ｮ蠖薙◆繧雁愛螳壹・蜑企勁
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

	//縺昴・莉悶す繝ｼ繝ｳ遘ｻ陦・
	if (bossenemy->GetHP() <= 0) {
		SceneManager::GetInstance()->ChangeScene("CLEAR");
	}

	if (player->GetHp() <= 0) {
		SceneManager::GetInstance()->ChangeScene("GAMEOVER");
	}
	object1->Update();
	camera->SetTarget(player->GetPosition());
	camera->SetEye({ player->GetPosition().x,player->GetPosition().y + 10,player->GetPosition().z - 10 });
	// 全ての衝突をチェック
	collsionManager->CheckAllCollisions();
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
	objSphere->Draw();
	Texture::PreDraw();
	//limit->Draw();
	//Sprite::PreDraw();
	//閭梧勹逕ｨ
	//sprite->Draw();

	//object1->Draw(dxCommon->GetCmdList());
	//閭梧勹逕ｨ

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
}