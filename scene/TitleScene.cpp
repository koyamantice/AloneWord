#include "TitleScene.h"
#include"SceneManager.h"
#include "Audio.h"
#include "input.h"
#include "DebugText.h"
#include"ImageManager.h"
void TitleScene::Initialize(DirectXCommon* dxCommon) {
	// �J��������
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height);
	Texture::SetCamera(camera);
	// 3D�I�u�W�F�N�g�ɃJ�������Z�b�g
	Object3d::SetCamera(camera);
	// ���f���ǂݍ���
	Audio::GetInstance()->LoadSound(1, "Resources/BGM/NewWorld.wav");
	//srand(NULL);
	// ���C�g����
	lightGroup = LightGroup::Create();
	// 3D�I�u�G�N�g�Ƀ��C�g���Z�b�g
	Object3d::SetLightGroup(lightGroup);

	//���̏��Ԃŏ����Ȃ��Ɨ�O�X���[�ɂȂ�܂�
	// �f�o�C�X���Z�b�g
	FBXObject3d::SetDevice(dxCommon->GetDev());
	// �J�������Z�b�g
	FBXObject3d::SetCamera(camera);
	// �O���t�B�b�N�X�p�C�v���C������
	FBXObject3d::CreateGraphicsPipeline();
	player = new Player();
	player->Initialize();
	player->SetMove(50.0f, 50.0f);
	player->SetPosition({ 0.0f,5.0f,-10.0f });

	//�w�i�X�v���C�g����
	sprite[back] = Sprite::Create(ImageManager::TITLE, { 0.0f,0.0f });
	sprite[button1] = Sprite::Create(ImageManager::Tbutton, { 320.0f,600.0f });
	sprite[button1]->SetAnchorPoint({ 0.5f,0.5f });
	sprite[button1]->SetScale(0.7f);
	sprite[button2] = Sprite::Create(ImageManager::Tbutton, { 960.0f,600.0f });
	sprite[button2]->SetAnchorPoint({ 0.5f,0.5f });
	sprite[button2]->SetScale(0.7f);
	sprite[sky] = Sprite::Create(ImageManager::sky, { 0.0f,0.0f });
	sprite[ground] = Sprite::Create(ImageManager::ground, { 0.0f,0.0f });
	//�X�v���C�g����
	expandchange = new ExpandChange();
}

void TitleScene::Finalize() {
	//�R���̃��f���̃f���[�g
	delete player;
	delete sprite[0];
	expandchange->Finalize();
}

void TitleScene::Update(DirectXCommon* dxCommon) {
	Input* input = Input::GetInstance();
	if (input->PushKey(DIK_RETURN) || input->TriggerButton(input->Button_X)) {
		Audio::GetInstance()->PlayWave("Resources/Sound/Button.wav", 0.4f);
		expandchange->SetStartChange(true);
		SelectNumber = Select;
	} else if (input->TriggerButton(input->Button_A)) {
		Audio::GetInstance()->PlayWave("Resources/Sound/Button.wav", 0.4f);
		expandchange->SetStartChange(true);
		SelectNumber = Start;
	}

	if (expandchange->GetTimer() >= 58) {
		if (SelectNumber == Select) {
			SceneManager::GetInstance()->ChangeScene("StageSelect");
		} else {
			SceneManager::GetInstance()->ChangeScene("STARTMAP");
		}
	}
	player->TitleUp();
	expandchange->Update();
	camera->Update();
	cameraPos.x = player->GetPosition().x;
	cameraPos.y = player->GetPosition().y + 4.0f;
	cameraPos.z = player->GetPosition().z - 4.0f;
	camera->SetTarget(player->GetPosition());
	camera->SetEye(cameraPos);
}

void TitleScene::Draw(DirectXCommon* dxCommon) {
	
	Sprite::PreDraw();

	//�w�i�p
	sprite[0]->Draw();
	//sprite[4]->Draw();
	//sprite[3]->Draw();
	sprite[1]->Draw();
	sprite[2]->Draw();


	player->Draw(dxCommon);

	Sprite::PreDraw();
	
	//�O�ʗp
	expandchange->Draw();

}

