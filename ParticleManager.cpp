<<<<<<< HEAD
ï»¿//#include "ParticleManager.h"
//#include <d3dcompiler.h>
//#include <DirectXTex.h>
//
//#pragma comment(lib, "d3dcompiler.lib")
//
//using namespace DirectX;
//using namespace Microsoft::WRL;
//
//static const DirectX::XMFLOAT3 operator+(const DirectX::XMFLOAT3& lhs, const DirectX::XMFLOAT3& rhs)
//{
//	XMFLOAT3 result;
//	result.x = lhs.x + rhs.x;
//	result.y = lhs.y + rhs.y;
//	result.z = lhs.z + rhs.z;
//	return result;
//}
//
//static const DirectX::XMFLOAT3 operator-(const DirectX::XMFLOAT3& lhs, const DirectX::XMFLOAT3& rhs)
//{
//	XMFLOAT3 result;
//	result.x = lhs.x - rhs.x;
//	result.y = lhs.y - rhs.y;
//	result.z = lhs.z - rhs.z;
//	return result;
//}
//
//const DirectX::XMFLOAT3 operator/(const DirectX::XMFLOAT3& lhs, const float rhs)
//{
//	XMFLOAT3 result;
//	result.x = lhs.x / rhs;
//	result.y = lhs.y / rhs;
//	result.z = lhs.z / rhs;
//	return result;
//}
//
//ParticleManager* ParticleManager::GetInstance()
//{
//	static ParticleManager instance;
//	return &instance;
//}
//
//void ParticleManager::Initialize(ID3D12Device* device)
//{
//	// nullptrãƒã‚§ãƒƒã‚¯
//	assert(device);
//
//	this->device = device;
//
//	HRESULT result;
//
//	// ãƒ‡ã‚¹ã‚¯ãƒªãƒ—ã‚¿ãƒ’ãƒ¼ãƒ—ã®åˆæœŸåŒ–
//	InitializeDescriptorHeap();
//
//	// ãƒ‘ã‚¤ãƒ—ãƒ©ã‚¤ãƒ³åˆæœŸåŒ–
//	InitializeGraphicsPipeline();
//
//	// ãƒ†ã‚¯ã‚¹ãƒãƒ£èª­ã¿è¾¼ã¿
//	LoadTexture();
//
//	// ãƒ¢ãƒ‡ãƒ«ç”Ÿæˆ
//	CreateModel();
//
//	// å®šæ•°ãƒãƒƒãƒ•ã‚¡ã®ç”Ÿæˆ
//	result = device->CreateCommittedResource(
//		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), 	// ã‚¢ãƒƒãƒ—ãƒ­ãƒ¼ãƒ‰å¯èƒ½
//		D3D12_HEAP_FLAG_NONE,
//		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferData) + 0xff) & ~0xff),
//		D3D12_RESOURCE_STATE_GENERIC_READ,
//		nullptr,
//		IID_PPV_ARGS(&constBuff));
//	if (FAILED(result)) {
//		assert(0);
//	}
//}
//
//void ParticleManager::Update()
//{
//	HRESULT result;
//
//	// å¯¿å‘½ãŒå°½ããŸãƒ‘ãƒ¼ãƒ†ã‚£ã‚¯ãƒ«ã‚’å…¨å‰Šé™¤
//	particles.remove_if([](Particle& x) { return x.frame >= x.num_frame; });
//
//	// å…¨ãƒ‘ãƒ¼ãƒ†ã‚£ã‚¯ãƒ«æ›´æ–°
//	for (std::forward_list<Particle>::iterator it = particles.begin();
//		it != particles.end();
//		it++) {
//
//		// çµŒéãƒ•ãƒ¬ãƒ¼ãƒ æ•°ã‚’ã‚«ã‚¦ãƒ³ãƒˆ
//		it->frame++;
//		// é€²è¡Œåº¦ã‚’0ï½1ã®ç¯„å›²ã«æ›ç®—
//		float f = (float)it->num_frame / it->frame;
//
//		// é€Ÿåº¦ã«åŠ é€Ÿåº¦ã‚’åŠ ç®—
//		it->velocity = it->velocity + it->accel;
//
//		// é€Ÿåº¦ã«ã‚ˆã‚‹ç§»å‹•
//		it->position = it->position + it->velocity;
//
//		// ã‚«ãƒ©ãƒ¼ã®ç·šå½¢è£œé–“
//		it->color = it->s_color + (it->e_color - it->s_color) / f;
//
//		// ã‚¹ã‚±ãƒ¼ãƒ«ã®ç·šå½¢è£œé–“
//		it->scale = it->s_scale + (it->e_scale - it->s_scale) / f;
//
//		// ã‚¹ã‚±ãƒ¼ãƒ«ã®ç·šå½¢è£œé–“
//		it->rotation = it->s_rotation + (it->e_rotation - it->s_rotation) / f;
//	}
//
//	// é ‚ç‚¹ãƒãƒƒãƒ•ã‚¡ã¸ãƒ‡ãƒ¼ã‚¿è»¢é€
//	int vertCount = 0;
//	VertexPos* vertMap = nullptr;
//	result = vertBuff->Map(0, nullptr, (void**)&vertMap);
//	if (SUCCEEDED(result)) {
//		// ãƒ‘ãƒ¼ãƒ†ã‚£ã‚¯ãƒ«ã®æƒ…å ±ã‚’1ã¤ãšã¤åæ˜ 
//		for (std::forward_list<Particle>::iterator it = particles.begin();
//			it != particles.end();
//			it++) {
//			// åº§æ¨™
//			vertMap->pos = it->position;
//			// ã‚¹ã‚±ãƒ¼ãƒ«
//			vertMap->scale = it->scale;
//			// æ¬¡ã®é ‚ç‚¹ã¸
//			vertMap++;
//			if (++vertCount >= vertexCount) {
//				break;
//			}
//		}
//		vertBuff->Unmap(0, nullptr);
//	}
//
//	// å®šæ•°ãƒãƒƒãƒ•ã‚¡ã¸ãƒ‡ãƒ¼ã‚¿è»¢é€
//	ConstBufferData* constMap = nullptr;
//	result = constBuff->Map(0, nullptr, (void**)&constMap);
//	constMap->mat = camera->GetViewProjectionMatrix();
//	constMap->matBillboard = camera->GetBillboardMatrix();
//	constBuff->Unmap(0, nullptr);
//}
//
//void ParticleManager::Draw(ID3D12GraphicsCommandList* cmdList)
//{
//	UINT drawNum = (UINT)std::distance(particles.begin(), particles.end());
//	if (drawNum > vertexCount) {
//		drawNum = vertexCount;
//	}
//
//	// ãƒ‘ãƒ¼ãƒ†ã‚£ã‚¯ãƒ«ãŒ1ã¤ã‚‚ãªã„å ´åˆ
//	if (drawNum == 0) {
//		return;
//	}
//
//	// nullptrãƒã‚§ãƒƒã‚¯
//	assert(cmdList);
//
//	// ãƒ‘ã‚¤ãƒ—ãƒ©ã‚¤ãƒ³ã‚¹ãƒ†ãƒ¼ãƒˆã®è¨­å®š
//	cmdList->SetPipelineState(pipelinestate.Get());
//	// ãƒ«ãƒ¼ãƒˆã‚·ã‚°ãƒãƒãƒ£ã®è¨­å®š
//	cmdList->SetGraphicsRootSignature(rootsignature.Get());
//	// ãƒ—ãƒªãƒŸãƒ†ã‚£ãƒ–å½¢çŠ¶ã‚’è¨­å®š
//	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_POINTLIST);
//
//	// é ‚ç‚¹ãƒãƒƒãƒ•ã‚¡ã®è¨­å®š
//	cmdList->IASetVertexBuffers(0, 1, &vbView);
//
//	// ãƒ‡ã‚¹ã‚¯ãƒªãƒ—ã‚¿ãƒ’ãƒ¼ãƒ—ã®é…åˆ—
//	ID3D12DescriptorHeap* ppHeaps[] = { descHeap.Get() };
//	cmdList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
//
//	// å®šæ•°ãƒãƒƒãƒ•ã‚¡ãƒ“ãƒ¥ãƒ¼ã‚’ã‚»ãƒƒãƒˆ
//	cmdList->SetGraphicsRootConstantBufferView(0, constBuff->GetGPUVirtualAddress());
//	// ã‚·ã‚§ãƒ¼ãƒ€ãƒªã‚½ãƒ¼ã‚¹ãƒ“ãƒ¥ãƒ¼ã‚’ã‚»ãƒƒãƒˆ
//	cmdList->SetGraphicsRootDescriptorTable(1, gpuDescHandleSRV);
//	// æç”»ã‚³ãƒãƒ³ãƒ‰
//	cmdList->DrawInstanced(drawNum, 1, 0, 0);
//}
//
//void ParticleManager::Add(int life, XMFLOAT3 position, XMFLOAT3 velocity, XMFLOAT3 accel, float start_scale, float end_scale)
//{
//	// ãƒªã‚¹ãƒˆã«è¦ç´ ã‚’è¿½åŠ 
//	particles.emplace_front();
//	// è¿½åŠ ã—ãŸè¦ç´ ã®å‚ç…§
//	Particle& p = particles.front();
//	p.position = position;
//	p.velocity = velocity;
//	p.accel = accel;
//	p.s_scale = start_scale;
//	p.e_scale = end_scale;
//	p.num_frame = life;
//}
//
//void ParticleManager::InitializeDescriptorHeap()
//{
//	HRESULT result = S_FALSE;
//
//	// ãƒ‡ã‚¹ã‚¯ãƒªãƒ—ã‚¿ãƒ’ãƒ¼ãƒ—ã‚’ç”Ÿæˆ	
//	D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc = {};
//	descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
//	descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;//ã‚·ã‚§ãƒ¼ãƒ€ã‹ã‚‰è¦‹ãˆã‚‹ã‚ˆã†ã«
//	descHeapDesc.NumDescriptors = 1; // ã‚·ã‚§ãƒ¼ãƒ€ãƒ¼ãƒªã‚½ãƒ¼ã‚¹ãƒ“ãƒ¥ãƒ¼1ã¤
//	result = device->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&descHeap));//ç”Ÿæˆ
//	if (FAILED(result)) {
//		assert(0);
//	}
//
//	// ãƒ‡ã‚¹ã‚¯ãƒªãƒ—ã‚¿ã‚µã‚¤ã‚ºã‚’å–å¾—
//	descriptorHandleIncrementSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
//}
//
//void ParticleManager::InitializeGraphicsPipeline()
//{
//	HRESULT result = S_FALSE;
//	ComPtr<ID3DBlob> vsBlob; // é ‚ç‚¹ã‚·ã‚§ãƒ¼ãƒ€ã‚ªãƒ–ã‚¸ã‚§ã‚¯ãƒˆ
//	ComPtr<ID3DBlob> psBlob;	// ãƒ”ã‚¯ã‚»ãƒ«ã‚·ã‚§ãƒ¼ãƒ€ã‚ªãƒ–ã‚¸ã‚§ã‚¯ãƒˆ
//	ComPtr<ID3DBlob> gsBlob;	// ã‚¸ã‚ªãƒ¡ãƒˆãƒªã‚·ã‚§ãƒ¼ãƒ€ã‚ªãƒ–ã‚¸ã‚§ã‚¯ãƒˆ
//	ComPtr<ID3DBlob> errorBlob; // ã‚¨ãƒ©ãƒ¼ã‚ªãƒ–ã‚¸ã‚§ã‚¯ãƒˆ
//
//	// é ‚ç‚¹ã‚·ã‚§ãƒ¼ãƒ€ã®èª­ã¿è¾¼ã¿ã¨ã‚³ãƒ³ãƒ‘ã‚¤ãƒ«
//	result = D3DCompileFromFile(
//		L"Resources/shaders/ParticleVS.hlsl",	// ã‚·ã‚§ãƒ¼ãƒ€ãƒ•ã‚¡ã‚¤ãƒ«å
//		nullptr,
//		D3D_COMPILE_STANDARD_FILE_INCLUDE, // ã‚¤ãƒ³ã‚¯ãƒ«ãƒ¼ãƒ‰å¯èƒ½ã«ã™ã‚‹
//		"main", "vs_5_0",	// ã‚¨ãƒ³ãƒˆãƒªãƒ¼ãƒã‚¤ãƒ³ãƒˆåã€ã‚·ã‚§ãƒ¼ãƒ€ãƒ¼ãƒ¢ãƒ‡ãƒ«æŒ‡å®š
//		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // ãƒ‡ãƒãƒƒã‚°ç”¨è¨­å®š
//		0,
//		&vsBlob, &errorBlob);
//	if (FAILED(result)) {
//		// errorBlobã‹ã‚‰ã‚¨ãƒ©ãƒ¼å†…å®¹ã‚’stringå‹ã«ã‚³ãƒ”ãƒ¼
//		std::string errstr;
//		errstr.resize(errorBlob->GetBufferSize());
//
//		std::copy_n((char*)errorBlob->GetBufferPointer(),
//			errorBlob->GetBufferSize(),
//			errstr.begin());
//		errstr += "\n";
//		// ã‚¨ãƒ©ãƒ¼å†…å®¹ã‚’å‡ºåŠ›ã‚¦ã‚£ãƒ³ãƒ‰ã‚¦ã«è¡¨ç¤º
//		OutputDebugStringA(errstr.c_str());
//		exit(1);
//	}
//
//	// ãƒ”ã‚¯ã‚»ãƒ«ã‚·ã‚§ãƒ¼ãƒ€ã®èª­ã¿è¾¼ã¿ã¨ã‚³ãƒ³ãƒ‘ã‚¤ãƒ«
//	result = D3DCompileFromFile(
//		L"Resources/shaders/ParticlePS.hlsl",	// ã‚·ã‚§ãƒ¼ãƒ€ãƒ•ã‚¡ã‚¤ãƒ«å
//		nullptr,
//		D3D_COMPILE_STANDARD_FILE_INCLUDE, // ã‚¤ãƒ³ã‚¯ãƒ«ãƒ¼ãƒ‰å¯èƒ½ã«ã™ã‚‹
//		"main", "ps_5_0",	// ã‚¨ãƒ³ãƒˆãƒªãƒ¼ãƒã‚¤ãƒ³ãƒˆåã€ã‚·ã‚§ãƒ¼ãƒ€ãƒ¼ãƒ¢ãƒ‡ãƒ«æŒ‡å®š
//		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // ãƒ‡ãƒãƒƒã‚°ç”¨è¨­å®š
//		0,
//		&psBlob, &errorBlob);
//	if (FAILED(result)) {
//		// errorBlobã‹ã‚‰ã‚¨ãƒ©ãƒ¼å†…å®¹ã‚’stringå‹ã«ã‚³ãƒ”ãƒ¼
//		std::string errstr;
//		errstr.resize(errorBlob->GetBufferSize());
//
//		std::copy_n((char*)errorBlob->GetBufferPointer(),
//			errorBlob->GetBufferSize(),
//			errstr.begin());
//		errstr += "\n";
//		// ã‚¨ãƒ©ãƒ¼å†…å®¹ã‚’å‡ºåŠ›ã‚¦ã‚£ãƒ³ãƒ‰ã‚¦ã«è¡¨ç¤º
//		OutputDebugStringA(errstr.c_str());
//		exit(1);
//	}
//
//	// ã‚¸ã‚ªãƒ¡ãƒˆãƒªã‚·ã‚§ãƒ¼ãƒ€ã®èª­ã¿è¾¼ã¿ã¨ã‚³ãƒ³ãƒ‘ã‚¤ãƒ«
//	result = D3DCompileFromFile(
//		L"Resources/shaders/ParticleGS.hlsl",	// ã‚·ã‚§ãƒ¼ãƒ€ãƒ•ã‚¡ã‚¤ãƒ«å
//		nullptr,
//		D3D_COMPILE_STANDARD_FILE_INCLUDE, // ã‚¤ãƒ³ã‚¯ãƒ«ãƒ¼ãƒ‰å¯èƒ½ã«ã™ã‚‹
//		"main", "gs_5_0",	// ã‚¨ãƒ³ãƒˆãƒªãƒ¼ãƒã‚¤ãƒ³ãƒˆåã€ã‚·ã‚§ãƒ¼ãƒ€ãƒ¼ãƒ¢ãƒ‡ãƒ«æŒ‡å®š
//		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // ãƒ‡ãƒãƒƒã‚°ç”¨è¨­å®š
//		0,
//		&gsBlob, &errorBlob);
//	if (FAILED(result)) {
//		// errorBlobã‹ã‚‰ã‚¨ãƒ©ãƒ¼å†…å®¹ã‚’stringå‹ã«ã‚³ãƒ”ãƒ¼
//		std::string errstr;
//		errstr.resize(errorBlob->GetBufferSize());
//
//		std::copy_n((char*)errorBlob->GetBufferPointer(),
//			errorBlob->GetBufferSize(),
//			errstr.begin());
//		errstr += "\n";
//		// ã‚¨ãƒ©ãƒ¼å†…å®¹ã‚’å‡ºåŠ›ã‚¦ã‚£ãƒ³ãƒ‰ã‚¦ã«è¡¨ç¤º
//		OutputDebugStringA(errstr.c_str());
//		exit(1);
//	}
//
//	// é ‚ç‚¹ãƒ¬ã‚¤ã‚¢ã‚¦ãƒˆ
//	D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
//		{ // xyåº§æ¨™(1è¡Œã§æ›¸ã„ãŸã»ã†ãŒè¦‹ã‚„ã™ã„)
//			"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
//			D3D12_APPEND_ALIGNED_ELEMENT,
//			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
//		},
//		{ // ã‚¹ã‚±ãƒ¼ãƒ«
//			"TEXCOORD", 0, DXGI_FORMAT_R32_FLOAT, 0,
//			D3D12_APPEND_ALIGNED_ELEMENT,
//			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
//		},
//	};
//
//	// ã‚°ãƒ©ãƒ•ã‚£ãƒƒã‚¯ã‚¹ãƒ‘ã‚¤ãƒ—ãƒ©ã‚¤ãƒ³ã®æµã‚Œã‚’è¨­å®š
//	D3D12_GRAPHICS_PIPELINE_STATE_DESC gpipeline{};
//	gpipeline.VS = CD3DX12_SHADER_BYTECODE(vsBlob.Get());
//	gpipeline.PS = CD3DX12_SHADER_BYTECODE(psBlob.Get());
//	gpipeline.GS = CD3DX12_SHADER_BYTECODE(gsBlob.Get());
//
//	// ã‚µãƒ³ãƒ—ãƒ«ãƒã‚¹ã‚¯
//	gpipeline.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // æ¨™æº–è¨­å®š
//	// ãƒ©ã‚¹ã‚¿ãƒ©ã‚¤ã‚¶ã‚¹ãƒ†ãƒ¼ãƒˆ
//	gpipeline.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
//	//gpipeline.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
//	//gpipeline.RasterizerState.FillMode = D3D12_FILL_MODE_WIREFRAME;
//	// ãƒ‡ãƒ—ã‚¹ã‚¹ãƒ†ãƒ³ã‚·ãƒ«ã‚¹ãƒ†ãƒ¼ãƒˆ
//	gpipeline.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
//	// ãƒ‡ãƒ—ã‚¹ã®æ›¸ãè¾¼ã¿ã‚’ç¦æ­¢
//	gpipeline.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ZERO;
//
//	// ãƒ¬ãƒ³ãƒ€ãƒ¼ã‚¿ãƒ¼ã‚²ãƒƒãƒˆã®ãƒ–ãƒ¬ãƒ³ãƒ‰è¨­å®š
//	D3D12_RENDER_TARGET_BLEND_DESC blenddesc{};
//	blenddesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;	// RBGAå…¨ã¦ã®ãƒãƒ£ãƒ³ãƒãƒ«ã‚’æç”»
//	blenddesc.BlendEnable = true;
//	// åŠ ç®—ãƒ–ãƒ¬ãƒ³ãƒ‡ã‚£ãƒ³ã‚°
//	blenddesc.BlendOp = D3D12_BLEND_OP_ADD;
//	blenddesc.SrcBlend = D3D12_BLEND_ONE;
//	blenddesc.DestBlend = D3D12_BLEND_ONE;
//	//// æ¸›ç®—ãƒ–ãƒ¬ãƒ³ãƒ‡ã‚£ãƒ³ã‚°
//	//blenddesc.BlendOp = D3D12_BLEND_OP_REV_SUBTRACT;
//	//blenddesc.SrcBlend = D3D12_BLEND_ONE;
//	//blenddesc.DestBlend = D3D12_BLEND_ONE;
//
//	blenddesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;
//	blenddesc.SrcBlendAlpha = D3D12_BLEND_ONE;
//	blenddesc.DestBlendAlpha = D3D12_BLEND_ZERO;
//
//	// ãƒ–ãƒ¬ãƒ³ãƒ‰ã‚¹ãƒ†ãƒ¼ãƒˆã®è¨­å®š
//	gpipeline.BlendState.RenderTarget[0] = blenddesc;
//
//	// æ·±åº¦ãƒãƒƒãƒ•ã‚¡ã®ãƒ•ã‚©ãƒ¼ãƒãƒƒãƒˆ
//	gpipeline.DSVFormat = DXGI_FORMAT_D32_FLOAT;
//
//	// é ‚ç‚¹ãƒ¬ã‚¤ã‚¢ã‚¦ãƒˆã®è¨­å®š
//	gpipeline.InputLayout.pInputElementDescs = inputLayout;
//	gpipeline.InputLayout.NumElements = _countof(inputLayout);
//
//	// å›³å½¢ã®å½¢çŠ¶è¨­å®šï¼ˆä¸‰è§’å½¢ï¼‰
//	gpipeline.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT;
//
//	gpipeline.NumRenderTargets = 1;	// æç”»å¯¾è±¡ã¯1ã¤
//	gpipeline.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM; // 0ï½255æŒ‡å®šã®RGBA
//	gpipeline.SampleDesc.Count = 1; // 1ãƒ”ã‚¯ã‚»ãƒ«ã«ã¤ã1å›ã‚µãƒ³ãƒ—ãƒªãƒ³ã‚°
//
//	// ãƒ‡ã‚¹ã‚¯ãƒªãƒ—ã‚¿ãƒ¬ãƒ³ã‚¸
//	CD3DX12_DESCRIPTOR_RANGE descRangeSRV;
//	descRangeSRV.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0); // t0 ãƒ¬ã‚¸ã‚¹ã‚¿
//
//	// ãƒ«ãƒ¼ãƒˆãƒ‘ãƒ©ãƒ¡ãƒ¼ã‚¿
//	CD3DX12_ROOT_PARAMETER rootparams[2];
//	rootparams[0].InitAsConstantBufferView(0, 0, D3D12_SHADER_VISIBILITY_ALL);
//	rootparams[1].InitAsDescriptorTable(1, &descRangeSRV, D3D12_SHADER_VISIBILITY_ALL);
//
//	// ã‚¹ã‚¿ãƒ†ã‚£ãƒƒã‚¯ã‚µãƒ³ãƒ—ãƒ©ãƒ¼
//	CD3DX12_STATIC_SAMPLER_DESC samplerDesc = CD3DX12_STATIC_SAMPLER_DESC(0);
//
//	// ãƒ«ãƒ¼ãƒˆã‚·ã‚°ãƒãƒãƒ£ã®è¨­å®š
//	CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC rootSignatureDesc;
//	rootSignatureDesc.Init_1_0(_countof(rootparams), rootparams, 1, &samplerDesc, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);
//
//	ComPtr<ID3DBlob> rootSigBlob;
//	// ãƒãƒ¼ã‚¸ãƒ§ãƒ³è‡ªå‹•åˆ¤å®šã®ã‚·ãƒªã‚¢ãƒ©ã‚¤ã‚º
//	result = D3DX12SerializeVersionedRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob, &errorBlob);
//	// ãƒ«ãƒ¼ãƒˆã‚·ã‚°ãƒãƒãƒ£ã®ç”Ÿæˆ
//	result = device->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(), IID_PPV_ARGS(&rootsignature));
//	if (FAILED(result)) {
//		assert(0);
//	}
//
//	gpipeline.pRootSignature = rootsignature.Get();
//
//	// ã‚°ãƒ©ãƒ•ã‚£ãƒƒã‚¯ã‚¹ãƒ‘ã‚¤ãƒ—ãƒ©ã‚¤ãƒ³ã®ç”Ÿæˆ
//	result = device->CreateGraphicsPipelineState(&gpipeline, IID_PPV_ARGS(&pipelinestate));
//
//	if (FAILED(result)) {
//		assert(0);
//	}
//}
//
//void ParticleManager::LoadTexture()
//{
//	HRESULT result = S_FALSE;
//
//	// WICãƒ†ã‚¯ã‚¹ãƒãƒ£ã®ãƒ­ãƒ¼ãƒ‰
//	TexMetadata metadata{};
//	ScratchImage scratchImg{};
//
//	result = LoadFromWICFile(
//		L"Resources/2d/effect1.png", WIC_FLAGS_NONE,
//		&metadata, scratchImg);
//	if (FAILED(result)) {
//		assert(0);
//	}
//
//	const Image* img = scratchImg.GetImage(0, 0, 0); // ç”Ÿãƒ‡ãƒ¼ã‚¿æŠ½å‡º
//
//	// ãƒªã‚½ãƒ¼ã‚¹è¨­å®š
//	CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(
//		metadata.format,
//		metadata.width,
//		(UINT)metadata.height,
//		(UINT16)metadata.arraySize,
//		(UINT16)metadata.mipLevels
//	);
//
//	// ãƒ†ã‚¯ã‚¹ãƒãƒ£ç”¨ãƒãƒƒãƒ•ã‚¡ã®ç”Ÿæˆ
//	result = device->CreateCommittedResource(
//		&CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0),
//		D3D12_HEAP_FLAG_NONE,
//		&texresDesc,
//		D3D12_RESOURCE_STATE_GENERIC_READ, // ãƒ†ã‚¯ã‚¹ãƒãƒ£ç”¨æŒ‡å®š
//		nullptr,
//		IID_PPV_ARGS(&texbuff));
//	if (FAILED(result)) {
//		assert(0);
//	}
//
//	// ãƒ†ã‚¯ã‚¹ãƒãƒ£ãƒãƒƒãƒ•ã‚¡ã«ãƒ‡ãƒ¼ã‚¿è»¢é€
//	result = texbuff->WriteToSubresource(
//		0,
//		nullptr, // å…¨é ˜åŸŸã¸ã‚³ãƒ”ãƒ¼
//		img->pixels,    // å…ƒãƒ‡ãƒ¼ã‚¿ã‚¢ãƒ‰ãƒ¬ã‚¹
//		(UINT)img->rowPitch,  // 1ãƒ©ã‚¤ãƒ³ã‚µã‚¤ã‚º
//		(UINT)img->slicePitch // 1æšã‚µã‚¤ã‚º
//	);
//	if (FAILED(result)) {
//		assert(0);
//	}
//
//	// ã‚·ã‚§ãƒ¼ãƒ€ãƒªã‚½ãƒ¼ã‚¹ãƒ“ãƒ¥ãƒ¼ä½œæˆ
//	cpuDescHandleSRV = CD3DX12_CPU_DESCRIPTOR_HANDLE(descHeap->GetCPUDescriptorHandleForHeapStart(), 0, descriptorHandleIncrementSize);
//	gpuDescHandleSRV = CD3DX12_GPU_DESCRIPTOR_HANDLE(descHeap->GetGPUDescriptorHandleForHeapStart(), 0, descriptorHandleIncrementSize);
//
//	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{}; // è¨­å®šæ§‹é€ ä½“
//	D3D12_RESOURCE_DESC resDesc = texbuff->GetDesc();
//
//	srvDesc.Format = resDesc.Format;
//	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
//	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;//2Dãƒ†ã‚¯ã‚¹ãƒãƒ£
//	srvDesc.Texture2D.MipLevels = 1;
//
//	device->CreateShaderResourceView(texbuff.Get(), //ãƒ“ãƒ¥ãƒ¼ã¨é–¢é€£ä»˜ã‘ã‚‹ãƒãƒƒãƒ•ã‚¡
//		&srvDesc, //ãƒ†ã‚¯ã‚¹ãƒãƒ£è¨­å®šæƒ…å ±
//		cpuDescHandleSRV
//	);
//}
//
//void ParticleManager::CreateModel()
//{
//	HRESULT result = S_FALSE;
//
//	// é ‚ç‚¹ãƒãƒƒãƒ•ã‚¡ç”Ÿæˆ
//	result = device->CreateCommittedResource(
//		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
//		D3D12_HEAP_FLAG_NONE,
//		&CD3DX12_RESOURCE_DESC::Buffer(sizeof(VertexPos) * vertexCount),
//		D3D12_RESOURCE_STATE_GENERIC_READ,
//		nullptr,
//		IID_PPV_ARGS(&vertBuff));
//	if (FAILED(result)) {
//		assert(0);
//		return;
//	}
//
//	// é ‚ç‚¹ãƒãƒƒãƒ•ã‚¡ãƒ“ãƒ¥ãƒ¼ã®ä½œæˆ
//	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
//	vbView.SizeInBytes = sizeof(VertexPos) * vertexCount;
//	vbView.StrideInBytes = sizeof(VertexPos);
//}
=======
#include "ParticleManager.h"
#include <d3dcompiler.h>
#include <DirectXTex.h>

#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;
using namespace Microsoft::WRL;

static const DirectX::XMFLOAT3 operator+(const DirectX::XMFLOAT3& lhs, const DirectX::XMFLOAT3& rhs)
{
	XMFLOAT3 result;
	result.x = lhs.x + rhs.x;
	result.y = lhs.y + rhs.y;
	result.z = lhs.z + rhs.z;
	return result;
}

static const DirectX::XMFLOAT3 operator-(const DirectX::XMFLOAT3& lhs, const DirectX::XMFLOAT3& rhs)
{
	XMFLOAT3 result;
	result.x = lhs.x - rhs.x;
	result.y = lhs.y - rhs.y;
	result.z = lhs.z - rhs.z;
	return result;
}

const DirectX::XMFLOAT3 operator/(const DirectX::XMFLOAT3& lhs, const float rhs)
{
	XMFLOAT3 result;
	result.x = lhs.x / rhs;
	result.y = lhs.y / rhs;
	result.z = lhs.z / rhs;
	return result;
}

ParticleManager* ParticleManager::GetInstance()
{
	static ParticleManager instance;
	return &instance;
}

void ParticleManager::Initialize(ID3D12Device* device)
{
	// nullptrƒ`ƒFƒbƒN
	assert(device);

	this->device = device;

	HRESULT result;

	// ƒfƒXƒNƒŠƒvƒ^ƒq[ƒv‚Ì‰Šú‰»
	InitializeDescriptorHeap();

	// ƒpƒCƒvƒ‰ƒCƒ“‰Šú‰»
	InitializeGraphicsPipeline();

	// ƒeƒNƒXƒ`ƒƒ“Ç‚İ‚İ
	LoadTexture();

	// ƒ‚ƒfƒ‹¶¬
	CreateModel();

	// ’è”ƒoƒbƒtƒ@‚Ì¶¬
	result = device->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), 	// ƒAƒbƒvƒ[ƒh‰Â”\
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferData) + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuff));
	if (FAILED(result)) {
		assert(0);
	}
}

void ParticleManager::Update()
{
	HRESULT result;

	// õ–½‚ªs‚«‚½ƒp[ƒeƒBƒNƒ‹‚ğ‘Síœ
	particles.remove_if([](Particle& x) { return x.frame >= x.num_frame; });

	// ‘Sƒp[ƒeƒBƒNƒ‹XV
	for (std::forward_list<Particle>::iterator it = particles.begin();
		it != particles.end();
		it++) {

		// Œo‰ßƒtƒŒ[ƒ€”‚ğƒJƒEƒ“ƒg
		it->frame++;
		// is“x‚ğ0`1‚Ì”ÍˆÍ‚ÉŠ·Z
		float f = (float)it->num_frame / it->frame;

		// ‘¬“x‚É‰Á‘¬“x‚ğ‰ÁZ
		it->velocity = it->velocity + it->accel;

		// ‘¬“x‚É‚æ‚éˆÚ“®
		it->position = it->position + it->velocity;

		// ƒJƒ‰[‚ÌüŒ`•âŠÔ
		it->color = it->s_color + (it->e_color - it->s_color) / f;

		// ƒXƒP[ƒ‹‚ÌüŒ`•âŠÔ
		it->scale = it->s_scale + (it->e_scale - it->s_scale) / f;

		// ƒXƒP[ƒ‹‚ÌüŒ`•âŠÔ
		it->rotation = it->s_rotation + (it->e_rotation - it->s_rotation) / f;
	}

	// ’¸“_ƒoƒbƒtƒ@‚Öƒf[ƒ^“]‘—
	int vertCount = 0;
	VertexPos* vertMap = nullptr;
	result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	if (SUCCEEDED(result)) {
		// ƒp[ƒeƒBƒNƒ‹‚Ìî•ñ‚ğ1‚Â‚¸‚Â”½‰f
		for (std::forward_list<Particle>::iterator it = particles.begin();
			it != particles.end();
			it++) {
			// À•W
			vertMap->pos = it->position;
			// ƒXƒP[ƒ‹
			vertMap->scale = it->scale;
			// Ÿ‚Ì’¸“_‚Ö
			vertMap++;
			if (++vertCount >= vertexCount) {
				break;
			}
		}
		vertBuff->Unmap(0, nullptr);
	}

	// ’è”ƒoƒbƒtƒ@‚Öƒf[ƒ^“]‘—
	ConstBufferData* constMap = nullptr;
	result = constBuff->Map(0, nullptr, (void**)&constMap);
	constMap->mat = camera->GetViewProjectionMatrix();
	constMap->matBillboard = camera->GetBillboardMatrix();
	constBuff->Unmap(0, nullptr);
}

void ParticleManager::Draw(ID3D12GraphicsCommandList* cmdList)
{
	UINT drawNum = (UINT)std::distance(particles.begin(), particles.end());
	if (drawNum > vertexCount) {
		drawNum = vertexCount;
	}

	// ƒp[ƒeƒBƒNƒ‹‚ª1‚Â‚à‚È‚¢ê‡
	if (drawNum == 0) {
		return;
	}

	// nullptrƒ`ƒFƒbƒN
	assert(cmdList);

	// ƒpƒCƒvƒ‰ƒCƒ“ƒXƒe[ƒg‚Ìİ’è
	cmdList->SetPipelineState(pipelinestate.Get());
	// ƒ‹[ƒgƒVƒOƒlƒ`ƒƒ‚Ìİ’è
	cmdList->SetGraphicsRootSignature(rootsignature.Get());
	// ƒvƒŠƒ~ƒeƒBƒuŒ`ó‚ğİ’è
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_POINTLIST);

	// ’¸“_ƒoƒbƒtƒ@‚Ìİ’è
	cmdList->IASetVertexBuffers(0, 1, &vbView);

	// ƒfƒXƒNƒŠƒvƒ^ƒq[ƒv‚Ì”z—ñ
	ID3D12DescriptorHeap* ppHeaps[] = { descHeap.Get() };
	cmdList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);

	// ’è”ƒoƒbƒtƒ@ƒrƒ…[‚ğƒZƒbƒg
	cmdList->SetGraphicsRootConstantBufferView(0, constBuff->GetGPUVirtualAddress());
	// ƒVƒF[ƒ_ƒŠƒ\[ƒXƒrƒ…[‚ğƒZƒbƒg
	cmdList->SetGraphicsRootDescriptorTable(1, gpuDescHandleSRV);
	// •`‰æƒRƒ}ƒ“ƒh
	cmdList->DrawInstanced(drawNum, 1, 0, 0);
}

void ParticleManager::Add(int life, XMFLOAT3 position, XMFLOAT3 velocity, XMFLOAT3 accel, float start_scale, float end_scale)
{
	// ƒŠƒXƒg‚É—v‘f‚ğ’Ç‰Á
	particles.emplace_front();
	// ’Ç‰Á‚µ‚½—v‘f‚ÌQÆ
	Particle& p = particles.front();
	p.position = position;
	p.velocity = velocity;
	p.accel = accel;
	p.s_scale = start_scale;
	p.e_scale = end_scale;
	p.num_frame = life;
}

void ParticleManager::InitializeDescriptorHeap()
{
	HRESULT result = S_FALSE;

	// ƒfƒXƒNƒŠƒvƒ^ƒq[ƒv‚ğ¶¬	
	D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc = {};
	descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;//ƒVƒF[ƒ_‚©‚çŒ©‚¦‚é‚æ‚¤‚É
	descHeapDesc.NumDescriptors = 1; // ƒVƒF[ƒ_[ƒŠƒ\[ƒXƒrƒ…[1‚Â
	result = device->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&descHeap));//¶¬
	if (FAILED(result)) {
		assert(0);
	}

	// ƒfƒXƒNƒŠƒvƒ^ƒTƒCƒY‚ğæ“¾
	descriptorHandleIncrementSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
}

void ParticleManager::InitializeGraphicsPipeline()
{
	HRESULT result = S_FALSE;
	ComPtr<ID3DBlob> vsBlob; // ’¸“_ƒVƒF[ƒ_ƒIƒuƒWƒFƒNƒg
	ComPtr<ID3DBlob> psBlob;	// ƒsƒNƒZƒ‹ƒVƒF[ƒ_ƒIƒuƒWƒFƒNƒg
	ComPtr<ID3DBlob> gsBlob;	// ƒWƒIƒƒgƒŠƒVƒF[ƒ_ƒIƒuƒWƒFƒNƒg
	ComPtr<ID3DBlob> errorBlob; // ƒGƒ‰[ƒIƒuƒWƒFƒNƒg

	// ’¸“_ƒVƒF[ƒ_‚Ì“Ç‚İ‚İ‚ÆƒRƒ“ƒpƒCƒ‹
	result = D3DCompileFromFile(
		L"Resources/shaders/ParticleVS.hlsl",	// ƒVƒF[ƒ_ƒtƒ@ƒCƒ‹–¼
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // ƒCƒ“ƒNƒ‹[ƒh‰Â”\‚É‚·‚é
		"main", "vs_5_0",	// ƒGƒ“ƒgƒŠ[ƒ|ƒCƒ“ƒg–¼AƒVƒF[ƒ_[ƒ‚ƒfƒ‹w’è
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // ƒfƒoƒbƒO—pİ’è
		0,
		&vsBlob, &errorBlob);
	if (FAILED(result)) {
		// errorBlob‚©‚çƒGƒ‰[“à—e‚ğstringŒ^‚ÉƒRƒs[
		std::string errstr;
		errstr.resize(errorBlob->GetBufferSize());

		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			errstr.begin());
		errstr += "\n";
		// ƒGƒ‰[“à—e‚ğo—ÍƒEƒBƒ“ƒhƒE‚É•\¦
		OutputDebugStringA(errstr.c_str());
		exit(1);
	}

	// ƒsƒNƒZƒ‹ƒVƒF[ƒ_‚Ì“Ç‚İ‚İ‚ÆƒRƒ“ƒpƒCƒ‹
	result = D3DCompileFromFile(
		L"Resources/shaders/ParticlePS.hlsl",	// ƒVƒF[ƒ_ƒtƒ@ƒCƒ‹–¼
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // ƒCƒ“ƒNƒ‹[ƒh‰Â”\‚É‚·‚é
		"main", "ps_5_0",	// ƒGƒ“ƒgƒŠ[ƒ|ƒCƒ“ƒg–¼AƒVƒF[ƒ_[ƒ‚ƒfƒ‹w’è
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // ƒfƒoƒbƒO—pİ’è
		0,
		&psBlob, &errorBlob);
	if (FAILED(result)) {
		// errorBlob‚©‚çƒGƒ‰[“à—e‚ğstringŒ^‚ÉƒRƒs[
		std::string errstr;
		errstr.resize(errorBlob->GetBufferSize());

		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			errstr.begin());
		errstr += "\n";
		// ƒGƒ‰[“à—e‚ğo—ÍƒEƒBƒ“ƒhƒE‚É•\¦
		OutputDebugStringA(errstr.c_str());
		exit(1);
	}

	// ƒWƒIƒƒgƒŠƒVƒF[ƒ_‚Ì“Ç‚İ‚İ‚ÆƒRƒ“ƒpƒCƒ‹
	result = D3DCompileFromFile(
		L"Resources/shaders/ParticleGS.hlsl",	// ƒVƒF[ƒ_ƒtƒ@ƒCƒ‹–¼
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // ƒCƒ“ƒNƒ‹[ƒh‰Â”\‚É‚·‚é
		"main", "gs_5_0",	// ƒGƒ“ƒgƒŠ[ƒ|ƒCƒ“ƒg–¼AƒVƒF[ƒ_[ƒ‚ƒfƒ‹w’è
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // ƒfƒoƒbƒO—pİ’è
		0,
		&gsBlob, &errorBlob);
	if (FAILED(result)) {
		// errorBlob‚©‚çƒGƒ‰[“à—e‚ğstringŒ^‚ÉƒRƒs[
		std::string errstr;
		errstr.resize(errorBlob->GetBufferSize());

		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			errstr.begin());
		errstr += "\n";
		// ƒGƒ‰[“à—e‚ğo—ÍƒEƒBƒ“ƒhƒE‚É•\¦
		OutputDebugStringA(errstr.c_str());
		exit(1);
	}

	// ’¸“_ƒŒƒCƒAƒEƒg
	D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
		{ // xyÀ•W(1s‚Å‘‚¢‚½‚Ù‚¤‚ªŒ©‚â‚·‚¢)
			"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		},
		{ // ƒXƒP[ƒ‹
			"TEXCOORD", 0, DXGI_FORMAT_R32_FLOAT, 0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		},
	};

	// ƒOƒ‰ƒtƒBƒbƒNƒXƒpƒCƒvƒ‰ƒCƒ“‚Ì—¬‚ê‚ğİ’è
	D3D12_GRAPHICS_PIPELINE_STATE_DESC gpipeline{};
	gpipeline.VS = CD3DX12_SHADER_BYTECODE(vsBlob.Get());
	gpipeline.PS = CD3DX12_SHADER_BYTECODE(psBlob.Get());
	gpipeline.GS = CD3DX12_SHADER_BYTECODE(gsBlob.Get());

	// ƒTƒ“ƒvƒ‹ƒ}ƒXƒN
	gpipeline.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // •W€İ’è
	// ƒ‰ƒXƒ^ƒ‰ƒCƒUƒXƒe[ƒg
	gpipeline.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	//gpipeline.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
	//gpipeline.RasterizerState.FillMode = D3D12_FILL_MODE_WIREFRAME;
	// ƒfƒvƒXƒXƒeƒ“ƒVƒ‹ƒXƒe[ƒg
	gpipeline.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	// ƒfƒvƒX‚Ì‘‚«‚İ‚ğ‹Ö~
	gpipeline.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ZERO;

	// ƒŒƒ“ƒ_[ƒ^[ƒQƒbƒg‚ÌƒuƒŒƒ“ƒhİ’è
	D3D12_RENDER_TARGET_BLEND_DESC blenddesc{};
	blenddesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;	// RBGA‘S‚Ä‚Ìƒ`ƒƒƒ“ƒlƒ‹‚ğ•`‰æ
	blenddesc.BlendEnable = true;
	// ‰ÁZƒuƒŒƒ“ƒfƒBƒ“ƒO
	blenddesc.BlendOp = D3D12_BLEND_OP_ADD;
	blenddesc.SrcBlend = D3D12_BLEND_ONE;
	blenddesc.DestBlend = D3D12_BLEND_ONE;
	//// Œ¸ZƒuƒŒƒ“ƒfƒBƒ“ƒO
	//blenddesc.BlendOp = D3D12_BLEND_OP_REV_SUBTRACT;
	//blenddesc.SrcBlend = D3D12_BLEND_ONE;
	//blenddesc.DestBlend = D3D12_BLEND_ONE;

	blenddesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;
	blenddesc.SrcBlendAlpha = D3D12_BLEND_ONE;
	blenddesc.DestBlendAlpha = D3D12_BLEND_ZERO;

	// ƒuƒŒƒ“ƒhƒXƒe[ƒg‚Ìİ’è
	gpipeline.BlendState.RenderTarget[0] = blenddesc;

	// [“xƒoƒbƒtƒ@‚ÌƒtƒH[ƒ}ƒbƒg
	gpipeline.DSVFormat = DXGI_FORMAT_D32_FLOAT;

	// ’¸“_ƒŒƒCƒAƒEƒg‚Ìİ’è
	gpipeline.InputLayout.pInputElementDescs = inputLayout;
	gpipeline.InputLayout.NumElements = _countof(inputLayout);

	// }Œ`‚ÌŒ`óİ’èiOŠpŒ`j
	gpipeline.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT;

	gpipeline.NumRenderTargets = 1;	// •`‰æ‘ÎÛ‚Í1‚Â
	gpipeline.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM; // 0`255w’è‚ÌRGBA
	gpipeline.SampleDesc.Count = 1; // 1ƒsƒNƒZƒ‹‚É‚Â‚«1‰ñƒTƒ“ƒvƒŠƒ“ƒO

	// ƒfƒXƒNƒŠƒvƒ^ƒŒƒ“ƒW
	CD3DX12_DESCRIPTOR_RANGE descRangeSRV;
	descRangeSRV.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0); // t0 ƒŒƒWƒXƒ^

	// ƒ‹[ƒgƒpƒ‰ƒ[ƒ^
	CD3DX12_ROOT_PARAMETER rootparams[2];
	rootparams[0].InitAsConstantBufferView(0, 0, D3D12_SHADER_VISIBILITY_ALL);
	rootparams[1].InitAsDescriptorTable(1, &descRangeSRV, D3D12_SHADER_VISIBILITY_ALL);

	// ƒXƒ^ƒeƒBƒbƒNƒTƒ“ƒvƒ‰[
	CD3DX12_STATIC_SAMPLER_DESC samplerDesc = CD3DX12_STATIC_SAMPLER_DESC(0);

	// ƒ‹[ƒgƒVƒOƒlƒ`ƒƒ‚Ìİ’è
	CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC rootSignatureDesc;
	rootSignatureDesc.Init_1_0(_countof(rootparams), rootparams, 1, &samplerDesc, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	ComPtr<ID3DBlob> rootSigBlob;
	// ƒo[ƒWƒ‡ƒ“©“®”»’è‚ÌƒVƒŠƒAƒ‰ƒCƒY
	result = D3DX12SerializeVersionedRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob, &errorBlob);
	// ƒ‹[ƒgƒVƒOƒlƒ`ƒƒ‚Ì¶¬
	result = device->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(), IID_PPV_ARGS(&rootsignature));
	if (FAILED(result)) {
		assert(0);
	}

	gpipeline.pRootSignature = rootsignature.Get();

	// ƒOƒ‰ƒtƒBƒbƒNƒXƒpƒCƒvƒ‰ƒCƒ“‚Ì¶¬
	result = device->CreateGraphicsPipelineState(&gpipeline, IID_PPV_ARGS(&pipelinestate));

	if (FAILED(result)) {
		assert(0);
	}
}

void ParticleManager::LoadTexture()
{
	HRESULT result = S_FALSE;

	// WICƒeƒNƒXƒ`ƒƒ‚Ìƒ[ƒh
	TexMetadata metadata{};
	ScratchImage scratchImg{};

	result = LoadFromWICFile(
		L"Resources/2d/effect1.png", WIC_FLAGS_NONE,
		&metadata, scratchImg);
	if (FAILED(result)) {
		assert(0);
	}

	const Image* img = scratchImg.GetImage(0, 0, 0); // ¶ƒf[ƒ^’Šo

	// ƒŠƒ\[ƒXİ’è
	CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		metadata.format,
		metadata.width,
		(UINT)metadata.height,
		(UINT16)metadata.arraySize,
		(UINT16)metadata.mipLevels
	);

	// ƒeƒNƒXƒ`ƒƒ—pƒoƒbƒtƒ@‚Ì¶¬
	result = device->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0),
		D3D12_HEAP_FLAG_NONE,
		&texresDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ, // ƒeƒNƒXƒ`ƒƒ—pw’è
		nullptr,
		IID_PPV_ARGS(&texbuff));
	if (FAILED(result)) {
		assert(0);
	}

	// ƒeƒNƒXƒ`ƒƒƒoƒbƒtƒ@‚Éƒf[ƒ^“]‘—
	result = texbuff->WriteToSubresource(
		0,
		nullptr, // ‘S—Ìˆæ‚ÖƒRƒs[
		img->pixels,    // Œ³ƒf[ƒ^ƒAƒhƒŒƒX
		(UINT)img->rowPitch,  // 1ƒ‰ƒCƒ“ƒTƒCƒY
		(UINT)img->slicePitch // 1–‡ƒTƒCƒY
	);
	if (FAILED(result)) {
		assert(0);
	}

	// ƒVƒF[ƒ_ƒŠƒ\[ƒXƒrƒ…[ì¬
	cpuDescHandleSRV = CD3DX12_CPU_DESCRIPTOR_HANDLE(descHeap->GetCPUDescriptorHandleForHeapStart(), 0, descriptorHandleIncrementSize);
	gpuDescHandleSRV = CD3DX12_GPU_DESCRIPTOR_HANDLE(descHeap->GetGPUDescriptorHandleForHeapStart(), 0, descriptorHandleIncrementSize);

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{}; // İ’è\‘¢‘Ì
	D3D12_RESOURCE_DESC resDesc = texbuff->GetDesc();

	srvDesc.Format = resDesc.Format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;//2DƒeƒNƒXƒ`ƒƒ
	srvDesc.Texture2D.MipLevels = 1;

	device->CreateShaderResourceView(texbuff.Get(), //ƒrƒ…[‚ÆŠÖ˜A•t‚¯‚éƒoƒbƒtƒ@
		&srvDesc, //ƒeƒNƒXƒ`ƒƒİ’èî•ñ
		cpuDescHandleSRV
	);
}

void ParticleManager::CreateModel()
{
	HRESULT result = S_FALSE;

	// ’¸“_ƒoƒbƒtƒ@¶¬
	result = device->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeof(VertexPos) * vertexCount),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertBuff));
	if (FAILED(result)) {
		assert(0);
		return;
	}

	// ’¸“_ƒoƒbƒtƒ@ƒrƒ…[‚Ìì¬
	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	vbView.SizeInBytes = sizeof(VertexPos) * vertexCount;
	vbView.StrideInBytes = sizeof(VertexPos);
}
>>>>>>> master
