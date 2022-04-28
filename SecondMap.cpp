#include "SecondMap.h"
#include "Audio.h"
#include "DebugText.h"
#include "TitleScene.h"
#include "FbxLoader.h"
#include"Collision.h"
#include "TouchableObject.h"
#include "MeshCollider.h"
#include "SphereCollider.h"
#include "CollisionManager.h"
#include <XorShift.h>
void SecondMap::Initialize(DirectXCommon* dxCommon) {
	//Texture::LoadTexture(0, L"Resources/2d/enemy.png");
	////Texture::LoadTexture(1, L"Resources/2d/limit.png");
	//Texture::LoadTexture(2, L"Resources/2d/shadow.png");
	//Texture::LoadTexture(3, L"Resources/2d/Resporn.png");
	//Texture::LoadTexture(4, L"Resources/2d/effect2.png");
	//Texture::LoadTexture(5, L"Resources/2d/PlayerHP.png");
	//Texture::LoadTexture(6, L"Resources/2d/magic2.png");
	collisionManager = CollisionManager::GetInstance();
	// �J��������
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height);
	Texture::SetCamera(camera);
	// 3D�I�u�W�F�N�g�ɃJ�������Z�b�g
	Object3d::SetCamera(camera);
	player = new Player();
	player->Initialize();
	player->SetMove(50.0f, 50.0f);
	player->SetPosition({ 0.0f,0.0f,-30.0f });

	ui = new UI(player);
	for (std::size_t i = 0; i < spawing.size(); i++) {
		spawing[i] = new Spawning();
		spawing[i]->SetPlayer(player);
		spawing[i]->Initialize();
	}

	spawing[0]->SetPosition({ -20.0f,0.0f,-4.0f });
	spawing[0]->SetRotation({ 0,90,0 });

	spawing[1]->SetPosition({ 0,0.0f,8.0f });
	spawing[1]->SetRotation({ 0,90,0 });

	spawing[2]->SetPosition({ 20.0f,0.0f,-4.0f });
	spawing[2]->SetRotation({ 0,90,0 });

	//�I�u�W�F�N�g������
	/*modelGround = Model::CreateFromOBJ("ground");
	objFloor = Object3d::Create();
	objFloor->Initialize();
	objFloor->SetModel(modelGround);
	objFloor->SetPosition({ 0,-1,0 });*/
	//�X�e�[�W��
	objFloor = Object3d::Create();
	modelFloor = Model::CreateFromOBJ("floor");
	objFloor->SetModel(modelFloor);
	objFloor->SetPosition({ 0, -1, 0 });
	objFloor->SetScale({ 4.0f,1.0f,5.0f });

	//�X�e�[�W�}�b�v
	modelSecondMap = Model::CreateFromOBJ("StartMap");
	objSecondMap = TouchableObject::Create(modelSecondMap);
	objSecondMap->SetPosition({ 0,-1,2 });
	objSecondMap->SetRotation({ 0, 90, 0 });
	objSecondMap->SetScale({ 1.4f,1.5f,1.6f });
	//�o���P�[�h
	for (std::size_t i = 0; i < objBlock.size(); i++) {
		objBlock[i] = Object3d::Create();
		modelBlock[i] = Model::CreateFromOBJ("Fork");
		objBlock[i]->SetModel(modelBlock[i]);
		BlockRotation[i] = { 0.0f,90.0f,0.0f };
		objBlock[i]->SetRotation(BlockRotation[i]);
	}
	//�o���P�[�h�I�Ȃ�̊e�ꏊ�ݒ�
	objBlock[0]->SetPosition({ -5.5f,0.0f,-25.0f });
	objBlock[1]->SetPosition({ 3.5f,0.0f,-25.0f });
	objBlock[2]->SetPosition({ -5.5f,0.0f, 25.0f });
	objBlock[3]->SetPosition({ 3.5f,0.0f, 25.0f });

	//���ʂ̃e�N�X�`��(�|��)
	warp = new Warp;
	warp->Initialize();
	warp->SetPosition({ 0.0f,10.0f,50.0f });
	/*limit = texture::create(1, { 0,0,0 }, { 12,12,12 }, { 1,1,1,0.6f });
	limit->texturecreate();
	limit->setposition({ 0.0f,0.01f,0.0f });
	limit->setrotation({ 90.0f,0, 0 });
	limit->setscale({ 5.5f, 5.5f,  5.5f});*/

	//�w�i�X�v���C�g����

	// ���f���ǂݍ���
	Audio::GetInstance()->LoadSound(1, "Resources/BGM/NewWorld.wav");
	//srand(NULL);
	// ���C�g����
	lightGroup = LightGroup::Create();
	// 3D�I�u�G�N�g�Ƀ��C�g���Z�b�g
	Object3d::SetLightGroup(lightGroup);

	//�J�����|�W�V����
	cameraPos.x = player->GetTargetPosition().x;
	cameraPos.y = player->GetTargetPosition().y + 10;
	cameraPos.z = player->GetTargetPosition().z - 10;
	// �J���������_���Z�b�g
	camera->SetTarget(player->GetTargetPosition());
	camera->SetEye(cameraPos);
	// ���f�������w�肵�ăt�@�C���ǂݍ���
	model1 =ModelManager::GetIns()->GetFBXModel(ModelManager::Pla);

	// �f�o�C�X���Z�b�g
	FBXObject3d::SetDevice(dxCommon->GetDev());
	// �J�������Z�b�g
	FBXObject3d::SetCamera(camera);
	// �O���t�B�b�N�X�p�C�v���C������
	FBXObject3d::CreateGraphicsPipeline();
	// �p�[�e�B�N���}�l�[�W������
	particleMan = ParticleManager::GetInstance();
	particleMan->SetCamera(camera);

	object1 = new FBXObject3d;
	object1->Initialize();
	object1->SetModel(model1);
	object1->SetScale({ 0.007f,0.007f,0.007f });
	object1->SetRotation(player->GetRotation());
	object1->SetPosition(player->GetPosition());
}

void SecondMap::Finalize() {
	delete camera;
	//�R���̃��f���̃f���[�g
	//for (int i = 0; i < StartEnemyMax; i++) {
	//	enemy[i]->Finalize();
	//}
	for (std::size_t i = 0; i < spawing.size(); i++) {
		spawing[i]->Finalize();
	}

	for (std::size_t i = 0; i < objBlock.size(); i++) {
		delete objBlock[i];
		delete modelBlock[i];
	}
	player->Finalize();
	delete modelFloor;
	delete objFloor;
	delete modelSecondMap;
	delete objSecondMap;
	delete object1;
	//delete model1;
	warp->Finalize();
}

void SecondMap::Update(DirectXCommon* dxCommon) {
	if (pause) {
		particleMan->Update();
		for (std::size_t i = 0; i < spawing.size(); i++) {
			spawing[i]->Update();
		}
		Pause(set);
		return;
	}
	for (std::size_t i = 0; i < spawing.size(); i++) {
		for (int j = 0; j < 1; j++) {
			if (spawing[i]->GetEnemy(j)->collideAttackArm()) {
				set = 30;
				set = 15;

				pause = true;
				break;
			}
		}
	}
	//objFloor->Update();
	objFloor->Update();
	objSecondMap->Update();
	lightGroup->Update();
	camera->Update();
	player->Update();
	particleMan->Update();
	warp->Update(player);
	for (std::size_t i = 0; i < objBlock.size(); i++) {
		objBlock[i]->SetRotation(BlockRotation[i]);
		objBlock[i]->Update();
	}
	if (spawing[0]->collideAttackArm()) {
		set = spawing[0]->GetStop();
		pause = true;
	}
	for (std::size_t i = 0; i < spawing.size(); i++) {
		spawing[i]->Update();
	}

	if (warp->collidePlayer(player)) {
		SceneManager::GetInstance()->ChangeScene("SECONDBOSS");
	}
	for (std::size_t i = 0; i < spawing.size(); i++) {
		for (int j = 0; j < 1; j++) {
			player->ResetWeight(spawing[i]->GetEnemy(j));
			player->Rebound(spawing[i]->GetEnemy(j));
		}
	}

	if (input->TriggerKey(DIK_C || input->TriggerButton(input->Button_X))) {
		Audio::GetInstance()->StopWave(0);
		Audio::GetInstance()->StopWave(1);
		Audio::GetInstance()->LoopWave(1, 0.7f);
	}
	if (input->TriggerKey(DIK_SPACE)) {
		set = 15;
		pause = true;
	}

	////�G���m�̓����蔻��
	//if (sizeof(enemy) > 2) {//�z��̃T�C�Y�m�F
	//	for (int colA = 0; colA < StartEnemyMax; colA++) {
	//		for (int colB = 1; colB < StartEnemyMax; colB++) {
	//			if (Collision::CheckSphere2Sphere(enemy[colA]->collider, enemy[colB]->collider) == true && colA != colB) {//�����蔻��Ǝ��@���m�̓����蔻��̍폜
	//				//DebugText::GetInstance()->Print("Hit", 0, 0, 5.0f);
	//				enemy[colA]->SetHit(true);
	//				enemy[colB]->SetHit(false);
	//				break;

	//			}
	//			else {
	//				enemy[colA]->SetHit(false);
	//			}
	//		}
	//	}
	//}
	//for (std::size_t i = 0; i < spawing.size(); i++) {
	//	for (int colA = 0; colA < 5; colA++) {
	//		for (int colB = 1; colB < 5; colB++) {
	//			if (spawing[i]->GetEnemy(colA)->GetIsAlive()) {
	//				if (Collision::CheckSphere2Sphere(spawing[i]->GetEnemy(colA)->collider, spawing[i]->GetEnemy(colB)->collider) == true && colA != colB) {//�����蔻��Ǝ��@���m�̓����蔻��̍폜
	//					spawing[i]->GetEnemy(colA)->SetHit(true);
	//					spawing[i]->GetEnemy(colB)->SetHit(false);
	//					break;

	//				} else {
	//					spawing[i]->GetEnemy(colA)->SetHit(false);
	//				}
	//			}
	//		}
	//	}
	//}

	//���̑��V�[���ڍs

	/*if (bossenemy->GetHP() <= 0) {
		SceneManager::GetInstance()->ChangeScene("CLEAR");
	}*/


	Ray ray;
	ray.start = { player->GetPosition().x,player->GetPosition().y + 3,player->GetPosition().z,1 };
	ray.dir = { 0,0.28,-1,0 };
	RaycastHit raycastHit;

	if (!collisionManager->Raycast(ray, &raycastHit)) {
		if (distanceZ <= 10.0f) {
			distanceZ += 0.25f;
		}

		if (distanceY >= 10.0f) {
			distanceY -= 0.25f;
		}
	}
	else {
		if (distanceZ >= 6.0f) {
			distanceZ -= 0.4f;
		}

		if (distanceY <= 18.0f) {
			distanceY += 0.25f;
		}
	}


	//if (spawing[0]->GetIsAlive() == 0) {
	//	if (spawing[1]->GetIsAlive() == 0) {
	//		if (spawing[2]->GetIsAlive() == 0) {
	//			Clear = true;
	//		}
	//	}
	//}
	if (input->TriggerKey(DIK_C)) {
		Clear = true;
	}

	if (player->GetPosition().z >= -22) {
		start = true;
	}

	if (!Clear) {
		if (player->GetPosition().z >= 23.9f) {
			player->SetPosition({ player->GetPosition().x,0,23.9f });
		}
		if (player->GetPosition().z <= -22 && start) {
			player->SetPosition({ player->GetPosition().x,0,-22 });
		}
		if (start == true) {
			if (BlockRotation[0].x <= 45.0f) {
				BlockRotation[0].x += 4.5f;
				BlockRotation[2].x += 4.5f;
			}

			if (BlockRotation[1].x >= -45.0f) {
				BlockRotation[1].x -= 4.5f;
				BlockRotation[3].x -= 4.5f;
			}
		}
	}
	else {
		if (BlockRotation[0].x >= 0.0f) {
			BlockRotation[0].x -= 4.5f;
			BlockRotation[2].x -= 4.5f;
		}

		if (BlockRotation[1].x <= 0.0f) {
			BlockRotation[1].x += 4.5f;
			BlockRotation[3].x += 4.5f;
		}
	}

	if (player->GetHp() <= 0) {
		SceneManager::GetInstance()->ChangeScene("GAMEOVER");
	}

	if (input->PushKey(DIK_0)) {
		object1->PlayAnimation();
	}
	ui->Update();
	object1->SetRotation(player->GetRotation());
	object1->SetPosition(player->GetPosition());
	object1->Update();
	cameraPos.x = player->GetTargetPosition().x;
	cameraPos.y = player->GetTargetPosition().y + distanceY;
	cameraPos.z = player->GetPosition().z - distanceZ;
	camera->SetTarget(player->GetTargetPosition());
	camera->SetEye(cameraPos);
	/*if (cameraPos.z <= -20.0f) {

	}*/
	/*DebugText::GetInstance()->Print("PUSH to RB!!", 1040, 620, 2.0f);
	DebugText::GetInstance()->Print("PUSH to A!!", 1040, 660, 2.0f);*/
	if (player->GetArmWeight() > 0) {
		DebugText::GetInstance()->Print("RB or LB :Rotate", 900, 620, 2.0f);
	}
	DebugText::GetInstance()->Print("A         :Hand", 900, 650, 2.0f);
}

void SecondMap::Draw(DirectXCommon* dxCommon) {
	ImGui::Begin("test");
	if (ImGui::TreeNode("Debug"))
	{
		if (ImGui::TreeNode("Field"))
		{
			float a = (float)XorShift::GetInstance()->xor128();
			ImGui::SliderFloat("a", &a, 100, 0);
			ImGui::SliderFloat("b", &distanceZ, 50, -50);
			ImGui::Unindent();
			ImGui::TreePop();
		}
		ImGui::TreePop();
	}
	ImGui::End();
	Object3d::PreDraw();
	//objFloor->Draw();
	objFloor->Draw();
	objSecondMap->Draw();
	for (std::size_t i = 0; i < objBlock.size(); i++) {
		objBlock[i]->Draw();
	}
	Texture::PreDraw();
	if (start && !Clear) {
		//limit->Draw();
	}
	warp->Draw();

	//Sprite::PreDraw();
	//�w�i�p
	//sprite->Draw();


	Object3d::PreDraw();
	object1->Draw(dxCommon->GetCmdList());
	//�w�i�p
	player->Draw();
	//for (int i = 0; i < StartEnemyMax; i++) {
	//	enemy[i]->Draw();
	//}
	for (std::size_t i = 0; i < spawing.size(); i++) {
		spawing[i]->Draw();
	}
	//bossenemy->Draw();
	ui->Draw();
	// �p�[�e�B�N���̕`��
	particleMan->Draw(dxCommon->GetCmdList());
}

void SecondMap::Pause(const int& Timer) {
	wait++;
	if (wait >= Timer) {
		pause = false;
		wait = 0;
	}
	else {
		pause = true;
	}
	player->Pause(Timer);
	for (std::size_t i = 0; i < spawing.size(); i++) {
		spawing[i]->Pause(Timer);
	}

}
