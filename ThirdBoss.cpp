#include "ThirdBoss.h"
#include "Audio.h"
#include "DebugText.h"
#include "TitleScene.h"
#include "FbxLoader.h"
#include"Collision.h"
#include "TouchableObject.h"
#include "MeshCollider.h"
#include "SphereCollider.h"
#include "ImageManager.h"
#include <Easing.h>
//int BaseScene::ClearCount;
//������
void ThirdBoss::Initialize(DirectXCommon* dxCommon) {
	//�C���X�^���X�擾
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
		enemy[i]->SetLimit({ 22.0f,-17.0f, 21.0f,-20.5f });
	}

	//�X�e�[�W��
	objFloor = Object3d::Create();
	modelFloor = Model::CreateFromOBJ("JstyleFloor");
	objFloor->SetModel(modelFloor);
	objFloor->SetPosition({ 0, -1, 0 });
	objFloor->SetScale({ 8.0f,1.0f,8.0f });

	//�X�J�C�h�[��
	objJstyle = Object3d::Create();
	modelJstyle = Model::CreateFromOBJ("Jstyle");
	objJstyle->SetModel(modelJstyle);
	objJstyle->SetPosition({ 0, -1, 0 });
	objJstyle->SetScale({ 1.0f,1.0f,1.0f });

	//objSkydome = Object3d::Create();
	//modelSkydome = Model::CreateFromOBJ("skydome");
	//objSkydome->SetModel(modelSkydome);
	//objSkydome->SetPosition({ 0, -1, 0 });
	//objSkydome->SetScale({ 1.0f,1.0f,1.0f });

	//�X�e�[�W�}�b�v
	modelBossMap = Model::CreateFromOBJ("JstyleMap");
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

	//�e�N�X�`���֌W�̏�����
	bossName = Sprite::Create(ImageManager::select4, namePos);
	bossName->SetAnchorPoint({ 1.0f,0.0f });

	WhiteFilter = Sprite::Create(ImageManager::WhiteFilter, { 0.0f,0.0f });
	//WhiteFilter->SetAnchorPoint({ 1.0f,0.0f });
	WhiteFilter->SetColor(WhiteColor);

	BlackFilter = Sprite::Create(ImageManager::BlackFilter, { 0.0f,0.0f });
	BlackFilter->SetColor(BlackColor);
	GameOverSprite = Sprite::Create(ImageManager::GameOver, overPos);
	GameOverSprite->SetColor(GameOverColor);

	GameClearSprite = Sprite::Create(ImageManager::StageClear, { 640.0f,200.0f });
	GameClearSprite->SetSize(clearSize);
	GameClearSprite->SetAnchorPoint({ 0.5f, 0.5f });

	SkipSprite = Sprite::Create(ImageManager::Change, { 0.0f,0.0f });
	SkipSprite->SetPosition(Skippos);
	SkipSprite->SetAnchorPoint({ 0.5f, 0.5f });
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
	
	//�T�E���h�錾&�v���C
	Audio::GetInstance()->LoadSound(5, "Resources/Sound/inBoss.wav");
	Audio::GetInstance()->LoadSound(3, "Resources/Sound/greenTeaBGM.wav");
	Audio::GetInstance()->LoopWave(5, 0.3f);
	
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
	//�X�v���C�g����
	expandchange = new ExpandChange();

	save = new Save();
	//ui->Initialize();
}
//�J��
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
	delete modelJstyle;
	delete objJstyle;
	for (std::size_t i = 0; i < effect.size(); i++) {
		effect[i]->Finalize();
	}

	delete camera;
	ui->Finalize();
	delete WhiteFilter;
	delete BlackFilter;
	delete bossName;
	delete SkipSprite;
	delete GameOverSprite;
	delete GameClearSprite;
	delete save;
	expandchange->Finalize();
}
//�X�V
void ThirdBoss::Update(DirectXCommon* dxCommon) {
	//objBossMap->Update();
	//�e�I�u�W�F�N�g�̍X�V
	objBossMap->Update();
	objFloor->Update();
	lightGroup->Update();
	objJstyle->Update();
	if (Input::GetInstance()->AllNoPush()) {
		Audio::GetInstance()->StopWave(3);
		player->SetFlash(0);
		end = true;

	}
	//�ŏ��̉��o(����)
	if (!end && !gameover) {
		if (Skip == true) {
			SkipTimer++;
			if (SkipTimer <= 60) {
				SkipSprite->SetScale(1.1f);
			}
			else {
				bossenemy->Initialize();
				bossstart = true;
				SkipSprite->SetScale(0.9f);
				if (SkipTimer == 140) {
					Skip = false;
					SkipTimer = 0;
					SkipSprite->SetScale(1.0f);
				}
			}
		}
		if (!bossstart) {
			if (input->TriggerButton(input->Select)) {
				Audio::GetInstance()->LoopWave(3, 0.3f);
				Audio::GetInstance()->StopWave(5);
				Skip = true;
			}

			if (BlackColor.w >= 0.0f) {
				BlackColor.w -= 0.005f;
				frame = 0.0f;
			}
			else {
				appearanceTimer++;
			}
			player->Begin();
			bossenemy->Begin();
			bossenemy->AppeaMovie(appearanceTimer);
			//�J�����̈ʒu�����ꂼ�ꍇ�킹��
			if (appearanceNumber == 0) {
				cameraPos.x = player->GetPosition().x;
				cameraPos.y = player->GetPosition().y + 6;
				cameraPos.z = player->GetPosition().z - 8;
				cameratargetPos = { 0.0f,2.0f,0.0 };

				if (appearanceTimer == 300) {
					appearanceNumber++;
				}
			}
			else if (appearanceNumber == 1) {
				Aftereyepos = {
				bossenemy->GetPosition().x,
				bossenemy->GetPosition().y + 1,
				bossenemy->GetPosition().z - 5,
				};

				Aftertargetpos = {
					bossenemy->GetPosition().x,
					bossenemy->GetPosition().y + 1,
					bossenemy->GetPosition().z,
				};


				if (frame < 1.0f) {
					frame += 0.01f;
				}
				else {
					frame = 1.0f;
				}

				if (appearanceTimer == 400) {
					appearanceNumber++;
					frame = 0.0f;
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
				if (appearanceTimer == 550) {
					nameframe = 0.0f;
					appearanceNumber++;
				}
			}

			else if (appearanceNumber == 3) {
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
					Audio::GetInstance()->LoopWave(3, 0.3f);
					appearanceTimer = 0;
					appearanceNumber = 0;
					frame = 0;
					nameframe = 0.0f;
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
			/*else if (appearanceNumber == 2) {

			}*/

			camera->SetTarget(cameratargetPos);
			camera->SetEye(cameraPos);
		}
		//�퓬�J�n
		else {
			Audio::GetInstance()->StopWave(5);
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
			ParticleManager::GetInstance()->Update();
			objSphere->Update();
			cameraPos.x = player->GetPosition().x;
			cameraPos.y = player->GetPosition().y + distanceY;
			cameraPos.z = player->GetPosition().z - distanceZ;
			camera->SetTarget(player->GetPosition());
			camera->SetEye(cameraPos);
		}
		//���̑��V�[���ڍs
		if (bossenemy->GetHP() <= 0) {
			Audio::GetInstance()->StopWave(3);
			player->SetFlash(0);
			end = true;
			//SceneManager::GetInstance()->ChangeScene("StageSelect");
		}

		if (player->GetHp() <= 0) {
			Audio::GetInstance()->StopWave(3);
			gameover = true;
		}
	}//�{�X���j���[�r�[���o
	else {
	if (end) {
		//expandchange->SetStartChange(true);
		EndTimer++;
		bossenemy->EndMovie(EndTimer);
		player->End(EndTimer);
		//�J�����̈ʒu�����ꂼ���ς���
		if (EndNumber == 0) {
			if (EndTimer == 1) {
				cameraPos.x = player->GetPosition().x;
				cameraPos.y = player->GetPosition().y + distanceY;
				cameraPos.z = player->GetPosition().z - distanceZ;
				cameratargetPos = player->GetPosition();
			}
			if (WhiteColor.w <= 1.0f) {
				WhiteColor.w += 0.008f;
			}
			if (EndTimer == 250) {
				frame = 0.0f;
				EndNumber++;
				cameraPos.x = bossenemy->GetPosition().x;
				cameraPos.y = bossenemy->GetPosition().y + 7;
				cameraPos.z = bossenemy->GetPosition().z - 10;
				cameratargetPos = bossenemy->GetPosition();

			}
		}
		else if (EndNumber == 1) {
			if (WhiteColor.w >= 0.0f) {
				WhiteColor.w -= 0.008f;
			}

			if (EndTimer == 650) {
				frame = 0.0f;
				EndNumber++;
			}
		}

		else if (EndNumber == 2) {
			Aftereyepos = {
			player->GetPosition().x,
			player->GetPosition().y + 2,
			player->GetPosition().z - 5,
			};

			Aftertargetpos = {
				0,
				2,
				0
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

			if (EndTimer == 750) {
				Audio::GetInstance()->PlayWave("Resources/Sound/gameClear.wav", 0.4f);
				frame = 0.0f;
				EndNumber++;
			}
		}
		else if (EndNumber == 3) {
			clearSize = {
		Ease(In,Quad,clearframe,clearSize.x,600.0f),
		Ease(In,Quad,clearframe,clearSize.y,400.0f)
			};

			if (clearframe >= 1.0f) {
				clearframe = 1.0f;
			}
			else {
				clearframe += 0.01f;
			}

			GameClearSprite->SetSize(clearSize);

			if (EndTimer == 900) {
				expandchange->SetStartChange(true);
			}
		}

		WhiteFilter->SetColor(WhiteColor);
		if (expandchange->GetTimer() >= 58) {
			if (!save->GetSecondClear()) {
				save->ClearSave();
				save->SecondSave();
			}
			//Audio::GetInstance()->LoopWave(4, 0.2f);
			SceneManager::GetInstance()->ChangeScene("StageSelect");
		}
		camera->SetTarget(cameratargetPos);
		camera->SetEye(cameraPos);
		}

		if (gameover == true) {
			Audio::GetInstance()->StopWave(3);
			overTimer++;
			//player->Begin();
			bossenemy->Begin();
			player->gameover(overTimer);
			if (overNumber == 0) {
				if (BlackColor.w <= 1.0f) {
					BlackColor.w += 0.01f;
				}

				if (overTimer == 1) {
					Aftereyepos = {
					player->GetPosition().x,
					player->GetPosition().y + 5,
					player->GetPosition().z - 7,
					};
					Aftertargetpos = {
					player->GetPosition().x,
					player->GetPosition().y,
					player->GetPosition().z + 6,
					};
					cameraPos.x = player->GetPosition().x;
					cameraPos.y = player->GetPosition().y + distanceY;
					cameraPos.z = player->GetPosition().z - distanceZ;
					cameratargetPos = player->GetPosition();
				}

				if (overTimer >= 50) {

					if (frame < 1.0f) {
						frame += 0.015f;
					}
					else {
						frame = 1.0f;
					}

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
				if (overTimer == 150) {
					Audio::GetInstance()->PlayWave("Resources/Sound/gameOver.wav", 0.4f);
				}
				if (overTimer == 420) {
					overNumber++;
				}
			}
			else if (overNumber == 1) {
				if (GameOverColor.w <= 1.0f) {
					GameOverColor.w += 0.01f;
				}


				if (overframe >= 1.0f) {
					overframe = 1.0f;
				}
				else {
					overframe += 0.01f;
				}

				overPos = {
			240,
			Ease(In,Quad,overframe,overPos.y,100.0f)
				};

				GameOverSprite->SetPosition(overPos);
			}

			if (overTimer == 650) {
				expandchange->SetStartChange(true);
			}

			if (expandchange->GetTimer() >= 58) {
				//Audio::GetInstance()->LoadSound(4, "Resources/Sound/selectBGM.wav");	
				SceneManager::GetInstance()->ChangeScene("StageSelect");
			}

			camera->SetTarget(cameratargetPos);
			camera->SetEye(cameraPos);
		}
	}

	BlackFilter->SetColor(BlackColor);
	GameOverSprite->SetColor(GameOverColor);
	camera->Update();
	expandchange->Update();

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
		for (int colA = 0; colA < enemy.size(); colA++) {
			for (int colB = 1; colB < enemy.size(); colB++) {
				if (!enemy[colA]->GetEnemyCatcth() && !enemy[colB]->GetEnemyCatcth()) {
					if (Collision::CircleCollision(enemy[colA]->GetPosition().x, enemy[colA]->GetPosition().z, 1.0f, enemy[colB]->GetPosition().x, enemy[colB]->GetPosition().z, 1.0f) && colA != colB) {//�����蔻��Ǝ��@���m�̓����蔻��̍폜
						if (!enemy[colA]->GetHit()) {
							enemy[colA]->SetHit(true);
							enemy[colA]->SetExP(enemy[colB]->GetPosition());
						}
						if (!enemy[colB]->GetHit()) {
							enemy[colB]->SetHit(true);
							enemy[colB]->SetExP(enemy[colA]->GetPosition());
						}
						break;
					}
				}
			}
		}
	}

	////���̑��V�[���ڍs
	//if (bossenemy->GetHP() <= 0) {
	//	SceneManager::GetInstance()->ChangeScene("StageSelect");
	//}

	//if (player->GetHp() <= 0) {
	//	SceneManager::GetInstance()->ChangeScene("GAMEOVER");
	//}
	
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
void ThirdBoss::Draw(DirectXCommon* dxCommon) {
	//ImGui::Begin("test");
	////ImGui::SliderFloat("pos.z", &pos.z, 50, 0);
	////ImGui::SliderFloat("pos.y", &pos.y, 50, 0);
	////ImGui::SliderFloat("enemypos.z", &enemypos.z, 50, 0);
	////ImGui::SliderFloat("pos.y", &distanceY, 30, 0);
	////ImGui::SliderFloat("pos.z", &distanceZ, 30, 0);
	//ImGui::SliderFloat("frame", &frame, 30, 0);
	//ImGui::Text("appearanceTimer::%d", appearanceTimer);
	//ImGui::Text("appearanceNumber::%d", appearanceNumber);
	//ImGui::Unindent();
	//ImGui::End();
	//�e�I�u�W�F�N�g�̕`��
	Object3d::PreDraw();
	if (!gameover) {
		objBossMap->Draw();
	}
	objFloor->Draw();
	objJstyle->Draw();

	if (!gameover) {
		bossenemy->Draw();
	}

	for (std::size_t i = 0; i < effect.size(); i++) {
		effect[i]->Draw();
	}

	if (!gameover) {
		Texture::PreDraw();
		player->Draw(dxCommon);
		Sprite::PreDraw();

		if (!bossstart) {
			BlackFilter->Draw();
			bossName->Draw();
		}

		if (SkipTimer != 0) {
			SkipSprite->Draw();
		}


	}
	else {
		Sprite::PreDraw();

		BlackFilter->Draw();
		GameOverSprite->Draw();
		Texture::PreDraw();
		if (EndNumber <= 1) {
			player->Draw(dxCommon);
		}
	}

	//for (std::size_t i = 0; i < exp.size(); i++) {
	//	for (std::size_t j = 0; j < exp[i].size(); j++) {
	//		exp[i][j]->Draw();
	//	}
	//}
	if (end) {
		WhiteFilter->Draw();
		GameClearSprite->Draw();
	}
	if (!end) {
		if (!gameover) {
			for (std::size_t i = 0; i < enemy.size(); i++) {
				enemy[i]->Draw();
			}
			if (bossstart) {
				ui->Draw();
				// �p�[�e�B�N���̕`��
				particleMan->Draw(dxCommon->GetCmdList());
			}
			else {
				ui->SkipDraw();
			}
		}
	}
	Sprite::PreDraw();

	//�O�ʗp
	expandchange->Draw();

}