#pragma once
#include "InterBoss.h"
#include "Player.h"

class Mill :public InterBoss {
public:
	Mill();

	void Initialize() override;
	void Finalize() override;
	void Spec() override;
	void App() override;
	void specialDraw() override;
	bool collideAttackArm(Player* player);

private:

	float y = 0.0f;
	//�ҋ@���[�V�����̂��߂̂��
	enum Motion {
		Up,
		Down
	};
	
};