#pragma once
#include "BaseScene.h"
#include "BossEnemy.h"
#include "Collision.h"
/// <summary>
/// ゲームプレイシーン
/// </summary>
const int StartEnemyMax = 7;
class StartMap : public BaseScene {

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
	Model* modelground = nullptr;
	Object3d* objground;

	Model* modeltree = nullptr;
	Object3d* objtree;

	FBXModel* model1 = nullptr;
	FBXObject3d* object1 = nullptr;
	DebugCamera* camera = { nullptr };
	//Texture* limit = nullptr;
	Player* player = nullptr;
	Enemy* enemy[StartEnemyMax] = { nullptr };
	//BossEnemy* bossenemy = nullptr;

};

