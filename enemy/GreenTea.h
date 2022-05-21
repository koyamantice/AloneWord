#pragma once
#include "InterBoss.h"
#include "HotWater.h"
#include "Audio.h"
class GreenTea :public InterBoss {
public:
	GreenTea();
	void Initialize(bool shadow = true) override;//������
	void Finalize() override;//�J��
	void Spec() override;//�{�X�̍s��
	void App(int Timer) override;//����
	void End(int Timer) override;//���j
	void specialDraw() override;//���̃V�[���݂̂̕`��
	void AppearDraw();
private:
	HotWater* hotWater[50];
	Sprite* meter[2]{};
	XMFLOAT3 AfterPos{};
	XMFLOAT3 AttackPos = { 0.0f,0.0f,0.0f };
	float degree=0.0f;
	float y = 0.0f;
	int check = false;
	int count =0;
	float vel = 3;
	float Zma=45;
	float Zmi=-45;
	double speedX = 0.0f;
	double speedZ = 0.0f;
	int MoveCount = 0;
	//�ҋ@���[�V�����̂��߂̂��
	enum Motion {
		Up,
		Down
	};

	enum Hit {
		HitNot,
		HitUp,
		HitDown,
		HitRight,
		HitLeft
	};
	bool Attack = false;
};