#pragma once
<<<<<<< HEAD
#include <DirectXMath.h>
#include"CollisionPrimitive.h"
/// <summary>
/// 当たり判定ヘルパークラス
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
private: // エイリアス
// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
>>>>>>> master
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
<<<<<<< HEAD
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	//球と球
	static bool SphereCollision(const float& X1, const float& Y1, const float& Z1, const float& R1, const float& X2, const float& Y2, const float& Z2, const float& R2);
	static bool SphereCollision2(const XMFLOAT3& pos1, const float& R1, const XMFLOAT3& pos2, const float& R2);

	//円と円
	static bool CircleCollision(const float& X1, const float& Y1, const float& R1, const float& X2, const float& Y2,const float& R2);

	/// <summary>
	/// 球と平面の当たり判定
	/// </summary>
	///<param name="sphere">球</param>
	///<param name="plane">平面</param>
	///<param name="inter">交点（平面上の最高接点）</param>
	///<returns>交差しているか否か</returns>
	static bool CheckSphere2Plane(const Sphere& sphere, const Plane&
		plane, DirectX::XMVECTOR* inter = nullptr);
	/// <summary>
/// 球と球の当たり判定
/// </summary>
///<param name="sphere">球</param>
///<param name="sphere2">球</param>
///<param name="inter">交点（平面上の最高接点）</param>
///<returns>交差しているか否か</returns>
	static bool CheckSphere2Sphere(const Sphere& sphere, const Sphere&
		sphere2, DirectX::XMVECTOR* inter = nullptr);
	/// <summary>
/// 点と三角形の最近接点を求める
/// </summary>
///<param name="point">点</param>
///<param name="triangle">三角形</param>
///<param name="closest">最近接点（出力用）</param>
///<returns>交差しているか否か</returns>
	static void ClosestPtPoint2Triangle(const DirectX::XMVECTOR& point,
		const Triangle& triangle, DirectX::XMVECTOR* closest);

	/// <summary>
/// 球と法線付き三角形の当たりチェック
/// </summary>
///<param name="sphere">球</param>
///<param name="triangle">三角形</param>
///<param name="inter">交点</param>
///<returns>交差しているか否か</returns>
	static bool CheckSphere2Triangle(const Sphere& sphere,
		const Triangle& triangle, DirectX::XMVECTOR* inter = nullptr);

	/// <summary>
	///	レイと平面の当たりチェック
	/// </summary>
	///<param name="lay">レイ</param>
	///<param name="plane">平面</param>
	///<param name="inter">距離</param>
	///
	///<returns>交差しているか否か</returns>
	static bool CheckRay2Plane(const Ray& ray, const Plane& plane,
		float* distance = nullptr, DirectX::XMVECTOR* inter = nullptr);
=======
	using XMMATRIX = DirectX::XMMATRIX;
>>>>>>> master

public:

	//当たり判定関数
	//円と円
	static bool CircleCollision(const float& X1, const float& Y1, const float& R1, const float& X2, const float& Y2, const float& R2);
	//球と球
	static bool SphereCollision(const float& X1, const float& Y1, const float& Z1, const float& R1, const float& X2, const float& Y2, const float& Z2,const float& R2);
	//球と球2
	static bool CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB, DirectX::XMVECTOR* inter = nullptr, DirectX::XMVECTOR* reject = nullptr);
	//平面と球
	static bool CheckSphere2Plane(const Sphere& sphere, const Plane& plane, XMVECTOR* inter = nullptr);
	//点と三角形
	static void ClodestPtPoint2Triangle(const XMVECTOR& point, const Triangle& triangle, XMVECTOR* closest);
	//球と三角形
	static bool CheckSphere2Triangle(const Sphere& sphere, const Triangle& triangle, DirectX::XMVECTOR* inter = nullptr, DirectX::XMVECTOR* reject = nullptr);
	//レイと平面
	static bool CheckRay2Plane(const Ray& ray, const Plane& plane, float* distance = nullptr, XMVECTOR* inter = nullptr);
	//レイと三角形
	static bool CheckRay2Triangle(const Ray& ray, const Triangle& triangle, float* distance = nullptr, XMVECTOR* inter = nullptr);
	//レイと球
	static bool CheckRay2Sphere(const Ray& ray, const Sphere& sphere, float* distance = nullptr, XMVECTOR* inter = nullptr);
};