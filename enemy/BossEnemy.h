#pragma once
#include "InterBoss.h"

class BossEnemy :public InterBoss {
public:
	BossEnemy();

	void Initialize() override;
	void Finalize() override;
	void Spec() override;
	void specialDraw() override;

private:

	float y = 0.0f;
	//�ҋ@���[�V�����̂��߂̂��
	enum Motion {
		Up,
		Down
	};
};