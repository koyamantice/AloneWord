#pragma once
#include "InterBoss.h"

class LeftShose :public InterBoss {
public:
	LeftShose();

	void Initialize() override;
	void Finalize() override;
	void Spec() override;
	void specialDraw() override;

private:

	float y = 0.0f;
	//待機モーションのためのやつ
	enum Motion {
		Up,
		Down
	};
	

};