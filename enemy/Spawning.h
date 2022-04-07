#pragma once
#include <DirectXMath.h>
#include"InterMob.h"
class Spawning {
private:
	// DirectX::‚ðÈ—ª
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	Spawning();
	
	void Initialize();
	void Update();
	void Finalize();
	void Draw();

	void SetEnemy(const int& i, InterMob*enemy);
public:
	const XMFLOAT3& GetPosition() { return  object3d->GetPosition(); }
	const XMFLOAT3& GetRotation() { return object3d->GetRotation(); }
	void SetPosition(XMFLOAT3 position) { this->pos = position; }
	void SetRotation(XMFLOAT3 rotation) { object3d->SetRotation(rotation); }


private:
	Object3d* object3d;
	Model* model;
	XMFLOAT3 pos = { 0,0,0 };

	InterMob* enemy[10] = {};
};

