#pragma once
//#include "Sprite.h"
//#include "Texture.h"
//class ExpamdChange {
//private: // エイリアス
//// Microsoft::WRL::を省略
//	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
//	// DirectX::を省略
//	using XMFLOAT2 = DirectX::XMFLOAT2;
//	using XMFLOAT3 = DirectX::XMFLOAT3;
//	using XMFLOAT4 = DirectX::XMFLOAT4;
//	using XMMATRIX = DirectX::XMMATRIX;
//public:
//	void Init();
//	void Upda();
//	void Draw();
//	void Final();
//	void ShrinkChange();
//	void ShrinkChange();
//
//	const float& GetScale() { return scale; }
//
//	void SetStartChange(bool startchange) { this->startchange = startchange; }
//	void SetendChange(bool endchange) { this->endchange = endchange; }
//private:
//	Sprite* change = nullptr;
//	XMFLOAT2 pos = { 0.0f,0.0f };
//	Texture* wave = nullptr;
//	float scale = 0.0f;
//	bool startchange = false;
//	bool endchange = false;
//};
//

#pragma once
#include"Sprite.h"

class ShrinkChange {
public:
	ShrinkChange();
	void Update();
	void Finalize();
	const void Draw();

	//void EaseScale();
	void Shrink();

	const float& GetScale() { return scale; }

	const int& GetTimer() { return timer; }

	void SetEndChange(bool endchange) { this->endchange = endchange; }
private:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

private:
	//シーン切り替え(縮小の方)
	Sprite* change = nullptr;
	XMFLOAT2 pos = { 640.0f,360.0f, };
	float scale = 1.0f;
	bool endchange = false;
	int timer = 0;
};

