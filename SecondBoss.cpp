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
#include "ImageManager.h"
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
	//�e�N�X�`���֌W�̏�����
	WhiteFilter = Sprite::Create(ImageManager::WhiteFilter, { 0.0f,0.0f });
	//WhiteFilter->SetAnchorPoint({ 1.0f,0.0f });
	WhiteFilter->SetColor(WhiteColor);

	BlackFilter = Sprite::Create(ImageManager::BlackFilter, { 0.0f,0.0f });
	BlackFilter->SetColor(BlackColor);
	
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
	leftshose->Initialize(false);

	rightshose = new RightShose();
	rightshose->SetPlayer(player);
	rightshose->Initialize(false);

	//�G
	for (std::size_t i = 0; i < enemy.size(); i++) {
		enemy[i] = new Rice();
		enemy[i]->SetPlayer(player);
		enemy[i]->Initialize();
		enemy[i]->SetLimit({ 21.0f,-17.0f,19.0f,-19.0f });
	}

	cameraPos.x = player->GetPosition().x;
	cameraPos.y = player->GetPosition().y + distanceY;
	cameraPos.z = player->GetPosition().z - distanceZ;
	camera->SetTarget(player->GetPosition());
	camera->SetEye(cameraPos);
	ui = new UI(player, leftshose, rightshose);
	expandchange = new ExpandChange();
	//ui->Initialize();
}
//�J������
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
	/*for (std::size_t i = 0; i < exp.size(); i++) {
		for (std::size_t j = 0; j < exp[i].size(); j++) {
			exp[i][j]->Finalize();
		}
	}*/
	delete camera;
	delete object1;
	delete model1;
	ui->Finalize();
}

void SecondBoss::Update(DirectXCommon* dxCommon) {
	//objBossMap->Update();
	//�e�I�u�W�F�N�g�̍X�V
	objBossMap->Update();
	objFloor->Update();
	lightGroup->Update();

	//�ŏ��̉��o(����)
	if (!end) {
		if (!bossstart) {
			if (BlackColor.w >= 0.0f && appearanceNumber == 0) {
				BlackColor.w -= 0.005f;
				frame = 0.0f;
			}
			else {
				appearanceTimer++;
			}
			player->Begin();
			leftshose->Begin();
			rightshose->Begin();
			rightshose->AppeaMovie(appearanceTimer);
			leftshose->AppeaMovie(appearanceTimer);
			//�J�����̈ʒu�����ꂼ��ύX���Ă���
			if (appearanceNumber == 0) {
				cameraPos.x = rightshose->GetPosition().x + 5;
				cameraPos.y = rightshose->GetPosition().y + 2;
				cameraPos.z = rightshose->GetPosition().z - 3;
				cameratargetPos = rightshose->GetPosition();

				if (appearanceTimer == 50) {
					appearanceNumber++;
				}
			}

			else if (appearanceNumber == 1) {
				cameraPos.x = leftshose->GetPosition().x - 5;
				cameraPos.y = leftshose->GetPosition().y + 2;
				cameraPos.z = leftshose->GetPosition().z - 3;
				cameratargetPos = rightshose->GetPosition();

				if (appearanceTimer == 100) {
					appearanceNumber++;
				}
			}

			else if (appearanceNumber == 2) {
				cameraPos.x = player->GetPosition().x;
				cameraPos.y = player->GetPosition().y + 3;
				cameraPos.z = player->GetPosition().z - 8;
				cameratargetPos = { 0.0f,2.0f,0.0 };

				if (appearanceTimer == 230) {
					BlackColor.w = 1.0f;
					appearanceNumber++;
					//�X�̉��ύX�Č�
					Audio::GetInstance()->PlayWave("Resources/Sound/Damage.wav", 0.4f);
				}
			}

			else if (appearanceNumber == 3) {
				if (appearanceTimer == 300) {
					BlackColor.w = 0.0f;
					appearanceNumber++;
				}
			}

			else if (appearanceNumber == 4) {
				if (appearanceTimer == 500) {
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
			if (rightshose->GetHP() > 0) {
				rightshose->SetAct(leftshose);
				rightshose->HitShose(leftshose);
			}
			rightshose->Update();
		/*	
			if (rightshose->GetHP() <= 0) {
				DeadRight++;
				leftshose->SetPosition({ 0.0f,-20.8f,0.0f });
			}

			if (leftshose->GetHP() <= 0) {
				DeadLeft++;
				rightshose->SetPosition({ 0.0f,-20.8f,0.0f });
			}*/
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

		//���̑��V�[���ڍs
		if (leftshose->GetHP() <= 0 && rightshose->GetHP() <= 0) {
			end = true;
		}

		if (player->GetHp() <= 0) {
			SceneManager::GetInstance()->ChangeScene("GAMEOVER");
		}
	}//�{�X���j���[�r�[���o
	else {
		EndTimer++;
		rightshose->EndMovie(EndTimer);
		leftshose->EndMovie(EndTimer);
		player->End();
		if (EndNumber == 0) {
		/*	if (DeadLeft > DeadRight) {
			
			}
			else {
				
			}*/
			/*if (EndTimer == 1) {
				cameraPos.x = 0;
				cameraPos.y = 7;
				cameraPos.z = -10;
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
			cameraPos.x = 0;
			cameraPos.y = 7;
			cameraPos.z = -10;
		}
		WhiteFilter->SetColor(WhiteColor);
		camera->SetTarget({0.0f,0.0f,0.0f});
		camera->SetEye(cameraPos);

		if (EndTimer == 700) {
			expandchange->SetStartChange(true);
		}

		if (expandchange->GetTimer() >= 58) {
			SceneManager::GetInstance()->ChangeScene("StageSelect");
		}
	}
	BlackFilter->SetColor(BlackColor);
	camera->Update();
	expandchange->Update();

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
void SecondBoss::Draw(DirectXCommon* dxCommon) {
	ImGui::Begin("test");
	//ImGui::SliderFloat("pos.z", &pos.z, 50, 0);
	//ImGui::SliderFloat("pos.y", &pos.y, 50, 0);
	//ImGui::SliderFloat("enemypos.z", &enemypos.z, 50, 0);
	//ImGui::SliderFloat("pos.y", &distanceY, 30, 0);
	//ImGui::SliderFloat("pos.z", &distanceZ, 30, 0);
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
	if (EndNumber <= 1) {
		player->Draw(dxCommon);
	}

	if (rightshose->GetHP() > 0 || end) {
		rightshose->Draw();
	}

	if (leftshose->GetHP() > 0 || end) {
		leftshose->Draw();
	}


	for (std::size_t i = 0; i < effect.size(); i++) {
		effect[i]->Draw();
	}

	//for (std::size_t i = 0; i < exp.size(); i++) {
	//	for (std::size_t j = 0; j < exp[i].size(); j++) {
	//		exp[i][j]->Draw();
	//	}
	//}
	if (bossstart && !end) {
		ui->Draw();
		// �p�[�e�B�N���̕`��
		particleMan->Draw(dxCommon->GetCmdList());
	}
	
	
	Sprite::PreDraw();
	if (!bossstart) {
		BlackFilter->Draw();
		//bossName->Draw();
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