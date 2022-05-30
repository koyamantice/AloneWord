#pragma once
#include "Texture.h"
#include "Object3d.h"
#include"Player.h"
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
	void SetPlayer(Player* player) { this->player = player; }
	void Collide();
	void FollowCollide();
	void Set(const XMFLOAT3& pos);
	void Follow(const XMFLOAT3& pos);
	void AppeaSet(const XMFLOAT3& pos);
	void Final();
	const bool& GetIsAlive() { return IsAlive; };
private:
	int collide=0;
	Player* player;
	Object3d* water = nullptr;
	Texture* hot=nullptr;
	float radius=1.0f;
	float frame = 0;
	bool shrink = false;
	XMFLOAT3 sca{};
	XMFLOAT3 watersca{};
	XMFLOAT3 vel{};
	XMFLOAT3 pos{};
	bool onGround=false;
	bool IsAlive = false;
	bool hit;
	bool StopFollow = false;
	int action = 0;
	int followTimer = 0;
	
};

