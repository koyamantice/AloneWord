#pragma once
#include "InterBoss.h"

class LeftShose :public InterBoss {
public:
	LeftShose();

	void Initialize() override;
	void Finalize() override;
	void Spec() override;
private:

	float y = 0.0f;
	//�ҋ@���[�V�����̂��߂̂��
	enum Motion {
		Up,
		Down
	};
	
};