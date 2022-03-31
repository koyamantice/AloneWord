#pragma once
#include"Object3d.h"
#include"Model.h"
#include <DirectXMath.h>
#include <Input.h>
#include"CollisionPrimitive.h"
#include "Sprite.h"
#include "Texture.h"
#include "Enemy.h"
#include "Player.h"

class Exp {
public:
	Exp();

	void Initialize();
	void Finalize();
	void Update(Player* player,Enemy* enemy);
	void Draw();
private:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:

	/// <summary>
/// 座標の取得
/// </summary>
/// <returns>座標</returns>
	const XMFLOAT3& GetPosition() { return  object3d->GetPosition(); }

	const XMFLOAT3& GetRotation() { return object3d->GetRotation(); }

	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="position">座標</param>
	void SetPosition(XMFLOAT3 position) { object3d->SetPosition(position); }

	void SetRotation(XMFLOAT3 rotation) { object3d->SetRotation(rotation); }

	//void SetExpAlive(bool ExpAlive) { this->ExpAlive = ExpAlive; }
	void SetExp(Enemy* enemy);
private:
	Object3d* object3d;
	Model* model;
	XMFLOAT3 pos = { 0,0,-10 };

	//経験値
	XMFLOAT3 scale = { 0.4f,0.4f,0.4f };
	XMFLOAT3 boundpower = { 0.0f,0.0f,0.0f };
	bool ExpAlive = false;
public:
	Sphere collider;
};