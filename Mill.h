#pragma once
#include "InterBoss.h"
#include "Player.h"

class Mill :public InterBoss {
public:
	Mill();

	void Initialize() override;
	void Finalize() override;
	void Spec() override;
	void specialDraw() override;
	bool collideAttackArm(Player* player);
	const float& GetHaveEnemy() { return haveEnemy; }
	const bool& GetHaveTimer() { return haveTimer; }
private:

	float y = 0.0f;
	//‘Ò‹@ƒ‚[ƒVƒ‡ƒ“‚Ì‚½‚ß‚Ì‚â‚Â
	enum Motion {
		Up,
		Down
	};
	float haveEnemy = 0.0f;
	int haveTimer = 0;
};