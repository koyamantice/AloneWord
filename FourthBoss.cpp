#include "FourthBoss.h"
#include "Audio.h"
#include "DebugText.h"
#include "TitleScene.h"
#include "FbxLoader.h"
#include"Collision.h"
#include "TouchableObject.h"
#include "MeshCollider.h"
#include "SphereCollider.h"
#include "CollisionManager.h"
#include <Easing.h>
void FourthBoss::Initialize(DirectXCommon* dxCommon) {
	//インスタンス取得
	collisionManager = CollisionManager::GetInstance();
	// カメラ生成
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height);
	Texture::SetCamera(camera);
	// 3Dオブジェクトにカメラをセット
	Object3d::SetCamera(camera);
	//各オブジェクトの初期化

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
	/*
	objBossMap->SetModel(modelBossMap);
	objBossMap->SetPosition({ 0,-1,2 });
	objBossMap->SetRotation({ 0, 90, 0 });
	objBossMap->SetScale({ 1.4f,1.5f,1.6f });
	*/
	
	// コライダーの追加
	//objSphere->SetCollider(new SphereCollider);

	for (std::size_t i = 0; i < effect.size(); i++) {
		effect[i] = new Effect();
		effect[i]->Initialize();
	}

	//for (std::size_t i = 0; i < exp.size(); i++) {
	//	for (std::size_t j = 0; j < exp[i].size(); j++) {
	//		exp[i][j] = new Exp();
	//		exp[i][j]->Initialize();
	//	}
	//}

	Audio::GetInstance()->LoadSound(1, "Resources/BGM/NewWorld.wav");
	//srand(NULL);
	// ライト生成
	lightGroup = LightGroup::Create();
	// 3Dオブジェクトにライトをセット
	Object3d::SetLightGroup(lightGroup);
	
	// デバイスをセット
	FBXObject3d::SetDevice(dxCommon->GetDev());
	// カメラをセット
	FBXObject3d::SetCamera(camera);
	// グラフィックスパイプライン生成
	FBXObject3d::CreateGraphicsPipeline();
	// パーティクルマネージャ生成
	particleMan = ParticleManager::GetInstance();
	particleMan->SetCamera(camera);

	shockwave = new ShockWave;
	shockwave->Init();
	//プレイヤー
	player = new Player();
	player->Initialize();
	player->SetPosition({ 0.0f,0.0f,-10.0f });
	player->SetMove(250.0f, 200.0f);

	//ボス(杵)
	pastel = new Pastel();
	pastel->SetPlayer(player);
	pastel->Initialize();
	//ボス(臼)
	/*mill = new Mill();
	mill->SetPlayer(player);
	mill->Initialize();*/
	//敵
	for (std::size_t i = 0; i < enemy.size(); i++) {
		enemy[i] = new Rice();
		enemy[i]->SetPlayer(player);
		enemy[i]->Initialize();
	}

	//当たり判定確認用です
	modelSphere = Model::CreateFromOBJ("sphere");
	objSphere = TouchableObject::Create(modelSphere);
	objSphere->SetScale({ 2.0f, 2.0f, 2.0f });
	objSphere->SetPosition({0.0f,0.0f,15.0f});

	//カメラポジション
	cameraPos.x = player->GetPosition().x;
	cameraPos.y = player->GetPosition().y + distanceY;
	cameraPos.z = player->GetPosition().z - distanceZ;
	// カメラ注視点をセット
	cameratargetPos = player->GetPosition();
	camera->SetTarget(cameratargetPos);
	camera->SetEye(cameraPos);

	ui = new UI(player, pastel);
	//ui->Initialize();
}

void FourthBoss::Finalize() {

	//3dのモデルのデリート
	for (std::size_t i = 0; i < enemy.size(); i++) {
		enemy[i]->Finalize();
	}
	player->Finalize();
	pastel->Finalize();
	//mill->Finalize();
	shockwave->Final();
	delete objBossMap;
	delete objFloor;
	delete modelBossMap;
	delete modelFloor;
	for (std::size_t i = 0; i < effect.size(); i++) {
		effect[i]->Finalize();
	}
	for (std::size_t i = 0; i < exp.size(); i++) {
		for (std::size_t j = 0; j < exp[i].size(); j++) {
			exp[i][j]->Finalize();
		}
	}
	delete camera;
}

void FourthBoss::Update(DirectXCommon* dxCommon) {
	//objBossMap->Update();
	//各オブジェクトの更新
	objBossMap->Update();
	objFloor->Update();
	lightGroup->Update();
	
	//最初の演出
	if(!bossstart){
		appearanceTimer++;
		player->Begin();
		pastel->Begin();
		pastel->MillUpdate();
		if (appearanceTimer == 1) {
			cameraPos.x = player->GetPosition().x;
			cameraPos.y = player->GetPosition().y + distanceY;
			cameraPos.z = player->GetPosition().z - distanceZ;
		}

		if (appearanceTimer == 100) {
			appearanceNumber++;
		}

		if (appearanceNumber == 1) {
			Aftereyepos = {
				pastel->GetPosition().x,
				pastel->GetPosition().y + distanceY,
				pastel->GetPosition().z - distanceZ,
			};

			Aftertargetpos = {
				pastel->GetPosition().x,
				pastel->GetPosition().y + 5.0f,
				pastel->GetPosition().z,
			};

			if (frame <= 1.0f) {
				frame += 0.01f;
			}
			else {
				frame = 1.0f;
				pastel->AppeaMovie();
				if(pastel->GetAppearanceEnd() == true){
					Interval = 0;
					frame = 0.0f;
					appearanceNumber = 2;
				}
			}

			cameraPos = {
Ease(In,Cubic,frame,cameraPos.x,Aftereyepos.x),
Ease(In,Cubic,frame,cameraPos.y,Aftereyepos.y),
Ease(In,Cubic,frame,cameraPos.z,Aftereyepos.z)
			};

			cameratargetPos = {
Ease(In,Cubic,frame,cameratargetPos.x,Aftertargetpos.x),
Ease(In,Cubic,frame,cameratargetPos.y,Aftertargetpos.y),
Ease(In,Cubic,frame,cameratargetPos.z,Aftertargetpos.z)
			};
		}
		else if (appearanceNumber == 2) {
			Aftereyepos = {
				player->GetPosition().x,
				player->GetPosition().y + distanceY,
				player->GetPosition().z - distanceZ,
			};

			Aftertargetpos = {
				player->GetPosition().x,
				player->GetPosition().y,
				player->GetPosition().z,
			};

			if (frame < 1.0f) {
				frame += 0.01f;
			}
			else {
				bossstart = true;
				appearanceTimer = 0;
				appearanceNumber = 0;
				frame = 0;
			}

			cameraPos = {
Ease(In,Cubic,frame,cameraPos.x,Aftereyepos.x),
Ease(In,Cubic,frame,cameraPos.y,Aftereyepos.y),
Ease(In,Cubic,frame,cameraPos.z,Aftereyepos.z)
			};

			cameratargetPos = {
Ease(In,Cubic,frame,cameratargetPos.x,Aftertargetpos.x),
Ease(In,Cubic,frame,cameratargetPos.y,Aftertargetpos.y),
Ease(In,Cubic,frame,cameratargetPos.z,Aftertargetpos.z)
			};
		}
		
		camera->SetTarget(cameratargetPos);
		camera->SetEye(cameraPos);
	}
	//戦闘開始
	else {
		player->Update();
		pastel->Update();
		pastel->collideAttackArm(player);
		for (std::size_t i = 0; i < enemy.size(); i++) {
			enemy[i]->Update();
			enemy[i]->SetEnemy();
			player->ResetWeight(enemy[i]);
			player->Rebound(enemy[i]);
		}
		ui->Update();
		particleMan->Update();
		objSphere->Update();
		shockwave->Upda(pastel, player);
		cameraPos.x = player->GetPosition().x;
		cameraPos.y = player->GetPosition().y + distanceY;
		cameraPos.z = player->GetPosition().z - distanceZ;
		camera->SetTarget(player->GetPosition());
		camera->SetEye(cameraPos);
	}

	camera->Update();
	/*
	for (std::size_t i = 0; i < exp.size(); i++) {
		for (std::size_t j = 0; j < exp[i].size(); j++) {
			exp[i][j]->Update(player, enemy[j]);
		}
	}*/

	for (std::size_t i = 0; i < effect.size(); i++) {
		effect[i]->Update(pastel);
	}

	if (input->TriggerKey(DIK_C || input->TriggerButton(input->Button_X))) {
		Audio::GetInstance()->StopWave(0);
		Audio::GetInstance()->StopWave(1);
		Audio::GetInstance()->LoopWave(1, 0.7f);
	}
	if (input->TriggerKey(DIK_SPACE)) {
		bossstart = true;
	}

	//敵同士の当たり判定
	if (sizeof(enemy) > 2) {//配列のサイズ確認
		for (int colA = 0; colA < FourthBossEnemyMax; colA++) {
			for (int colB = 1; colB < FourthBossEnemyMax; colB++) {
				if (Collision::CircleCollision(enemy[colA]->GetPosition().x, enemy[colA]->GetPosition().z, 3.0f, enemy[colB]->GetPosition().x, enemy[colB]->GetPosition().z, 3.0f) == true && colA != colB) {//蠖薙◆繧雁愛螳壹→閾ｪ讖溷酔螢ｫ縺ｮ蠖薙◆繧雁愛螳壹・蜑企勁
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

	Ray ray;
	ray.start = { player->GetPosition().x,player->GetPosition().y + 3,player->GetPosition().z,1 };
	ray.dir = { 0.0f,0.025f,-1.0f };
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

	//その他シーン移行
	if (pastel->GetHP() <= 0) {
		SceneManager::GetInstance()->ChangeScene("StageSelect");
	}

	if (player->GetHp() <= 0) {
		SceneManager::GetInstance()->ChangeScene("GAMEOVER");
	}
	//object1->Update();

	// 全ての衝突をチェック
	//collsionManager->CheckAllCollisions();
	/*DebugText::GetInstance()->Print("PUSH to RB!!",200, 100,1.0f);
	DebugText::GetInstance()->Print("PUSH to A!!", 200, 115, 1.0f);*/
	//DebugText::GetInstance()->Print("PUSH to RB!!", 1040, 620, 2.0f);
	//DebugText::GetInstance()->Print("PUSH to A!!", 1040, 660, 2.0f);
}

void FourthBoss::Draw(DirectXCommon* dxCommon) {
	//各オブジェクトの描画
	Object3d::PreDraw();
	//objBossMap->Draw();
	//objSphere->Draw();
	objBossMap->Draw();
	objFloor->Draw();

	Texture::PreDraw();
	shockwave->Draw();
	//limit->Draw();
	//Sprite::PreDraw();
	//sprite->Draw();

	//object1->Draw(dxCommon->GetCmdList());

	player->Draw(dxCommon);
	for (std::size_t i = 0; i < enemy.size(); i++) {
		enemy[i]->Draw();
	}
	pastel->Draw();
	
	for (std::size_t i = 0; i < effect.size(); i++) {
		effect[i]->Draw();
	}

	XMFLOAT3 pos = player->GetPosition();
	XMFLOAT3 enemypos = pastel->GetPosition();
	//ImGui::Begin("test");
	////ImGui::SliderFloat("pos.z", &pos.z, 50, 0);
	////ImGui::SliderFloat("pos.y", &pos.y, 50, 0);
	////ImGui::SliderFloat("enemypos.z", &enemypos.z, 50, 0);
	////ImGui::SliderFloat("enemypos.y", &enemypos.y, 50, 0);
	//ImGui::Text("Interval::%d", Interval);
	//ImGui::Text("appearanceTimer::%d", appearanceTimer);
	//ImGui::Unindent();
	//ImGui::End();

	ui->Draw();

	// パーティクルの描画
	particleMan->Draw(dxCommon->GetCmdList());
}