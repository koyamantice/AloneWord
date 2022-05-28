#include "ClearScene.h"
#include "Audio.h"
#include "input.h"
#include "DebugText.h"
#include "SceneManager.h"
#include "BossScene.h"
#include "ClearScene.h"
#include"ImageManager.h"
#include <Easing.h>
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
	cameraPos.z = -10.0f;
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

	for (int i = 0; i < endText10 + 1; i++) {
		comment[i]->SetAnchorPoint({ 0.5f, 0.5f });
		comment[i]->SetPosition({ 640.0f,500.0f });
		comment[i]->SetSize({ 0,0 });
	}
}

void ClearScene::Update(DirectXCommon* dxCommon) {
	ClearTimer++;
	nowTimer++;
	player->Clear(ClearTimer);
	switch (nowText) {
	case endText1:
		if (nowTimer < 61) {
			if (!open && !openT) {
				open = true;
			}
		}
		if (nowTimer > 180) {
			if (!close && !closeT) {
				close = true;
			}
		}
		if (closeT) {
			if (nowTimer > 120) {
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
		if (nowTimer > 180) {
			if (!close && !closeT) {
				close = true;
			}
		}
		if (closeT) {
			if (nowTimer > 120) {
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
		if (nowTimer > 180) {
			if (!close && !closeT) {
				close = true;
			}
		}
		if (closeT) {
			if (nowTimer > 120) {
				openT = false;
				closeT = false;
				nowTimer = 0;
				nowText = endText4;
			}
		}
		break;
	case endText4:
		if (nowTimer < 61) {
			if (!open && !openT) {
				open = true;
			}
		}
		if (nowTimer > 180) {
			if (!close && !closeT) {
				close = true;
			}
		}
		if (closeT) {
			if (nowTimer > 120) {
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
		if (nowTimer > 180) {
			if (!close && !closeT) {
				close = true;
			}
		}
		if (closeT) {
			if (nowTimer > 120) {
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
		if (nowTimer > 180) {
			if (!close && !closeT) {
				close = true;
			}
		}
		if (closeT) {
			if (nowTimer > 120) {
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
		if (nowTimer > 180) {
			if (!close && !closeT) {
				close = true;
			}
		}
		if (closeT) {
			if (nowTimer > 120) {
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
		if (nowTimer > 180) {
			if (!close && !closeT) {
				close = true;
			}
		}
		if (closeT) {
			if (nowTimer > 120) {
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
		if (nowTimer > 180) {
			if (!close && !closeT) {
				close = true;
			}
		}
		if (closeT) {
			if (nowTimer > 120) {
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
		if (nowTimer > 180) {
			if (!close && !closeT) {
				close = true;
			}
		}
		if (closeT) {
			if (nowTimer > 120) {
				openT = false;
				closeT = false;
				nowTimer = 0;
			}
		}
		break;
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
			//if (checkZ) {
			//}
			nowTimer = 0;
		}
		comment[nowText]->SetSize(sca);
	}

	/*if (input->PushKey(DIK_RETURN) || input->TriggerButton(input->Button_B)) {
		Audio::GetInstance()->PlayWave("Resources/Sound/Button.wav", 0.4f);
		SceneManager::GetInstance()->ChangeScene("TITLE");
	}*/
	//DebugText::GetInstance()->Print("Buttun_B or ENTER to TITLE!!", 200, 100, 1.0f);
}

void ClearScene::Draw(DirectXCommon* dxCommon) {
	Sprite::PreDraw();
	sprite->Draw();
	comment[nowText]->Draw();
	Texture::PreDraw();
	player->Draw(dxCommon);
}
void ClearScene::Finalize() {
	//３ｄのモデルのデリート
	delete sprite;
}

