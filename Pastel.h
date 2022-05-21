#pragma once
#include "InterBoss.h"
#include "Player.h"
#include <array>       // �w�b�_�t�@�C���C���N���[�h
using namespace std;         //  ���O��Ԏw��
class TouchableObject;
class Pastel :public InterBoss {
public:
	Pastel();

	void Initialize(bool shadow = true) override;//������
	void Finalize() override;//�J��
	void Spec() override;//�{�X�̍s��
	void App(int Timer) override;//����
	void End(int Timer) override;//���j
	void specialDraw() override;//���̃V�[���݂̂̕`��
	void MillUpdate();
	bool collideAttackArm(Player* player);

private:

	float y = 0.0f;
	//�ҋ@���[�V�����̂��߂̂��
	enum Motion {
		Up,
		Down
	};
	int oldpat = 0;
	//�{�X�ł͂Ȃ��I�u�W�F�N�g�p
	Object3d* Millobj = nullptr;
	Model* Millmodel = nullptr;
	Object3d* Mottiobj = nullptr;
	Model* Mottimodel = nullptr;
	XMFLOAT3 Millpos = {0,0,0};
	XMFLOAT3 MottiScale = { 0.0f,0.0f,0.0f };
	array<TouchableObject*, 4> Platformobj;
	Model* Platformmodel = nullptr;
	array<XMFLOAT3, 4> Plapos ={};
	array<bool, 4>SetPlatform = { false };
	array<int, 4> BirthNumber;
	array<Texture*, 4> Plattexture;
};