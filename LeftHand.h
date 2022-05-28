#pragma once
#include "InterBoss.h"
#include "Human.h"
#include <array>   
using namespace std;         //  ���O��Ԏw��
class LeftHand :public InterBoss {
public:
	LeftHand();//�R���X�g���N�^

	void Initialize(bool shadow = true) override;//������
	void Finalize() override;//�J��
	void Spec() override;//�{�X�̍s��
	void App(int Timer) override;//����
	void Roll(int Timer) override;//����
	void End(int Timer) override;//���j
	void specialDraw() override;//���̃V�[���݂̂̕`��
	void SetAct(Human* human);
	bool collideMottiPlayer(Player* player);
private:

	enum Hit {
		HitNot,
		HitUp,
		HitDown,
		HitRight,
		HitLeft
	};
	enum state {
		Open,
		Close,
	};
	int stateNumber = 0;
	Model* hand_closemodel = nullptr;
	double speedX = 0.0f;
	double speedZ = 0.0f;
	int MoveCount = 0;
	bool Attack = false;

};