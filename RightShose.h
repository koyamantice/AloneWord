#pragma once
#include "InterBoss.h"
#include "LeftShose.h"
#include "Foot.h"

class RightShose :public InterBoss{
public:
	RightShose();

	void Initialize(bool shadow = true) override;//������
	void Finalize() override;//�J��
	void Spec() override;//�{�X�̍s��
	void App(int Timer) override;//����
	void End(int Timer) override;//���j
	void specialDraw() override;//���̃V�[���݂̂̕`��
	void SetAct(Foot* foot);
	bool HitShose(LeftShose* leftshose);
	void Follow();
	//�����Ƀp�[�e�B�N��
	void BirthParticle();
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
	int FollowTimer = 0;
	XMFLOAT2 vel{};
};