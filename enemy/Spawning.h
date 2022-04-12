#pragma once
#include <DirectXMath.h>
#include"Rice.h"
#include"Player.h"

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

	void SetEnemy(const int& i,Rice*enemy);
public:
	const XMFLOAT3& GetPosition() { return  object3d->GetPosition(); }
	const XMFLOAT3& GetRotation() { return object3d->GetRotation(); }
	const bool& GetIsAlive() { return isAlive; }
	void SetPosition(XMFLOAT3 position) { this->pos = position; }

	void SetRotation(XMFLOAT3 rotation) { object3d->SetRotation(rotation); }
	void collideAttackArm();
	void SetPlayer(Player* player) { this->player = player; };
private:
	Object3d* object3d;
	Model* model;
	XMFLOAT3 pos = { 0,0,0 };
	Texture* texture=nullptr;
	bool Hit=false;
	float Hp = 12.0f;
	bool isAlive = true;
	Rice* enemy[10] = {};
	Player* player = nullptr;
};

