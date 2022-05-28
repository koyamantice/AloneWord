#include "ClearScene.h"
#include "Audio.h"
#include "input.h"
#include "DebugText.h"
#include "SceneManager.h"
#include "BossScene.h"
#include "ClearScene.h"
#include"ImageManager.h"
#include <Easing.h>
#include "imgui.h"
void ClearScene::Initialize(DirectXCommon* dxCommon) {
	//背景スプライト生成
	sprite = Sprite::Create(ImageManager::BlackFilter, { 0.0f,0.0f });

	camera = new DebugCamera(WinApp::window_width, WinApp::window_height);
	Texture::SetCamera(camera);
	// 3Dオブジェクトにカメラをセット
	Object3d::SetCamera(camera);
	// デバイスをセット
	FBXObject3d::SetDevice(dxCommon->GetDev());
	// カメラをセット
	FBXObject3d::SetCamera(camera);
	// グラフィックスパイプライン生成
	FBXObject3d::CreateGraphicsPipeline();
	//各オブジェクトの初期化
	//プレイヤー
	player = new Player();
	player->Initialize();
	
	ParticleManager::GetInstance()->SetCamera(camera);

	//カメラポジション
	cameraPos.x = 0;
	cameraPos.y = 0;
	cameraPos.z = -5.0f;
	// カメラ注視点をセット
	cameratargetPos = { 0.0f,0.0f,0.0f };
	camera->SetTarget(cameratargetPos);
	camera->SetEye(cameraPos);

	//スプライト
	comment[endText1] = Sprite::Create(ImageManager::endtext1, { 640.0f,360.0f });
	comment[endText2] = Sprite::Create(ImageManager::endtext2, { 570.0f,450.0f });
	comment[endText3] = Sprite::Create(ImageManager::endtext3, { 570.0f,450.0f });
	comment[endText4] = Sprite::Create(ImageManager::endtext4, { 570.0f,450.0f });
	comment[endText5] = Sprite::Create(ImageManager::endtext5, { 570.0f,450.0f });
	comment[endText6] = Sprite::Create(ImageManager::endtext6, { 570.0f,450.0f });
	comment[endText7] = Sprite::Create(ImageManager::endtext7, { 570.0f,450.0f });
	comment[endText8] = Sprite::Create(ImageManager::endtext8, { 570.0f,450.0f });
	comment[endText9] = Sprite::Create(ImageManager::endtext9, { 570.0f,450.0f });
	comment[endText10] = Sprite::Create(ImageManager::endtext10, { 570.0f,450.0f });

	roll[endrollText1] = Sprite::Create(ImageManager::endroll1, { 0.0f,0.0f });
	roll[endrollText2] = Sprite::Create(ImageManager::endroll2, { 0.0f,0.0f });
	roll[endrollText3] = Sprite::Create(ImageManager::endroll3, { 0.0f,0.0f });
	roll[endrollText4] = Sprite::Create(ImageManager::endroll4, { 0.0f,0.0f });
	roll[endrollText5] = Sprite::Create(ImageManager::endroll5, { 0.0f,0.0f });
	roll[endrollText6] = Sprite::Create(ImageManager::endroll6, { 0.0f,0.0f });
	roll[endrollText7] = Sprite::Create(ImageManager::endroll7, { 0.0f,0.0f });
	roll[endrollText8] = Sprite::Create(ImageManager::endroll8, { 0.0f,0.0f });
	roll[endrollText9] = Sprite::Create(ImageManager::endroll9, { 0.0f,0.0f });

	for (int i = 0; i < endText10 + 1; i++) {
		comment[i]->SetAnchorPoint({ 0.5f, 0.5f });
		comment[i]->SetPosition({ 640.0f,500.0f });
		comment[i]->SetSize({ 0,0 });
	}

	for (int i = 0; i < endrollText9 + 1; i++) {
		//roll[i]->SetAnchorPoint({ 0.5f, 0.5f });
		roll[i]->SetPosition({ 0.0f,0.0f });
		roll[i]->SetColor(endColor);
	}

	//初期化ボス
	//ボス
	fork = new BossEnemy();
	fork->SetPlayer(player);
	fork->Initialize();

	tea = new GreenTea();
	tea->SetPlayer(player);
	tea->Initialize();

	leftshose = new LeftShose();
	leftshose->SetPlayer(player);
	leftshose->Initialize();

	rightshose = new RightShose();
	rightshose->SetPlayer(player);
	rightshose->Initialize();

	pastel = new Pastel();
	pastel->SetPlayer(player);
	pastel->Initialize();

	lefthand = new LeftHand();
	lefthand->SetPlayer(player);
	lefthand->Initialize();

	righthand = new RightHand();
	righthand->SetPlayer(player);
	righthand->Initialize();
}

void ClearScene::Update(DirectXCommon* dxCommon) {
	ClearTimer++;
	player->Clear(ClearTimer);
	if (!endroll) {
		if (ClearTimer >= 200) {
			nowTimer += 10;
			switch (nowText) {
			case endText1:
				if (nowTimer < 61) {
					if (!open && !openT) {
						open = true;
					}
				}
				if (nowTimer > 220) {
					if (!close && !closeT) {
						close = true;
					}
				}
				if (closeT) {
					if (nowTimer > 160) {
						openT = false;
						closeT = false;
						nowTimer = 0;
						nowText = endText2;
					}
				}
				break;
			case endText2:
				if (!open) {
					if (!openT) {
						open = true;
					}
				}
				if (nowTimer > 120) {
					if (!close && !closeT) {
						close = true;
					}
				}
				if (closeT) {
					if (nowTimer > 60) {
						openT = false;
						closeT = false;
						nowTimer = 0;
						nowText = endText3;
					}
				}
				break;
			case endText3:
				if (!open) {
					if (!openT) {
						open = true;
					}
				}
				if (nowTimer > 120) {
					if (!close && !closeT) {
						close = true;
					}
				}
				if (closeT) {
					if (nowTimer > 60) {
						openT = false;
						closeT = false;
						nowTimer = 0;
						nowText = endText4;
					}
				}
				break;
			case endText4:
				if (!open) {
					if (!openT) {
						open = true;
					}
				}
				if (nowTimer > 120) {
					if (!close && !closeT) {
						close = true;
					}
				}
				if (closeT) {
					if (nowTimer > 60) {
						openT = false;
						closeT = false;
						nowTimer = 0;
						nowText = endText5;
					}
				}
				break;
			case endText5:
				if (!open) {
					if (!openT) {
						open = true;
					}
				}
				if (nowTimer > 120) {
					if (!close && !closeT) {
						close = true;
					}
				}
				if (closeT) {
					if (nowTimer > 60) {
						openT = false;
						closeT = false;
						nowTimer = 0;
						nowText = endText6;
					}
				}
				break;
			case endText6:
				if (!open) {
					if (!openT) {
						open = true;
					}
				}
				if (nowTimer > 120) {
					if (!close && !closeT) {
						close = true;
					}
				}
				if (closeT) {
					if (nowTimer > 60) {
						openT = false;
						closeT = false;
						nowTimer = 0;
						nowText = endText7;
					}
				}
				break;
			case endText7:
				if (!open) {
					if (!openT) {
						open = true;
					}
				}
				if (nowTimer > 120) {
					if (!close && !closeT) {
						close = true;
					}
				}
				if (closeT) {
					if (nowTimer > 60) {
						openT = false;
						closeT = false;
						nowTimer = 0;
						nowText = endText8;
					}
				}
				break;
			case endText8:
				if (!open) {
					if (!openT) {
						open = true;
					}
				}
				if (nowTimer > 120) {
					if (!close && !closeT) {
						close = true;
					}
				}
				if (closeT) {
					if (nowTimer > 60) {
						openT = false;
						closeT = false;
						nowTimer = 0;
						nowText = endText9;
					}
				}
				break;
			case endText9:
				if (!open) {
					if (!openT) {
						open = true;
					}
				}
				if (nowTimer > 120) {
					if (!close && !closeT) {
						close = true;
					}
				}
				if (closeT) {
					if (nowTimer > 60) {
						openT = false;
						closeT = false;
						nowTimer = 0;
						nowText = endText10;
					}
				}
				break;
			case endText10:
				if (!open) {
					if (!openT) {
						open = true;
					}
				}
				if (nowTimer > 120) {
					if (!close && !closeT) {
						close = true;
						endroll = true;
					}
				}
				if (closeT) {
					if (nowTimer > 60) {
						openT = false;
						closeT = false;
						nowTimer = 0;
					}
				}
				break;
			}
		}
	}
	//エンドロール突入
	else {
		rollTimer++;
		fork->RollMovie(rollTimer);
		tea->RollMovie(rollTimer);
		leftshose->RollMovie(rollTimer);
		rightshose->RollMovie(rollTimer);
		pastel->RollMovie(rollTimer);
		lefthand->RollMovie(rollTimer);
		righthand->RollMovie(rollTimer);
		if (rollTimer >= 500) {
			endTimer++;
			switch (nowendText) {
			case endrollText1:
				if (endTimer < 61) {
					if (!endopen && !endopenT) {
						endopen = true;
					}
				}
				if (endTimer > 220) {
					if (!endclose && !endcloseT) {
						endclose = true;
					}
				}
				if (endcloseT) {
					if (endTimer > 160) {
						endopenT = false;
						endcloseT = false;
						endTimer = 0;
						nowendText = endrollText2;
					}
				}
				break;
			case endrollText2:
				if (!endopen) {
					if (!endopenT) {
						endopen = true;
					}
				}
				if (endTimer > 160) {
					if (!endclose && !endcloseT) {
						endclose = true;
					}
				}
				if (endcloseT) {
					if (endTimer > 60) {
						endopenT = false;
						endcloseT = false;
						endTimer = 0;
						nowendText = endrollText3;
					}
				}
				break;
			case endrollText3:
				if (!endopen) {
					if (!endopenT) {
						endopen = true;
					}
				}
				if (endTimer > 160) {
					if (!endclose && !endcloseT) {
						endclose = true;
					}
				}
				if (endcloseT) {
					if (endTimer > 60) {
						endopenT = false;
						endcloseT = false;
						endTimer = 0;
						nowendText = endrollText4;
					}
				}
				break;
			case endrollText4:
				if (!endopen) {
					if (!endopenT) {
						endopen = true;
					}
				}
				if (endTimer > 160) {
					if (!endclose && !endcloseT) {
						endclose = true;
					}
				}
				if (endcloseT) {
					if (endTimer > 60) {
						endopenT = false;
						endcloseT = false;
						endTimer = 0;
						nowendText = endrollText5;
					}
				}
				break;
			case endrollText5:
				if (!endopen) {
					if (!endopenT) {
						endopen = true;
					}
				}
				if (endTimer > 160) {
					if (!endclose && !endcloseT) {
						endclose = true;
					}
				}
				if (endcloseT) {
					if (endTimer > 60) {
						endopenT = false;
						endcloseT = false;
						endTimer = 0;
						nowendText = endrollText6;
					}
				}
				break;
			case endrollText6:
				if (!endopen) {
					if (!endopenT) {
						endopen = true;
					}
				}
				if (endTimer > 160) {
					if (!endclose && !endcloseT) {
						endclose = true;
					}
				}
				if (endcloseT) {
					if (endTimer > 60) {
						endopenT = false;
						endcloseT = false;
						endTimer = 0;
						nowendText = endrollText7;
					}
				}
				break;
			case endrollText7:
				if (!endopen) {
					if (!endopenT) {
						endopen = true;
					}
				}
				if (endTimer > 160) {
					if (!endclose && !endcloseT) {
						endclose = true;
					}
				}
				if (endcloseT) {
					if (endTimer > 60) {
						endopenT = false;
						endcloseT = false;
						endTimer = 0;
						nowendText = endrollText8;
					}
				}
				break;
			case endrollText8:
				if (!endopen) {
					if (!endopenT) {
						endopen = true;
					}
				}
				if (endTimer > 160) {
					if (!endclose && !endcloseT) {
						endclose = true;
					}
				}
				if (endcloseT) {
					if (endTimer > 60) {
						endopenT = false;
						endcloseT = false;
						endTimer = 0;
						nowendText = endrollText9;
					}
				}
				break;
			case endrollText9:
				if (!endopen) {
					if (!endopenT) {
						endopen = true;
					}
				}
				if (endTimer > 160) {
					if (!endclose && !endcloseT) {
						//endclose = true;
					}
				}
				if (endcloseT) {
					if (endTimer > 60) {
						/*endopenT = false;
						endcloseT = false;
						endTimer = 0;
						*/
					}
				}
				break;
			}
		}
	}


	if (open) {
		sca = {
		Ease(Out,Quad,frame,816,816),
		Ease(Out,Quad,frame,0,160),
		};
		if (frame < 1.0f) {
			frame += 0.05f;
		}
		else {
			frame = 0.0f;
			open = false;
			openT = true;
		}
		comment[nowText]->SetSize(sca);
	}
	if (close) {
		sca = {
		Ease(Out,Quad,frame,816,816),
		Ease(Out,Quad,frame,160,0),
		};

		if (frame < 1.0f) {
			frame += 0.05f;
		}
		else {
			frame = 0.0f;
			close = false;
			closeT = true;

			nowTimer = 0;
		}
		comment[nowText]->SetSize(sca);
	}

	if (endopen) {
		endColor.w = Ease(In, Quad, frame, endColor.w, 1.0f);
		if (frame < 1.0f) {
			frame += 0.01f;
		}
		else {
			frame = 0.0f;
			endopen = false;
			endopenT = true;
		}
		roll[nowendText]->SetColor(endColor);
	}
	if (endclose) {
		endColor.w = Ease(In, Quad, frame, endColor.w, 0.0f);

		if (frame < 1.0f) {
			frame += 0.01f;
		}
		else {
			frame = 0.0f;
			endclose = false;
			endcloseT = true;
			endTimer = 0;
		}
		roll[nowendText]->SetColor(endColor);
	}

	/*if (input->PushKey(DIK_RETURN) || input->TriggerButton(input->Button_B)) {
		Audio::GetInstance()->PlayWave("Resources/Sound/Button.wav", 0.4f);
		SceneManager::GetInstance()->ChangeScene("TITLE");
	}*/
	//DebugText::GetInstance()->Print("Buttun_B or ENTER to TITLE!!", 200, 100, 1.0f);
}

void ClearScene::Draw(DirectXCommon* dxCommon) {
	ImGui::Begin("test");
	ImGui::Text("rollTimer:%d", rollTimer);
	ImGui::Text("endCount:%d", endTimer);
	ImGui::SliderFloat("color.w", &endColor.w, 1, 0);
	ImGui::End();
	Sprite::PreDraw();
	sprite->Draw();
	comment[nowText]->Draw();
	roll[nowendText]->Draw();
	Texture::PreDraw();
	//player->Draw(dxCommon);
	Object3d::PreDraw();
	fork->Draw();
	tea->Draw();
	leftshose->Draw();
	rightshose->Draw();
	pastel->Draw();
	lefthand->Draw();
	righthand->Draw();
}
void ClearScene::Finalize() {
	//３ｄのモデルのデリート
	delete sprite;
}

