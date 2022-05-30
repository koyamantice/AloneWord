#pragma once
#include "SceneManager.h"
#include "GreenTea.h"
#include "HotWater.h"
#include "UI.h"
#include <array>       // �w�b�_�t�@�C���C���N���[�h

using namespace std;         //  ���O��Ԏw��
/// <summary>
/// �Q�[���v���C�V�[��
/// </summary>
const int ThirdEnemyMax = 5;
class CollisionManager;
class TouchableObject;
class ThirdBoss : public BaseScene {
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
	Model* modelJstyle = nullptr;
	Object3d* objJstyle;
	Texture* limit = nullptr;
	//�J�����֌W
	DebugCamera* camera = { nullptr };
	//���ꂼ��̃N���X�̂���
	Player* player = nullptr;
	array<Effect*, 60> effect;
	array<Rice*, 10> enemy;
	InterBoss* bossenemy = nullptr;
	//std::array<std::array<Exp*, 5>, 5> exp;
	float weight = 0;
	UI* ui = nullptr;
	ParticleManager* particleMan = nullptr;
	ExpandChange* expandchange = nullptr;
};


