#include "FourthBoss.h"
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
void FourthBoss::Initialize(DirectXCommon* dxCommon) {
	//�C���X�^���X�擾
	collisionManager = CollisionManager::GetInstance();
	// �J��������
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height);
	Texture::SetCamera(camera);
	// 3D�I�u�W�F�N�g�ɃJ�������Z�b�g
	Object3d::SetCamera(camera);
	//�e�I�u�W�F�N�g�̏�����

	//�X�e�[�W��
	objFloor = Object3d::Create();
	modelFloor = Model::CreateFromOBJ("floor");
	objFloor->SetModel(modelFloor);
	objFloor->SetPosition({ 0, -1, 0 });
	objFloor->SetScale({ 8.0f,1.0f,6.0f });

	//�X�e�[�W�}�b�v
	modelBossMap = Model::CreateFromOBJ("BossMap");
	objBossMap = TouchableObject::Create(modelBossMap);
	objBossMap->SetPosition({ 0,-1,2 });
	objBossMap->SetRotation({ 0, 90, 0 });
	objBossMap->SetScale({ 3.0f, 1.5f, 3.0f });
	/*
	objBossMap->SetModel(modelBossMap);
	objBossMap->SetPosition({ 0,-1,2 });
	objBossMap->SetRotation({ 0, 90, 0 });
	objBossMap->SetScale({ 1.4f,1.5f,1.6f });
	*/
	
	// �R���C�_�[�̒ǉ�
	//objSphere->SetCollider(new SphereCollider);

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
	
	// �f�o�C�X���Z�b�g
	FBXObject3d::SetDevice(dxCommon->GetDev());
	// �J�������Z�b�g
	FBXObject3d::SetCamera(camera);
	// �O���t�B�b�N�X�p�C�v���C������
	FBXObject3d::CreateGraphicsPipeline();
	// �p�[�e�B�N���}�l�[�W������
	particleMan = ParticleManager::GetInstance();
	particleMan->SetCamera(camera);

	shockwave = new ShockWave;
	shockwave->Init();
	//�v���C���[
	player = new Player();
	player->Initialize();
	player->SetPosition({ 0.0f,0.0f,-10.0f });
	player->SetMove(250.0f, 200.0f);

	//�{�X(�n)
	pastel = new Pastel();
	pastel->SetPlayer(player);
	pastel->Initialize();
	//�{�X(�P)
	/*mill = new Mill();
	mill->SetPlayer(player);
	mill->Initialize();*/
	//�e�N�X�`���֌W�̏�����
	//�{�X�̖��O�\�L
	bossName = Sprite::Create(ImageManager::select1, namePos);
	bossName->SetAnchorPoint({ 1.0f,0.0f });

	WhiteFilter = Sprite::Create(ImageManager::WhiteFilter, { 0.0f,0.0f });
	//WhiteFilter->SetAnchorPoint({ 1.0f,0.0f });
	WhiteFilter->SetColor(WhiteColor);
	BlackFilter = Sprite::Create(ImageManager::BlackFilter, { 0.0f,0.0f });
	BlackFilter->SetColor(BlackColor);
	//�G
	for (std::size_t i = 0; i < enemy.size(); i++) {
		enemy[i] = new Rice();
		enemy[i]->SetPlayer(player);
		enemy[i]->Initialize();
		enemy[i]->SetLimit({ 21.0f,-17.0f,19.0f,-19.0f });
	}

	//�����蔻��m�F�p�ł�
	modelSphere = Model::CreateFromOBJ("sphere");
	objSphere = TouchableObject::Create(modelSphere);
	objSphere->SetScale({ 2.0f, 2.0f, 2.0f });
	objSphere->SetPosition({0.0f,0.0f,1.0f});

	//�J�����|�W�V����
	cameraPos.x = player->GetPosition().x;
	cameraPos.y = player->GetPosition().y + distanceY;
	cameraPos.z = player->GetPosition().z - distanceZ;
	// �J���������_���Z�b�g
	cameratargetPos = player->GetPosition();
	camera->SetTarget(cameratargetPos);
	camera->SetEye(cameraPos);

	ui = new UI(player, pastel);
	//�X�v���C�g����
	expandchange = new ExpandChange();
	//ui->Initialize();
}

void FourthBoss::Finalize() {

	//3d�̃��f���̃f���[�g
	for (std::size_t i = 0; i < enemy.size(); i++) {
		enemy[i]->Finalize();
	}
	player->Finalize();
	pastel->Finalize();
	//mill->Finalize();
	shockwave->Final();
	delete objSphere;
	delete modelSphere;
	delete objBossMap;
	delete objFloor;
	delete modelBossMap;
	delete modelFloor;
	for (std::size_t i = 0; i < effect.size(); i++) {
		effect[i]->Finalize();
	}
	/*for (std::size_t i = 0; i < exp.size(); i++) {
		for (std::size_t j = 0; j < exp[i].size(); j++) {
			exp[i][j]->Finalize();
		}
	}*/
	delete camera;
	ui->Finalize();
}

void FourthBoss::Update(DirectXCommon* dxCommon) {
	//objBossMap->Update();
	//�e�I�u�W�F�N�g�̍X�V
	objBossMap->Update();
	objFloor->Update();
	lightGroup->Update();
	
	//�ŏ��̉��o(����)
	if (!end) {
		if (!bossstart) {
			if (BlackColor.w >= 0.0f) {
				BlackColor.w -= 0.005f;
				frame = 0.0f;
			}
			else {
				appearanceTimer++;
			}
			player->Begin();
			pastel->Begin();
			pastel->MillUpdate();
			pastel->AppeaMovie(appearanceTimer);
			//�J�����̈ʒu�����ꂼ�ꍇ�킹��
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
				cameraPos.x = pastel->GetPosition().x + 5;
				cameraPos.y = pastel->GetPosition().y;
				cameraPos.z = pastel->GetPosition().z;
				cameratargetPos = pastel->GetPosition();

				if (appearanceTimer == 200) {
					appearanceNumber++;
				}

			}

			else if (appearanceNumber == 2) {
				cameraPos.x = pastel->GetPosition().x;
				cameraPos.y = pastel->GetPosition().y + 5;
				cameraPos.z = pastel->GetPosition().z - distanceZ;
				cameratargetPos = { 0.0f,5.0f,8.0f };

				if (appearanceTimer == 300) {
					appearanceNumber++;
				}
			}

			else if (appearanceNumber == 3) {
				Aftereyepos = {
					pastel->GetPosition().x,
					pastel->GetPosition().y,
					pastel->GetPosition().z - 7,
				};

				Aftertargetpos = {
					pastel->GetPosition().x,
					pastel->GetPosition().y,
					pastel->GetPosition().z,
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
			pastel->Update();
			pastel->collideAttackArm(player);
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
			//objSphere->Update();
			shockwave->Upda(pastel, player);
			cameraPos.x = player->GetPosition().x;
			cameraPos.y = player->GetPosition().y + distanceY;
			cameraPos.z = player->GetPosition().z - distanceZ;
			camera->SetTarget(player->GetPosition());
			camera->SetEye(cameraPos);
		}
		//���̑��V�[���ڍs
		if (pastel->GetHP() <= 0) {
			end = true;
			//SceneManager::GetInstance()->ChangeScene("StageSelect");
		}

		if (player->GetHp() <= 0) {
			SceneManager::GetInstance()->ChangeScene("GAMEOVER");
		}
	}//�{�X���j���[�r�[���o
	else {
		EndTimer++;
		pastel->EndMovie(EndTimer);
		player->End();
		if (EndNumber == 0) {
			/*if (EndTimer == 1) {
				cameraPos.x = bossenemy->GetPosition().x;
				cameraPos.y = bossenemy->GetPosition().y + 4;
				cameraPos.z = bossenemy->GetPosition().z + 4;
			}*/

			if (EndTimer == 50) {
				EndNumber = 1;
			}
		}
		else if (EndNumber == 1) {
			if (WhiteColor.w <= 1.0f) {
				WhiteColor.w += 0.005f;
			}

			if (EndTimer == 300) {
				EndNumber++;
			}
		}
		else if (EndNumber == 2) {
			if (WhiteColor.w >= 0.0f) {
				WhiteColor.w -= 0.005f;
			}
			cameraPos.x = pastel->GetPosition().x;
			cameraPos.y = pastel->GetPosition().y + 7;
			cameraPos.z = pastel->GetPosition().z - 10;
		}
		WhiteFilter->SetColor(WhiteColor);
		camera->SetTarget(pastel->GetPosition());
		camera->SetEye(cameraPos);

		if (EndTimer == 700) {
			expandchange->SetStartChange(true);
		}

		if (expandchange->GetTimer() >= 58) {
			SceneManager::GetInstance()->ChangeScene("StageSelect");
		}
	}

	camera->Update();
	BlackFilter->SetColor(BlackColor);
	expandchange->Update();
	/*
	for (std::size_t i = 0; i < exp.size(); i++) {
		for (std::size_t j = 0; j < exp[i].size(); j++) {
			exp[i][j]->Update(player, enemy[j]);
		}
	}*/

	for (std::size_t i = 0; i < effect.size(); i++) {
		effect[i]->Update(pastel);
	}

	if (input->TriggerKey(DIK_C || input->TriggerButton(input->Button_X))) {
		Audio::GetInstance()->StopWave(0);
		Audio::GetInstance()->StopWave(1);
		Audio::GetInstance()->LoopWave(1, 0.7f);
	}
	if (input->TriggerKey(DIK_SPACE)) {
		bossstart = true;
	}

	//�G���m�̓����蔻��
	if (sizeof(enemy) > 2) {//�z��̃T�C�Y�m�F
		for (int colA = 0; colA < enemy.size(); colA++) {
			for (int colB = 1; colB < enemy.size(); colB++) {
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
	ray.dir = { 0.0f,0.025f,-1.0f };
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
	/*if (pastel->GetHP() <= 0) {
		SceneManager::GetInstance()->ChangeScene("StageSelect");
	}*/

	//if (player->GetHp() <= 0) {
	//	SceneManager::GetInstance()->ChangeScene("GAMEOVER");
	//}
	//object1->Update();

	// �S�Ă̏Փ˂��`�F�b�N
	//collsionManager->CheckAllCollisions();
	/*DebugText::GetInstance()->Print("PUSH to RB!!",200, 100,1.0f);
	DebugText::GetInstance()->Print("PUSH to A!!", 200, 115, 1.0f);*/
	//DebugText::GetInstance()->Print("RB or LB :Rotate", 900, 620, 2.0f);
	//DebugText::GetInstance()->Print("A         :Hand", 900, 650, 2.0f);
	//DebugText::GetInstance()->Print("PUSH to RB!!", 1040, 620, 2.0f);
	//DebugText::GetInstance()->Print("PUSH to A!!", 1040, 660, 2.0f);
}

//�`��
void FourthBoss::Draw(DirectXCommon* dxCommon) {
	//ImGui::Begin("test");
	////ImGui::SliderFloat("pos.z", &pos.z, 50, 0);
	////ImGui::SliderFloat("pos.y", &pos.y, 50, 0);
	////ImGui::SliderFloat("enemypos.z", &enemypos.z, 50, 0);
	////ImGui::SliderFloat("pos.y", &distanceY, 30, 0);
	////ImGui::SliderFloat("pos.z", &distanceZ, 30, 0);
	//ImGui::SliderFloat("nameframe", &nameframe, 30, 0);
	//ImGui::SliderFloat("namepos.x", &namePos.x, 30, 0);
	//ImGui::Text("appearanceTimer::%d", appearanceTimer);
	//ImGui::Text("appearanceNumber::%d", appearanceNumber);
	//ImGui::Unindent();
	//ImGui::End();
	//�e�I�u�W�F�N�g�̕`��
	Object3d::PreDraw();
	//objBossMap->Draw();
	objSphere->Draw();
	objBossMap->Draw();
	objFloor->Draw();

	Texture::PreDraw();
	shockwave->Draw();
	//limit->Draw();
	//Sprite::PreDraw();
	//sprite->Draw();

	//object1->Draw(dxCommon->GetCmdList());

	player->Draw(dxCommon);
	pastel->Draw();
	
	for (std::size_t i = 0; i < effect.size(); i++) {
		effect[i]->Draw();
	}

	XMFLOAT3 pos = player->GetPosition();
	XMFLOAT3 enemypos = pastel->GetPosition();
	
	if (bossstart && !end) {
		ui->Draw();
	}
	// �p�[�e�B�N���̕`��
	particleMan->Draw(dxCommon->GetCmdList());
	Sprite::PreDraw();
	if (!bossstart) {
		BlackFilter->Draw();
		bossName->Draw();
	}

	if (end) {
		WhiteFilter->Draw();
	}
	else {
		for (std::size_t i = 0; i < enemy.size(); i++) {
			enemy[i]->Draw();
		}
	}

	Sprite::PreDraw();

	//�O�ʗp
	expandchange->Draw();

}