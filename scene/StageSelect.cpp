#include "StageSelect.h"
#include "ImageManager.h"
#include "Input.h"
#include"SceneManager.h"

void StageSelect::Initialize(DirectXCommon* dxCommon) {
	//�w�i�X�v���C�g����
	BackGround = Sprite::Create(ImageManager::SELECT, { 0.0f,0.0f });
	select[0] = Sprite::Create(ImageManager::select1, { 0.0f,0.0f });
	select[0]->SetAnchorPoint({1.0f,0.5f});
	// �J��������
	//srand(NULL);
	// ���C�g����
	lightGroup = LightGroup::Create();
	// 3D�I�u�W�F�N�g�Ƀ��C�g���Z�b�g
	Object3d::SetLightGroup(lightGroup);

	camera = new DebugCamera(WinApp::window_width, WinApp::window_height);
	Texture::SetCamera(camera);
	// 3D�I�u�W�F�N�g�ɃJ�������Z�b�g
	Object3d::SetCamera(camera);
	// �f�o�C�X���Z�b�g
	FBXObject3d::SetDevice(dxCommon->GetDev());
	// �J�������Z�b�g
	FBXObject3d::SetCamera(camera);
	// �O���t�B�b�N�X�p�C�v���C������
	FBXObject3d::CreateGraphicsPipeline();
	//�e�I�u�W�F�N�g�̏�����
	//�v���C���[
	player = new Player();
	player->Initialize();
	player->SetRotation({ 0.0f,0.0f,0.0f });
	player->SetPosition({ 0.0f,0.0f,0.0f });
	player->SetMove(10.0f, 10.0f);
	camera->SetEye(XMFLOAT3{0,15,-1});
	//camera->SetTarget(XMFLOAT3{ 0,0,0 });
	camera->SetDistance(200.0f);
}

void StageSelect::Finalize() {
	delete BackGround;
	player->Finalize();

}

void StageSelect::Update(DirectXCommon* dxCommon) {
	input = Input::GetInstance();
	lightGroup->Update();
	camera->Update();
	player->SelectUp();

	if (input->PushKey(DIK_1) || input->PushKey(DIK_RETURN) || input->TriggerButton(input->Button_A)) {
		Audio::GetInstance()->PlayWave("Resources/Sound/Button.wav", 0.4f);
		SceneManager::GetInstance()->ChangeScene("STARTMAP");
	}
	if (input->PushKey(DIK_SPACE) || input->PushKey(DIK_2) || input->TriggerButton(input->Button_X)) {
		SceneManager::GetInstance()->ChangeScene("SECONDBOSS");
	}

	if (input->PushKey(DIK_3)) {
		SceneManager::GetInstance()->ChangeScene("THIRDBOSS");
	}
	if (input->PushKey(DIK_4) || input->TriggerButton(input->Button_Y)) {
		SceneManager::GetInstance()->ChangeScene("FOURTHBOSS");
	}

}

void StageSelect::Draw(DirectXCommon* dxCommon) {
	Sprite::PreDraw();
	BackGround->Draw();
	player->Draw(dxCommon);
	Sprite::PreDraw();
	select[0]->Draw();
}
