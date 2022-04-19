#pragma once
#include"InterEnemy.h"

class BossEnemy;
class Rice :public InterEnemy {
public:
	Rice();

	void Initialize() override;
	void Finalize() override;
	void Update()override;
	void Draw() override;
private:
	bool collidePlayer() override;
	bool collideAttackArm() override;
	bool collideArm();
	bool LockOn();
	void Move();
	float speed_y = 3.0f/20.0f;
	const float gravity = speed_y/20.0f;

};

