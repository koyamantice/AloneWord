#pragma once
#include "Texture.h"
class HotWater {
private: // �G�C���A�X
	// DirectX::���ȗ�
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
	const bool& GetIsAlive() { return IsAlive; };
private:
	Texture* hot=nullptr;
	float frame = 0;
	XMFLOAT3 sca{};
	bool IsAlive = false;
};

