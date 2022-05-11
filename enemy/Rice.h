#pragma once
#include"InterEnemy.h"

class BossEnemy;
class Rice :public InterEnemy {
public:
	Rice();

	void Initialize() override;
	void Finalize() override;
	void Update()override;
	void Demo(int num=0);
	void Draw() override;
	void SetHit(const bool& hit) { this->hit = hit; }
	const bool& GetHit() { return hit; };
	const bool& GetStart() { return start; };
	void SetExP(const XMFLOAT3& exp) { this->exP = exp; }

	void Rebound();
private:
	bool collidePlayer() override;
	bool collideAttackArm() override;
	bool collideArm();
	bool LockOn();
	void Move();
	float speed_y = 3.0f/20.0f;
	const float gravity = speed_y/20.0f;
	float speed_y2 = 3.0f / 20.0f;
	const float gravity2 = speed_y / 20.0f;
	bool stun = false;
	bool hit=false;
	bool start = false;
	XMFLOAT3 exP{};
};

