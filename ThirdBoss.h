#pragma once
#include "SceneManager.h"
#include "GreenTea.h"
#include "HotWater.h"
#include "UI.h"
#include <array>       // ヘッダファイルインクルード

using namespace std;         //  名前空間指定
/// <summary>
/// ゲームプレイシーン
/// </summary>
const int ThirdEnemyMax = 5;
class CollisionManager;
class TouchableObject;
class ThirdBoss : public BaseScene {
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
	Model* modelJstyle = nullptr;
	Object3d* objJstyle;
	Texture* limit = nullptr;
	//カメラ関係
	DebugCamera* camera = { nullptr };
	//それぞれのクラスのもの
	Player* player = nullptr;
	array<Effect*, 60> effect;
	array<Rice*, 10> enemy;
	InterBoss* bossenemy = nullptr;
	//std::array<std::array<Exp*, 5>, 5> exp;
	float weight = 0;
	UI* ui = nullptr;
	ParticleManager* particleMan = nullptr;
	ExpandChange* expandchange = nullptr;
};


