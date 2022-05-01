#pragma once
#include "Texture.h"
class HotWater {
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
	void Set(const XMFLOAT3& pos);
	void Final();
private:
	Texture* hot=nullptr;
	bool IsAlive = false;
};

