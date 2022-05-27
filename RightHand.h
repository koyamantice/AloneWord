#pragma once
#include "InterBoss.h"
#include "Human.h"
#include <array>   
using namespace std;         //  ���O��Ԏw��
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
	bool collideMottiPlayer(Player* player);
private:
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

	enum state {
		Open,
		Close,
	};

	int stateNumber = 0;
	Object3d* hand_closeobj = nullptr;
	Model* hand_closemodel = nullptr;
	int count = 0;
};