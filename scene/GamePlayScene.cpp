#include "GamePlayScene.h"
#include "Audio.h"
#include "input.h"
#include "DebugText.h"
#include "TitleScene.h"
#include "FbxLoader.h"
void GamePlayScene::Initialize(DirectXCommon* dxCommon) {
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
	//���ʂ̃e�N�X�`��(�|��)
	/*Texture::LoadTexture(0, L"Resources/2d/title.png");
	titleTexture = Texture::Create(0, { 0,0,0 }, { 12,12,12 }, { 1,1,1,1 });
	titleTexture->TextureCreate();
	titleTexture->SetPosition({ 5.0f,10.0f,-10.0f });
	titleTexture->SetScale({ 0.5,0.5,0.5 });*/
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
	camera->SetEye({ player->GetPosition().x,player->GetPosition().y + 10,player->GetPosition().z - 10});
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

void GamePlayScene::Finalize() {
	//�R���̃��f���̃f���[�g
}

void GamePlayScene::Update(DirectXCommon* dxCommon) {
	Input* input = Input::GetInstance();
	objGround->Update();
	lightGroup->Update();
	camera->Update();
	player->Update();
	bossenemy->Update(player);
	for (int i = 0; i < EnemyMax; i++) {
		enemy[i]->Update(player,bossenemy);
	}
	
	if (input->TriggerKey(DIK_C || input->TriggerButton(input->Button_X))) {
		Audio::GetInstance()->StopWave(0);
		Audio::GetInstance()->StopWave(1);
		Audio::GetInstance()->LoopWave(1,0.7f);
	}
	//if (input->TriggerKey(DIK_SPACE) || input->TriggerButton(input->Button_A)) {
	//	Audio::GetInstance()->StopWave(0);
	//	Audio::GetInstance()->StopWave(1);
	//	SceneManager::GetInstance()->ChangeScene("TITLE");
	//}

	if (input->PushKey(DIK_0) || input->TriggerButton(input->Button_Y)) {
		object1->PlayAnimation();
	}

	object1->Update();
	DebugText::GetInstance()->Print("SPACE to TITLE!!",200, 100,1.0f);
	DebugText::GetInstance()->Print("Z or C to Sound!!", 200, 115, 1.0f);
	
	camera->SetTarget(player->GetPosition());
	camera->SetEye({ player->GetPosition().x,player->GetPosition().y + 10,player->GetPosition().z - 10 });
}

void GamePlayScene::Draw(DirectXCommon* dxCommon) {
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