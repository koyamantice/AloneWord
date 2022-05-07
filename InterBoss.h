#pragma once
#include <DirectXMath.h>
#include"CollisionPrimitive.h"
#include "Object3d.h"
#include"Model.h"
#include"Sprite.h"
#include "Player.h"
#include "Texture.h"
#include "Audio.h"
#include"Rice.h"
#include"ModelManager.h"


#define DIRECTINPUT_VERSION 0x0800

class InterBoss {
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
	void SetPosition(XMFLOAT3 position) { enemyobj->SetPosition(position); }
	void SetRotation(XMFLOAT3 rotation) { enemyobj->SetRotation(rotation); }

	//ゲッター
	const bool& GetEnemyCatch() { return EnemyCatch; }
	const XMFLOAT3& GetBoundPower() { return boundpower; }
	const bool& GetHit() { return hit; }
	const int& GetBound() { return bound; }
	const bool& GetIsAlive() { return IsAlive; }
	const int& GetDrawExp() { return DrawExp; }
	const int& GetAction() { return action; }
	const int& GetAttackCount() { return AttackCount; }
	const int& GetPat() { return pat; }
	const bool& GetActive() { return active; }
	const bool& GetStun() { return stun; }
	//bool Collision(XMFLOAT3 position, float radius);
	//セッター
	void SetIsAlive(int IsAlive) { this->IsAlive = IsAlive; }
	void SetEnemyCatch(bool EnemyCatch) { this->EnemyCatch = EnemyCatch; }
	void SetBound(bool bound) { this->bound = bound; }
	void SetHit(bool hit) { this->hit = hit; }
	void Back();
	void SetDrawExp(int DrawExp) { this->DrawExp = DrawExp; }
	void Setboundpower(XMFLOAT3 boundpower) { this->boundpower = boundpower; }
	void SetStun(bool stun) { this->stun = stun; }
	//関数
	void SetEnemy();
	void DeadEnemy();
	void RandDeadPower();
	void SetBasePos(XMFLOAT3 basePos) { this->basePos = basePos; }
	void Respawn(float speed);
	void Follow();
	void Reborn();
	bool CollidePos(XMFLOAT3 pos, float radius);
	const float& GetHaveEnemy() { return haveEnemy; }
	//const int& GetHaveTimer() { return haveTimer; }
	const int& GetHaveTimer() { return haveTimer; }
public:
	const float& GetHP() { return BossHP; }
	const bool& GetEffect() { return Effect; }
	void SetHP(float BossHP) { this->BossHP = BossHP; }
	void SetEffect(bool Effect) { this->Effect = Effect; }

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
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void Update2();
	virtual void Spec()=0;//ボス特有の処理
	virtual void specialDraw()=0;//ボス特有の描画

	bool collidePlayer();
	bool collideAttackArm();

	void Pause(const int& Timer);
protected:
	const float PI = 3.14f;

	Object3d* enemyobj = nullptr;
	Model* model = nullptr;

	Texture* texture = nullptr;
	Texture* Restexture = nullptr;
	XMFLOAT3 pos = { 0,0,0 };
	XMFLOAT3 oldpos = { 0,0,0 };
	XMFLOAT3 rot = { 0,0,0 };
	XMFLOAT3 boundpower{};
	XMFLOAT3 Deadbound = {};
	XMFLOAT3 enescale{ 0.4f,0.4f,0.4f };
	XMFLOAT3 shosepos;
	Player* player = nullptr;
	XMFLOAT3 playerpos{};
	
	XMFLOAT3 targetpos{};
	XMFLOAT3 StartPos{};
	XMFLOAT3 EndPos{};
	XMFLOAT3 EndRot{};
	XMFLOAT3 basePos{};

	float radius = 0.0f;
	float speed = 0.0f;
	float savespeed = 0.0f;
	float scale = 0.0f;
	float savesacale = 0.0f;
	float circleX = 0.0f;
	float circleZ = 0.0f;
	float EnemyWeight = 0.0f;
	bool IsAlive = 0;
	int IsTimer = 200;
	bool EnemyCatch = false;
	bool isMove = false;
	bool hit = false;
	int moveCount = 30;
	int dir = 0;
	bool zmove = false;
	bool bound = false;
	bool add = false;
	bool appearance = false;
	bool Exp = false;
	int DrawExp = false;
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
	bool pause = false;
	bool respawn = false;	float Afterrot = 90;//初期向き
	//
	float BossHP = 40;
	bool BossHit = false;
	bool Effect = false;
	//
	bool already = false;
	//
	int hitpoint = 0;
	bool active = false;//行動開始
	int action = 0;//攻撃の種類
	int pat = 0;//パターン
	int aiming = 0;//敵追従
	int coolT = 0;//クールタイム
	int AttackC = 0;//何回攻撃したか
	bool finish = false;//フィニッシュ
	int State = 0;
	int AttackCount = 0;
	float y = 0.0f;
	float angle = 0.0f;
	float angle2 = 0.0f;
	//待機モーションのためのやつ
	enum Motion {
		Up,
		Down
	};
	//靴のボス
	bool stun = false;
	int stunTimer = 0;
	//杵のボス
	bool Off = false;
	int haveTimer = 0;
	float haveEnemy = 0.0f;
};

