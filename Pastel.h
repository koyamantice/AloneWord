#pragma once
#include "InterBoss.h"
#include "Player.h"
#include <array>       // �w�b�_�t�@�C���C���N���[�h
using namespace std;         //  ���O��Ԏw��
class TouchableObject;
class Pastel :public InterBoss {
public:
	Pastel();

	void Initialize() override;
	void Finalize() override;
	void Spec() override;
	void specialDraw() override;
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
	XMFLOAT3 Millpos = {0,0,0};
	array<TouchableObject*, 4> Platformobj;
	Model* Platformmodel = nullptr;
	array<XMFLOAT3, 4> Plapos ={};
	array<bool, 4>SetPlatform = { false };
	array<int, 4> BirthNumber;
	array<Texture*, 4> Plattexture;
};