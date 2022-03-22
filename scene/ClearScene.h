#pragma once
#include "Sprite.h"
#include "Object3d.h"
#include "BaseScene.h"
/// �^�C�g���V�[��
class ClearScene : public BaseScene {
public:
	/// ������
	void Initialize(DirectXCommon* dxCommon) override;
	/// �I��
	void Finalize() override;
	/// ���t���[���X�V
	void Update(DirectXCommon* dxCommon) override;
	/// �`��
	void Draw(DirectXCommon* dxCommon) override;

private://�����o�ϐ�
	Sprite* sprite = { nullptr };
};
