#pragma once
#include "BaseScene.h"
#include "BossEnemy.h"
#include "Collision.h"
#include "Spawning.h"
#include "UI.h"
#include <array>       // ヘッダファイルインクルード
using namespace std;         //  名前空間指定
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
	void Pause(const int& Timer);
private:
	XMFLOAT3 cameraPos = { 0.0f,0.0f,0.0f };
	Model* modelFloor = nullptr;
	Object3d* objFloor;

	Model* modelStartMap = nullptr;
	TouchableObject* objStartMap;
	UI* ui = nullptr;

	//バリケード(仮)
	array<Model*,4> modelBlock;
	array<Object3d*,4> objBlock;
	array<XMFLOAT3,4> BlockRotation;

	FBXModel* model1 = nullptr;
	FBXObject3d* object1 = nullptr;
	DebugCamera* camera = { nullptr };
	Texture* limit = nullptr;
	Player* player = nullptr;
	array<Rice*,10> enemy;
	Warp* warp = nullptr;
	//BossEnemy* bossenemy = nullptr;
	array<Spawning*,1> spawing;
	ParticleManager* particleMan = nullptr;
	bool start = false;
	bool Clear = false;
	int a = 0;
	CollisionManager* collisionManager = nullptr;
	bool pause = false;
	int wait = 0;
	int set = 0;
};

