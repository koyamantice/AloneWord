<<<<<<< HEAD
ï»¿//#pragma once
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
///// ãƒ‘ãƒ¼ãƒ†ã‚£ã‚¯ãƒ«ãƒãƒãƒ¼ã‚¸ãƒ£
///// </summary>
//class ParticleManager
//{
//private: // ã‚¨ã‚¤ãƒªã‚¢ã‚¹
//	// Microsoft::WRL::ã‚’çœç•¥
//	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
//	// DirectX::ã‚’çœç•¥
//	using XMFLOAT2 = DirectX::XMFLOAT2;
//	using XMFLOAT3 = DirectX::XMFLOAT3;
//	using XMFLOAT4 = DirectX::XMFLOAT4;
//	using XMMATRIX = DirectX::XMMATRIX;
//
//public: // ã‚µãƒ–ã‚¯ãƒ©ã‚¹
//	// é ‚ç‚¹ãƒ‡ãƒ¼ã‚¿æ§‹é€ ä½“
//	struct VertexPos
//	{
//		XMFLOAT3 pos; // xyzåº§æ¨™
//		float scale; // ã‚¹ã‚±ãƒ¼ãƒ«
//	};
//
//	// å®šæ•°ãƒãƒƒãƒ•ã‚¡ç”¨ãƒ‡ãƒ¼ã‚¿æ§‹é€ ä½“
//	struct ConstBufferData
//	{
//		XMMATRIX mat;	// ãƒ“ãƒ¥ãƒ¼ãƒ—ãƒ­ã‚¸ã‚§ã‚¯ã‚·ãƒ§ãƒ³è¡Œåˆ—
//		XMMATRIX matBillboard;	// ãƒ“ãƒ«ãƒœãƒ¼ãƒ‰è¡Œåˆ—
//	};
//
//	// ãƒ‘ãƒ¼ãƒ†ã‚£ã‚¯ãƒ«1ç²’
//	class Particle
//	{
//		// Microsoft::WRL::ã‚’çœç•¥
//		template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
//		// DirectX::ã‚’çœç•¥
//		using XMFLOAT2 = DirectX::XMFLOAT2;
//		using XMFLOAT3 = DirectX::XMFLOAT3;
//		using XMFLOAT4 = DirectX::XMFLOAT4;
//		using XMMATRIX = DirectX::XMMATRIX;
//
//	public:
//		// åº§æ¨™
//		XMFLOAT3 position = {};
//		// é€Ÿåº¦
//		XMFLOAT3 velocity = {};
//		// åŠ é€Ÿåº¦
//		XMFLOAT3 accel = {};
//		// è‰²
//		XMFLOAT3 color = {};
//		// ã‚¹ã‚±ãƒ¼ãƒ«
//		float scale = 1.0f;
//		// å›è»¢
//		float rotation = 0.0f;
//		// åˆæœŸå€¤
//		XMFLOAT3 s_color = {};
//		float s_scale = 1.0f;
//		float s_rotation = 0.0f;
//		// æœ€çµ‚å€¤
//		XMFLOAT3 e_color = {};
//		float e_scale = 0.0f;
//		float e_rotation = 0.0f;
//		// ç¾åœ¨ãƒ•ãƒ¬ãƒ¼ãƒ 
//		int frame = 0;
//		// çµ‚äº†ãƒ•ãƒ¬ãƒ¼ãƒ 
//		int num_frame = 0;
//	};
//
//private: // å®šæ•°
//	static const int vertexCount = 65536;		// é ‚ç‚¹æ•°
//
//public:// é™çš„ãƒ¡ãƒ³ãƒé–¢æ•°
//	static ParticleManager* GetInstance();
//
//public: // ãƒ¡ãƒ³ãƒé–¢æ•°	
//	/// <summary>
//	/// åˆæœŸåŒ–
//	/// </summary>
//	/// <returns></returns>
//	void Initialize(ID3D12Device* device);
//	/// <summary>
//	/// æ¯ãƒ•ãƒ¬ãƒ¼ãƒ å‡¦ç†
//	/// </summary>
//	void Update();
//
//	/// <summary>
//	/// æç”»
//	/// </summary>
//	void Draw(ID3D12GraphicsCommandList* cmdList);
//
//	/// <summary>
//	/// ã‚«ãƒ¡ãƒ©ã®ã‚»ãƒƒãƒˆ
//	/// </summary>
//	/// <param name="camera">ã‚«ãƒ¡ãƒ©</param>
//	inline void SetCamera(Camera* camera) { this->camera = camera; }
//
//	/// <summary>
//	/// ãƒ‘ãƒ¼ãƒ†ã‚£ã‚¯ãƒ«ã®è¿½åŠ 
//	/// </summary>
//	/// <param name="life">ç”Ÿå­˜æ™‚é–“</param>
//	/// <param name="position">åˆæœŸåº§æ¨™</param>
//	/// <param name="velocity">é€Ÿåº¦</param>
//	/// <param name="accel">åŠ é€Ÿåº¦</param>
//	/// <param name="start_scale">é–‹å§‹æ™‚ã‚¹ã‚±ãƒ¼ãƒ«</param>
//	/// <param name="end_scale">çµ‚äº†æ™‚ã‚¹ã‚±ãƒ¼ãƒ«</param>
//	void Add(int life, XMFLOAT3 position, XMFLOAT3 velocity, XMFLOAT3 accel, float start_scale, float end_scale);
//
//	/// <summary>
//	/// ãƒ‡ã‚¹ã‚¯ãƒªãƒ—ã‚¿ãƒ’ãƒ¼ãƒ—ã®åˆæœŸåŒ–
//	/// </summary>
//	/// <returns></returns>
//	void InitializeDescriptorHeap();
//
//	/// <summary>
//	/// ã‚°ãƒ©ãƒ•ã‚£ãƒƒã‚¯ãƒ‘ã‚¤ãƒ—ãƒ©ã‚¤ãƒ³ç”Ÿæˆ
//	/// </summary>
//	/// <returns>æˆå¦</returns>
//	void InitializeGraphicsPipeline();
//
//	/// <summary>
//	/// ãƒ†ã‚¯ã‚¹ãƒãƒ£èª­ã¿è¾¼ã¿
//	/// </summary>
//	/// <returns>æˆå¦</returns>
//	void LoadTexture();
//
//	/// <summary>
//	/// ãƒ¢ãƒ‡ãƒ«ä½œæˆ
//	/// </summary>
//	void CreateModel();
//
//private: // ãƒ¡ãƒ³ãƒå¤‰æ•°
//	// ãƒ‡ãƒã‚¤ã‚¹
//	ID3D12Device* device = nullptr;
//	// ãƒ‡ã‚¹ã‚¯ãƒªãƒ—ã‚¿ã‚µã‚¤ã‚º
//	UINT descriptorHandleIncrementSize = 0u;
//	// ãƒ«ãƒ¼ãƒˆã‚·ã‚°ãƒãƒãƒ£
//	ComPtr<ID3D12RootSignature> rootsignature;
//	// ãƒ‘ã‚¤ãƒ—ãƒ©ã‚¤ãƒ³ã‚¹ãƒ†ãƒ¼ãƒˆã‚ªãƒ–ã‚¸ã‚§ã‚¯ãƒˆ
//	ComPtr<ID3D12PipelineState> pipelinestate;
//	// ãƒ‡ã‚¹ã‚¯ãƒªãƒ—ã‚¿ãƒ’ãƒ¼ãƒ—
//	ComPtr<ID3D12DescriptorHeap> descHeap;
//	// é ‚ç‚¹ãƒãƒƒãƒ•ã‚¡
//	ComPtr<ID3D12Resource> vertBuff;
//	// ãƒ†ã‚¯ã‚¹ãƒãƒ£ãƒãƒƒãƒ•ã‚¡
//	ComPtr<ID3D12Resource> texbuff;
//	// ã‚·ã‚§ãƒ¼ãƒ€ãƒªã‚½ãƒ¼ã‚¹ãƒ“ãƒ¥ãƒ¼ã®ãƒãƒ³ãƒ‰ãƒ«(CPU)
//	CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
//	// ã‚·ã‚§ãƒ¼ãƒ€ãƒªã‚½ãƒ¼ã‚¹ãƒ“ãƒ¥ãƒ¼ã®ãƒãƒ³ãƒ‰ãƒ«(CPU)
//	CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;
//	// é ‚ç‚¹ãƒãƒƒãƒ•ã‚¡ãƒ“ãƒ¥ãƒ¼
//	D3D12_VERTEX_BUFFER_VIEW vbView;
//	// å®šæ•°ãƒãƒƒãƒ•ã‚¡
//	ComPtr<ID3D12Resource> constBuff;
//	// ãƒ‘ãƒ¼ãƒ†ã‚£ã‚¯ãƒ«é…åˆ—
//	std::forward_list<Particle> particles;
//	// ã‚«ãƒ¡ãƒ©
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
/// ƒp[ƒeƒBƒNƒ‹ƒ}ƒl[ƒWƒƒ
/// </summary>
class ParticleManager
{
private: // ƒGƒCƒŠƒAƒX
	// Microsoft::WRL::‚ğÈ—ª
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::‚ğÈ—ª
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public: // ƒTƒuƒNƒ‰ƒX
	// ’¸“_ƒf[ƒ^\‘¢‘Ì
	struct VertexPos
	{
		XMFLOAT3 pos; // xyzÀ•W
		float scale; // ƒXƒP[ƒ‹
	};

	// ’è”ƒoƒbƒtƒ@—pƒf[ƒ^\‘¢‘Ì
	struct ConstBufferData
	{
		XMMATRIX mat;	// ƒrƒ…[ƒvƒƒWƒFƒNƒVƒ‡ƒ“s—ñ
		XMMATRIX matBillboard;	// ƒrƒ‹ƒ{[ƒhs—ñ
	};

	// ƒp[ƒeƒBƒNƒ‹1—±
	class Particle
	{
		// Microsoft::WRL::‚ğÈ—ª
		template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
		// DirectX::‚ğÈ—ª
		using XMFLOAT2 = DirectX::XMFLOAT2;
		using XMFLOAT3 = DirectX::XMFLOAT3;
		using XMFLOAT4 = DirectX::XMFLOAT4;
		using XMMATRIX = DirectX::XMMATRIX;

	public:
		// À•W
		XMFLOAT3 position = {};
		// ‘¬“x
		XMFLOAT3 velocity = {};
		// ‰Á‘¬“x
		XMFLOAT3 accel = {};
		// F
		XMFLOAT3 color = {};
		// ƒXƒP[ƒ‹
		float scale = 1.0f;
		// ‰ñ“]
		float rotation = 0.0f;
		// ‰Šú’l
		XMFLOAT3 s_color = {};
		float s_scale = 1.0f;
		float s_rotation = 0.0f;
		// ÅI’l
		XMFLOAT3 e_color = {};
		float e_scale = 0.0f;
		float e_rotation = 0.0f;
		// Œ»İƒtƒŒ[ƒ€
		int frame = 0;
		// I—¹ƒtƒŒ[ƒ€
		int num_frame = 0;
	};

private: // ’è”
	static const int vertexCount = 65536;		// ’¸“_”

public:// Ã“Iƒƒ“ƒoŠÖ”
	static ParticleManager* GetInstance();

public: // ƒƒ“ƒoŠÖ”	
	/// <summary>
	/// ‰Šú‰»
	/// </summary>
	/// <returns></returns>
	void Initialize(ID3D12Device* device);
	/// <summary>
	/// –ˆƒtƒŒ[ƒ€ˆ—
	/// </summary>
	void Update();

	/// <summary>
	/// •`‰æ
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// ƒJƒƒ‰‚ÌƒZƒbƒg
	/// </summary>
	/// <param name="camera">ƒJƒƒ‰</param>
	inline void SetCamera(Camera* camera) { this->camera = camera; }

	/// <summary>
	/// ƒp[ƒeƒBƒNƒ‹‚Ì’Ç‰Á
	/// </summary>
	/// <param name="life">¶‘¶ŠÔ</param>
	/// <param name="position">‰ŠúÀ•W</param>
	/// <param name="velocity">‘¬“x</param>
	/// <param name="accel">‰Á‘¬“x</param>
	/// <param name="start_scale">ŠJnƒXƒP[ƒ‹</param>
	/// <param name="end_scale">I—¹ƒXƒP[ƒ‹</param>
	void Add(int life, XMFLOAT3 position, XMFLOAT3 velocity, XMFLOAT3 accel, float start_scale, float end_scale);

	/// <summary>
	/// ƒfƒXƒNƒŠƒvƒ^ƒq[ƒv‚Ì‰Šú‰»
	/// </summary>
	/// <returns></returns>
	void InitializeDescriptorHeap();

	/// <summary>
	/// ƒOƒ‰ƒtƒBƒbƒNƒpƒCƒvƒ‰ƒCƒ“¶¬
	/// </summary>
	/// <returns>¬”Û</returns>
	void InitializeGraphicsPipeline();

	/// <summary>
	/// ƒeƒNƒXƒ`ƒƒ“Ç‚İ‚İ
	/// </summary>
	/// <returns>¬”Û</returns>
	void LoadTexture();

	/// <summary>
	/// ƒ‚ƒfƒ‹ì¬
	/// </summary>
	void CreateModel();

private: // ƒƒ“ƒo•Ï”
	// ƒfƒoƒCƒX
	ID3D12Device* device = nullptr;
	// ƒfƒXƒNƒŠƒvƒ^ƒTƒCƒY
	UINT descriptorHandleIncrementSize = 0u;
	// ƒ‹[ƒgƒVƒOƒlƒ`ƒƒ
	ComPtr<ID3D12RootSignature> rootsignature;
	// ƒpƒCƒvƒ‰ƒCƒ“ƒXƒe[ƒgƒIƒuƒWƒFƒNƒg
	ComPtr<ID3D12PipelineState> pipelinestate;
	// ƒfƒXƒNƒŠƒvƒ^ƒq[ƒv
	ComPtr<ID3D12DescriptorHeap> descHeap;
	// ’¸“_ƒoƒbƒtƒ@
	ComPtr<ID3D12Resource> vertBuff;
	// ƒeƒNƒXƒ`ƒƒƒoƒbƒtƒ@
	ComPtr<ID3D12Resource> texbuff;
	// ƒVƒF[ƒ_ƒŠƒ\[ƒXƒrƒ…[‚Ìƒnƒ“ƒhƒ‹(CPU)
	CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
	// ƒVƒF[ƒ_ƒŠƒ\[ƒXƒrƒ…[‚Ìƒnƒ“ƒhƒ‹(CPU)
	CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;
	// ’¸“_ƒoƒbƒtƒ@ƒrƒ…[
	D3D12_VERTEX_BUFFER_VIEW vbView;
	// ’è”ƒoƒbƒtƒ@
	ComPtr<ID3D12Resource> constBuff;
	// ƒp[ƒeƒBƒNƒ‹”z—ñ
	std::forward_list<Particle> particles;
	// ƒJƒƒ‰
	Camera* camera = nullptr;
private:
	ParticleManager() = default;
	ParticleManager(const ParticleManager&) = delete;
	~ParticleManager() = default;
	ParticleManager& operator=(const ParticleManager&) = delete;
};

>>>>>>> master
