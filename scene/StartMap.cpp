#include "StartMap.h"
#include "Audio.h"
#include "DebugText.h"
#include "TitleScene.h"
#include "FbxLoader.h"
void StartMap::Initialize(DirectXCommon* dxCommon) {
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
	for (int i = 0; i < EnemyMax; i++) {
		enemy[i] = new Enemy();
		enemy[i]->Initialize();
	}
	//�I�u�W�F�N�g������
	modelGround = Model::CreateFromOBJ("ground");
	objGround = Object3d::Create();
	objGround->Initialize();
	objGround->SetModel(modelGround);
	objGround->SetPosition({ 0,-1,0 });

	//�e�X�g
	modelSara = Model::CreateFromOBJ("sara");
	objSara = Object3d::Create();
	objSara->Initialize();
	objSara->SetModel(modelSara);
	objSara->SetPosition({ 2,2,0 });
	//���ʂ̃e�N�X�`��(�|��)
	limit =Texture::Create(1, { 0,0,0 }, { 12,12,12 }, { 1,1,1,1 });
	limit->TextureCreate();
	limit->SetPosition({ 0.0f,0.01f,0.0f });
	limit->SetRotation({ 90.0f,0, 0});
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

void StartMap::Finalize() {
	//�R���̃��f���̃f���[�g
	delete objGround;
	delete player;
	for(int i = 0; i < EnemyMax; i++) {
		delete enemy[i];
	}
	delete bossenemy;

}

void StartMap::Update(DirectXCommon* dxCommon) {
	objGround->Update();
	objSara->Update();//����
	lightGroup->Update();
	camera->Update();
	player->Update();
	bossenemy->Update(player);
	limit->Update();
	for (int i = 0; i < EnemyMax; i++) {
		enemy[i]->Update(player, bossenemy);
		player->ResetWeight(enemy[i]);
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

	if (input->PushKey(DIK_0) || input->TriggerButton(input->Button_Y)) {
		object1->PlayAnimation();
		//SceneManager::GetInstance()->ChangeScene("BOSS");
	}

	object1->Update();
	camera->SetTarget(player->GetPosition());
	camera->SetEye({ player->GetPosition().x,player->GetPosition().y + 10,player->GetPosition().z - 10 });
}

void StartMap::Draw(DirectXCommon* dxCommon) {
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

	Sprite::PreDraw();
	//�w�i�p
	//sprite->Draw();


	Object3d::PreDraw();
	//object1->Draw(dxCommon->GetCmdList());
	//�w�i�p
	objGround->Draw();
	player->Draw();
	for (int i = 0; i < EnemyMax; i++) {
		enemy[i]->Draw();
	}

	bossenemy->Draw();
	Texture::PreDraw();
}