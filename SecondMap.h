#pragma once
#include "BaseScene.h"
#include "LeftShose.h"
#include "Collision.h"
#include "Spawning.h"
#include "UI.h"
#include <array>       // �w�b�_�t�@�C���C���N���[�h
using namespace std;         //  ���O��Ԏw��
class CollisionManager;
class TouchableObject;
/// <summary>
/// �Q�[���v���C�V�[��
/// </summary>
const int SecondSpawn = 3;
class SecondMap : public BaseScene {

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
	void Pause(const int& Timer);
private:
	XMFLOAT3 cameraPos = { 0.0f,0.0f,0.0f };
	Model* modelFloor = nullptr;
	Object3d* objFloor;

	Model* modelSecondMap = nullptr;
	TouchableObject* objSecondMap;
	UI* ui = nullptr;

	//�o���P�[�h(��)
	array<Model*, 4> modelBlock;
	array<Object3d*, 4> objBlock;
	array<XMFLOAT3, 4> BlockRotation;

	DebugCamera* camera = { nullptr };
	Texture* limit = nullptr;
	Player* player = nullptr;
	array<Rice*, 10> enemy;
	Warp* warp = nullptr;
	//BossEnemy* bossenemy = nullptr;
	array<Spawning*, SecondSpawn> spawing;
	ParticleManager* particleMan = nullptr;
	bool start = false;
	bool Clear = false;
	int a = 0;
	CollisionManager* collisionManager = nullptr;
	bool pause = false;
	int wait = 0;
	int set = 0;
};

