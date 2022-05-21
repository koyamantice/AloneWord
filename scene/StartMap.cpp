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
	bossenemy = new Spawning();
	bossenemy->SetPlayer(player);
	bossenemy->Initialize();
	//敵
	for (std::size_t i = 0; i < enemy.size(); i++) {
		enemy[i] = new Rice();
		enemy[i]->SetPlayer(player);
		enemy[i]->Initialize();
		enemy[i]->SetLimit({ 21.0f,-17.0f,19.0f,-19.0f });
	}
	//当たり判定確認用です
	modelSphere = Model::CreateFromOBJ("sphere");
	objSphere = TouchableObject::Create(modelSphere);
	objSphere->SetScale({ 2.0f, 2.0f, 2.0f });
	objSphere->SetPosition({ 0.0f,0.0f,1.0f });

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

	Ok = Sprite::Create(ImageManager::ok, { 570.0f,500.0f });
	Ok->SetAnchorPoint({0.5f, 0.5f});
	//Ok->SetScale(3.0f);
	OkSheet = Sprite::Create(ImageManager::okSheet, { 570.0f,500.0f });
	OkSheet->SetAnchorPoint({ 0.5f, 0.5f });
	OkSheet->SetScale(1.0f);

	comment[move] = Sprite::Create(ImageManager::move, { 570.0f,450.0f });
	comment[chage] = Sprite::Create(ImageManager::chage, { 570.0f,450.0f });
	comment[get] = Sprite::Create(ImageManager::get, { 570.0f,450.0f });
	comment[Attack] = Sprite::Create(ImageManager::Attack, { 570.0f,450.0f });
	comment[Perfect] = Sprite::Create(ImageManager::Perfect, { 570.0f,450.0f });

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
	delete objSphere;
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
	if (input->PushButton(input->Select)) {
		check = true;
	}
	//行動により次のチュートリアルに移る
	if (tutorial==move) {
		if (input->LeftTriggerStick(input->Right) ||
			input->LeftTriggerStick(input->Left) ||
			input->LeftTriggerStick(input->Up) ||
			input->LeftTriggerStick(input->Down)) {
			check = true;
		}
	}
	if (tutorial==chage) {
		if (input->PushButton(input->Button_RB)) {
			//tutorial++;
			if (!check) {
				check = true;
			}
		}
	}
	if (tutorial == get) {
		if (player->GetArmWeight()) {
			//tutorial++;
			if (!check) {
				check = true;
			}
		}
	}
	if (tutorial == Attack) {
		if (bossenemy->GetHP()<10) {
			//tutorial++;
			if (!check) {
				check = true;
			}
		}
	}
	//チュートリアルが終わるとシーン遷移に移る
	if (tutorial == Perfect) {
		if (input->TriggerButton(input->Select)) {
			expandchange->SetStartChange(true);
		}
	}
	if (expandchange->GetTimer() >= 58) {
		SceneManager::GetInstance()->ChangeScene("StageSelect");
	}
	if (check) {
		sca = {
		Ease(In,Quad,frame,256,128),
		Ease(In,Quad,frame,256,128),
		};
		if (frame < 1.0f) {
			frame += 0.025f;
		} else {
			frame = 0.0f;
			if (tutorial != Perfect) {
				tutorial++;
			}
			check = false;
		}
		Ok->SetSize(sca);
	}
	objBossMap->Update();
	player->Update();
	ui->Update();
	objFloor->Update();
	objSkydome->Update();
	lightGroup->Update();
	bossenemy->Update();
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
	Object3d::PreDraw();
	objBossMap->Draw();
	objFloor->Draw();
	objSkydome->Draw();
	objSphere->Draw();

	for (int i = 0; i < enemy.size() - 1; i++) {
		enemy[i]->Draw();
	}
	player->Draw(dxCommon);
	bossenemy->Draw();
	// パーティクルの描画
	particleMan->Draw(dxCommon->GetCmdList());
	ui->Draw();
	Sprite::PreDraw();
	OkSheet->Draw();
	if (check) {
		Ok->Draw();
	}
	for (int i = 0; i < Perfect + 1; i++) {
		if (tutorial==i) {
			comment[i]->Draw();
		}
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
	}
	else {
		pause = true;
	}
}
