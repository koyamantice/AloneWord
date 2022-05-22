#pragma once
#include "InterBoss.h"
#include "Human.h"

class LeftHand :public InterBoss {
public:
	LeftHand();//�R���X�g���N�^

	void Initialize(bool shadow = true) override;//������
	void Finalize() override;//�J��
	void Spec() override;//�{�X�̍s��
	void App(int Timer) override;//����
	void End(int Timer) override;//���j
	void specialDraw() override;//���̃V�[���݂̂̕`��
	void SetAct(Human* human);
private:
	enum state {
		Open,
		Close,
	};

	int stateNumber = 0;

	Model* hand_closemodel = nullptr;
};