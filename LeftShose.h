#pragma once
#include "InterBoss.h"
#include "Foot.h"

class LeftShose :public InterBoss {
public:
	LeftShose();//�R���X�g���N�^

	void Initialize(bool shadow = true) override;//������
	void Finalize() override;//�J��
	void Spec() override;//�{�X�̍s��
	void App(int Timer) override;//����
	void Roll(int Timer) override;//����
	void End(int Timer) override;//���j
	void specialDraw() override;//���̃V�[���݂̂̕`��
	void SetAct(Foot* foot);
	void Follow();
	//�����Ƀp�[�e�B�N��
	void BirthParticle();
public:
	//�Ǐ]�̂��߂̂��
	int FollowTimer = 0;
	XMFLOAT2 vel{};
	enum State {
		Down,
		Up,
	};
	int StateNumber = 0;
};