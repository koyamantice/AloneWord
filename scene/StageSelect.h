#pragma once
#include "BaseScene.h"
#include "Player.h"
#include "ExpandChange.h"
#include "ShrinkChange.h"
class StageSelect :
    public BaseScene {

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(DirectXCommon* dxCommon) override;
	/// <summary>
	/// �I��
	/// </summary>
	void Finalize()override;
	/// <summary>
	/// ���t���[���X�V
	/// </summary>
	void Update(DirectXCommon* dxCommon)override;
	/// <summary>
	/// �`��
	/// </summary>
	void Draw(DirectXCommon* dxCommon)override;
private:
	bool UICheck();
private:
	//�����o�ϐ�
	//�e�N�X�`���⃂�f��
	Texture* DarkBackGround = nullptr;
	Texture* LightBackGround = nullptr;
	Sprite* select[5]{};
	Sprite* plane[5]{};
	Sprite* Stage1[3]{};
	Sprite* Stage2[3]{};
	Sprite* Stage3[3]{};
	Sprite* Stage4[3]{};
	Sprite* Stage5[3]{};
	Sprite* BlackFilter = nullptr;
	Player* player = nullptr;
	//�e�|�W�V����
	XMFLOAT2 selectP[4]{};
	XMFLOAT2 StageP[5]{};
	Input* input = Input::GetInstance();
	DebugCamera* camera = { nullptr };
	//���o�̂��߂̂���
	ExpandChange* expandchange = false;
	ShrinkChange* shrinkchange = false;
	//�ǂ̃X�e�[�W��I��������
	enum stage {
		No,
		fork,
		Tea,
		Pastel,
		boots,
		human,
	};
	int StageSelectNumber = 0;
	//�C�[�W���O�̂��߂̂���
	float frame = 0;
	float selectframe = 0.0f;
	bool dark = false;
};