#pragma once
#include "InterBoss.h"
#include "LeftShose.h"

class RightShose :public InterBoss{
public:
	RightShose();

	void Initialize() override;
	void Finalize() override;
	void Spec() override;
	void SetAct(LeftShose* leftshose);
private:

	float y = 0.0f;
	//待機モーションのためのやつ
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