#pragma once
#include "BaseScene.h"
#include "LeftShose.h"
#include "RightShose.h"
#include "UI.h"
#include "Foot.h"
#include <array>       // �w�b�_�t�@�C���C���N���[�h
using namespace std;         //  ���O��Ԏw��
/// <summary>
/// �Q�[���v���C�V�[��
/// </summary>
const int SecondBossEnemyMax = 10;
class CollisionManager;
class TouchableObject;
class SecondBoss : public BaseScene {
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
	Model* modelEntrance = nullptr;
	Object3d* objEntrance;
	//�J����
	DebugCamera* camera = { nullptr };
	//�e�N���X�̂��߂̂���
	Player* player = nullptr;
	array<Effect*, 40> effect;
	array<Rice*, 6> enemy;
	LeftShose* leftshose = nullptr;
	RightShose* rightshose = nullptr;
	Foot* foot = nullptr;
	//std::array<std::array<Exp*, 6>, 5> exp;
	
	UI* ui = nullptr;
	ParticleManager* particleMan = nullptr;
	ExpandChange* expandchange = nullptr;
	int DethRight = 0;
	int DethLeft = 0;
	/*int DeadLeft = 0;
	int DeadRight = 0;
	float weight = 0;*/
};

