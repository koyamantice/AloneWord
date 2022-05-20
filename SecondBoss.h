#pragma once
#include "BaseScene.h"
#include "LeftShose.h"
#include "RightShose.h"
#include "UI.h"
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
	XMFLOAT3 cameraPos = { 0.0f,0.0f,0.0f };
	Model* modelFloor = nullptr;
	Object3d* objFloor;

	Model* modelBossMap = nullptr;
	TouchableObject* objBossMap;

	Model* modelSphere = nullptr;
	Object3d* objSphere;

	FBXModel* model1 = nullptr;
	FBXObject3d* object1 = nullptr;
	DebugCamera* camera = { nullptr };
	Texture* limit = nullptr;
	Player* player = nullptr;
	array<Effect*, 40> effect;
	array<InterEnemy*, 6> enemy;
	LeftShose* leftshose = nullptr;
	RightShose* rightshose = nullptr;
	//std::array<std::array<Exp*, 6>, 5> exp;
	float weight = 0;
	UI* ui = nullptr;
	CollisionManager* collisionManager = nullptr;
	ParticleManager* particleMan = nullptr;
	ExpandChange* expandchange = nullptr;
};

