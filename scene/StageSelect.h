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
	Texture* BackGround = nullptr;
	Sprite* select[5]{};
	XMFLOAT2 selectP[4]{};
	Sprite* plane[5]{};
	Sprite* BlackFilter = nullptr;
	float frame=0;
	Input* input = Input::GetInstance();
	DebugCamera* camera = { nullptr };
	Player* player=nullptr;
	ExpandChange* expandchange = false;
	ShrinkChange* shrinkchange = false;
	enum stage {
		No,
		fork,
		Tea,
		Pastel,
		boots,
	};
	int StageSelectNumber = 0;
	float selectframe = 0.0f;
	bool UICheck();
};