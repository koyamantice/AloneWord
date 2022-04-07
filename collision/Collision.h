#pragma once
<<<<<<< HEAD
#include <DirectXMath.h>
#include"CollisionPrimitive.h"
/// <summary>
/// �����蔻��w���p�[�N���X
/// </summary>
class Collision {
private:
=======
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include "CollisionPrimitive.h"
class Collision {
private: // �G�C���A�X
// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
>>>>>>> master
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
<<<<<<< HEAD
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	//���Ƌ�
	static bool SphereCollision(const float& X1, const float& Y1, const float& Z1, const float& R1, const float& X2, const float& Y2, const float& Z2, const float& R2);
	static bool SphereCollision2(const XMFLOAT3& pos1, const float& R1, const XMFLOAT3& pos2, const float& R2);

	//�~�Ɖ~
	static bool CircleCollision(const float& X1, const float& Y1, const float& R1, const float& X2, const float& Y2,const float& R2);

	/// <summary>
	/// ���ƕ��ʂ̓����蔻��
	/// </summary>
	///<param name="sphere">��</param>
	///<param name="plane">����</param>
	///<param name="inter">��_�i���ʏ�̍ō��ړ_�j</param>
	///<returns>�������Ă��邩�ۂ�</returns>
	static bool CheckSphere2Plane(const Sphere& sphere, const Plane&
		plane, DirectX::XMVECTOR* inter = nullptr);
	/// <summary>
/// ���Ƌ��̓����蔻��
/// </summary>
///<param name="sphere">��</param>
///<param name="sphere2">��</param>
///<param name="inter">��_�i���ʏ�̍ō��ړ_�j</param>
///<returns>�������Ă��邩�ۂ�</returns>
	static bool CheckSphere2Sphere(const Sphere& sphere, const Sphere&
		sphere2, DirectX::XMVECTOR* inter = nullptr);
	/// <summary>
/// �_�ƎO�p�`�̍ŋߐړ_�����߂�
/// </summary>
///<param name="point">�_</param>
///<param name="triangle">�O�p�`</param>
///<param name="closest">�ŋߐړ_�i�o�͗p�j</param>
///<returns>�������Ă��邩�ۂ�</returns>
	static void ClosestPtPoint2Triangle(const DirectX::XMVECTOR& point,
		const Triangle& triangle, DirectX::XMVECTOR* closest);

	/// <summary>
/// ���Ɩ@���t���O�p�`�̓�����`�F�b�N
/// </summary>
///<param name="sphere">��</param>
///<param name="triangle">�O�p�`</param>
///<param name="inter">��_</param>
///<returns>�������Ă��邩�ۂ�</returns>
	static bool CheckSphere2Triangle(const Sphere& sphere,
		const Triangle& triangle, DirectX::XMVECTOR* inter = nullptr);

	/// <summary>
	///	���C�ƕ��ʂ̓�����`�F�b�N
	/// </summary>
	///<param name="lay">���C</param>
	///<param name="plane">����</param>
	///<param name="inter">����</param>
	///
	///<returns>�������Ă��邩�ۂ�</returns>
	static bool CheckRay2Plane(const Ray& ray, const Plane& plane,
		float* distance = nullptr, DirectX::XMVECTOR* inter = nullptr);
=======
	using XMMATRIX = DirectX::XMMATRIX;
>>>>>>> master

public:

	//�����蔻��֐�
	//�~�Ɖ~
	static bool CircleCollision(const float& X1, const float& Y1, const float& R1, const float& X2, const float& Y2, const float& R2);
	//���Ƌ�
	static bool SphereCollision(const float& X1, const float& Y1, const float& Z1, const float& R1, const float& X2, const float& Y2, const float& Z2,const float& R2);
	//���Ƌ�2
	static bool CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB, DirectX::XMVECTOR* inter = nullptr, DirectX::XMVECTOR* reject = nullptr);
	//���ʂƋ�
	static bool CheckSphere2Plane(const Sphere& sphere, const Plane& plane, XMVECTOR* inter = nullptr);
	//�_�ƎO�p�`
	static void ClodestPtPoint2Triangle(const XMVECTOR& point, const Triangle& triangle, XMVECTOR* closest);
	//���ƎO�p�`
	static bool CheckSphere2Triangle(const Sphere& sphere, const Triangle& triangle, DirectX::XMVECTOR* inter = nullptr, DirectX::XMVECTOR* reject = nullptr);
	//���C�ƕ���
	static bool CheckRay2Plane(const Ray& ray, const Plane& plane, float* distance = nullptr, XMVECTOR* inter = nullptr);
	//���C�ƎO�p�`
	static bool CheckRay2Triangle(const Ray& ray, const Triangle& triangle, float* distance = nullptr, XMVECTOR* inter = nullptr);
	//���C�Ƌ�
	static bool CheckRay2Sphere(const Ray& ray, const Sphere& sphere, float* distance = nullptr, XMVECTOR* inter = nullptr);
};