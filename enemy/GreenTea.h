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
	HotWater* hotWater[50];
	float degree;
	float y = 0.0f;
	int check = false;
	int count =0;
	//‘Ò‹@ƒ‚[ƒVƒ‡ƒ“‚Ì‚½‚ß‚Ì‚â‚Â
	enum Motion {
		Up,
		Down
	};
};