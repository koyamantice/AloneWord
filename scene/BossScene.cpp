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
#include <Easing.h>
#include "ImageManager.h"
void BossScene::Initialize(DirectXCommon* dxCommon) {
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
	objFloor->SetScale({ 6.0f,1.0f,6.0f });

	//スカイドーム
	objSkydome = Object3d::Create();
	modelSkydome = Model::CreateFromOBJ("skydome");
	objSkydome->SetModel(modelSkydome);
	objSkydome->SetPosition({ 0, -1, 0 });
	objSkydome->SetScale({ 1.0f,1.0f,1.0f });

	//ステージマップ
	modelBossMap = Model::CreateFromOBJ("BossMap");
	objBossMap = TouchableObject::Create(modelBossMap);
	objBossMap->SetPosition({ 0,0,4 });
	objBossMap->SetRotation({ 0, 90, 0 });
	objBossMap->SetScale({ 3.0f,1.5f,3.0f });

	//当たり判定確認用です

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
	bossName = Sprite::Create(ImageManager::select1, namePos);
	bossName->SetAnchorPoint({ 1.0f,0.0f });

	WhiteFilter = Sprite::Create(ImageManager::WhiteFilter, { 0.0f,0.0f });
	//WhiteFilter->SetAnchorPoint({ 1.0f,0.0f });
	WhiteFilter->SetColor(WhiteColor);

	BlackFilter = Sprite::Create(ImageManager::BlackFilter, { 0.0f,0.0f });
	BlackFilter->SetColor(BlackColor);

	GameOverSprite = Sprite::Create(ImageManager::GameOver, overPos);
	GameOverSprite->SetColor(GameOverColor);
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
	//プレイヤー
	player = new Player();
	player->Initialize();
	player->SetPosition({ 0.0f,0.0f,-10.0f });
	player->SetMove(250.0f, 200.0f);

	//ボス
	bossenemy = new BossEnemy();
	bossenemy->SetPlayer(player);
	bossenemy->Initialize();

	//敵
	for (std::size_t i = 0; i < enemy.size(); i++) {
		enemy[i] = new Rice();
		enemy[i]->SetPlayer(player);
		enemy[i]->Initialize();
		enemy[i]->SetLimit({ 21.0f,-17.0f,19.0f,-19.0f });
	}

	// パーティクルマネージャ生成
	particleMan = ParticleManager::GetInstance();
	particleMan->SetCamera(camera);

	//カメラポジション
	cameraPos.x = bossenemy->GetPosition().x + 5;
	cameraPos.y = 2;
	cameraPos.z = bossenemy->GetPosition().z + 8;
	// カメラ注視点をセット
	cameratargetPos = player->GetPosition();
	camera->SetTarget(cameratargetPos);
	camera->SetEye(cameraPos);

	// モデル名を指定してファイル読み込み
	//model1 =ModelManager::GetIns()->GetFBXModel(ModelManager::MottiMove);

	ui = new UI(player, bossenemy);
	//スプライト生成
	expandchange = new ExpandChange();
	//ui->Initialize();
}

void BossScene::Finalize() {

	//3dのモデルのデリート
	for (std::size_t i = 0; i < enemy.size(); i++) {
		enemy[i]->Finalize();
	}
	player->Finalize();
	bossenemy->Finalize();
	delete objBossMap;
	delete objFloor;
	delete modelBossMap;
	delete modelFloor;
	delete objSkydome;
	delete modelSkydome;
	for (std::size_t i = 0; i < effect.size(); i++) {
		effect[i]->Finalize();
	}
	//for (std::size_t i = 0; i < exp.size(); i++) {
	//	for (std::size_t j = 0; j < exp[i].size(); j++) {
	//		exp[i][j]->Finalize();
	//	}
	//}
	delete camera;
	ui->Finalize();
	//delete object1;
	//delete model1;
}

void BossScene::Update(DirectXCommon* dxCommon) {
	//objBossMap->Update();
	//各オブジェクトの更新
	objBossMap->Update();
	objFloor->Update();
	objSkydome->Update();
	lightGroup->Update();
	ParticleManager::GetInstance()->Update();
	//最初の演出(導入)
	if (!end && !gameover) {
		if (!bossstart) {
			player->Begin();
			bossenemy->Begin();
			if (BlackColor.w >= 0.0f) {
				BlackColor.w -= 0.005f;
				frame = 0.0f;
			}
			else {
				appearanceTimer++;
			}
		
			//カメラの位置をそれぞれを変える
			if (appearanceNumber == 0) {
				if (appearanceTimer == 1) {
					cameraPos.x = bossenemy->GetPosition().x + 5;
					cameraPos.y = 2;
					cameraPos.z = bossenemy->GetPosition().z + 8;
					camera->SetTarget(player->GetPosition());
				}

				else if (appearanceTimer == 20) {
					Aftereyepos = {
						bossenemy->GetPosition().x + 2,
						2,
						bossenemy->GetPosition().z + 5,
					};
				}

				if (frame < 1.0f) {
					frame += 0.005f;
				}
				else {
					bossenemy->AppeaMovie(appearanceTimer);
					frame = 1.0f;
				}

				cameraPos = {
				Ease(In,Cubic,frame,cameraPos.x,Aftereyepos.x),
				Ease(In,Cubic,frame,cameraPos.y,Aftereyepos.y),
				Ease(In,Cubic,frame,cameraPos.z,Aftereyepos.z)
				};

				if (appearanceTimer == 300) {
					frame = 0.0f;
					appearanceNumber++;
				}
			}
			else if (appearanceNumber == 1) {
				Aftereyepos = {
					bossenemy->GetPosition().x,
					bossenemy->GetPosition().y + distanceY,
					bossenemy->GetPosition().z - distanceZ,
				};

				Aftertargetpos = {
					bossenemy->GetPosition().x,
					bossenemy->GetPosition().y + 5,
					bossenemy->GetPosition().z,
				};

				if (frame < 1.0f) {
					frame += 0.015f;
				}
				else {
					frame = 1.0f;
					bossenemy->AppeaMovie(appearanceTimer);
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

				if (appearanceTimer == 400) {
					frame = 0.0f;
					appearanceNumber++;
				}
			}

			else if (appearanceNumber == 2) {
				Aftereyepos = {
				bossenemy->GetPosition().x,
				bossenemy->GetPosition().y + 1,
				bossenemy->GetPosition().z - 5,
				};

				Aftertargetpos = {
					bossenemy->GetPosition().x,
					bossenemy->GetPosition().y + 1,
					bossenemy->GetPosition().z,
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
					frame = 0.0f;
					appearanceNumber++;
				}

			}

			else if (appearanceNumber == 3) {
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
				if (appearanceTimer == 520) {
					nameframe = 0.0f;
					appearanceNumber++;
				}

			}

			else if (appearanceNumber == 4) {
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
					nameframe = 0.0f;
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
			bossenemy->Update();
			for (std::size_t i = 0; i < enemy.size(); i++) {
				enemy[i]->Update();
				enemy[i]->SetEnemy();
				player->ResetWeight(enemy[i]);
			}
			if (player->GetDamageFlag() == true) {
				player->Rebound();
			}
			ui->Update();
			cameraPos.x = player->GetPosition().x;
			cameraPos.y = player->GetPosition().y + distanceY;
			cameraPos.z = player->GetPosition().z - distanceZ;
			camera->SetTarget(player->GetPosition());
			camera->SetEye(cameraPos);
		}
		//その他シーン移行
		if (bossenemy->GetHP() <= 0) {
			end = true;
			//SceneManager::GetInstance()->ChangeScene("StageSelect");
		}

		if (player->GetHp() <= 0) {
			gameover = true;
		}
	}
	//ボス撃破ムービー演出
	else {
		if (end) {
			EndTimer++;
			bossenemy->EndMovie(EndTimer);
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
				cameraPos.x = bossenemy->GetPosition().x;
				cameraPos.y = bossenemy->GetPosition().y + 7;
				cameraPos.z = bossenemy->GetPosition().z - 10;
				camera->SetTarget(bossenemy->GetPosition());
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
			bossenemy->Begin();
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

	camera->Update();
	BlackFilter->SetColor(BlackColor);
	GameOverSprite->SetColor(GameOverColor);
	expandchange->Update();
	for (std::size_t i = 0; i < effect.size(); i++) {
		effect[i]->Update(bossenemy);
	}

	if (input->TriggerKey(DIK_C || input->TriggerButton(input->Button_X))) {
		Audio::GetInstance()->StopWave(0);
		Audio::GetInstance()->StopWave(1);
		Audio::GetInstance()->LoopWave(1, 0.7f);
	}

	//敵同士の当たり判定
	if (sizeof(enemy) > 2) {//配列のサイズ確認
		for (int colA = 0; colA < enemy.size(); colA++) {
			for (int colB = 1; colB < enemy.size(); colB++) {
				if (!enemy[colA]->GetEnemyCatcth() && !enemy[colB]->GetEnemyCatcth()) {
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
	ray.start = { player->GetPosition().x,player->GetPosition().y + 3,player->GetPosition().z,1 };
	ray.dir = { 0,0.025f,-1.0f,0.0f };
	RaycastHit raycastHit;

	//if (!collisionManager->Raycast(ray, &raycastHit)) {
	//	if (distanceZ <= 10.0f) {
	//		distanceZ += 0.25f;
	//	}

	//	if (distanceY >= 10.0f) {
	//		distanceY -= 0.25f;
	//	}
	//}
	//else {
	//	if (distanceZ >= 6.0f) {
	//		distanceZ -= 0.4f;
	//	}

	//	if (distanceY <= 18.0f) {
	//		distanceY += 0.25f;
	//	}
	//}

	
	
	// 全ての衝突をチェック
	//collsionManager->CheckAllCollisions();
	/*DebugText::GetInstance()->Print("PUSH to RB!!",200, 100,1.0f);
	DebugText::GetInstance()->Print("PUSH to A!!", 200, 115, 1.0f);*/
	/*DebugText::GetInstance()->Print("RB or LB :Rotate", 900, 620, 2.0f);
	DebugText::GetInstance()->Print("A         :Hand", 900, 650, 2.0f);*/
	//DebugText::GetInstance()->Print("PUSH to RB!!", 1040, 620, 2.0f);
	//DebugText::GetInstance()->Print("PUSH to A!!", 1040, 660, 2.0f);
}

//描画
void BossScene::Draw(DirectXCommon* dxCommon) {
	//ImGui::Begin("test");
	////ImGui::SliderFloat("pos.z", &pos.z, 50, 0);
	////ImGui::SliderFloat("pos.y", &pos.y, 50, 0);
	///*ImGui::SliderFloat("enemypos.z", &Aftereyepos.z, 50, 0);
	//ImGui::SliderFloat("frame.y", &frame, 30, 0);
	//ImGui::SliderFloat("color.w", &BlackColor.w, 30, 0);
	//ImGui::Text("overT::%d", overTimer);*/
	//ImGui::Text("overT::%d", overTimer);
	//ImGui::Unindent();
	//ImGui::End();

	//各オブジェクトの描画
	Object3d::PreDraw();
	objBossMap->Draw();
	objFloor->Draw();
	objSkydome->Draw();

	if (!gameover) {
		bossenemy->Draw();
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