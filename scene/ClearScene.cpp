#include "ClearScene.h"
#include "Audio.h"
#include "input.h"
#include "DebugText.h"
#include "SceneManager.h"
#include "BossScene.h"
#include "ClearScene.h"
#include"ImageManager.h"
void ClearScene::Initialize(DirectXCommon* dxCommon) {
	//�w�i�X�v���C�g����
	sprite = Sprite::Create(ImageManager::BlackFilter, { 0.0f,0.0f });

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
	/*player->SetRotation({ 0.0f,0.0f,0.0f });
	player->SetPosition({ 0.0f,0.0f,0.0f });
	player->SetMove(10.0f, 10.0f);*/


	//camera->SetEye(XMFLOAT3{ 0,15,-0.5f });
	////camera->SetTarget(XMFLOAT3{ 0,0,0 });
	//camera->SetDistance(200.0f);
	ParticleManager::GetInstance()->SetCamera(camera);

	//�J�����|�W�V����
	cameraPos.x = 0;
	cameraPos.y = 0;
	cameraPos.z = -10.0f;
	// �J���������_���Z�b�g
	cameratargetPos = { 0.0f,0.0f,0.0f };
	camera->SetTarget(cameratargetPos);
	camera->SetEye(cameraPos);
}

void ClearScene::Update(DirectXCommon* dxCommon) {
	ClearTimer++;
	player->Clear(ClearTimer);
	/*if (input->PushKey(DIK_RETURN) || input->TriggerButton(input->Button_B)) {
		Audio::GetInstance()->PlayWave("Resources/Sound/Button.wav", 0.4f);
		SceneManager::GetInstance()->ChangeScene("TITLE");
	}*/
	//DebugText::GetInstance()->Print("Buttun_B or ENTER to TITLE!!", 200, 100, 1.0f);
}

void ClearScene::Draw(DirectXCommon* dxCommon) {
	Sprite::PreDraw();
	sprite->Draw();
	Texture::PreDraw();
	player->Draw(dxCommon);
}
void ClearScene::Finalize() {
	//�R���̃��f���̃f���[�g
	delete sprite;
}

