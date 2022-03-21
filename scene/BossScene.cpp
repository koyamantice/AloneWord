#include "BossScene.h"
#include "Audio.h"
#include "DebugText.h"
#include "TitleScene.h"
#include "FbxLoader.h"
void BossScene::Initialize(DirectXCommon* dxCommon) {
	Texture::LoadTexture(0, L"Resources/2d/enemy.png");
	Texture::LoadTexture(1, L"Resources/2d/limit.png");
	// �J��������
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height);
	Texture::SetCamera(camera);
	// 3D�I�u�W�F�N�g�ɃJ�������Z�b�g
	Object3d::SetCamera(camera);
	player = new Player();
	player->Initialize();

	bossenemy = new BossEnemy();
	bossenemy->Initialize();

	for (int i = 0; i < EnemyMa; i++) {
		enemy[i] = new Enemy();
		enemy[i]->Initialize();
	}
	//�I�u�W�F�N�g������
	modelGround = Model::CreateFromOBJ("ground");
	objGround = Object3d::Create();
	objGround->Initialize();
	objGround->SetModel(modelGround);
	objGround->SetPosition({ 0,-1,0 });

	modelFork = Model::CreateFromOBJ("Fork");
	objFork = Object3d::Create();
	objFork->Initialize();
	objFork->SetModel(modelFork);
	objFork->SetRotation({ 0,90.0f,0 });
	objFork->SetPosition({ 5.0f,0,-10.0f });

	modelMotti = Model::CreateFromOBJ("Motti");
	objMotti = Object3d::Create();
	objMotti->Initialize();
	objMotti->SetModel(modelMotti);
	objMotti->SetRotation({ 0,90.0f,0 });
	objMotti->SetPosition({ -3.0f,0,0 });

	modelArm = Model::CreateFromOBJ("Arm");
	objArm = Object3d::Create();
	objArm->Initialize();
	objArm->SetModel(modelArm);
	objArm->SetRotation({ 0,90.0f,0 });
	objArm->SetPosition({ -3.5f,1.0f,-1.0f });
	//���ʂ̃e�N�X�`��(�|��)
	limit = Texture::Create(1, { 0,0,0 }, { 12,12,12 }, { 1,1,1,1 });
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
}

void BossScene::Update(DirectXCommon* dxCommon) {
	objGround->Update();
	objFork->Update();
	objMotti->Update();
	objArm->Update();
	lightGroup->Update();
	camera->Update();
	player->Update();
	bossenemy->Update(player);
	limit->Update();
	for (int i = 0; i < EnemyMa; i++) {
		enemy[i]->Update(player,bossenemy);
		player->ResetWeight(enemy[i]);
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

	if (input->PushKey(DIK_0) || input->TriggerButton(input->Button_Y)) {
		object1->PlayAnimation();
		//SceneManager::GetInstance()->ChangeScene("BOSS");
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
	objGround->Draw();
	Texture::PreDraw();
	limit->Draw();

	//Sprite::PreDraw();
	//�w�i�p
	//sprite->Draw();
	Object3d::PreDraw();
	objFork->Draw();
	objMotti->Draw();
	objArm->Draw();

	//object1->Draw(dxCommon->GetCmdList());
	//�w�i�p
	player->Draw();
	for (int i = 0; i < EnemyMa; i++) {
		enemy[i]->Draw();
	}

	bossenemy->Draw();
}