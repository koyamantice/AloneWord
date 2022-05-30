#pragma once
#include "BaseScene.h"
#include "LeftShose.h"
#include "RightShose.h"
#include "UI.h"
#include "Foot.h"
#include <array>       // ヘッダファイルインクルード
using namespace std;         //  名前空間指定
/// <summary>
/// ゲームプレイシーン
/// </summary>
const int SecondBossEnemyMax = 10;
class CollisionManager;
class TouchableObject;
class SecondBoss : public BaseScene {
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
	//オブジェクトやテクスチャ
	Model* modelFloor = nullptr;
	Object3d* objFloor;
	Model* modelBossMap = nullptr;
	TouchableObject* objBossMap;
	Model* modelSphere = nullptr;
	Object3d* objSphere;
	Model* modelEntrance = nullptr;
	Object3d* objEntrance;
	//カメラ
	DebugCamera* camera = { nullptr };
	//各クラスのためのもの
	Player* player = nullptr;
	array<Effect*, 40> effect;
	array<Rice*, 6> enemy;
	LeftShose* leftshose = nullptr;
	RightShose* rightshose = nullptr;
	Foot* foot = nullptr;
	//std::array<std::array<Exp*, 6>, 5> exp;
	
	UI* ui = nullptr;
	ParticleManager* particleMan = nullptr;
	ExpandChange* expandchange = nullptr;
	int DethRight = 0;
	int DethLeft = 0;
	/*int DeadLeft = 0;
	int DeadRight = 0;
	float weight = 0;*/
};

