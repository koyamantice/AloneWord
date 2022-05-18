#pragma once
#include "BaseScene.h"
#include "Player.h"
#include "ExpandChange.h"
#include "ShrinkChange.h"
class StageSelect :
    public BaseScene {

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(DirectXCommon* dxCommon) override;
	/// <summary>
	/// 終了
	/// </summary>
	void Finalize()override;
	/// <summary>
	/// 毎フレーム更新
	/// </summary>
	void Update(DirectXCommon* dxCommon)override;
	/// <summary>
	/// 描画
	/// </summary>
	void Draw(DirectXCommon* dxCommon)override;
private:
	Sprite* BackGround = nullptr;
	Sprite* select[5]{};
	XMFLOAT2 selectP[4]{};
	Sprite* plane[5]{};
	float frame=0;
	Input* input = Input::GetInstance();
	DebugCamera* camera = { nullptr };
	Player* player=nullptr;
	ExpandChange* expandchange = false;
	ShrinkChange* shrinkchange = false;
	enum stage {
		fork,
		boots,
	};
	bool UICheck();
};