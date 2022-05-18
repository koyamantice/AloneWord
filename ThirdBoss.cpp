#include "ThirdBoss.h"
#include "Audio.h"
#include "DebugText.h"
#include "TitleScene.h"
#include "FbxLoader.h"
#include"Collision.h"
#include "TouchableObject.h"
#include "MeshCollider.h"
#include "SphereCollider.h"
#include "CollisionManager.h"
#include "ImageManager.h"
#include <Easing.h>

void ThirdBoss::Initialize(DirectXCommon* dxCommon) {
	//�C���X�^���X�擾
	collisionManager = CollisionManager::GetInstance();
	// �J��������
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
	player->SetPosition({ 0.0f,0.0f,-10.0f });
	player->SetMove(250.0f, 200.0f);

	//�{�X
	bossenemy = new GreenTea();
	bossenemy->SetPlayer(player);
	bossenemy->Initialize();

	//�G
	for (std::size_t i = 0; i < enemy.size(); i++) {
		enemy[i] = new Rice();
		enemy[i]->SetPlayer(player);
		enemy[i]->Initialize();
	}

	//�X�e�[�W��
	objFloor = Object3d::Create();
	modelFloor = Model::CreateFromOBJ("floor");
	objFloor->SetModel(modelFloor);
	objFloor->SetPosition({ 0, -1, 0 });
	objFloor->SetScale({ 6.0f,1.0f,6.0f });

	//objSkydome = Object3d::Create();
	//modelSkydome = Model::CreateFromOBJ("skydome");
	//objSkydome->SetModel(modelSkydome);
	//objSkydome->SetPosition({ 0, -1, 0 });
	//objSkydome->SetScale({ 1.0f,1.0f,1.0f });

	//�X�e�[�W�}�b�v
	modelBossMap = Model::CreateFromOBJ("BossMap");
	objBossMap = TouchableObject::Create(modelBossMap);
	objBossMap->SetPosition({ 0,0,4 });
	objBossMap->SetRotation({ 0, 90, 0 });
	objBossMap->SetScale({ 3.0f,1.5f,3.0f });
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

	//�{�X�̖��O�\�L
	bossName = Sprite::Create(ImageManager::select1, namePos);
	bossName->SetAnchorPoint({ 1.0f,0.0f });

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
	//srand(NULL);
	// ���C�g����
	lightGroup = LightGroup::Create();
	// 3D�I�u�W�F�N�g�Ƀ��C�g���Z�b�g
	Object3d::SetLightGroup(lightGroup);
	cameraPos.x = player->GetPosition().x;
	cameraPos.y = player->GetPosition().y + distanceY;
	cameraPos.z = player->GetPosition().z - distanceZ;
	camera->SetTarget(player->GetPosition());
	camera->SetEye(cameraPos);
	// �p�[�e�B�N���}�l�[�W������
	particleMan = ParticleManager::GetInstance();
	particleMan->SetCamera(camera);

	ui = new UI(player, bossenemy);
	//ui->Initialize();
}

void ThirdBoss::Finalize() {

	//3d�̃��f���̃f���[�g
	for (std::size_t i = 0; i < enemy.size(); i++) {
		enemy[i]->Finalize();
	}
	player->Finalize();
	bossenemy->Finalize();
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
	ui->Finalize();
}

void ThirdBoss::Update(DirectXCommon* dxCommon) {
	//objBossMap->Update();
	//�e�I�u�W�F�N�g�̍X�V
	objBossMap->Update();
	objFloor->Update();
	lightGroup->Update();
	
	//�ŏ��̉��o(����)
	//�ŏ��̉��o(����)
	if (!bossstart) {
		appearanceTimer++;
		player->Begin();
		bossenemy->Begin();
		bossenemy->AppeaMovie(appearanceTimer);
		if (appearanceNumber == 0) {
			cameraPos.x = -7;
			cameraPos.y = 9;
			cameraPos.z = 0;
			cameratargetPos = { 0.0f,4.0f,0.0f };

			if (appearanceTimer == 100) {
				appearanceNumber++;
			}
		}

		else if (appearanceNumber == 1) {
			cameraPos.x = bossenemy->GetPosition().x + 5;
			cameraPos.y = bossenemy->GetPosition().y;
			cameraPos.z = bossenemy->GetPosition().z;
			cameratargetPos = bossenemy->GetPosition();

			if (appearanceTimer == 200) {
				appearanceNumber++;
			}

		}

		else if (appearanceNumber == 2) {
			cameraPos.x = bossenemy->GetPosition().x;
			cameraPos.y = bossenemy->GetPosition().y + 5;
			cameraPos.z = bossenemy->GetPosition().z - distanceZ;
			cameratargetPos = { 0.0f,5.0f,8.0f };

			if (appearanceTimer == 300) {
				appearanceNumber++;
			}
		}

		else if (appearanceNumber == 3) {
			Aftereyepos = {
				bossenemy->GetPosition().x,
				bossenemy->GetPosition().y,
				bossenemy->GetPosition().z - 7,
			};

			Aftertargetpos = {
				bossenemy->GetPosition().x,
				bossenemy->GetPosition().y,
				bossenemy->GetPosition().z,
			};

			if (frame < 1.0f) {
				frame += 0.015f;
			}
			else {
				frame = 1.0f;
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

			if (appearanceTimer == 360) {
				appearanceNumber++;
				frame = 0.0f;
			}
		}
		else if (appearanceNumber == 4) {
			if (nameframe >= 1.0f) {
				nameframe = 1.0f;
			}
			else {
				nameframe += 0.06f;
			}
			namePos = {
			Ease(In,Quad,nameframe,2000,940),
			480
			};

			bossName->SetPosition(namePos);
			if (appearanceTimer == 450) {
				nameframe = 0.0f;
				appearanceNumber++;
			}
		}
		else if (appearanceNumber == 5) {
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

			if (nameframe >= 1.0f) {
				nameframe = 1.0f;
			}
			else {
				nameframe += 0.06f;
			}
			namePos = {
			Ease(In,Quad,nameframe,940,2000),
			480
			};

			bossName->SetPosition(namePos);

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
		bossenemy->Update();
		for (std::size_t i = 0; i < enemy.size(); i++) {
			enemy[i]->Update();
			enemy[i]->SetEnemy();
			player->ResetWeight(enemy[i]);
		}
		if (player->GetDamageFlag() == true) {
			player->Rebound();
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
		effect[i]->Update(bossenemy);
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
		for (int colA = 0; colA < ThirdEnemyMax; colA++) {
			for (int colB = 1; colB < ThirdEnemyMax; colB++) {
				if (Collision::CircleCollision(enemy[colA]->GetPosition().x, enemy[colA]->GetPosition().z, 3.0f, enemy[colB]->GetPosition().x, enemy[colB]->GetPosition().z, 3.0f) == true && colA != colB) {//当たり判定と自機同士の当たり判定�E削除
					//DebugText::GetInstance()->Print("Hit", 0, 0, 5.0f);
					enemy[colA]->SetHit(true);
					enemy[colB]->SetHit(false);
					break;
				} else {
					enemy[colA]->SetHit(false);
				}
			}
		}
	}

	//Ray ray;
	//ray.start = { player->GetPosition().x,player->GetPosition().y + 3,player->GetPosition().z,1 };
	//ray.dir = { 0,0.025f,-1,0 };
	//RaycastHit raycastHit;

	//if (!collisionManager->Raycast(ray, &raycastHit)) {
	//	if (distanceZ <= 10.0f) {
	//		distanceZ += 0.25f;
	//	}

	//	if (distanceY >= 10.0f) {
	//		distanceY -= 0.25f;
	//	}
	//} else {
	//	if (distanceZ >= 6.0f) {
	//		distanceZ -= 0.4f;
	//	}

	//	if (distanceY <= 18.0f) {
	//		distanceY += 0.25f;
	//	}
	//}

	//���̑��V�[���ڍs
	if (bossenemy->GetHP() <= 0) {
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

void ThirdBoss::Draw(DirectXCommon* dxCommon) {
	ImGui::Begin("test");
	//ImGui::SliderFloat("pos.z", &pos.z, 50, 0);
	//ImGui::SliderFloat("pos.y", &pos.y, 50, 0);
	//ImGui::SliderFloat("enemypos.z", &enemypos.z, 50, 0);
	//ImGui::SliderFloat("pos.y", &distanceY, 30, 0);
	//ImGui::SliderFloat("pos.z", &distanceZ, 30, 0);
	ImGui::SliderFloat("nameframe", &nameframe, 30, 0);
	ImGui::SliderFloat("namepos.x", &namePos.x, 30, 0);
	ImGui::Text("appearanceTimer::%d", appearanceTimer);
	ImGui::Text("appearanceNumber::%d", appearanceNumber);
	ImGui::Unindent();
	ImGui::End();
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
	bossenemy->Draw();

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
	bossName->Draw();
}