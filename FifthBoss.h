#pragma once
#include "BaseScene.h"
#include "LeftHand.h"
#include "RightHand.h"
#include"LeftHumanWave.h"
#include"RightHumanWave.h"
#include "Human.h"
#include "UI.h"
#include <array>       // �w�b�_�t�@�C���C���N���[�h
using namespace std;         //  ���O��Ԏw��
/// <summary>
/// �Q�[���v���C�V�[��
/// </summary>
const int FifthBossEnemyMax = 10;
class CollisionManager;
class TouchableObject;
class FifthBoss : public BaseScene {
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(DirectXCommon* dxCommon) override;
	/// <summary>
	/// �I��
	/// </summary>
	void Finalize() override;

	/// <summary>
	/// ���t���[���X�V
	/// </summary>
	void Update(DirectXCommon* dxCommon) override;
	/// <summary>
	/// �`��
	/// </summary>
	void Draw(DirectXCommon* dxCommon) override;

private:
	//�I�u�W�F�N�g��e�N�X�`��
	Model* modelFloor = nullptr;
	Object3d* objFloor;
	Model* modelBossMap = nullptr;
	TouchableObject* objBossMap;
	Model* modelSphere = nullptr;
	Object3d* objSphere;
	Model* modelBedroom = nullptr;
	Object3d* objBedroom;
	FBXModel* model1 = nullptr;
	FBXObject3d* object1 = nullptr;
	Texture* limit = nullptr;
	//�J����
	DebugCamera* camera = { nullptr };
	//�e�N���X�̂��߂̂���
	Player* player = nullptr;
	array<Effect*, 40> effect;
	array<InterEnemy*, 6> enemy;
	LeftHand* lefthand = nullptr;
	RightHand* righthand = nullptr;
	RightHumanWave* rightwave = nullptr;
	LeftHumanWave* leftwave = nullptr;
	Human* human = nullptr;
	//std::array<std::array<Exp*, 6>, 5> exp;

	UI* ui = nullptr;
	CollisionManager* collisionManager = nullptr;
	ParticleManager* particleMan = nullptr;
	ExpandChange* expandchange = nullptr;
	bool act = false;
	int DethRight = 0;
	int DethLeft = 0;
};

