#pragma once
#include"Object3d.h"
#include"Model.h"
#include <DirectXMath.h>
#include <Input.h>
#include"CollisionPrimitive.h"
#include "Player.h"
#include "Collision.h"
class Enemy {
public:
	Enemy();

	void Initialize();
	void Update(Player* player);
	void Draw();
	bool collidePlayer(Player* player);
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
	/// 座標の設定
	void SetPosition(XMFLOAT3 position) { object3d->SetPosition(position); }

	void SetRotation(XMFLOAT3 rotation) { object3d->SetRotation(rotation); }

	//bool Collision(XMFLOAT3 position, float radius);

	void SetIsAlive(int IsAlive) { this->IsAlive = IsAlive; }
private:
	Object3d* object3d;
	Model* model;
	XMFLOAT3 pos = {0,0,0};
	
	float rad = 0.4f;
	const float PI = 3.14f;

	float radius = 0.0f;
	float speed = 0.0f;
	float scale = 0.0f;// LaneNumと一緒に変えること
	float circleX = 0.0f;
	float circleZ = 0.0f;
	int IsAlive = 0;
	int IsTimer = 100;
	int IsMove = 0;

public:
	Sphere collider;
	Collision* collision = nullptr;
};

