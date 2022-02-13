#include "GamePlayScene.h"
#include "Audio.h"
#include "input.h"
#include "DebugText.h"
#include "TitleScene.h"

void GamePlayScene::Initialize() {
	//�I�u�W�F�N�g������
	modelPin=Model::CreateFromOBJ("chr_knight");
	objPin=Object3d::Create();
	objPin->Initialize();
	objPin->SetModel(modelPin);
	objPin->SetPosition({0,0,0});
	// �e�N�X�`���ǂݍ���
	Sprite::LoadTexture(1, L"Resources/2d/title.png");
	Sprite::LoadTexture(2, L"Resources/2d/gameplay.png");

	//�w�i�X�v���C�g����
	sprite = Sprite::Create(2, { 0.0f,0.0f });
	//�X�v���C�g����
	objSkydome = Object3d::Create();
	modelSkydome = Model::CreateFromOBJ("skydome");
	// ���f���ǂݍ���
	Audio::GetInstance()->LoadSound(1, "Resources/BGM/NewWorld.wav");
	srand(NULL);
}

void GamePlayScene::Finalize() {
	//�R���̃��f���̃f���[�g
	delete objPin;
}

void GamePlayScene::Update() {
	Input* input = Input::GetInstance();
	objPin->Update();
	if (input->TriggerKey(DIK_Z)) {
		Audio::GetInstance()->StopWave(0);
		Audio::GetInstance()->StopWave(1);
		Audio::GetInstance()->LoopWave(0,0.7f);
	}
	if (input->TriggerKey(DIK_C)) {
		Audio::GetInstance()->StopWave(0);
		Audio::GetInstance()->StopWave(1);
		Audio::GetInstance()->LoopWave(1,0.7f);
	}
	if (input->TriggerKey(DIK_SPACE)) {
		Audio::GetInstance()->StopWave(0);
		Audio::GetInstance()->StopWave(1);
		SceneManager::GetInstance()->ChangeScene("TITLE");
	}
	DebugText::GetInstance()->Print("SPACE to TITLE!!",200, 100,1.0f);
	DebugText::GetInstance()->Print("Z or C to Sound!!", 200, 115, 1.0f);
	objSkydome->Update();
}

void GamePlayScene::Draw() {
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
	//�w�i�p
<<<<<<< HEAD
	objSkydome->Draw();
=======
	objPin->Draw();
>>>>>>> master


	//�O�ʗp

}

