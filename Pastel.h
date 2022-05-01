#pragma once
#include "InterBoss.h"
#include "Mill.h"
class Pastel :public InterBoss {
public:
	Pastel();

	void Initialize() override;
	void Finalize() override;
	void Spec() override;
	void specialDraw() override;
	void GetOff(Mill* mill);
private:

	float y = 0.0f;
	//待機モーションのためのやつ
	enum Motion {
		Up,
		Down
	};

	bool Off = false;
};