#pragma once

class SceneManager;
#include "DirectXCommon.h"
/// <summary>
/// �V�[���K��
/// </summary>
class BaseScene {
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

