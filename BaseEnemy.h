#pragma once
#include <DirectXMath.h>
#include"CollisionPrimitive.h"
#include "Object3d.h"
#include"Model.h"
#include"Sprite.h"
#include "Player.h"
#include "Texture.h"

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
protected:
	Object3d* enemyobj = nullptr;
	Model* model;
	Sphere collider;

	XMFLOAT3 pos = { 0,0,0 };
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
	virtual void Update(Player* player) = 0;
	/// <summary>
	/// 描画
	/// </summary>
	virtual const void Draw() = 0;

};
