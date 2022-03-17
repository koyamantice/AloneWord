#pragma once

#include "BaseScene.h"
#include "Sprite.h"
#include "Object3d.h"
#include "DebugCamera.h"
#include "LightGroup.h"
#include "FBXObject3d.h"
#include "Texture.h"
#include <DirectXMath.h>
#include<memory>
#include "Player.h"
#include "Enemy.h"
#include "BossEnemy.h"
#include "Easing.h"
/// <summary>
/// �Q�[���v���C�V�[��
/// </summary>
const int EnemyMax = 13;
class StartMap : public BaseScene {
private:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

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
	Model* modelSara = nullptr;
	Object3d* objSara;
	FBXModel* model1 = nullptr;
	FBXObject3d* object1 = nullptr;
	DebugCamera* camera = { nullptr };
	LightGroup* lightGroup = nullptr;
	float ambientColor0[3] = { 1,1,1 };

	Player* player = nullptr;
	Enemy* enemy[EnemyMax] = { nullptr };
	BossEnemy* bossenemy = nullptr;
	// �������������l
	float lightDir0[3] = { 0,0,1 };
	float lightColor0[3] = { 1,0,0 };

	float lightDir1[3] = { 0,1,0 };
	float lightColor1[3] = { 0,1,0 };

	float lightDir2[3] = { 1,0,0 };
	float lightColor2[3] = { 0,0,1 };

	float pointLightPos[3] = { 0,0,0 };
	float pointLightColor[3] = { 1,1,1 };
	float pointLightAtten[3] = { 0.3f,0.1f,0.1f };
};

