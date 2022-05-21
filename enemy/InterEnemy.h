#pragma once
#include <DirectXMath.h>
#include"CollisionPrimitive.h"
#include "Object3d.h"
#include"Model.h"
#include"Sprite.h"
#include "Player.h"
#include "Texture.h"
#include "Audio.h"


#define DIRECTINPUT_VERSION 0x0800

/// <summary>
/// 敵基底
/// </summary>
class InterEnemy {
protected:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	void SetPlayer(Player* player) { this->player = player; }
	/// 座標・回転の取得
	const XMFLOAT3& GetPosition() { return  enemyobj->GetPosition(); }
	const XMFLOAT3& GetRotation() { return enemyobj->GetRotation(); }

	/// 座標・回転の設定
	void SetPosition(const XMFLOAT3& position) { enemyobj->SetPosition(position); }
	void SetRotation(const XMFLOAT3& rotation) { enemyobj->SetRotation(rotation); }
	//このクラスで使うもののゲッター : セッター
	const int& GetIsTimer() { return IsTimer; };
	const bool& GetEnemyCatch() { return EnemyCatch; }
	const XMFLOAT3& GetBoundPower() { return boundpower; }
	const bool& GetHit() { return hit; }
	const int& GetBound() { return bound; }
	const bool& GetIsAlive() { return IsAlive; }
	const int& GetDrawExp() { return DrawExp; }
	const bool& GetFollowed() { return followed; }
	const bool& GetEnemyCatcth() { return EnemyCatch; }
	//bool Collision(XMFLOAT3 position, float radius);
	void SetIsAlive(const int& IsAlive) { this->IsAlive = IsAlive; }
	void SetEnemyCatch(const bool& EnemyCatch) { this->EnemyCatch = EnemyCatch; }
	void SetBound(const bool& bound) { this->bound = bound; }
	void SetScale(const float& Scale) { this->scale=Scale; }
	void SetSpeed(const float& speed) { this->speed = speed; }
	void SetHit(const bool& hit) { this->hit = hit; }
	void SetDrawExp(const int& DrawExp) { this->DrawExp = DrawExp; }
	void Setboundpower(const XMFLOAT3& boundpower) { this->boundpower = boundpower; }
	void SetLimit(const XMFLOAT4& limit) {
		this->z_max = limit.x;
		this->z_min = limit.y;
		this->x_max = limit.z;
		this->x_min = limit.w;
	}
	//メンバ関数
	void SetBasePos(XMFLOAT3 basePos) { this->basePos = basePos; }
	void Back();
	void Stop();
	void SetEnemy();
	void DeadEnemy();
	void RandDeadPower();
	void Respawn(float speed);
	void Follow();
	void Reborn();
	bool CollidePos(XMFLOAT3 pos,float radius);

protected:
///メンバ変数
	//円周率(円運動のためのやつ)
	const float PI = 3.14f;

	//モデルやテクスチャー
	Object3d* enemyobj = nullptr;
	Model* model = nullptr;
	Texture* texture = nullptr;
	Texture* Restexture = nullptr;
	Player* player = nullptr;

	//各座標や回転やサイズ
	XMFLOAT3 pos = { 0,0,0 };
	XMFLOAT3 oldpos = { 0,0,0 };
	XMFLOAT3 rot = { 0,0,0 };
	XMFLOAT3 enescale{ 0.4f,0.4f,0.4f };
	XMFLOAT3 playerpos{};
	XMFLOAT3 NextP{};
	XMFLOAT3 StartPos{};
	XMFLOAT3 EndPos{};
	XMFLOAT3 EndRot{};
	XMFLOAT3 basePos{};

	//死んだときの変数
	XMFLOAT3 boundpower{};
	XMFLOAT3 Deadbound = {};
	//円運動に使う変数
	float radius = 0.0f;
	float speed = 0.0f;
	float savespeed = 0.0f;
	float scale = 0.0f;
	float savesacale = 0.0f;
	float circleX = 0.0f;
	float circleZ = 0.0f;
	
	//リスポーン関係
	bool IsAlive = 0;
	int IsTimer = 200;
	//フラグ関係
	bool EnemyCatch = false;
	bool isMove = false;
	bool hit = false;
	bool lost = false;
	bool followed = false;
	bool bound = false;
	bool add = false;
	bool appearance = false;
	bool Exp = false;
	int DrawExp = false;
	bool pause = false;
	bool respawn = false;
	//敵のAI関係
	int moveCount = 30;
	int CheckCount = 0;
	int count = 0;
	int dir = 180;
	int dirVel = 2;
	int dirMin = dir - 90;
	int dirMax = dir + 90;
	double posR;
	double Check;
	double Check2;
	float frame = 0;
	int Interval = 0;
	int FlashCount = 0;
	float x_min = -25;
	float x_max = 25;
	float z_min = -20;
	float z_max = 20;
	XMFLOAT2 vel{};

public:
	virtual ~InterEnemy() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize() = 0;
	/// <summary>
	/// 終了
	/// </summary>
	virtual void Finalize() = 0;
	/// <summary>
	/// 毎フレーム更新
	/// </summary>
	virtual void Update() = 0;
	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw() = 0;

	virtual bool collidePlayer() = 0;
	virtual bool collideAttackArm() = 0;
	void Pause(const int& Timer);

protected:
	const int& GetisAlive() { return IsAlive; }
};
