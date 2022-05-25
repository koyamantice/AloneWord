#include "FifthBoss.h"
#include "Audio.h"
#include "DebugText.h"
#include "TitleScene.h"
#include "FbxLoader.h"
#include"Collision.h"
#include "TouchableObject.h"
#include "MeshCollider.h"
#include "SphereCollider.h"
#include "CollisionManager.h"
#include "ImageManager.h"
#include <Easing.h>
void FifthBoss::Initialize(DirectXCommon* dxCommon) {
	//インスタンス取得
	collisionManager = CollisionManager::GetInstance();
	// カメラ生成
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height);
	Texture::SetCamera(camera);
	// 3Dオブジェクトにカメラをセット
	Object3d::SetCamera(camera);

	//ステージ床
	objFloor = Object3d::Create();
	modelFloor = Model::CreateFromOBJ("BedroomFloor");
	objFloor->SetModel(modelFloor);
	objFloor->SetPosition({ 0, -1, 0 });
	objFloor->SetScale({ 8.0f,1.0f,6.0f });

	//スカイドーム
	objBedroom = Object3d::Create();
	modelBedroom = Model::CreateFromOBJ("Bedroom");
	objBedroom->SetModel(modelBedroom);
	objBedroom->SetPosition({ 0, -1, 0 });
	objBedroom->SetScale({ 1.0f,1.0f,1.0f });

	//ステージマップ
	modelBossMap = Model::CreateFromOBJ("BedroomMap");
	objBossMap = TouchableObject::Create(modelBossMap);
	objBossMap->SetPosition({ 0,0,4 });
	objBossMap->SetRotation({ 0, 90, 0 });
	objBossMap->SetScale({ 3.0f, 1.5f, 3.0f });
	/*
	objBossMap->SetModel(modelBossMap);
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
	//テクスチャ関係の初期化
	bossName = Sprite::Create(ImageManager::select5, namePos);
	bossName->SetAnchorPoint({ 1.0f,0.0f });
	WhiteFilter = Sprite::Create(ImageManager::WhiteFilter, { 0.0f,0.0f });
	//WhiteFilter->SetAnchorPoint({ 1.0f,0.0f });
	WhiteFilter->SetColor(WhiteColor);

	BlackFilter = Sprite::Create(ImageManager::BlackFilter, { 0.0f,0.0f });
	BlackFilter->SetColor(BlackColor);

	GameOverSprite = Sprite::Create(ImageManager::GameOver, overPos);
	GameOverSprite->SetColor(GameOverColor);

	SkipSprite = Sprite::Create(ImageManager::Change, { 0.0f,0.0f });
	SkipSprite->SetPosition(Skippos);
	SkipSprite->SetAnchorPoint({ 0.5f, 0.5f });
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
	//srand(NULL);GetFBXModel(ModelManager::MottiMove);
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
	//各オブジェクトの初期化
	//プレイヤー
	player = new Player();
	player->Initialize();
	player->SetPosition({ 0.0f,0.0f,-10.0f });
	player->SetMove(250.0f, 200.0f);

	//ボス
	lefthand = new LeftHand();
	lefthand->SetPlayer(player);
	lefthand->Initialize(false);

	righthand = new RightHand();
	righthand->SetPlayer(player);
	righthand->Initialize(false);

	//敵
	for (std::size_t i = 0; i < enemy.size(); i++) {
		enemy[i] = new Rice();
		enemy[i]->SetPlayer(player);
		enemy[i]->Initialize();
		enemy[i]->SetLimit({ 21.0f,-17.0f,19.0f,-19.0f });
	}

	cameraPos.x = player->GetPosition().x;
	cameraPos.y = player->GetPosition().y + distanceY;
	cameraPos.z = player->GetPosition().z - distanceZ;
	camera->SetTarget(player->GetPosition());
	camera->SetEye(cameraPos);
	ui = new UI(player, lefthand, righthand);
	expandchange = new ExpandChange();
	human = new Human();
	human->init();
	//ui->Initialize();
}
//開放処理
void FifthBoss::Finalize() {
	//3dのモデルのデリート
	for (std::size_t i = 0; i < enemy.size(); i++) {
		enemy[i]->Finalize();
	}
	player->Finalize();
	lefthand->Finalize();
	righthand->Finalize();
	delete objBossMap;
	delete objFloor;
	delete modelBossMap;
	delete modelFloor;
	delete objBedroom;
	delete modelBedroom;
	for (std::size_t i = 0; i < effect.size(); i++) {
		effect[i]->Finalize();
	}
	/*for (std::size_t i = 0; i < exp.size(); i++) {
		for (std::size_t j = 0; j < exp[i].size(); j++) {
			exp[i][j]->Finalize();
		}
	}*/
	delete camera;
	delete object1;
	delete model1;
	ui->Finalize();
}

void FifthBoss::Update(DirectXCommon* dxCommon) {
	//objBossMap->Update();
	//各オブジェクトの更新
	objBossMap->Update();
	objFloor->Update();
	lightGroup->Update();
	objBedroom->Update();

	//最初の演出(導入)
	if (!end && !gameover) {
		if (Skip == true) {
			SkipTimer++;
			if (SkipTimer <= 60) {
				SkipSprite->SetScale(1.1f);
			}
			else {
				righthand->Initialize();
				lefthand->Initialize();
				bossstart = true;
				SkipSprite->SetScale(0.9f);
				if (SkipTimer == 140) {
					Skip = false;
					SkipTimer = 0;
					SkipSprite->SetScale(1.0f);
				}
			}
		}
		if (!bossstart) {
			if (input->TriggerButton(input->Button_B)) {
				Skip = true;
			}

			if (BlackColor.w >= 0.0f && appearanceNumber == 0) {
				BlackColor.w -= 0.005f;
				frame = 0.0f;
			}
			else {
				appearanceTimer++;
			}
			player->Begin();
			lefthand->Begin();
			righthand->Begin();
			righthand->AppeaMovie(appearanceTimer);
			lefthand->AppeaMovie(appearanceTimer);
			//カメラの位置をそれぞれ変更していく
			if (appearanceNumber == 0) {
				cameraPos.x = righthand->GetPosition().x + 5;
				cameraPos.y = righthand->GetPosition().y + 2;
				cameraPos.z = righthand->GetPosition().z - 3;
				cameratargetPos = righthand->GetPosition();

				if (appearanceTimer == 50) {
					appearanceNumber++;
				}
			}

			else if (appearanceNumber == 1) {
				cameraPos.x = lefthand->GetPosition().x - 5;
				cameraPos.y = lefthand->GetPosition().y + 2;
				cameraPos.z = lefthand->GetPosition().z - 3;
				cameratargetPos = righthand->GetPosition();

				if (appearanceTimer == 100) {
					appearanceNumber++;
				}
			}

			else if (appearanceNumber == 2) {
				cameraPos.x = player->GetPosition().x;
				cameraPos.y = player->GetPosition().y + 3;
				cameraPos.z = player->GetPosition().z - 8;
				cameratargetPos = { 0.0f,2.0f,0.0 };

				if (appearanceTimer == 230) {
					BlackColor.w = 1.0f;
					appearanceNumber++;
					//個々の音変更案件
					Audio::GetInstance()->PlayWave("Resources/Sound/Damage.wav", 0.4f);
				}
			}

			else if (appearanceNumber == 3) {
				if (appearanceTimer == 300) {
					BlackColor.w = 0.0f;
				}

				if (appearanceTimer == 350) {
					appearanceNumber++;
				}
			}

			else if (appearanceNumber == 4) {
				Aftereyepos = {
					0,
					1,
					-7,
				};

				Aftertargetpos = {
					0,
					1,
					0
				};

				if (frame < 1.0f) {
					frame += 0.015f;
				}
				else {
					frame = 1.0f;
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

				if (appearanceTimer == 450) {
					appearanceNumber++;
					frame = 0.0f;
				}
			}

			else if (appearanceNumber == 5) {
				if (nameframe >= 1.0f) {
					nameframe = 1.0f;
				}
				else {
					nameframe += 0.06f;
				}
				namePos = {
				Ease(In,Quad,nameframe,2000,940),
				480
				};

				bossName->SetPosition(namePos);
				if (appearanceTimer == 550) {
					nameframe = 0.0f;
					appearanceNumber++;
				}
			}
			else if (appearanceNumber == 6) {
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

				if (nameframe >= 1.0f) {
					nameframe = 1.0f;
				}
				else {
					nameframe += 0.06f;
				}
				namePos = {
				Ease(In,Quad,nameframe,940,2000),
				480
				};

				bossName->SetPosition(namePos);

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
			human->SetAttack(lefthand, righthand);
			lefthand->Update();
			righthand->Update();
			lefthand->SetAct(human);
			righthand->SetAct(human);
		
			/*
				if (righthand->GetHP() <= 0) {
					DeadRight++;
					lefthand->SetPosition({ 0.0f,-20.8f,0.0f });
				}

				if (lefthand->GetHP() <= 0) {
					DeadLeft++;
					righthand->SetPosition({ 0.0f,-20.8f,0.0f });
				}*/
			for (std::size_t i = 0; i < enemy.size(); i++) {
				enemy[i]->Update();
				enemy[i]->SetEnemy();
				player->ResetWeight(enemy[i]);
			}
			if (player->GetDamageFlag() == true) {
				player->Rebound();
			}
			ui->Update();
			particleMan->Update();
			objSphere->Update();
			cameraPos.x = player->GetPosition().x;
			cameraPos.y = player->GetPosition().y + distanceY;
			cameraPos.z = player->GetPosition().z - distanceZ;
			camera->SetTarget(player->GetPosition());
			camera->SetEye(cameraPos);
		}

		//その他シーン移行
		if (lefthand->GetHP() <= 0 && righthand->GetHP() <= 0) {
			end = true;
		}

		if (player->GetHp() <= 0) {
			gameover = true;
		}
	}//ボス撃破ムービー演出
	else {
	if (end) {
		EndTimer++;
		righthand->EndMovie(EndTimer);
		lefthand->EndMovie(EndTimer);
		player->End();
		if (EndNumber == 0) {
			cameraPos.x = player->GetPosition().x;
			cameraPos.y = player->GetPosition().y + distanceY;
			cameraPos.z = player->GetPosition().z - distanceZ;
			camera->SetTarget(player->GetPosition());
			if (EndTimer == 50) {
				EndNumber = 1;
			}
		}
		else if (EndNumber == 1) {
			if (WhiteColor.w <= 1.0f) {
				WhiteColor.w += 0.005f;
			}

			if (EndTimer == 300) {
				EndNumber++;
			}
		}
		else if (EndNumber == 2) {
			if (WhiteColor.w >= 0.0f) {
				WhiteColor.w -= 0.005f;
			}
			cameraPos.x = 0;
			cameraPos.y = 7;
			cameraPos.z = 10;
			camera->SetTarget({ 0.0f,0.0f,0.0f });
		}
		WhiteFilter->SetColor(WhiteColor);
		camera->SetEye(cameraPos);

		if (EndTimer == 700) {
			expandchange->SetStartChange(true);
		}

		if (expandchange->GetTimer() >= 58) {
			SceneManager::GetInstance()->ChangeScene("StageSelect");
		}
	}

	if (gameover == true) {
		overTimer++;
		//player->Begin();
		righthand->Begin();
		lefthand->Begin();
		player->gameover(overTimer);
		if (overNumber == 0) {
			if (BlackColor.w <= 1.0f) {
				BlackColor.w += 0.01f;
			}

			if (overTimer == 1) {
				Aftereyepos = {
				player->GetPosition().x,
				player->GetPosition().y + 5,
				player->GetPosition().z - 7,
				};
				Aftertargetpos = {
				player->GetPosition().x,
				player->GetPosition().y,
				player->GetPosition().z + 6,
				};
				cameraPos.x = player->GetPosition().x;
				cameraPos.y = player->GetPosition().y + distanceY;
				cameraPos.z = player->GetPosition().z - distanceZ;
				cameratargetPos = player->GetPosition();
			}

			if (overTimer >= 50) {

				if (frame < 1.0f) {
					frame += 0.015f;
				}
				else {
					frame = 1.0f;
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

			if (overTimer == 420) {
				overNumber++;
			}
		}
		else if (overNumber == 1) {
			if (GameOverColor.w <= 1.0f) {
				GameOverColor.w += 0.01f;
			}


			if (overframe >= 1.0f) {
				overframe = 1.0f;
			}
			else {
				overframe += 0.01f;
			}

			overPos = {
		240,
		Ease(In,Quad,overframe,overPos.y,100.0f)
			};

			GameOverSprite->SetPosition(overPos);
		}

		if (overTimer == 650) {
			expandchange->SetStartChange(true);
		}

		if (expandchange->GetTimer() >= 58) {
			SceneManager::GetInstance()->ChangeScene("StageSelect");
		}

		camera->SetTarget(cameratargetPos);
		camera->SetEye(cameraPos);
	}
	}
	BlackFilter->SetColor(BlackColor);
	GameOverSprite->SetColor(GameOverColor);
	camera->Update();
	expandchange->Update();

	for (std::size_t i = 0; i < effect.size(); i++) {
		effect[i]->Update(lefthand);
		effect[i]->Update(righthand);
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
		for (int colA = 0; colA < enemy.size(); colA++) {
			for (int colB = 1; colB < enemy.size(); colB++) {
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

	// 全ての衝突をチェック
	//collsionManager->CheckAllCollisions();
	/*DebugText::GetInstance()->Print("PUSH to RB!!",200, 100,1.0f);
	DebugText::GetInstance()->Print("PUSH to A!!", 200, 115, 1.0f);*/
	//DebugText::GetInstance()->Print("RB or LB :Rotate", 900, 620, 2.0f);
	//DebugText::GetInstance()->Print("A         :Hand", 900, 650, 2.0f);
	//DebugText::GetInstance()->Print("PUSH to RB!!", 1040, 620, 2.0f);
	//DebugText::GetInstance()->Print("PUSH to A!!", 1040, 660, 2.0f);
}

//描画
void FifthBoss::Draw(DirectXCommon* dxCommon) {

	//各オブジェクトの描画
	Object3d::PreDraw();
	objBossMap->Draw();
	objFloor->Draw();
	objBedroom->Draw();

	if (!gameover) {
		//bossenemy->Draw();
		if (righthand->GetHP() > 0 || end) {
			righthand->Draw();
		}

		if (lefthand->GetHP() > 0 || end) {
			lefthand->Draw();
		}
	}

	for (std::size_t i = 0; i < effect.size(); i++) {
		effect[i]->Draw();
	}

	if (!gameover) {
		Texture::PreDraw();
		if (EndNumber <= 1) {
			player->Draw(dxCommon);
		}

		Sprite::PreDraw();

		if (!bossstart) {
			BlackFilter->Draw();
			bossName->Draw();
		}

		if (SkipTimer != 0) {
			SkipSprite->Draw();
		}

	}
	else {
		Sprite::PreDraw();

		BlackFilter->Draw();
		GameOverSprite->Draw();
		Texture::PreDraw();
		if (EndNumber <= 1) {
			player->Draw(dxCommon);
		}
	}

	//for (std::size_t i = 0; i < exp.size(); i++) {
	//	for (std::size_t j = 0; j < exp[i].size(); j++) {
	//		exp[i][j]->Draw();
	//	}
	//}
	if (bossstart && !end && !gameover) {
		ui->Draw();
		// パーティクルの描画
		particleMan->Draw(dxCommon->GetCmdList());
	}


	if (end) {
		WhiteFilter->Draw();
	}
	else {
		if (!gameover) {
			for (std::size_t i = 0; i < enemy.size(); i++) {
				enemy[i]->Draw();
			}
		}
	}

	Sprite::PreDraw();

	//前面用
	expandchange->Draw();


}