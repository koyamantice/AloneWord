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
	Player* player = nullptr;
	Sprite* comment[10];
	DebugCamera* camera = { nullptr };
	XMFLOAT2 sca{};
	enum {
		endText1,
		endText2,
		endText3,
		endText4,
		endText5,
		endText6,
		endText7,
		endText8,
		endText9,
		endText10,
	};
	int ClearTimer = 0;
	int nowText = 0;
	int nowTimer = 0;
	bool closeT = false;
	bool openT = false;
	bool open = false;
	bool close = false;
};

