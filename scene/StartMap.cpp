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
#include <Easing.h>
#include "ImageManager.h"


void StartMap::Initialize(DirectXCommon* dxCommon) {
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

	//sound宣言
	Audio::GetInstance()->LoadSound(2, "Resources/Sound/tutorialBGM.wav");
	Audio::GetInstance()->LoopWave(2, 0.08f);
	
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
	player->SetRotation({ 0.0f,90.0f,0.0f });
	player->SetMove(250.0f, 200.0f);
	//ボス
	bossenemy = new Spawning();
	bossenemy->SetPlayer(player);
	bossenemy->Initialize();
	//敵
	for (std::size_t i = 0; i < enemy.size(); i++) {
		enemy[i] = new Rice();
		enemy[i]->SetPlayer(player);
		enemy[i]->Initialize();
		enemy[i]->SetLimit({ 22.0f,-17.0f, 21.0f,-20.5f });
	}
	//当たり判定確認用です
	//modelSphere = Model::CreateFromOBJ("sphere");
	//objSphere = TouchableObject::Create(modelSphere);
	//objSphere->SetScale({ 2.0f, 2.0f, 2.0f });
	//objSphere->SetPosition({ 0.0f,0.0f,1.0f });
	//
	Texture* Hit_ = Texture::Create(ImageManager::Hit, { 0,0,-10 }, { 0,0,0 }, { 1, 1, 1,1 });
	Hit_->TextureCreate();
	Hit_->SetPosition(player->GetPosition());
	Hit_->SetRotation({ 0.0f,0.0f,0.0f });
	Hit_->SetScale({1.0f,1.0f,1.0f});
	Hit_->Update();
	Hit.reset(Hit_);


	// パーティクルマネージャ生成
	particleMan = ParticleManager::GetInstance();
	particleMan->SetCamera(camera);

	//カメラポジション
	cameraPos.x = player->GetPosition().x;
	cameraPos.y = player->GetPosition().y + distanceY;
	cameraPos.z = player->GetPosition().z - distanceZ;
	// カメラ注視点をセット
	cameratargetPos = player->GetPosition();
	camera->SetTarget(cameratargetPos);
	camera->SetEye(cameraPos);

	// モデル名を指定してファイル読み込み
	//model1 =ModelManager::GetIns()->GetFBXModel(ModelManager::MottiMove);

	ui = new UI(player);

	Ok = Sprite::Create(ImageManager::ok, { 314.0f,500.0f });
	Ok->SetAnchorPoint({ 0.5f, 0.5f });

	comment[text1] = Sprite::Create(ImageManager::text1, { 640.0f,360.0f });
	comment[text2] = Sprite::Create(ImageManager::text2, { 570.0f,450.0f });
	comment[text3] = Sprite::Create(ImageManager::text3, { 570.0f,450.0f });
	comment[text4] = Sprite::Create(ImageManager::text4, { 570.0f,450.0f });
	comment[text5] = Sprite::Create(ImageManager::text5, { 570.0f,450.0f });
	comment[text6] = Sprite::Create(ImageManager::text6, { 570.0f,450.0f });
	comment[text7] = Sprite::Create(ImageManager::text7, { 570.0f,450.0f });
	comment[text8] = Sprite::Create(ImageManager::text8, { 570.0f,450.0f });
	comment[text9] = Sprite::Create(ImageManager::text9, { 570.0f,450.0f });
	comment[text10] = Sprite::Create(ImageManager::text10, { 570.0f,450.0f });
	comment[text11] = Sprite::Create(ImageManager::text11, { 570.0f,450.0f });

	for (int i = 0; i < text11 + 1; i++) {
		comment[i]->SetAnchorPoint({ 0.5f, 0.5f });
		comment[i]->SetPosition({ 640.0f,500.0f });
		comment[i]->SetSize({ 0,0 });
	}

	shrinkchange = new ShrinkChange();
	shrinkchange->SetEndChange(true);
	//スプライト生成
	expandchange = new ExpandChange();
}

//開放処理
void StartMap::Finalize() {
	//3dのモデルのデリート
	for (std::size_t i = 0; i < enemy.size(); i++) {
		enemy[i]->Finalize();
	}
	player->Finalize();
	bossenemy->Finalize();
	delete objBossMap;
	delete objFloor;
	//delete objSphere;
	delete modelBossMap;
	delete modelFloor;
	delete objSkydome;
	delete modelSkydome;
	for (std::size_t i = 0; i < effect.size(); i++) {
		effect[i]->Finalize();
	}
	delete camera;
	ui->Finalize();
	expandchange->Finalize();
	shrinkchange->Finalize();
}

//更新処理
void StartMap::Update(DirectXCommon* dxCommon) {
	if (pause) {
		Pause(set);
		return;
	} else {
		hit = false;
	}
	//行動により次のチュートリアルに移る
	nowTimer++;
	switch (nowText) {
	case text1:
		if (nowTimer < 61) {
			if (!open && !openT) {
				open = true;
			}
		}
		if (nowTimer > 180) {
			if (!close && !closeT) {
				close = true;
			}
		}
		if (closeT) {
			if (nowTimer > 120) {
				openT = false;
				closeT = false;
				nowTimer = 0;
				nowText = text2;
			}
		}
		break;
	case text2:
		if (!open) {
			if (!openT) {
				open = true;
			}
		}
		if (nowTimer > 180) {
			if (!close && !closeT) {
				close = true;
			}
		}
		if (closeT) {
			if (nowTimer > 120) {
				openT = false;
				closeT = false;
				nowTimer = 0;
				nowText = text3;
			}
		}
		break;
	case text3:
		if (!open) {
			if (!openT) {
				open = true;
			}
		}
		if (nowTimer > 180) {
			if (!close && !closeT) {
				close = true;
			}
		}
		if (closeT) {
			if (nowTimer > 120) {
				openT = false;
				closeT = false;
				nowTimer = 0;
				nowText = text4;
			}
		}
		break;
	case text4:
		if (!open) {
			if (!openT) {
				open = true;
			}
		}
		if (openT) {
			if ((input->LeftTiltStick(input->Right)) || (input->LeftTiltStick(input->Left))
				|| (input->LeftTiltStick(input->Up)) || (input->LeftTiltStick(input->Down))) {
				if (!checkZ && !close && !closeT) {
					check = true;
					nowTimer = 0;
				}
			}
		}
		if (check) {
			scaOk = {
			Ease(Out, Quad, frame, 128,64),
			Ease(Out, Quad, frame, 128,64),
			};
			if (frame < 1.0f) {
				frame += 0.05f;
			} else {
				frame = 0.0f;
				check = false;
				checkZ = true;
			}
			Ok->SetSize(scaOk);
		}
		if (nowTimer > 200 && checkZ) {
			if (!close && !closeT) {
				close = true;
			}
		}

		if (closeT) {
			check = false;
			checkZ = false;
			if (nowTimer > 120) {
				openT = false;
				closeT = false;
				nowTimer = 0;
				nowText = text5;
			}
		}
		break;
	case text5:
		if (!open) {
			if (!openT) {
				open = true;
			}
		}
		if (openT) {
			if (input->ReleaseButton(input->Button_A)||player->GetChargeTimer()>100) {
				if (!checkZ && !close && !closeT) {
					check = true;
					nowTimer = 0;
				}
			}
		}
		if (check) {
			scaOk = {
			Ease(Out, Quad, frame, 128,64),
			Ease(Out, Quad, frame, 128,64),
			};
			if (frame < 1.0f) {
				frame += 0.05f;
			} else {
				frame = 0.0f;
				check = false;
				checkZ = true;
			}
			Ok->SetSize(scaOk);
		}
		if (nowTimer > 200 && checkZ) {
			if (!close && !closeT) {
				close = true;
			}
		}

		if (closeT) {
			check = false;
			checkZ = false;
			if (nowTimer > 120) {
				openT = false;
				closeT = false;
				nowTimer = 0;
				nowText = text6;
			}
		}
		break;
	case text6:
		if (!open) {
			if (!openT) {
				open = true;
			}
		}
		if (openT) {
			if (player->GetArmWeight()) {
				if (!checkZ && !close && !closeT) {
					check = true;
					nowTimer = 0;
				}
			}
		}
		if (check) {
			scaOk = {
			Ease(Out, Quad, frame, 128,64),
			Ease(Out, Quad, frame, 128,64),
			};
			if (frame < 1.0f) {
				frame += 0.05f;
			} else {
				frame = 0.0f;
				check = false;
				checkZ = true;
			}
			Ok->SetSize(scaOk);
		}
		if (nowTimer > 200 && checkZ) {
			if (!close && !closeT) {
				close = true;
			}
		}

		if (closeT) {
			if (nowTimer > 120) {
				openT = false;
				closeT = false;
				//bossenemy->SetHP(15);
				nowTimer = 0;
				nowText = text7;
			}
		}
		break;
	case text7:
		if (!open) {
			if (!openT) {
				open = true;
			}
		}
		if (openT) {
			if (input->ReleaseButton(input->Button_A) || player->GetChargeTimer() >= 300) {
				if (!checkZ && !close && !closeT) {
					check = true;
					nowTimer = 0;
				}
			}
		}
		if (check) {
			scaOk = {
			Ease(Out, Quad, frame, 128,64),
			Ease(Out, Quad, frame, 128,64),
			};
			if (frame < 1.0f) {
				frame += 0.05f;
			} else {
				frame = 0.0f;
				check = false;
				checkZ = true;
			}
			Ok->SetSize(scaOk);
		}
		if (nowTimer > 200 && checkZ) {
			if (!close && !closeT) {
				close = true;
			}
		}

		if (closeT) {
			if (nowTimer > 120) {
				openT = false;
				closeT = false;
				nowTimer = 0;
				bossenemy->SetHP(15);
				nowText = text8;
			}
		}
		break;
	case text8:
		if (!open) {
			if (!openT) {
				open = true;
			}
		}
		if (openT) {
			if (player->GetOldArm() > 5.5f && bossenemy->GetHP() < 15) {
				if (!checkZ && !close && !closeT) {
					check = true;
					nowTimer = 0;
				}
			}
		}
		if (check) {
			scaOk = {
			Ease(Out, Quad, frame, 128,64),
			Ease(Out, Quad, frame, 128,64),
			};
			if (frame < 1.0f) {
				frame += 0.05f;
			} else {
				frame = 0.0f;
				check = false;
				checkZ = true;
			}
			Ok->SetSize(scaOk);
		}
		if (nowTimer > 200 && checkZ) {
			if (!close && !closeT) {
				close = true;
			}
		}

		if (closeT) {
			if (nowTimer > 120) {
				openT = false;
				closeT = false;
				nowTimer = 0;
				nowText = text9;
			}
		}
		break;
	case text9:
		if (!open) {
			if (!openT) {
				open = true;
			}
		}
		if (nowTimer > 180) {
			if (!close && !closeT) {
				close = true;
			}
		}
		if (closeT) {
			if (nowTimer > 120) {
				openT = false;
				closeT = false;
				nowTimer = 0;
				nowText = text10;
			}
		}
		break;
	case text10:
		if (!open) {
			if (!openT) {
				open = true;
			}
		}
		if (nowTimer > 180) {
			if (!close && !closeT) {
				close = true;
			}
		}
		if (closeT) {
			if (nowTimer > 120) {
				openT = false;
				closeT = false;
				nowTimer = 0;
				nowText = text11;
			}
		}
		break;
		//チュートリアルが終わるとシーン遷移に移る
	case text11:
		if (!open) {
			if (!openT) {
				open = true;
			}
		}
		if (input->PushButton(input->Select)) {
			Audio::GetInstance()->StopWave(2);
			expandchange->SetStartChange(true);
			//SceneManager::GetInstance()->ChangeScene("StageSelect");

		}
		break;
	default:
		break;
	}
	if (input->PushButton(input->Select)) {
		Audio::GetInstance()->StopWave(2);
		expandchange->SetStartChange(true);
		//SceneManager::GetInstance()->ChangeScene("StageSelect");

	}
	if (open) {
		sca = {
		Ease(Out,Quad,frame,816,816),
		Ease(Out,Quad,frame,0,160),
		};
		if (frame < 1.0f) {
			frame += 0.05f;
		} else {
			frame = 0.0f;
			open = false;
			openT = true;
		}
		comment[nowText]->SetSize(sca);
	}
	if (close) {
		sca = {
		Ease(Out,Quad,frame,816,816),
		Ease(Out,Quad,frame,160,0),
		};
		if (checkZ) {
			scaOk = {
			Ease(Out, Quad, frame, 64, 64),
			Ease(Out, Quad, frame, 64, 0), };
			Ok->SetSize(scaOk);
		}
		if (frame < 1.0f) {
			frame += 0.05f;
		} else {
			frame = 0.0f;
			close = false;
			closeT = true;
			//if (checkZ) {
			checkZ = false;
			//}
			nowTimer = 0;
		}
		comment[nowText]->SetSize(sca);

	}

	if (expandchange->GetTimer() >= 58) {
		SceneManager::GetInstance()->ChangeScene("StageSelect");
	}
	objBossMap->Update();
	player->Update();
	ui->Update();
	objFloor->Update();
	objSkydome->Update();
	lightGroup->Update();
	bossenemy->Update();
	if (bossenemy->collideAttackArm()) {
		Hit->Update();
	}
	camera->Update();
	particleMan->Update();
	expandchange->Update();
	shrinkchange->Update();
	for (int i = 0; i < enemy.size() - 1; i++) {
		enemy[i]->Demo(i);
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

	camera->Update();
	if (player->GetHp() <= 0) {
		player->SetHp(10);
	}
}

//描画
void StartMap::Draw(DirectXCommon* dxCommon) {
	//ImGui::Begin("test");
	//ImGui::SliderInt("nowTimer", &nowTimer, 500, 0);
	//ImGui::SliderFloat("frame", &frame, 1, 0);
	//ImGui::SliderInt("nowText", &nowText, 11, 0);
	////ImGui::("boundpower.x %d", &AttackFlag, 50, -50);
	////ImGui::Text("RotC:%d", AttackFlag);
	//ImGui::End();
	Object3d::PreDraw();
	objBossMap->Draw();
	objFloor->Draw();
	objSkydome->Draw();
	//objSphere->Draw();

	for (int i = 0; i < enemy.size() - 1; i++) {
		enemy[i]->Draw();
	}
	player->Draw(dxCommon);
	bossenemy->Draw();
	// パーティクルの描画
	particleMan->Draw(dxCommon->GetCmdList());
	ui->Draw();
	ui->SkipDraw();
	Texture::PreDraw();
	if (bossenemy->collideAttackArm()) {
		Hit->Draw();
	}
	Sprite::PreDraw();
	comment[nowText]->Draw();
	if (check || checkZ) {
		Ok->Draw();
	}
	expandchange->Draw();
	shrinkchange->Draw();
}

//ポーズ関係
void StartMap::Pause(const int& Timer) {
	wait++;
	if (wait >= Timer) {
		pause = false;
		wait = 0;
	} else {
		pause = true;
	}
}
