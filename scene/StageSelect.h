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
	bool UICheck();
private:
	//メンバ変数
	//テクスチャやモデル
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
	//各ポジション
	XMFLOAT2 selectP[4]{};
	XMFLOAT2 StageP[5]{};
	Input* input = Input::GetInstance();
	DebugCamera* camera = { nullptr };
	//演出のためのもの
	ExpandChange* expandchange = false;
	ShrinkChange* shrinkchange = false;
	//どのステージを選択したか
	enum stage {
		No,
		fork,
		Tea,
		Pastel,
		boots,
		human,
	};
	int StageSelectNumber = 0;
	//イージングのためのもの
	float frame = 0;
	float selectframe = 0.0f;
	bool dark = false;
};