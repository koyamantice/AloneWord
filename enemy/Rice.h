#pragma once
#include "InterMob.h"

class BossEnemy;
class Rice :public InterMob {
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
	void Follow();
	void Move();
};

