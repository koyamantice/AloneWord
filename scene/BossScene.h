#pragma once
#include "BaseScene.h"
#include "BossEnemy.h"
#include "UI.h"

/// <summary>
/// ゲームプレイシーン
/// </summary>
const int BossEnemyMax = 10;
const int EffectMax = 70;
const int ExpMax = 5;
class CollisionManager;
class TouchableObject;
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

	Model* modelground = nullptr;
	TouchableObject* objground;
	Model* modelSphere = nullptr;
	Object3d* objSphere;

	FBXModel* model1 = nullptr;
	FBXObject3d* object1 = nullptr;
	DebugCamera* camera = { nullptr };
	Texture* limit = nullptr;
	Player* player = nullptr;
	Effect* effect[EffectMax] = { nullptr };
	Enemy* enemy[BossEnemyMax] = { nullptr };
	BossEnemy* bossenemy = nullptr;
	Exp* exp[ExpMax][BossEnemyMax] = { nullptr };
	float weight = 0;
	UI* ui=nullptr;
	CollisionManager* collsionManager = nullptr;
};

