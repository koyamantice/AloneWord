#pragma once
#include "BaseScene.h"
#include "Player.h"
#include "SceneChange.h"
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
	Sprite* BackGround = nullptr;
	Sprite* select[4]{};
	XMFLOAT2 selectP[4]{};
	Sprite* plane[5]{};
	float frame=0;
	Input* input = Input::GetInstance();
	DebugCamera* camera = { nullptr };
	Player* player=nullptr;
	SceneChange* scenechange = false;
	enum stage {
		fork,
		boots,
	};
	bool UICheck();
};