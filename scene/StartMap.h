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
	//メンバ変数
	//オブジェクトやテクスチャ
	unique_ptr<Texture> Hit=nullptr;
	Model* modelFloor = nullptr;
	Object3d* objFloor;
	Model* modelBossMap = nullptr;
	TouchableObject* objBossMap;
	Model* modelSphere = nullptr;
	unique_ptr<TouchableObject> objSphere = nullptr;
	Model* modelSkydome = nullptr;
	Object3d* objSkydome;
	//カメラ関係
	XMFLOAT3 cameraPos = { 0.0f,0.0f,0.0f };
	DebugCamera* camera = { nullptr };
	//それぞれのクラスのもの
	Player* player = nullptr;
	array<Effect*, 40> effect;
	array<Rice*, 7> enemy;
	InterBoss* bossenemy = nullptr;
	UI* ui = nullptr;
	CollisionManager* collisionManager = nullptr;
	ParticleManager* particleMan = nullptr;
	ExpandChange* expandchange = false;
	ShrinkChange* shrinkchange = false;

	//チュートリアルのためのもの
	bool check = false;
	bool checkZ = false;
	float frame=0;
	XMFLOAT2 sca{};
	XMFLOAT2 scaOk{};
	int	tutorial =0;
	Sprite* comment[12];
	Sprite* Ok;
	bool open = false;
	bool close = false;
	enum {
		text1,
		text2,
		text3,
		text4,
		text5,
		text6,
		text7,
		text8,
		text9,
		text10,
		text11,
	};
	float angle = 0;
	XMFLOAT2 pos12{ 570.0f,450.0f };
	int nowText=0;
	int nowTimer = 0;
	bool closeT = false;
	bool openT = false;
	bool Clear = false;
	bool pause = false;
	int wait = 0;
	int set = 0;
	bool hit=false;
	//std::thread t;
};