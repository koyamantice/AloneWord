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
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:

	/// <summary>
	/// ���W�̎擾
	/// </summary>
	/// <returns>���W</returns>
	//const XMFLOAT3& GetPosition() { return  object3d->GetPosition(); }

	//const XMFLOAT3& GetRotation() { return object3d->GetRotation(); }

	/// <summary>
	/// ���W�̐ݒ�
	/// </summary>
	/// <param name="position">���W</param>
	void SetPosition(XMFLOAT3 position) { this->pos; }

	//void SetRotation(XMFLOAT3 rotation) { object3d->SetRotation(rotation); }

	//void SetWarpAlive(bool WarpAlive) { this->WarpAlive = WarpAlive; }

	bool collidePlayer(Player* player);
private:
	/*Object3d* Armobj;
	Object3d* object3d;
	Model* model;
	Model* Armmodel;*/
	//�G�t�F�N�g�֌W
	Texture* Warptexture = nullptr;
	XMFLOAT3 pos = { -1.0f,0.0f,36.0f };
	
public:
	Sphere collider;
};