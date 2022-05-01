#pragma once
#include "InterBoss.h"
#include "HotWater.h"
class GreenTea :public InterBoss {
public:
	GreenTea();

	void Initialize() override;
	void Finalize() override;
	void Spec() override;
	void specialDraw() override;
private:
	HotWater* hotWater=nullptr;
	float degree;
	float y = 0.0f;
	int check = false;
	//待機モーションのためのやつ
	enum Motion {
		Up,
		Down
	};
};