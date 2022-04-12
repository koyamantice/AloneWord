#pragma once
#include"Object3d.h"
#include"Model.h"
#include <DirectXMath.h>
#include <Input.h>
#include"CollisionPrimitive.h"
#include "Sprite.h"
#include "Texture.h"
#include "Player.h"

class Warp {
public:
	Warp();

	void Initialize();
	void Finalize();
	void Update(Player* player);
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
	//const XMFLOAT3& GetPosition() { return  object3d->GetPosition(); }

	//const XMFLOAT3& GetRotation() { return object3d->GetRotation(); }

	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="position">座標</param>
	void SetPosition(XMFLOAT3 position) { this->pos; }

	//void SetRotation(XMFLOAT3 rotation) { object3d->SetRotation(rotation); }

	//void SetWarpAlive(bool WarpAlive) { this->WarpAlive = WarpAlive; }

	bool collidePlayer(Player* player);
private:
	/*Object3d* Armobj;
	Object3d* object3d;
	Model* model;
	Model* Armmodel;*/
	//エフェクト関係
	Texture* Warptexture = nullptr;
	XMFLOAT3 pos = { -1.0f,0.0f,36.0f };
	
public:
	Sphere collider;
};