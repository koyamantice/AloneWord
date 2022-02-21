﻿#pragma once

#include "BaseScene.h"
#include "Sprite.h"
#include "Object3d.h"
#include "DebugCamera.h"
#include "LightGroup.h"
#include "FBXObject3d.h"
#include<memory>

/// <summary>
/// ゲームプレイシーン
/// </summary>
class GamePlayScene : public BaseScene{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(DirectXCommon* dxCommon) override;
	/// <summary>
	/// 終了
	/// </summary>
	void Finalize() override;

	/// <summary>
	/// 毎フレーム更新
	/// </summary>
	void Update(DirectXCommon* dxCommon) override;
	/// <summary>
	/// 描画
	/// </summary>
	void Draw(DirectXCommon* dxCommon) override;

private:
	Model* modelPin = nullptr;
	Object3d *objPin;
	Model* modelSkydome = nullptr;
	Object3d* objSkydome;
	Model* modelGround = nullptr;
	Object3d* objGround;
	FBXModel* model1 = nullptr;
	FBXObject3d* object1 = nullptr;
	Sprite* sprite = { nullptr };
	DebugCamera* camera = { nullptr };
	LightGroup* lightGroup = nullptr;
	float ambientColor0[3] = { 1,1,1 };
	// 光線方向初期値
	float lightDir0[3] = { 0,0,1 };
	float lightColor0[3] = { 1,0,0 };

	float lightDir1[3] = { 0,1,0 };
	float lightColor1[3] = { 0,1,0 };

	float lightDir2[3] = { 1,0,0 };
	float lightColor2[3] = { 0,0,1 };

	float pointLightPos[3] = { 0,0,0 };
	float pointLightColor[3] = { 1,1,1 };
	float pointLightAtten[3] = { 0.3f,0.1f,0.1f };
};

