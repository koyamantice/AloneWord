#pragma once
#include "SceneManager.h"
#include "Sprite.h"
#include "Object3d.h"
/// <summary>
/// タイトルシーン
/// </summary>

class TitleScene : public BaseScene {
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
		Sprite* sprite = { nullptr };
};

