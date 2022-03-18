#pragma once

class SceneManager;
#include "DirectXCommon.h"
#include "DebugCamera.h"
#include "LightGroup.h"
#include<memory>
#include "Sprite.h"
#include "FBXObject3d.h"
#include "Object3d.h"
#include "Texture.h"
#include <DirectXMath.h>
#include<memory>

/// <summary>
/// �V�[���K��
/// </summary>
class BaseScene {
protected:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:

	virtual ~BaseScene()=default;

	/// <summary>
	/// ������
	/// </summary>
	virtual void Initialize(DirectXCommon* dxCommon) =0;
	/// <summary>
	/// �I��
	/// </summary>
	virtual void Finalize()=0;
	/// <summary>
	/// ���t���[���X�V
	/// </summary>
	virtual void Update(DirectXCommon* dxCommon)=0;
	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw(DirectXCommon* dxCommon)=0;

};

