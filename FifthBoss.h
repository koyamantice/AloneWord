#pragma once
#include "BaseScene.h"
#include "LeftHand.h"
#include "RightHand.h"
#include"LeftHumanWave.h"
#include"RightHumanWave.h"
#include "Human.h"
#include "UI.h"
#include <array>       // ヘッダファイルインクルード
using namespace std;         //  名前空間指定
/// <summary>
/// ゲームプレイシーン
/// </summary>
const int FifthBossEnemyMax = 10;
class CollisionManager;
class TouchableObject;
class FifthBoss : public BaseScene {
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
	Model* modelBedroom = nullptr;
	Object3d* objBedroom;
	FBXModel* model1 = nullptr;
	FBXObject3d* object1 = nullptr;
	Texture* limit = nullptr;
	//カメラ
	DebugCamera* camera = { nullptr };
	//各クラスのためのもの
	Player* player = nullptr;
	array<Effect*, 60> effect;
	array<Rice*, 10> enemy;
	LeftHand* lefthand = nullptr;
	RightHand* righthand = nullptr;
	RightHumanWave* rightwave = nullptr;
	LeftHumanWave* leftwave = nullptr;
	Human* human = nullptr;
	//std::array<std::array<Exp*, 6>, 5> exp;

	UI* ui = nullptr;
	CollisionManager* collisionManager = nullptr;
	ParticleManager* particleMan = nullptr;
	ExpandChange* expandchange = nullptr;
	bool act = false;
	int DethRight = 0;
	int DethLeft = 0;
};

