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
	//�ҋ@���[�V�����̂��߂̂��
	enum Motion {
		Up,
		Down
	};
	int Count = 0;
};