#pragma once
#include"Sprite.h"
#include"Player.h"
#include"Rice.h"
#include"InterBoss.h"

class UI {
public:
	UI(Player* player, InterBoss* boss = nullptr, InterBoss* boss2 = nullptr);
	void Update();
	void Finalize();
	const void Draw();
private:
	// DirectX::Çè»ó™
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
private:
	Player* player = nullptr;
	InterBoss* boss = nullptr;
	InterBoss* boss2 = nullptr;
	Sprite* BossHp = nullptr;
	Sprite* BossHp2 = nullptr;
	Sprite* PlaHp = nullptr;
	Sprite* HpGauge = nullptr;
	Sprite* Mark1= nullptr;
	Sprite* Mark2 = nullptr;
	Sprite* Mark3 = nullptr;
	Sprite* Life = nullptr;
	Sprite* Arrow = nullptr;
	Sprite* Arrow2 = nullptr;
	Sprite* Vignette = nullptr;
	Sprite* number[2][10]{};
	Sprite* bairitu = nullptr;
	XMFLOAT2 bossPos{};
	XMFLOAT2 bossPos2{};
	XMFLOAT2 plaPos{};
	XMFLOAT2 ArrowPos{};
	XMFLOAT2 ArrowPos2{};
	XMFLOAT2 AfterPos[2]{};
	XMFLOAT2 AfterPos2[2]{};
	const float PI = 3.145265f;
	std::vector<int> power;
	float strong =200.0f;
	float speed = 0;

	float scale = 50;
	double a;
	double b;
	XMFLOAT2 basePos = { 1280 / 2,720 / 2 };
	XMFLOAT2 circle={640.0f,360.0f};
	XMFLOAT2 circle2 = { 640.0f,360.0f };
	XMFLOAT3 pos{};
	double posR;
	float Check;
	float Check2;
	int invisible = false;
private:
	void SeachBoss();
	void SeachBoss2();
};

