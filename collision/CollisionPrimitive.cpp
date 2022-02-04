#include "CollisionPrimitive.h"

using namespace DirectX;

void Triangle::ComputeNormal() {

	XMVECTOR p0_p1 = p1 - p0;
	XMVECTOR p1_p2 = p2 - p0;
	
	//外積により、二辺に垂直なベクトル
	normal = XMVector3Cross(p0_p1, p1_p2);
	normal = XMVector3Normalize(normal);
}
