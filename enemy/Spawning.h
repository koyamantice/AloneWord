#pragma once
#include <DirectXMath.h>
#include"InterEnemy.h"
#include"Player.h"
const int EneMax = 5;
class Spawning {
private:
	// DirectX::‚ðÈ—ª
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	Spawning(int Categoly = 0);

	void Initialize();
	void Update();
	void Finalize();
	void Draw();
	void Pause(const int& Timer);

public:
	const XMFLOAT3& GetPosition() { return  object3d->GetPosition(); }
	const XMFLOAT3& GetRotation() { return object3d->GetRotation(); }
	const int& GetStop() { return stop; }
	const bool& GetIsAlive() { return isAlive; }
	void SetPosition(XMFLOAT3 position) { this->pos = position; }

	void SetRotation(XMFLOAT3 rotation) { object3d->SetRotation(rotation); }
	bool collideAttackArm();
	void SetPlayer(Player* player) { this->player = player; };
	const int& GetEneMax() { return EneMax; }
	InterEnemy* GetEnemy(const int& num) { return enemy[num]; }
private:
	Object3d* object3d;
	Model* model;
	XMFLOAT3 pos = { 0,0,0 };
	Texture* net[2] = {nullptr};
	Texture* texture=nullptr;
	bool Hit=false;
	float Hp = 8.0f;
	bool isAlive = true;
	InterEnemy* enemy[EneMax] = {};
	Player* player = nullptr;
	bool pause = false;
	int stop = 0;
	int wait = 0;
};

