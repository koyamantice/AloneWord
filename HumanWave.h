#pragma once
#include "Texture.h"
#include "Player.h"
class HumanWave {
public:
	void Init();
	void Upda();
	void Draw();
	void Final();
	void Set(const XMFLOAT3& pos);
	void SetWave();
	bool CollideWave();
	bool CollideSafeWave();
	void SetPlayer(Player* player) { this->player = player; }
	const bool& GetExpand() { return expand; };
	//void ExpandWave();
private:
	Texture* wave = nullptr;
	XMFLOAT3 pos = { 0.0f,0.0f,0.0f };
	XMFLOAT3 scale = { 0.0f,0.0f,0.0f };
	Player* player;
	bool expand = false;
	float damegeArea = 0.0f;
	float safeArea = 0.0f;
	int Interval = 0;
};

