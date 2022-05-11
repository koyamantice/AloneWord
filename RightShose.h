#pragma once
#include "InterBoss.h"
#include "LeftShose.h"

class RightShose :public InterBoss{
public:
	RightShose();

	void Initialize() override;
	void Finalize() override;
	void Spec() override;
	void App(int Timer) override;
	void specialDraw() override;
	void SetAct(LeftShose* leftshose);
	bool HitShose(LeftShose* leftshose);
private:

	float y = 0.0f;
	//ë“ã@ÉÇÅ[ÉVÉáÉìÇÃÇΩÇﬂÇÃÇ‚Ç¬
	enum Motion {
		Up,
		Down
	};

	bool Attack = false;
	
	enum Hit {
		HitNot,
		HitUp,
		HitDown,
		HitRight,
		HitLeft
	};
	double speedX = 0.0f;
	double speedZ = 0.0f;
	int MoveCount = 0;
	bool LeftAct = false;
};