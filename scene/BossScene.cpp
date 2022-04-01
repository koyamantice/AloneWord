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
	// ã«ã¡ã©çæE
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height);
	Texture::SetCamera(camera);
	// 3Dãªãã¸ã§ã¯ãã«ã«ã¡ã©ãã»ãE
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
	//ÊÌeNX`(Â|)
	/*limit = Texture::Create(1, { 0,0,0 }, { 12,12,12 }, { 1,1,1,0.6f });
	objground->SetPosition({ 0,-1,10 });
	objground->SetScale({ 22,1,10 });
	//æ®éãEãE¯ã¹ãã£(æ¿ããª)
	limit = Texture::Create(1, { 0,0,0 }, { 12,12,12 }, { 1,1,1,0.6f });
	limit->TextureCreate();
	limit->SetPosition({ 0.0f,0.01f,0.0f });
	limit->SetRotation({ 90.0f,0, 0 });
	limit->SetScale({ 6,5,5 });*/

	for (int i = 0; i < EffectMax; i++) {
		effect[i] = new Effect();
		effect[i]->Initialize();
	}
	//èæ¯ã¹ãã©ã¤ãçæE

	// ã¢ãE«èª­ã¿è¾¼ã¿
	Audio::GetInstance()->LoadSound(1, "Resources/BGM/NewWorld.wav");
	//srand(NULL);
	// ã©ã¤ãçæE
	lightGroup = LightGroup::Create();
	// 3Dãªãã¨ã¯ãã«ã©ã¤ããã»ãE
	Object3d::SetLightGroup(lightGroup);

	// ã«ã¡ã©æ³¨è¦ç¹ãã»ãE
	camera->SetTarget(player->GetPosition());
	camera->SetEye({ player->GetPosition().x,player->GetPosition().y + 10,player->GetPosition().z - 10 });
	// ã¢ãE«åãæE®ãã¦ãã¡ã¤ã«èª­ã¿è¾¼ã¿
	model1 = FbxLoader::GetInstance()->LoadModelFromFile("boneTest");

	// ãEã¤ã¹ãã»ãE
	FBXObject3d::SetDevice(dxCommon->GetDev());
	// ã«ã¡ã©ãã»ãE
	FBXObject3d::SetCamera(camera);
	// ã°ã©ãã£ãE¯ã¹ãã¤ãã©ã¤ã³çæE
	FBXObject3d::CreateGraphicsPipeline();

	object1 = new FBXObject3d;
	object1->Initialize();
	object1->SetModel(model1);

	ui = new UI(player,bossenemy);
	//ui->Initialize();
}

void BossScene::Finalize() {

	//Eï½EEã¢ãE«ã®ãEªã¼ãE
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

	ui->Update();
	for (int i = 0; i < BossEnemyMax; i++) {
		enemy[i]->Update();
		
		player->ResetWeight(enemy[i]);
		player->Rebound(enemy[i]);
	}

	for (int i = 0; i < BossEnemyMax; i++) {
		enemy[i]->SetEnemy();
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

	//æµåå£«ã®å½ããå¤å®E
	if (sizeof(enemy) > 2) {//éåEã®ãµã¤ãºç¢ºèªE
		for (int colA = 0; colA < BossEnemyMax; colA++) {
			for (int colB = 1; colB < BossEnemyMax; colB++) {
				if (Collision::CheckSphere2Sphere(enemy[colA]->collider, enemy[colB]->collider) == true && colA != colB) {//å½ããå¤å®ã¨èªæ©åå£«ã®å½ããå¤å®ãEåé¤
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

	//ããEä»ã·ã¼ã³ç§»è¡E
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
	//èæ¯ç¨
	//sprite->Draw();


	//object1->Draw(dxCommon->GetCmdList());
	//èæ¯ç¨

	player->Draw();
	for (int i = 0; i < BossEnemyMax; i++) {
		enemy[i]->Draw();
	}
	bossenemy->Draw();

	ui->Draw();
}