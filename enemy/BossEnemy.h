#pragma once
#include "InterBoss.h"

class BossEnemy :public InterBoss {
public:
	BossEnemy();
	void Initialize(bool shadow = true) override;//������
	void Finalize() override;//�J��
	void Spec() override;//�{�X�̍s��
	void App(int Timer) override;//����
	void Roll(int Timer) override;//����
	void End(int Timer) override;//���j
	void specialDraw() override;//���̃V�[���݂̂̕`��

private:
	float vel = 3.0f;
	float y = 0.0f;
	//�ҋ@���[�V�����̂��߂̂��
	enum Motion {
		Up,
		Down
	};
};