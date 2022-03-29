#include "BossScene.h"
#include "Audio.h"
#include "DebugText.h"
#include "TitleScene.h"
#include "FbxLoader.h"
void BossScene::Initialize(DirectXCommon* dxCommon) {
	Texture::LoadTexture(0, L"Resources/2d/enemy.png");
	Texture::LoadTexture(1, L"Resources/2d/limit.png");
	Texture::LoadTexture(2, L"Resources/2d/shadow.png");
	Texture::LoadTexture(3, L"Resources/2d/Resporn.png");
	Texture::LoadTexture(4, L"Resources/2d/effect.png");
	// �J��������
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height);
	Texture::SetCamera(camera);
	// 3D�I�u�W�F�N�g�ɃJ�������Z�b�g
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

	for (int i = 0; i < ObstacleMax; i++) {
		obstacle[i] = new Obstacle();
		obstacle[i]->Initialize();
	}
	//�I�u�W�F�N�g������
	/*modelGround = Model::CreateFromOBJ("ground");
	objGround = Object3d::Create();
	objGround->Initialize();
	objGround->SetModel(modelGround);
	objGround->SetPosition({ 0,-1,0 });*/

	modelground = Model::CreateFromOBJ("ground");
	objground = Object3d::Create();
	objground->Initialize();
	objground->SetModel(modelground);
	objground->SetPosition({ 0,-1,10 });
	objground->SetScale({ 22,1,10 });
	//���ʂ̃e�N�X�`��(�|��)
	limit = Texture::Create(1, { 0,0,0 }, { 12,12,12 }, { 1,1,1,0.6f });
	limit->TextureCreate();
	limit->SetPosition({ 0.0f,0.01f,0.0f });
	limit->SetRotation({ 90.0f,0, 0 });
	limit->SetScale({ 6,5,5 });

	//�w�i�X�v���C�g����

	// ���f���ǂݍ���
	Audio::GetInstance()->LoadSound(1, "Resources/BGM/NewWorld.wav");
	//srand(NULL);
	// ���C�g����
	lightGroup = LightGroup::Create();
	// 3D�I�u�G�N�g�Ƀ��C�g���Z�b�g
	Object3d::SetLightGroup(lightGroup);

	// �J���������_���Z�b�g
	camera->SetTarget(player->GetPosition());
	camera->SetEye({ player->GetPosition().x,player->GetPosition().y + 10,player->GetPosition().z - 10 });
	// ���f�������w�肵�ăt�@�C���ǂݍ���
	model1 = FbxLoader::GetInstance()->LoadModelFromFile("boneTest");

	// �f�o�C�X���Z�b�g
	FBXObject3d::SetDevice(dxCommon->GetDev());
	// �J�������Z�b�g
	FBXObject3d::SetCamera(camera);
	// �O���t�B�b�N�X�p�C�v���C������
	FBXObject3d::CreateGraphicsPipeline();

	object1 = new FBXObject3d;
	object1->Initialize();
	object1->SetModel(model1);
}

void BossScene::Finalize() {

	//�R���̃��f���̃f���[�g
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
	for (int i = 0; i < ObstacleMax; i++) {
		obstacle[i]->Update();
		obstacle[i]->PosSet(obstacle);
	}
	limit->Update();
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

	//�G���m�̓����蔻��
	if (sizeof(enemy) > 2) {//�z��̃T�C�Y�m�F
		for (int colA = 0; colA < BossEnemyMax; colA++) {
			for (int colB = 1; colB < BossEnemyMax; colB++) {
				if (Collision::CheckSphere2Sphere(enemy[colA]->collider, enemy[colB]->collider) == true && colA != colB) {//�����蔻��Ǝ��@���m�̓����蔻��̍폜
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

	//���̑��V�[���ڍs
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
	Object3d::PreDraw();
	//objGround->Draw();
	objground->Draw();

	Texture::PreDraw();
	limit->Draw();
	//Sprite::PreDraw();
	//�w�i�p
	//sprite->Draw();


	Object3d::PreDraw();
	//object1->Draw(dxCommon->GetCmdList());
	//�w�i�p
	player->Draw();
	for (int i = 0; i < BossEnemyMax; i++) {
		enemy[i]->Draw();
	}
	bossenemy->Draw();
	for (int i = 0; i < ObstacleMax; i++) {
		obstacle[i]->Draw();
	}
}