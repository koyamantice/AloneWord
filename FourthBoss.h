#pragma once
#include "BaseScene.h"
#include "Pastel.h"
#include "Mill.h"
#include "ShockWave.h"
#include "UI.h"
#include <array>       // ヘッダファイルインクルード
using namespace std;         //  名前空間指定
/// <summary>
/// ゲームプレイシーン
/// </summary>
const int FourthBossEnemyMax = 10;
class CollisionManager;
class TouchableObject;
class FourthBoss : public BaseScene {
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

	Model* modelFloor = nullptr;
	Object3d* objFloor;

	Model* modelBossMap = nullptr;
	TouchableObject* objBossMap;

	Model* modelSphere = nullptr;
	TouchableObject* objSphere;
	FBXModel* model1 = nullptr;
	FBXObject3d* object1 = nullptr;
	DebugCamera* camera = { nullptr };
	Texture* limit = nullptr;
	Player* player = nullptr;
	array<Effect*, 40> effect;
	array<InterEnemy*, 6> enemy;
	Pastel* pastel = nullptr;
	ShockWave* shockwave = nullptr;
	//std::array<std::array<Exp*, 10>, 5> exp;
	float weight = 0;
	UI* ui = nullptr;
	CollisionManager* collisionManager = nullptr;
	ParticleManager* particleMan = nullptr;
	ExpandChange* expandchange = nullptr;
};

