#pragma once
#include <DirectXMath.h>
#include "CollisionPrimitive.h"
#include "Object3d.h"
#include "Model.h"
#include "Sprite.h"
#include "Player.h"
#include "Texture.h"
#include "Audio.h"
#include "Rice.h"
#include "ModelManager.h"
#include "TouchableObject.h"
#include <array>       // ヘッダファイルインクルード
using namespace std;         //  名前空間指定
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
	void SetPlayer(Player* player) { this->player.reset(player); }
	/// 座標・回転の取得
	const XMFLOAT3& GetPosition() { return  enemyobj->GetPosition(); }
	const XMFLOAT3& GetRotation() { return enemyobj->GetRotation(); }

	/// 座標・回転の設定
	void SetPosition(XMFLOAT3 position) { enemyobj->SetPosition(position); }
	void SetRotation(XMFLOAT3 rotation) { enemyobj->SetRotation(rotation); }
	void SetScale(XMFLOAT3 scale) { enemyobj->SetScale(scale); }
	//ゲッター
	const bool& GetBossHit() { return BossHit; }
	const bool& GetEnemyCatch() { return EnemyCatch; }
	const XMFLOAT3& GetBoundPower() { return boundpower; }
	const bool& GetHit() { return hit; }
	const int& GetBound() { return bound; }
	const bool& GetIsAlive() { return IsAlive; }
	const int& GetDrawExp() { return DrawExp; }
	const int& GetAction() { return action; }
	const int& GetAttackCount() { return AttackCount; }
	const int& GetPat() { return pat; }
	const int& GetCoolT() { return coolT; }
	const int& GetAttackPoint() { return AttackPoint; }
	const bool& GetActive() { return active; }
	const bool& GetStun() { return stun; }
	const bool& GetAppearanceEnd() { return appearanceEnd; }
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
	void SetActive(bool active) { this->active = active; }
	void SetAppearanceEnd(bool appearanceEnd) { this->appearanceEnd = appearanceEnd; }
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
	const bool& GetEffect2() { return Effect2; }
	void SetHP(float BossHP) { this->BossHP = BossHP; }
	void SetEffect(bool Effect) { this->Effect = Effect; }
	void SetEffect2(bool Effect) { this->Effect2 = Effect; }

/// <summary>
/// 初期化
/// </summary>
	virtual void Initialize(bool shadow=true) = 0;
	
	void InitCommon();
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
	//導入
	void Begin();
	//導入ムービー(動き)
	void AppeaMovie(int Timer);
	//撃破ムービー
	void EndMovie(int Timer);

	//撃破ムービー
	void RollMovie(int Timer);

	virtual void App(int Timer)=0;//ボス出現モーション

	virtual void End(int Timer) = 0;//ボス出現モーション

	virtual void Roll(int Timer) = 0;//ボス出現モーション

	virtual void Spec()=0;//ボス特有の処理
	virtual void specialDraw()=0;//ボス特有の描画

	bool collidePlayer();//プレイヤーとの当たり判定
	bool collideAttackArm();//攻撃判定

	void Pause(const int& Timer);
protected:
	const float PI = 3.14f;
	//テクスチャやオブジェクト
	unique_ptr<Object3d> enemyobj = nullptr;
	Model* model = nullptr;
	Texture* texture = nullptr;
	unique_ptr<Texture> Hit = nullptr;
	unique_ptr<Sprite> hit_S = nullptr;
	unique_ptr<Player> player = nullptr;
	//座標や回転
	XMFLOAT3 pos = { 0,0,0 };
	XMFLOAT3 oldpos = { 0,0,0 };
	XMFLOAT3 rot = { 0,0,0 };
	XMFLOAT3 enescale{ 0.4f,0.4f,0.4f };
	XMFLOAT3 Afterrot = { 0.0f,90.0f,0.0f };
	XMFLOAT3 playerpos{};
	XMFLOAT3 targetpos{};
	XMFLOAT3 MottiScale = { 0.0f,0.0f,0.0f };
	bool attach = false;
	XMFLOAT3 Hitsca = { 0.5f,0.5f,0.5f };
	XMFLOAT3 Maxsca{};
	//敵関係変数
	float hitradius = 0.0f;
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
	bool color = false;
	int colorTimer = 0;
	float Defense = 1.0f;

	//イージングのためのやつ
	float frame = 0;
	float frame2 = 0.0f;
	int Interval = 0;
	int FlashCount = 0;
	float x_min = -20;
	float x_max = 22;
	float z_min = -17;
	float z_max = 22;
	bool pause = false;
	bool respawn = false;
	//
	float BossHP = 40;
	bool BossHit = false;
	bool Effect = false;
	bool Effect2 = false;
	//ボスのAI関係(共通)
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
	float angle = 0.0f;
	float angle2 = 0.0f;
	bool shadow=false;
	//急須ボス
	XMFLOAT3 boundpower{};
	XMFLOAT3 Deadbound = {};
	XMFLOAT3 StartPos{};
	XMFLOAT4 bosscolor = { 1.0f,1.0f,1.0f,1.0f };
	XMFLOAT3 EndPos{};
	XMFLOAT3 EndRot{};
	XMFLOAT3 basePos{};
	//靴のボス
	bool stun = false;
	int stunTimer = 0;
	//杵のボス
	bool Off = false;
	int haveTimer = 0;
	int AttackPoint = 0;
	float haveEnemy = 0.0f;
	int damageCount = 0;
	//登場シーン
	bool appearanceEnd = false;
	int appearMove = 0;
	//倒したあとのシーン
	int EndMove = 0;
	float endframe = 0.0f;
	//倒したあとのシーン
	int rollMove = 0;
	float rollframe = 0.0f;
	//靴専用のテクスチャ用変数
	array<Texture*,4> Stuntexture;
	array<float, 4> Stunradius;
	array<float, 4> StunSpeed;
	array<float, 4> Stunscale;
	array<float, 4> StunCircleX;
	array<float, 4> StunCircleZ;
	array<XMFLOAT3, 4> StunPos;
	//投げ攻撃用の挙動
	Object3d* Mottiobj = nullptr;
	Model* Mottimodel = nullptr;
	XMFLOAT3 Mottipos{};
	XMFLOAT3 AfterMottipos{};
};

