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
class BaseEnemy {
protected:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	/// 座標・回転の取得
	const XMFLOAT3& GetPosition() { return  enemyobj->GetPosition(); }
	const XMFLOAT3& GetRotation() { return enemyobj->GetRotation(); }

	/// 座標・回転の設定
	void SetPosition(XMFLOAT3 position) { enemyobj->SetPosition(position); }
	void SetRotation(XMFLOAT3 rotation) { enemyobj->SetRotation(rotation); }
	void SetColor(XMFLOAT4 color) { enemyobj->SetColor(color); }
protected:
	const float PI = 3.14f;

	Object3d* enemyobj = nullptr;
	Model* model = nullptr;
	Texture* texture = nullptr;
	Texture* Restexture = nullptr;
	XMFLOAT3 pos = { 0,0,0 };
	XMFLOAT3 rot = { 0,0,0 };
	XMFLOAT3 boundpower{};
	XMFLOAT3 enescale{0.4f,0.4f,0.4f};
	Player* player=nullptr;
	float frame = 0;
	int IsAlive = 0;
	int Interval = 0;
	int FlashCount = 0;
	float x_min = -25;
	float x_max = 25;
	float z_min = -20;
	float z_max = 20;

public:
	Sphere collider;

public:
	virtual ~BaseEnemy() = default;

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

protected:
	const int& GetisAlive() { return IsAlive; }
};
