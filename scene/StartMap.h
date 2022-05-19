#pragma once
#include "BaseScene.h"
#include "BossEnemy.h"
#include "Collision.h"
#include "Spawning.h"
#include "UI.h"
#include <array>       // ヘッダファイルインクルード
#include <thread>
using namespace std;         //  名前空間指定
class CollisionManager;
class TouchableObject;
/// <summary>
/// ゲームプレイシーン
/// </summary>
const int StartSpawn = 1;
class StartMap : public BaseScene {
public:
	//~StartMap();
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
	Sprite* concent = nullptr;
	Sprite* concent2 = nullptr;
	Sprite* concent3 = nullptr;
	Sprite* concent4 = nullptr;
	Sprite* concent5 = nullptr;
	Sprite* button = nullptr;
	DebugCamera* camera = { nullptr };
	Texture* limit = nullptr;
	Player* player = nullptr;
	array<Rice*, 7> enemy;
	InterBoss* spawing;
	ParticleManager* particleMan = nullptr;
	int	tutorial =0;
	bool Clear = false;
	CollisionManager* collisionManager = nullptr;
	ExpandChange* expandchange = false;
	ShrinkChange* shrinkchange = false;
	bool pause = false;
	int wait = 0;
	int set = 0;
	bool hit=false;
	//std::thread t;
};