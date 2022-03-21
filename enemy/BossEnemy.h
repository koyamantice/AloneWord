#pragma once
#include"Object3d.h"
#include"Model.h"
#include <DirectXMath.h>
#include <Input.h>
#include"CollisionPrimitive.h"
#include "Player.h"
#include "Sprite.h"

class Enemy;
class BossEnemy {
public:
	BossEnemy();

	void Initialize();
	void Update();
	void Draw();
private:
	bool collidePlayer();
	bool collideAttackArm();
	void Fork();
private:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	/// 座標の取得
	const XMFLOAT3& GetPosition() { return  object3d->GetPosition(); }

	const XMFLOAT3& GetRotation() { return object3d->GetRotation(); }

	const int& GetisAlive() { return IsAlive; }

	const int& GetHP() { return BossHP; }
	/// 座標の設定
	void SetPosition(XMFLOAT3 position) { object3d->SetPosition(position); }

	void SetRotation(XMFLOAT3 rotation) { object3d->SetRotation(rotation); }

	void SetPlayer(Player*player) { this->player=player; }

	void SetIsAlive(int IsAlive) { this->IsAlive = IsAlive; }

	void SetHP(int BossHP) { this->BossHP = BossHP; }
private:
	Object3d* object3d;
	Model* model;
	XMFLOAT2 HPPos = { 0,0 };
	XMFLOAT3 pos = { 0,0,0 };
	Sprite* SpriteBossHP = false;
	float rad = 0.4f;
	const float PI = 3.14f;

	int IsAlive = 0;
	int IsTimer = 100;
	int IsMove = 0;
	int BossHP = 50;
	bool BossHit = false;

	int AttackCount = 0;

	int action = 0;
	bool active = false;

	int pat = 0;
	float frame = 0;
	Player* player;

public:
	Sphere collider;
};