#pragma once
#include "InterBoss.h"
#include "Player.h"
class Pastel :public InterBoss {
public:
	Pastel();

	void Initialize() override;
	void Finalize() override;
	void Spec() override;
	void specialDraw() override;
	bool collideAttackArm(Player* player);

private:

	float y = 0.0f;
	//ë“ã@ÉÇÅ[ÉVÉáÉìÇÃÇΩÇﬂÇÃÇ‚Ç¬
	enum Motion {
		Up,
		Down
	};
	int oldpat = 0;
	Object3d* Millobj = nullptr;
	Model* Millmodel = nullptr;
	XMFLOAT3 Millpos;
};