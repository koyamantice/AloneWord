#pragma once
#include "BaseScene.h"
#include "BossEnemy.h"
#include "Collision.h"
/// <summary>
/// �Q�[���v���C�V�[��
/// </summary>
const int StartEnemyMax = 7;
class StartMap : public BaseScene{
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
	Model* modelGround = nullptr;
	Object3d* objGround;

	Model* modelground = nullptr;
	Object3d* objground;

	FBXModel* model1 = nullptr;
	FBXObject3d* object1 = nullptr;
	DebugCamera* camera = { nullptr };
	Texture* limit = nullptr;
	Player* player = nullptr;
	Enemy* enemy[StartEnemyMax] = { nullptr };
	BossEnemy* bossenemy = nullptr;
};

