#pragma once
#include"InterEnemy.h"

class BossEnemy;
class Rice :public InterEnemy {
public:
	Rice();

	void Initialize() override;//������
	void Finalize() override;//�J��
	void Update()override;//�X�V
	void Demo(int num=0);//�`���[�g���A���X�V
	void Draw() override;//�`��
	//�Q�b�^�[�Z�b�^�[
	void SetHit(const bool& hit) { this->hit = hit; }
	const bool& GetHit() { return hit; };
	const bool& GetStart() { return start; };
	void SetExP(const XMFLOAT3& exp) { this->exP = exp; }
	
private:
//�����o�֐�   
	bool collidePlayer() override;
	bool collideAttackArm() override;
	bool collideArm();
	bool BoundEnemy();
	bool LockOn();
	void Move();
	void Rebound();
//�����o�ϐ�
	//�I�u�W�F�N�g��e�N�X�`��
	Object3d* Piyopiyo;
	Texture* net[2] = { nullptr };
	//�G��AI�֌W
	XMFLOAT3 smooth{ pos.x, pos.y,pos.z };
	float speed_y = 3.0f/20.0f;
	const float gravity = speed_y/20.0f;
	float speed_y2 = 1.5f / 20.0f;
	const float gravity2 = speed_y2 / 20.0f;
	bool stun = false;
	bool hit=false;
	bool start = false;
	XMFLOAT3 exP{};
};

