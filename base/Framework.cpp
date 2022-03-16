#include "Framework.h"
#include "FbxLoader.h"
void Framework::Run() {
	//������
	Initialize(dxcommon);
	while (true)//�Q�[�����[�v
	{
		//���t���[���X�V
		Update(dxcommon);

		//�I�����N�G�X�g�������甲����
		if (IsEndRequst()) {
			break;
		}

		//�`��
		Draw(dxcommon);
	}
	//�Q�[���̏I��
	Finalize();

}

void Framework::Initialize(DirectXCommon* dxCommon) {
	winApp = new WinApp();
	winApp->Initialize();
	dxcommon = new DirectXCommon();
	dxcommon->Initialize(winApp);
	// ���͂̏�����
	input = Input::GetInstance();
	input->Initialize(winApp);

	audio = Audio::GetInstance();
	audio->Initialize();	
	
	
	//�X�v���C�g�֌W
	// �X�v���C�g�ÓI������
	Sprite::StaticInitialize(dxcommon->GetDev(), dxcommon->GetCmdList(),WinApp::window_width, WinApp::window_height);

	const int debugTextTexNumber = 0;
	// �f�o�b�O�e�L�X�g�p�e�N�X�`���ǂݍ���
	if (!Sprite::LoadTexture(debugTextTexNumber, L"Resources/2d/debugfont.png")) {
		assert(0);
		return;
	}
	// �f�o�b�O�e�L�X�g������
	debugText = DebugText::GetInstance();
	debugText->Initialize(debugTextTexNumber);

	// ���C�g�ÓI������
	LightGroup::StaticInitialize(dxcommon->GetDev());
	//�e�N�X�`��������
	Texture::StaticInitialize(dxcommon->GetDev(), dxcommon->GetCmdList(), WinApp::window_width, WinApp::window_height);
	Object3d::StaticInitialize(dxcommon->GetDev(), dxcommon->GetCmdList(), WinApp::window_width, WinApp::window_height);
	// �}�E�X�J�[�\���̔�\��
	ShowCursor(TRUE);
	//�V�[���}�l�[�W���[
	// FBX�֘A�ÓI������
	FbxLoader::GetInstance()->Initialize(dxcommon->GetDev());
}

void Framework::Finalize() {
	delete sceneFactory_;
	//delete dxCommon;
	winApp->Finalize();
	delete winApp;

}

void Framework::Update(DirectXCommon* dxCommon) {
	input->Update(winApp);
	if (winApp->ProcessMessage() || input->TriggerKey(DIK_ESCAPE)) {
		endResquest_ = true;
		return;
	}
	SceneManager::GetInstance()->Update(dxCommon);
}

void Framework::Draw(DirectXCommon* dxCommon) {
	dxCommon->PreDraw();

	SceneManager::GetInstance()->Draw(dxCommon);

	debugText->DrawAll();
	dxCommon->PostDraw();

}
