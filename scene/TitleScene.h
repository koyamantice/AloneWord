#pragma once
#include "SceneManager.h"
#include "ExpandChange.h"
/// <summary>
/// タイトルシーン
/// </summary>

class TitleScene : public BaseScene {
	public:

		/// <summary>
		/// 初期化
		/// </summary>
		void Initialize(DirectXCommon* dxCommon) override;
		/// <summary>
		/// 終了
		/// </summary>
		void Finalize() override;

		/// <summary>
		/// 毎フレーム更新
		/// </summary>
		void Update(DirectXCommon* dxCommon) override;
		/// <summary>
		/// 描画
		/// </summary>
		void Draw(DirectXCommon* dxCommon) override;

	private:
		Sprite* sprite = { nullptr };
		ExpandChange* expandchange = nullptr;

		enum Select {
			Start,
			Select,
		};

		int SelectNumber = 0;
};

