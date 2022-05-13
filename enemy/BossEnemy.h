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

	float y = 0.0f;
	//‘Ò‹@ƒ‚[ƒVƒ‡ƒ“‚Ì‚½‚ß‚Ì‚â‚Â
	enum Motion {
		Up,
		Down
	};
};