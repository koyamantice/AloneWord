﻿#pragma once
#include "BaseScene.h"
#include "BossEnemy.h"
#include "Collision.h"
/// <summary>
/// ゲームプレイシーン
/// </summary>
const int BossEnemyMax = 1;
class BossScene : public BaseScene{
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
	Model* modelGround = nullptr;
	Object3d* objGround;
	FBXModel* model1 = nullptr;
	FBXObject3d* object1 = nullptr;
	DebugCamera* camera = { nullptr };
	Texture* limit = nullptr;
	Player* player = nullptr;
	Enemy* enemy[BossEnemyMax] = { nullptr };
	BossEnemy* bossenemy = nullptr;
};

