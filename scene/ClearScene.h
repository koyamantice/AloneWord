#pragma once
#include "Sprite.h"
#include "Object3d.h"
#include "BaseScene.h"
#include "BossEnemy.h"
#include "GreenTea.h"
#include "LeftShose.h"
#include "Rightshose.h"
#include "pastel.h"
#include "LeftHand.h"
#include "RightHand.h"
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
	Sprite* roll[9];
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
	enum {
		endrollText1,
		endrollText2,
		endrollText3,
		endrollText4,
		endrollText5,
		endrollText6,
		endrollText7,
		endrollText8,
		endrollText9,
	};
	int ClearTimer = 0;
	int nowText = 0;
	int nowTimer = 0;
	int nowendText = 0;
	int endTimer = 0;
	XMFLOAT4 endColor = { 1.0f,1.0f,1.0f,0.0f };
	bool closeT = false;
	bool openT = false;
	bool open = false;
	bool close = false;
	bool endcloseT = false;
	bool endopenT = false;
	bool endopen = false;
	bool endclose = false;
	bool endroll = true;
	int rollTimer = 0;
	//ボスムービーに登場する敵
	InterBoss* fork = nullptr;
	InterBoss* leftshose = nullptr;
	InterBoss* rightshose = nullptr;
	InterBoss* pastel = nullptr;
	InterBoss* tea = nullptr;
	InterBoss* lefthand = nullptr;
	InterBoss* righthand = nullptr;
};

