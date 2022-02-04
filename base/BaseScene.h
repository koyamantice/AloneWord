#pragma once

class SceneManager;

/// <summary>
/// シーン規定
/// </summary>
class BaseScene {
public:
	virtual ~BaseScene()=default;

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize() =0;
	/// <summary>
	/// 終了
	/// </summary>
	virtual void Finalize()=0;
	/// <summary>
	/// 毎フレーム更新
	/// </summary>
	virtual void Update()=0;
	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw()=0;

};

