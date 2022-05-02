#pragma once
#include "Texture.h"
#include "Pastel.h"
#include "Player.h"
class ShockWave {
public:
	void Init();
	void Upda(Pastel* pastel, Player* player);
	void Draw();
	void Final();
	void SetWave(Pastel* pastel);
	bool CollideWave(Player* player);
	bool CollideSafeWave(Player* player);
	//void ExpandWave();
private:
	Texture* wave = nullptr;
	XMFLOAT3 pos = { 0.0f,0.0f,0.0f };
	XMFLOAT3 scale = { 0.0f,0.0f,0.0f };
	bool expand = false;
	float damegeArea = 0.0f;
	float safeArea = 0.0f;
	int Interval = 0;
};

