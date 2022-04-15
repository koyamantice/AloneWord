#pragma once
#include "BaseScene.h"
#include "BossEnemy.h"
#include "UI.h"

/// <summary>
/// ゲームプレイシーン
/// </summary>
const int BossEnemyMax = 10;
const int EffectMax = 40;
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
	XMFLOAT3 cameraPos = { 0.0f,0.0f,0.0f };
	Model* modelFloor = nullptr;
	Object3d* objFloor;

	Model* modelBossMap = nullptr;
	TouchableObject* objBossMap;

	Model* modelSphere = nullptr;
	Object3d* objSphere;

	FBXModel* model1 = nullptr;
	FBXObject3d* object1 = nullptr;
	DebugCamera* camera = { nullptr };
	Texture* limit = nullptr;
	Player* player = nullptr;
	Effect* effect[EffectMax] = { nullptr };
	InterEnemy* enemy[BossEnemyMax] = { nullptr };
	BossEnemy* bossenemy = nullptr;
	Exp* exp[ExpMax][BossEnemyMax] = { nullptr };
	float weight = 0;
	UI* ui=nullptr;
	CollisionManager* collisionManager = nullptr;
	ParticleManager* particleMan = nullptr;
};

