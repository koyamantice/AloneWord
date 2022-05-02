#pragma once
#include "Texture.h"
#include "Pastel.h"
class ShockWave {
public:
	void Init();
	void Upda(Pastel* pastel);
	void Draw();
	void Final();
	void SetWave(Pastel* pastel);
	//void ExpandWave();
private:
	Texture* wave = nullptr;
	XMFLOAT3 pos = { 0.0f,0.0f,0.0f };
	XMFLOAT3 scale = { 0.0f,0.0f,0.0f };
	bool expand = false;
};

