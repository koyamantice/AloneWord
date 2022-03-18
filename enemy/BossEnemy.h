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
	void Update(Player* player);
	void Draw();
private:
	bool collidePlayer(Player* player);
	bool collideAttackArm(Player* player);
	void Fork();
private:
	// DirectX::‚ðÈ—ª
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	/// À•W‚ÌŽæ“¾
	const XMFLOAT3& GetPosition() { return  object3d->GetPosition(); }

	const XMFLOAT3& GetRotation() { return object3d->GetRotation(); }

	const int& GetisAlive() { return IsAlive; }
	/// À•W‚ÌÝ’è
	void SetPosition(XMFLOAT3 position) { object3d->SetPosition(position); }

	void SetRotation(XMFLOAT3 rotation) { object3d->SetRotation(rotation); }

	//bool Collision(XMFLOAT3 position, float radius);

	void SetIsAlive(int IsAlive) { this->IsAlive = IsAlive; }
private:
	Object3d* object3d;
	Model* model;
	XMFLOAT2 HPPos = {0,0};
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
	int action=0;
	bool active=false;
public:
	Sphere collider;
};

