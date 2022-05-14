#pragma once
#include "InterBoss.h"
#include "HotWater.h"
class GreenTea :public InterBoss {
public:
	GreenTea();

	void Initialize(bool shadow = true) override;
	void Finalize() override;
	void Spec() override;
	void App(int Timer) override;
	void specialDraw() override;
private:
	HotWater* hotWater[50];
	Sprite* meter[2]{};
	XMFLOAT3 AfterPos{};
	float degree=0.0f;
	float y = 0.0f;
	int check = false;
	int count =0;
	float vel = 3;
	float Zma=45;
	float Zmi=-45;
	//ë“ã@ÉÇÅ[ÉVÉáÉìÇÃÇΩÇﬂÇÃÇ‚Ç¬
	enum Motion {
		Up,
		Down
	};
};