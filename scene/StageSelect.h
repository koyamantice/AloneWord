#pragma once
#include "BaseScene.h"

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
	Input* input = Input::GetInstance();

	enum stage {
		fork,
		boots,
	};
};