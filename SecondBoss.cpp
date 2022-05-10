#include "SecondBoss.h"
#include "Audio.h"
#include "DebugText.h"
#include "TitleScene.h"
#include "FbxLoader.h"
#include"Collision.h"
#include "TouchableObject.h"
#include "MeshCollider.h"
#include "SphereCollider.h"
#include "CollisionManager.h"
#include <Easing.h>
void SecondBoss::Initialize(DirectXCommon* dxCommon) {
	//�C���X�^���X�擾
	collisionManager = CollisionManager::GetInstance();
	// �J��������
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height);
	Texture::SetCamera(camera);
	// 3D�I�u�W�F�N�g�ɃJ�������Z�b�g
	Object3d::SetCamera(camera);

	//�X�e�[�W��
	objFloor = Object3d::Create();
	modelFloor = Model::CreateFromOBJ("floor");
	objFloor->SetModel(modelFloor);
	objFloor->SetPosition({ 0, -1, 0 });
	objFloor->SetScale({ 3.0f,1.0f,3.0f });

	//�X�e�[�W�}�b�v
	modelBossMap = Model::CreateFromOBJ("BossMap");
	objBossMap = TouchableObject::Create(modelBossMap);
	objBossMap->SetPosition({ 0,-1,2 });
	objBossMap->SetRotation({ 0, 90, 0 });
	objBossMap->SetScale({ 1.4f,1.5f,1.6f });
	/*
	objBossMap->SetModel(modelBossMap);
	objBossMap->SetPosition({ 0,-1,2 });
	objBossMap->SetRotation({ 0, 90, 0 });
	objBossMap->SetScale({ 1.4f,1.5f,1.6f });
	*/
	//�����蔻��m�F�p�ł�

	objSphere = Object3d::Create();
	modelSphere = Model::CreateFromOBJ("sphere");
	objSphere->SetModel(modelSphere);
	objSphere->SetPosition({ -10, 1, 0 });
	// �R���C�_�[�̒ǉ�
	//objSphere->SetCollider(new SphereCollider);

	//���ʂ̃e�N�X�`��(�|��)
	/*limit = Texture::Create(1, { 0,0,0 }, { 12,12,12 }, { 1,1,1,0.6f });
	objBossMap->SetPosition({ 0,-1,10 });
	objBossMap->SetScale({ 22,1,10 });
	//普通�EチE��スチャ(板ポリ)
	limit = Texture::Create(1, { 0,0,0 }, { 12,12,12 }, { 1,1,1,0.6f });
	limit->TextureCreate();
	limit->SetPosition({ 0.0f,0.01f,0.0f });
	limit->SetRotation({ 90.0f,0, 0 });
	limit->SetScale({ 6,5,5 });*/

	for (std::size_t i = 0; i < effect.size(); i++) {
		effect[i] = new Effect();
		effect[i]->Initialize();
	}

	//for (std::size_t i = 0; i < exp.size(); i++) {
	//	for (std::size_t j = 0; j < exp[i].size(); j++) {
	//		exp[i][j] = new Exp();
	//		exp[i][j]->Initialize();
	//	}
	//}

	Audio::GetInstance()->LoadSound(1, "Resources/BGM/NewWorld.wav");
	//srand(NULL);GetFBXModel(ModelManager::MottiMove);
	// ���C�g����
	lightGroup = LightGroup::Create();
	// 3D�I�u�W�F�N�g�Ƀ��C�g���Z�b�g
	Object3d::SetLightGroup(lightGroup);

	// �f�o�C�X���Z�b�g
	FBXObject3d::SetDevice(dxCommon->GetDev());
	// �J�������Z�b�g
	FBXObject3d::SetCamera(camera);
	// �O���t�B�b�N�X�p�C�v���C������
	FBXObject3d::CreateGraphicsPipeline();
	// �p�[�e�B�N���}�l�[�W������
	particleMan = ParticleManager::GetInstance();
	particleMan->SetCamera(camera);
	//�e�I�u�W�F�N�g�̏�����
	//�v���C���[
	player = new Player();
	player->Initialize();
	player->SetPosition({ 0.0f,0.0f,-10.0f });
	player->SetMove(250.0f, 200.0f);

	//�{�X
	leftshose = new LeftShose();
	leftshose->SetPlayer(player);
	leftshose->Initialize();

	rightshose = new RightShose();
	rightshose->SetPlayer(player);
	rightshose->Initialize();

	//�G
	for (std::size_t i = 0; i < enemy.size(); i++) {
		enemy[i] = new Rice();
		enemy[i]->SetPlayer(player);
		enemy[i]->Initialize();
	}

	//�J�����|�W�V����
	cameraPos.x = player->GetTargetPosition().x;
	cameraPos.y = player->GetTargetPosition().y + 10;
	cameraPos.z = player->GetTargetPosition().z - 10;
	// �J���������_���Z�b�g
	cameratargetPos = player->GetPosition();
	camera->SetTarget(cameratargetPos);
	camera->SetEye(cameraPos);
	ui = new UI(player, leftshose, rightshose);
}

void SecondBoss::Finalize() {

	//3d�̃��f���̃f���[�g
	for (std::size_t i = 0; i < enemy.size(); i++) {
		enemy[i]->Finalize();
	}
	player->Finalize();
	leftshose->Finalize();
	rightshose->Finalize();
	delete objBossMap;
	delete objFloor;
	delete modelBossMap;
	delete modelFloor;
	for (std::size_t i = 0; i < effect.size(); i++) {
		effect[i]->Finalize();
	}
	for (std::size_t i = 0; i < exp.size(); i++) {
		for (std::size_t j = 0; j < exp[i].size(); j++) {
			exp[i][j]->Finalize();
		}
	}
	delete camera;
	delete object1;
	delete model1;
}

void SecondBoss::Update(DirectXCommon* dxCommon) {
	//objBossMap->Update();
	//�e�I�u�W�F�N�g�̍X�V
	objBossMap->Update();
	objFloor->Update();
	lightGroup->Update();

	//�ŏ��̉��o
	if (!bossstart) {
		appearanceTimer++;
		player->Begin();
		leftshose->Begin();
		rightshose->Begin();
		if (appearanceTimer == 1) {
			cameraPos.x = player->GetPosition().x;
			cameraPos.y = player->GetPosition().y + distanceY;
			cameraPos.z = player->GetPosition().z - distanceZ;
		}

		if (appearanceTimer == 100) {
			appearanceNumber++;

		}

		if (appearanceNumber == 1) {
			Aftereyepos = {
				0,
				leftshose->GetPosition().y + distanceY,
				leftshose->GetPosition().z - distanceZ,
			};

			Aftertargetpos = {
			0,
			2.0f,
			0,
			};

			if (frame < 1.0f) {
				frame += 0.01f;
			}
			else {
				frame = 0;
				appearanceNumber = 2;
			}

			cameraPos = {
Ease(In,Cubic,frame,cameraPos.x,Aftereyepos.x),
Ease(In,Cubic,frame,cameraPos.y,Aftereyepos.y),
Ease(In,Cubic,frame,cameraPos.z,Aftereyepos.z)
			};

			cameratargetPos = {
Ease(In,Cubic,frame,cameratargetPos.x,Aftertargetpos.x),
Ease(In,Cubic,frame,cameratargetPos.y,Aftertargetpos.y),
Ease(In,Cubic,frame,cameratargetPos.z,Aftertargetpos.z)
			};
		}
		else if (appearanceNumber == 2) {
			Aftereyepos = {
				player->GetPosition().x,
				player->GetPosition().y + distanceY,
				player->GetPosition().z - distanceZ,
			};

			Aftertargetpos = {
				player->GetPosition().x,
				player->GetPosition().y,
				player->GetPosition().z,
			};

			if (frame < 1.0f) {
				frame += 0.01f;
			}
			else {
				bossstart = true;
				appearanceTimer = 0;
				appearanceNumber = 0;
				frame = 0;
			}

			cameraPos = {
Ease(In,Cubic,frame,cameraPos.x,Aftereyepos.x),
Ease(In,Cubic,frame,cameraPos.y,Aftereyepos.y),
Ease(In,Cubic,frame,cameraPos.z,Aftereyepos.z)
			};

			cameratargetPos = {
Ease(In,Cubic,frame,cameratargetPos.x,Aftertargetpos.x),
Ease(In,Cubic,frame,cameratargetPos.y,Aftertargetpos.y),
Ease(In,Cubic,frame,cameratargetPos.z,Aftertargetpos.z)
			};
		}

		camera->SetTarget(cameratargetPos);
		camera->SetEye(cameraPos);
	}
	//�퓬�J�n
	else {
		player->Update();
		leftshose->Update();
		if (rightshose->GetHP() >= 1) {
			rightshose->SetAct(leftshose);
		}
		rightshose->Update();
		for (std::size_t i = 0; i < enemy.size(); i++) {
			enemy[i]->Update();
			enemy[i]->SetEnemy();
			player->ResetWeight(enemy[i]);
			player->Rebound(enemy[i]);
		}
		ui->Update();
		particleMan->Update();
		objSphere->Update();
		cameraPos.x = player->GetPosition().x;
		cameraPos.y = player->GetPosition().y + distanceY;
		cameraPos.z = player->GetPosition().z - distanceZ;
		camera->SetTarget(player->GetPosition());
		camera->SetEye(cameraPos);
	}
	camera->Update();

	for (std::size_t i = 0; i < effect.size(); i++) {
		effect[i]->Update(leftshose);
		effect[i]->Update(rightshose);
	}

	for (std::size_t i = 0; i < effect.size(); i++) {
		effect[i]->Update(leftshose);
		effect[i]->Update(rightshose);
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

	//�G���m�̓����蔻��
	if (sizeof(enemy) > 2) {//�z��̃T�C�Y�m�F
		for (int colA = 0; colA < SecondBossEnemyMax; colA++) {
			for (int colB = 1; colB < SecondBossEnemyMax; colB++) {
				if (Collision::CircleCollision(enemy[colA]->GetPosition().x, enemy[colA]->GetPosition().z, 3.0f, enemy[colB]->GetPosition().x, enemy[colB]->GetPosition().z, 3.0f) == true && colA != colB) {//当たり判定と自機同士の当たり判定�E削除
					//DebugText::GetInstance()->Print("Hit", 0, 0, 5.0f);
					enemy[colA]->SetHit(true);
					enemy[colB]->SetHit(false);
					break;
				}
				else {
					enemy[colA]->SetHit(false);
				}
			}
		}
	}

	Ray ray;
	ray.start = { player->GetPosition().x,player->GetPosition().y + 3,player->GetPosition().z,1 };
	ray.dir = { 0.0f,0.025f,-1.0f};
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

	//���̑��V�[���ڍs
	if (leftshose->GetHP() <= 0 && rightshose->GetHP() <= 0) {
		SceneManager::GetInstance()->ChangeScene("StageSelect");
	}

	if (player->GetHp() <= 0) {
		SceneManager::GetInstance()->ChangeScene("GAMEOVER");
	}
	
	// �S�Ă̏Փ˂��`�F�b�N
	//collsionManager->CheckAllCollisions();
	/*DebugText::GetInstance()->Print("PUSH to RB!!",200, 100,1.0f);
	DebugText::GetInstance()->Print("PUSH to A!!", 200, 115, 1.0f);*/
	//DebugText::GetInstance()->Print("RB or LB :Rotate", 900, 620, 2.0f);
	//DebugText::GetInstance()->Print("A         :Hand", 900, 650, 2.0f);
	//DebugText::GetInstance()->Print("PUSH to RB!!", 1040, 620, 2.0f);
	//DebugText::GetInstance()->Print("PUSH to A!!", 1040, 660, 2.0f);
}

void SecondBoss::Draw(DirectXCommon* dxCommon) {
	//�e�I�u�W�F�N�g�̕`��
	Object3d::PreDraw();
	//objBossMap->Draw();
	//objSphere->Draw();
	objBossMap->Draw();
	objFloor->Draw();

	Texture::PreDraw();
	//limit->Draw();
	//Sprite::PreDraw();
	//sprite->Draw();

	player->Draw(dxCommon);
	for (std::size_t i = 0; i < enemy.size(); i++) {
		enemy[i]->Draw();
	}
	leftshose->Draw();
	rightshose->Draw();

	for (std::size_t i = 0; i < effect.size(); i++) {
		effect[i]->Draw();
	}

	//for (std::size_t i = 0; i < exp.size(); i++) {
	//	for (std::size_t j = 0; j < exp[i].size(); j++) {
	//		exp[i][j]->Draw();
	//	}
	//}

	ui->Draw();
	// �p�[�e�B�N���̕`��
	particleMan->Draw(dxCommon->GetCmdList());
}