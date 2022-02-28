#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>

class Texture
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
	struct VertexPosNormalUv
	{
		XMFLOAT3 pos; // xyz���W
		XMFLOAT3 normal; // �@���x�N�g��
		XMFLOAT2 uv;  // uv���W
	};

	// �萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferData
	{
		XMFLOAT4 color;	// �F (RGBA)
		XMMATRIX mat;	// �R�c�ϊ��s��
	};

private: // �萔
	static const int division = 50;					// ������
	static const float radius;				// ��ʂ̔��a
	static const float prizmHeight;			// ���̍���
	static const int planeCount = division * 2 + division * 2;		// �ʂ̐�
	static const int vertexCount = 4;		// ���_��
	static const int indexCount = 3 * 2;
public: // �ÓI�����o�֐�
	/// �ÓI������
	static bool StaticInitialize(ID3D12Device* device, int window_width, int window_height);

	/// �e�N�X�`���ǂݍ���
	static bool LoadTexture(UINT texnumber, const wchar_t* filename);

	/// �`��O����
	static void PreDraw(ID3D12GraphicsCommandList* cmdList);

	/// �`��㏈��
	static void PostDraw();
	//�e�N�X�`������
	static Texture* Create(UINT texNumber, XMFLOAT3 position, XMFLOAT3 size, XMFLOAT4 color);
	/// ���_���W�̎擾
	static const XMFLOAT3& GetEye() { return eye; }

	/// ���_���W�̐ݒ�
	static void SetEye(XMFLOAT3 eye);

	/// �����_���W�̎擾
	static const XMFLOAT3& GetTarget() { return target; }

	/// �����_���W�̐ݒ�
	static void SetTarget(XMFLOAT3 target);

	/// �x�N�g���ɂ��ړ�
	static void CameraMoveVector(XMFLOAT3 move);

	/// �X�v���C�g����
	static Texture* Create(UINT texNumber, XMFLOAT2 position, XMFLOAT4 color = { 1, 1, 1, 1 }, XMFLOAT2 anchorpoint = { 0.0f, 0.0f }, bool isFlipX = false, bool isFlipY = false);

private: // �ÓI�����o�ϐ�
	static const int srvCount = 213;
	// �f�o�C�X
	static ID3D12Device* device;
	// �f�X�N���v�^�T�C�Y
	static UINT descriptorHandleIncrementSize;
	// �R�}���h���X�g
	static ID3D12GraphicsCommandList* cmdList;
	// ���[�g�V�O�l�`��
	static ComPtr<ID3D12RootSignature> rootsignature;
	// �p�C�v���C���X�e�[�g�I�u�W�F�N�g
	static ComPtr<ID3D12PipelineState> pipelinestate;
	// �f�X�N���v�^�q�[�v
	static ComPtr<ID3D12DescriptorHeap> descHeap;
	// ���_�o�b�t�@
	static ComPtr<ID3D12Resource> vertBuff;
	// �C���f�b�N�X�o�b�t�@
	static ComPtr<ID3D12Resource> indexBuff;
	// �e�N�X�`���o�b�t�@
	static ComPtr<ID3D12Resource> texbuff[srvCount];
	// �V�F�[�_���\�[�X�r���[�̃n���h��(CPU)
	static CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
	// �V�F�[�_���\�[�X�r���[�̃n���h��(CPU)
	static CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;
	// �r���[�s��
	static XMMATRIX matView;
	// �ˉe�s��
	static XMMATRIX matProjection;
	// ���_���W
	static XMFLOAT3 eye;
	// �����_���W
	static XMFLOAT3 target;
	// ������x�N�g��
	static XMFLOAT3 up;
	// ���_�o�b�t�@�r���[
	static D3D12_VERTEX_BUFFER_VIEW vbView;
	// �C���f�b�N�X�o�b�t�@�r���[
	static D3D12_INDEX_BUFFER_VIEW ibView;
	// ���_�f�[�^�z��
	static VertexPosNormalUv vertices[vertexCount];
	// ���_�C���f�b�N�X�z��
	static unsigned short indices[indexCount];
	private:
		UINT texNumber = 0;

private:// �ÓI�����o�֐�
	/// �f�X�N���v�^�q�[�v�̏�����
	static bool InitializeDescriptorHeap();

	/// �J����������
	static void InitializeCamera(int window_width, int window_height);

	/// �O���t�B�b�N�p�C�v���C������
	static bool InitializeGraphicsPipeline();

	/// ���f���쐬
	static void CreateModel();

	/// �r���[�s����X�V
	static void UpdateViewMatrix();

public: // �����o�֐�
	void TextureCreate();
	//�R���X�g���N�^
	Texture(UINT texNumber, XMFLOAT3 position, XMFLOAT3 size, XMFLOAT4 color);
	bool Initialize();
	/// ���t���[������
	void Update(XMMATRIX matview, XMMATRIX matprojection);

	/// �`��
	void Draw();

	/// ���W�̎擾
	const XMFLOAT3& GetPosition() { return position; }

	/// ���W�̐ݒ�
	void SetPosition(XMFLOAT3 position) { this->position = position; }
	void SetColor(XMFLOAT4 color) { this->color = color; }
	void SetRotation(XMFLOAT3 rotation) { this->rotation = rotation; }
	void SetScale(XMFLOAT3 scale) { this->scale = scale; }
	const XMFLOAT3& GetScale() { return scale; }
private: // �����o�ϐ�
	ComPtr<ID3D12Resource> constBuff; // �萔�o�b�t�@
	// �F
	static XMFLOAT4 color;
	// ���[�J���X�P�[��
	XMFLOAT3 scale = { 1,1,1 };
	// X,Y,Z�����̃��[�J����]�p
	XMFLOAT3 rotation = { 0,0,0 };
	// ���[�J�����W
	XMFLOAT3 position = { 0,0,0 };
	// ���[�J�����[���h�ϊ��s��
	XMMATRIX matWorld;
	
};


