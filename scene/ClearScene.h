#pragma once
#include "Sprite.h"
#include "Object3d.h"
#include "BaseScene.h"
/// タイトルシーン
class ClearScene : public BaseScene {
public:
	/// 初期化
	void Initialize(DirectXCommon* dxCommon) override;
	/// 終了
	void Finalize() override;
	/// 毎フレーム更新
	void Update(DirectXCommon* dxCommon) override;
	/// 描画
	void Draw(DirectXCommon* dxCommon) override;

private://メンバ変数
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

