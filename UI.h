#pragma once
#include"Sprite.h"
#include"Player.h"
#include"Enemy.h"
#include"BossEnemy.h"


class UI {
public:
	UI(Player*player,BossEnemy* boss=nullptr);
	void Update();
	const void Draw();
private:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
private:
	Player* player = nullptr;
	BossEnemy* boss=nullptr;

	Sprite* BossHp=nullptr;
	Sprite* PlaHp= nullptr;
	Sprite* Arrow = nullptr;


	XMFLOAT2 bossPos{};
	XMFLOAT2 plaPos{};
	XMFLOAT2 AfterPos[2]{};










};

