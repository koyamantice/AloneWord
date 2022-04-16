#pragma once
#include "BaseScene.h"
#include "BossEnemy.h"
#include "Collision.h"
#include "Spawning.h"
#include "UI.h"
class CollisionManager;
class TouchableObject;
/// <summary>
/// ゲームプレイシーン
/// </summary>
const int StartEnemyMax = 10;
const int Spawn = 3;
const int BlockMax = 4;
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
	XMFLOAT3 cameraPos = { 0.0f,0.0f,0.0f };
	Model* modelFloor = nullptr;
	Object3d* objFloor;

	Model* modelStartMap = nullptr;
	TouchableObject* objStartMap;
	UI* ui = nullptr;

	//バリケード(仮)
	Model* modelBlock[BlockMax] = { nullptr };
	Object3d* objBlock[BlockMax];
	XMFLOAT3 BlockRotation[BlockMax];

	FBXModel* model1 = nullptr;
	FBXObject3d* object1 = nullptr;
	DebugCamera* camera = { nullptr };
	Texture* limit = nullptr;
	Player* player = nullptr;
	Rice* enemy[StartEnemyMax] = { nullptr };
	Warp* warp = nullptr;
	//BossEnemy* bossenemy = nullptr;
	Spawning* spawing[Spawn];
	ParticleManager* particleMan = nullptr;
	bool start = false;
	bool Clear = false;
	CollisionManager* collisionManager = nullptr;
};

