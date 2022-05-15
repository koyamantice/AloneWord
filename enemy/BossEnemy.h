#pragma once
#include "InterBoss.h"

class BossEnemy :public InterBoss {
public:
	BossEnemy();

	void Initialize(bool shadow = true) override;
	void Finalize() override;
	void Spec() override;
	void App(int Timer) override;
	void specialDraw() override;

private:
	float vel = 3.0f;
	float y = 0.0f;
	//待機モーションのためのやつ
	enum Motion {
		Up,
		Down
	};
};