#pragma once
#include "InterBoss.h"
#include "HotWater.h"
class GreenTea :public InterBoss {
public:
	GreenTea();

	void Initialize() override;
	void Finalize() override;
	void Spec() override;
	void specialDraw() override;
private:
	HotWater* hotWater[50];
	XMFLOAT3 AfterPos{};
	float degree=0.0f;
	float y = 0.0f;
	int check = false;
	int count =0;
	//�ҋ@���[�V�����̂��߂̂��
	enum Motion {
		Up,
		Down
	};
};