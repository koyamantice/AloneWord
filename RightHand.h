#pragma once
#include "InterBoss.h"
#include "Human.h"

class RightHand :public InterBoss {
public:
	RightHand();

	void Initialize(bool shadow = true) override;//������
	void Finalize() override;//�J��
	void Spec() override;//�{�X�̍s��
	void App(int Timer) override;//����
	void End(int Timer) override;//���j
	void specialDraw() override;//���̃V�[���݂̂̕`��
	void SetAct(Human* human);
private:

	float y = 0.0f;
	//�ҋ@���[�V�����̂��߂̂��
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