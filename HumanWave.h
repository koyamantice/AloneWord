#pragma once
#include "Texture.h"
#include "Object3d.h"
#include"Player.h"
class HumanWave {
private: // エイリアス
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	void Init();
	void Upda();
	void Draw();
	void SetPlayer(Player* player) { this->player = player; }
	bool Collide();
	void Set(const XMFLOAT3& pos);
	void Final();
	const bool& GetIsAlive() { return IsAlive; };
private:
	Texture* wave = nullptr;
	XMFLOAT3 pos = { 0.0f,0.0f,0.0f };
	XMFLOAT3 scale = { 0.0f,0.0f,0.0f };
	Player* player;
	float radius = 1.0f;
	bool IsAlive = false;
	float damegeArea = 0.0f;
	float safeArea = 0.0f;
};

