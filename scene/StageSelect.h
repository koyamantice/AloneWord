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
	Texture* Stage1[3]{};
	Texture* Stage2[3]{};
	Texture* Stage3[3]{};
	Texture* Stage4[3]{};
	Texture* Stage5[3]{};
	Sprite* BlackFilter = nullptr;
	Player* player = nullptr;
	//�e�|�W�V����
	XMFLOAT2 selectP[4]{};
	XMFLOAT3 StageP[5]{};
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
	float sinFrame = 0;
	void SinMove(int selectNum,int planeNum);
	float vel = 0.02f;
	float selectframe = 0.0f;
	bool dark = false;
};