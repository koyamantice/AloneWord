<<<<<<< HEAD
﻿//#pragma once
//
//#include <Windows.h>
//#include <wrl.h>
//#include <d3d12.h>
//#include <DirectXMath.h>
//#include <d3dx12.h>
//#include <forward_list>
//
//#include "Camera.h"
//
///// <summary>
///// パーティクルマネージャ
///// </summary>
//class ParticleManager
//{
//private: // エイリアス
//	// Microsoft::WRL::を省略
//	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
//	// DirectX::を省略
//	using XMFLOAT2 = DirectX::XMFLOAT2;
//	using XMFLOAT3 = DirectX::XMFLOAT3;
//	using XMFLOAT4 = DirectX::XMFLOAT4;
//	using XMMATRIX = DirectX::XMMATRIX;
//
//public: // サブクラス
//	// 頂点データ構造体
//	struct VertexPos
//	{
//		XMFLOAT3 pos; // xyz座標
//		float scale; // スケール
//	};
//
//	// 定数バッファ用データ構造体
//	struct ConstBufferData
//	{
//		XMMATRIX mat;	// ビュープロジェクション行列
//		XMMATRIX matBillboard;	// ビルボード行列
//	};
//
//	// パーティクル1粒
//	class Particle
//	{
//		// Microsoft::WRL::を省略
//		template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
//		// DirectX::を省略
//		using XMFLOAT2 = DirectX::XMFLOAT2;
//		using XMFLOAT3 = DirectX::XMFLOAT3;
//		using XMFLOAT4 = DirectX::XMFLOAT4;
//		using XMMATRIX = DirectX::XMMATRIX;
//
//	public:
//		// 座標
//		XMFLOAT3 position = {};
//		// 速度
//		XMFLOAT3 velocity = {};
//		// 加速度
//		XMFLOAT3 accel = {};
//		// 色
//		XMFLOAT3 color = {};
//		// スケール
//		float scale = 1.0f;
//		// 回転
//		float rotation = 0.0f;
//		// 初期値
//		XMFLOAT3 s_color = {};
//		float s_scale = 1.0f;
//		float s_rotation = 0.0f;
//		// 最終値
//		XMFLOAT3 e_color = {};
//		float e_scale = 0.0f;
//		float e_rotation = 0.0f;
//		// 現在フレーム
//		int frame = 0;
//		// 終了フレーム
//		int num_frame = 0;
//	};
//
//private: // 定数
//	static const int vertexCount = 65536;		// 頂点数
//
//public:// 静的メンバ関数
//	static ParticleManager* GetInstance();
//
//public: // メンバ関数	
//	/// <summary>
//	/// 初期化
//	/// </summary>
//	/// <returns></returns>
//	void Initialize(ID3D12Device* device);
//	/// <summary>
//	/// 毎フレーム処理
//	/// </summary>
//	void Update();
//
//	/// <summary>
//	/// 描画
//	/// </summary>
//	void Draw(ID3D12GraphicsCommandList* cmdList);
//
//	/// <summary>
//	/// カメラのセット
//	/// </summary>
//	/// <param name="camera">カメラ</param>
//	inline void SetCamera(Camera* camera) { this->camera = camera; }
//
//	/// <summary>
//	/// パーティクルの追加
//	/// </summary>
//	/// <param name="life">生存時間</param>
//	/// <param name="position">初期座標</param>
//	/// <param name="velocity">速度</param>
//	/// <param name="accel">加速度</param>
//	/// <param name="start_scale">開始時スケール</param>
//	/// <param name="end_scale">終了時スケール</param>
//	void Add(int life, XMFLOAT3 position, XMFLOAT3 velocity, XMFLOAT3 accel, float start_scale, float end_scale);
//
//	/// <summary>
//	/// デスクリプタヒープの初期化
//	/// </summary>
//	/// <returns></returns>
//	void InitializeDescriptorHeap();
//
//	/// <summary>
//	/// グラフィックパイプライン生成
//	/// </summary>
//	/// <returns>成否</returns>
//	void InitializeGraphicsPipeline();
//
//	/// <summary>
//	/// テクスチャ読み込み
//	/// </summary>
//	/// <returns>成否</returns>
//	void LoadTexture();
//
//	/// <summary>
//	/// モデル作成
//	/// </summary>
//	void CreateModel();
//
//private: // メンバ変数
//	// デバイス
//	ID3D12Device* device = nullptr;
//	// デスクリプタサイズ
//	UINT descriptorHandleIncrementSize = 0u;
//	// ルートシグネチャ
//	ComPtr<ID3D12RootSignature> rootsignature;
//	// パイプラインステートオブジェクト
//	ComPtr<ID3D12PipelineState> pipelinestate;
//	// デスクリプタヒープ
//	ComPtr<ID3D12DescriptorHeap> descHeap;
//	// 頂点バッファ
//	ComPtr<ID3D12Resource> vertBuff;
//	// テクスチャバッファ
//	ComPtr<ID3D12Resource> texbuff;
//	// シェーダリソースビューのハンドル(CPU)
//	CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
//	// シェーダリソースビューのハンドル(CPU)
//	CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;
//	// 頂点バッファビュー
//	D3D12_VERTEX_BUFFER_VIEW vbView;
//	// 定数バッファ
//	ComPtr<ID3D12Resource> constBuff;
//	// パーティクル配列
//	std::forward_list<Particle> particles;
//	// カメラ
//	Camera* camera = nullptr;
//private:
//	ParticleManager() = default;
//	ParticleManager(const ParticleManager&) = delete;
//	~ParticleManager() = default;
//	ParticleManager& operator=(const ParticleManager&) = delete;
//};
//
=======
#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include <forward_list>

#include "Camera.h"

/// <summary>
/// �p�[�e�B�N���}�l�[�W��
/// </summary>
class ParticleManager
{
private: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public: // �T�u�N���X
	// ���_�f�[�^�\����
	struct VertexPos
	{
		XMFLOAT3 pos; // xyz���W
		float scale; // �X�P�[��
	};

	// �萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferData
	{
		XMMATRIX mat;	// �r���[�v���W�F�N�V�����s��
		XMMATRIX matBillboard;	// �r���{�[�h�s��
	};

	// �p�[�e�B�N��1��
	class Particle
	{
		// Microsoft::WRL::���ȗ�
		template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
		// DirectX::���ȗ�
		using XMFLOAT2 = DirectX::XMFLOAT2;
		using XMFLOAT3 = DirectX::XMFLOAT3;
		using XMFLOAT4 = DirectX::XMFLOAT4;
		using XMMATRIX = DirectX::XMMATRIX;

	public:
		// ���W
		XMFLOAT3 position = {};
		// ���x
		XMFLOAT3 velocity = {};
		// �����x
		XMFLOAT3 accel = {};
		// �F
		XMFLOAT3 color = {};
		// �X�P�[��
		float scale = 1.0f;
		// ��]
		float rotation = 0.0f;
		// �����l
		XMFLOAT3 s_color = {};
		float s_scale = 1.0f;
		float s_rotation = 0.0f;
		// �ŏI�l
		XMFLOAT3 e_color = {};
		float e_scale = 0.0f;
		float e_rotation = 0.0f;
		// ���݃t���[��
		int frame = 0;
		// �I���t���[��
		int num_frame = 0;
	};

private: // �萔
	static const int vertexCount = 65536;		// ���_��

public:// �ÓI�����o�֐�
	static ParticleManager* GetInstance();

public: // �����o�֐�	
	/// <summary>
	/// ������
	/// </summary>
	/// <returns></returns>
	void Initialize(ID3D12Device* device);
	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// �J�����̃Z�b�g
	/// </summary>
	/// <param name="camera">�J����</param>
	inline void SetCamera(Camera* camera) { this->camera = camera; }

	/// <summary>
	/// �p�[�e�B�N���̒ǉ�
	/// </summary>
	/// <param name="life">��������</param>
	/// <param name="position">�������W</param>
	/// <param name="velocity">���x</param>
	/// <param name="accel">�����x</param>
	/// <param name="start_scale">�J�n���X�P�[��</param>
	/// <param name="end_scale">�I�����X�P�[��</param>
	void Add(int life, XMFLOAT3 position, XMFLOAT3 velocity, XMFLOAT3 accel, float start_scale, float end_scale);

	/// <summary>
	/// �f�X�N���v�^�q�[�v�̏�����
	/// </summary>
	/// <returns></returns>
	void InitializeDescriptorHeap();

	/// <summary>
	/// �O���t�B�b�N�p�C�v���C������
	/// </summary>
	/// <returns>����</returns>
	void InitializeGraphicsPipeline();

	/// <summary>
	/// �e�N�X�`���ǂݍ���
	/// </summary>
	/// <returns>����</returns>
	void LoadTexture();

	/// <summary>
	/// ���f���쐬
	/// </summary>
	void CreateModel();

private: // �����o�ϐ�
	// �f�o�C�X
	ID3D12Device* device = nullptr;
	// �f�X�N���v�^�T�C�Y
	UINT descriptorHandleIncrementSize = 0u;
	// ���[�g�V�O�l�`��
	ComPtr<ID3D12RootSignature> rootsignature;
	// �p�C�v���C���X�e�[�g�I�u�W�F�N�g
	ComPtr<ID3D12PipelineState> pipelinestate;
	// �f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> descHeap;
	// ���_�o�b�t�@
	ComPtr<ID3D12Resource> vertBuff;
	// �e�N�X�`���o�b�t�@
	ComPtr<ID3D12Resource> texbuff;
	// �V�F�[�_���\�[�X�r���[�̃n���h��(CPU)
	CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
	// �V�F�[�_���\�[�X�r���[�̃n���h��(CPU)
	CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;
	// ���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView;
	// �萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuff;
	// �p�[�e�B�N���z��
	std::forward_list<Particle> particles;
	// �J����
	Camera* camera = nullptr;
private:
	ParticleManager() = default;
	ParticleManager(const ParticleManager&) = delete;
	~ParticleManager() = default;
	ParticleManager& operator=(const ParticleManager&) = delete;
};

>>>>>>> master
