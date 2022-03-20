#pragma once
#include"Object3d.h"
#include"Model.h"
#include <DirectXMath.h>
#include <Input.h>
#include"CollisionPrimitive.h"
#include "Player.h"
#include "Texture.h"

class BossEnemy;
class Enemy {
public:
	Enemy();

	void Initialize();
	void Update(Player* player,BossEnemy* bossenemy);
	void Draw();
private:
	bool collideArm(Player* player);
	bool collidePlayer(Player* player);
	bool collideAttackArm(Player* player);
	bool LockOn(Player*player);
	void Follow(Player* player);
	void Move();

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
	const bool& GetEnemyCatch() { return EnemyCatch; }
	const bool& GetHit() { return hit; }

	/// 座標の設定
	void SetPosition(XMFLOAT3 position) { object3d->SetPosition(position); }

	void SetRotation(XMFLOAT3 rotation) { object3d->SetRotation(rotation); }

	//bool Collision(XMFLOAT3 position, float radius);

	void SetIsAlive(int IsAlive) { this->IsAlive = IsAlive; }

	void SetEnemyCatch(bool EnemyCatch) {this-> EnemyCatch = EnemyCatch; }

	void SetHit(bool hit) { this->hit = hit; }

private:
	Object3d* object3d;
	Model* model;
	Texture* texture;
	XMFLOAT3 playerpos{};
	XMFLOAT3 StartPos{};
	XMFLOAT3 EndPos{};
	XMFLOAT3 pos = {0,0,0};
	XMFLOAT3 rot = { 0,0,0 };
	float rad = 0.4f;
	const float PI = 3.14f;

	float radius = 0.0f;
	float speed = 0.0f;
	float scale = 0.0f;// LaneNumと一緒に変えること
	float circleX = 0.0f;
	float circleZ = 0.0f;
	float EnemyWeight = 0.0f;
	bool IsAlive = 0;
	int IsTimer = 100;
	bool EnemyCatch = false;
	bool isMove = false;
	bool hit = false;
	float frame=0;
	int moveCount = 30;
	int dir = 0;
	bool zmove = false;
public:
	Sphere collider;
};

