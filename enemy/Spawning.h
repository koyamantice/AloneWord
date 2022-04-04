#pragma once
#include <DirectXMath.h>
#include"Enemy.h"
#include"Player.h"

class Spawning {
private:
	// DirectX::���ȗ�
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

	void SetEnemy(const int& i,Enemy*enemy);
public:
	const XMFLOAT3& GetPosition() { return  object3d->GetPosition(); }
	const XMFLOAT3& GetRotation() { return object3d->GetRotation(); }
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
	int Hp = 20;
	Enemy* enemy[10] = {};
	Player* player = nullptr;
};
