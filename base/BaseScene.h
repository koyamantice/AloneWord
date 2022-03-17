#pragma once

class SceneManager;
#include "DirectXCommon.h"
#include "DebugCamera.h"
#include "LightGroup.h"
#include<memory>
#include "Sprite.h"
#include "FBXObject3d.h"
#include "Object3d.h"
#include "Texture.h"
#include <DirectXMath.h>
#include<memory>

/// <summary>
/// シーン規定
/// </summary>
class BaseScene {
protected:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:

	virtual ~BaseScene()=default;

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize(DirectXCommon* dxCommon) =0;
	/// <summary>
	/// 終了
	/// </summary>
	virtual void Finalize()=0;
	/// <summary>
	/// 毎フレーム更新
	/// </summary>
	virtual void Update(DirectXCommon* dxCommon)=0;
	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw(DirectXCommon* dxCommon)=0;

};

