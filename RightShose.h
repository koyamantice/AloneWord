#pragma once
#include "InterBoss.h"

class RightShose :public InterBoss {
public:
	RightShose();

	void Initialize() override;
	void Finalize() override;
	void Spec() override;
private:

	float y = 0.0f;
	//待機モーションのためのやつ
	enum Motion {
		Up,
		Down
	};

};