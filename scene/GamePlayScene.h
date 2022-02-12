#pragma once

#include "BaseScene.h"
#include "Sprite.h"
#include "Object3d.h"

#include<memory>

/// <summary>
/// ゲームプレイシーン
/// </summary>
class GamePlayScene : public BaseScene{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;
	/// <summary>
	/// 終了
	/// </summary>
	void Finalize() override;

	/// <summary>
	/// 毎フレーム更新
	/// </summary>
	void Update() override;
	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

private:
	Model* modelPin = nullptr;
	Object3d *objPin;
	Sprite* sprite = { nullptr };
	Model* modelSkydome = nullptr;
	Object3d* objSkydome = nullptr;
};

