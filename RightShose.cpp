#include "RightShose.h"
#include"Collision.h"
#include<sstream>
#include<iomanip>
#include <Easing.h>
#include"ImageManager.h"
using namespace DirectX;

RightShose::RightShose() {
	model = ModelManager::GetIns()->GetModel(ModelManager::RightShoes);
	enemyobj = new Object3d();
}

void RightShose::Initialize(bool shadow) {
	assert(player);
	this->shadow = shadow;
	IsAlive = 0;
	enemyobj = Object3d::Create();
	enemyobj->SetModel(model);
	pos = { 10.0f,0.0f,0.0f };
	enemyobj->SetPosition(pos);
	
	rot = { 0,270,0 };
	Afterrot.y = rot.y;
	enemyobj->SetRotation(rot);
	enemyobj->SetScale({ 0.3f,0.3f,0.3f });
	texture = Texture::Create(ImageManager::shadow, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	texture->TextureCreate();
	//texture->SetColor({ 1,1,1,1 });
	texture->SetPosition(pos.x, -100, pos.z);
	texture->SetRotation({ 90,0,0 });
	texture->SetScale({ 0.3f,0.3f,0.3f });
	shadow = false;
}

void RightShose::Finalize() {
	//delete enemyobj;
	delete texture;
}

//�{�X�̍s��
void RightShose::Spec() {
	XMFLOAT3 AfterPos{};
	if (AttackCount > 180 && pos.y <= 0.1f) {
		if (!active) {
			action = (rand() % 2);
			frame = 0;
			pat = 1;
			active = true;
		}
	}
	else {
		if (!active) {
			AttackCount++;
			/*angle += 2.0f;
			angle2 = angle * (3.14f / 180.0f);
			pos.y = sin(angle2) * 0.5f + 0.5f;
			enemyobj->SetPosition(pos);*/
		}
	}

	if (active) {
		if ((action % 2) == 0) {
			Afterrot.x = 0.0f;
			if (!stun) {
				//3��ːi����
				if (AttackC < 100) {
					MoveCount++;
				}
				//�������߂����猳�̈ʒu�ɖ߂�
				else {
					AfterPos = {
					10,
					0,
					0
					};
					Afterrot.y = 270;
					if (frame < 0.45f) {
						frame += 0.004f;
					}
					else {
						frame = 0;
						AttackC = 0;
						AttackCount = 30;
						active = false;
					}

					pos = {
					Ease(In,Cubic,frame,pos.x,AfterPos.x),
					0,
					Ease(In,Cubic,frame,pos.z,AfterPos.z),
					};
				}

				if (MoveCount == 80) {
					XMFLOAT3 position{};
					position.x = (player->GetPosition().x - pos.x);
					position.z = (player->GetPosition().z - pos.z);
					Afterrot.y = (atan2(position.x, position.z) * (180.0f / XM_PI)) - 270;// *(XM_PI / 180.0f);
				}
				//�v���C���[�̈ʒu�����b�N�I��������
				if (MoveCount == 100) {
					double sb, sbx, sbz;
					if (!Attack) {
						hitpoint = HitNot;
						sbx = player->GetPosition().x - pos.x;
						sbz = player->GetPosition().z - pos.z;
						
						sb = sqrt(sbx * sbx + sbz * sbz);
						speedX = sbx / sb * 0.5;
						speedZ = sbz / sb * 0.5;
						Attack = true;
					}
				}
			}
			else {
				if (stunTimer < 200) {
					stunTimer++;
				}
				else {
					stunTimer = 0;
					stun = false;
				}
			}


			if (Attack) {
				//�v���C���[�ɃX�s�[�h���Z
				pos.x += (float)speedX;
				pos.z += (float)speedZ;
				
				//�G�̈ʒu���ǂ܂ōs������߂�
				if (pos.x >= x_max) {
					hitpoint = HitRight;
					Deadbound.y = 0.5f;
					Deadbound.x = 0.2f;
					speedX = 0.0f;
					speedZ = 0.0f;
				}
				else if (pos.x <= x_min) {
					hitpoint = HitLeft;
					Deadbound.y = 0.5f;
					Deadbound.x = 0.2f;
					speedX = 0.0f;
					speedZ = 0.0f;
				}
				else if (pos.z >= z_max) {
					hitpoint = HitUp;
					Deadbound.y = 0.5f;
					Deadbound.z = 0.2f;
					speedX = 0.0f;
					speedZ = 0.0f;
				}
				else if (pos.z <= z_min) {
					hitpoint = HitDown;
					Deadbound.y = 0.5f;
					Deadbound.z = 0.2f;
					speedX = 0.0f;
					speedZ = 0.0f;
				}

				//���˂�悤�Ȋ����Ŗ߂�(�߂肫������U���񐔂����Z�����)
				if (hitpoint == HitRight) {
					Deadbound.y -= 0.02f;
					pos.y += Deadbound.y;
					if (pos.y > 0.0f) {
						pos.x -= Deadbound.x;
					}
					else {
						pos.y = 0.0f;
					}

					if (pos.y == 0.0f) {
						MoveCount = 0;
						Attack = false;
						hitpoint = HitNot;
						AttackC++;
					}
				}
				else if (hitpoint == HitLeft) {
					Deadbound.y -= 0.02f;
					pos.y += Deadbound.y;
					if (pos.y > 0.0f) {
						pos.x += Deadbound.x;
					}
					else {
						pos.y = 0.0f;
					}

					if (pos.y == 0.0f) {
						MoveCount = 0;
						Attack = false;
						hitpoint = HitNot;
						AttackC++;
					}
				}
				else if (hitpoint == HitUp) {
					Deadbound.y -= 0.02f;
					pos.y += Deadbound.y;
					if (pos.y > 0.0f) {
						pos.z -= Deadbound.z;
					}
					else {
						pos.y = 0.0f;
					}

					if (pos.y == 0.0f) {
						MoveCount = 0;
						Attack = false;
						hitpoint = HitNot;
						AttackC++;
					}
				}
				else if (hitpoint == HitDown) {
					Deadbound.y -= 0.02f;
					pos.y += Deadbound.y;
					if (pos.y > 0.0f) {
						pos.z += Deadbound.z;
					}
					else {
						pos.y = 0.0f;
					}

					if (pos.y == 0.0f) {
						MoveCount = 0;
						Attack = false;
						hitpoint = HitNot;
						AttackC++;
					}
				}
			}
			enemyobj->SetPosition(pos);
		}
		if ((action % 2) == 1) {
			if (AttackC < 3) {
				Afterrot.x = 270.0f;
				switch (pat) {
				case 1:
					AfterPos = {
						player->GetPosition().x + 5,
						5,
						player->GetPosition().z
					};
					if (aiming < 180) {
						frame = 0.5f;
						aiming++;
						break;
					}
					else {
						frame = 0;
						targetpos.x = player->GetPosition().x + 1;
						aiming = 0;
						pat++;
						break;
					}
				case 2:
					AfterPos = {
						pos.x,
						0,
						pos.z,
					};
					if (frame < 1.0f) {
						frame += 0.01f;
						break;
					}
					else {
						frame = 0;
						pat++;
						break;
					}
				case 3:
					AfterPos = {
						targetpos.x,
						0,
						pos.z,
					};
					if (frame < 1.0f) {
						frame += 0.08f;
						break;
					}
					if (frame >= 1.0f) {
						frame = 1.0f;
						if (coolT < 90) {
							coolT++;
							break;
						}
						else {
							coolT = 0;
							frame = 0;
							pat = 1;
							AttackC++;
							break;
						}
					}
				default:
					AttackC = 0;
					pat = 1;
					break;
				}
			}
			else {
				switch (pat) {
				case 1:
					AfterPos = {
					pos.x,
					pos.y,
					pos.z
					};
					if (frame < 1.0f) {
						frame += 0.01f;
						break;
					}
					else {
						frame = 0;
						pat++;
						break;
					}
				case 2:
					Afterrot.x = 0.0f;
					AfterPos = {
					10,
					0,
					0
					};
					if (frame < 1.0f) {
						frame += 0.01f;
						break;
					}
					else {
						frame = 0;
						pat = 0;
						AttackC = 0;
						AttackCount = 30;
						Effect = true;
						active = false;
						break;
					}
				default:
					break;
				}
			}
			pos = {
	Ease(In,Cubic,frame,pos.x,AfterPos.x),
	Ease(In,Cubic,frame,pos.y,AfterPos.y),
	Ease(In,Cubic,frame,pos.z,AfterPos.z)
			};
			enemyobj->SetPosition(pos);
		}
	}
	rot.y = Ease(In, Quint, 0.7f, rot.y, Afterrot.y);
	rot.x = Ease(In, Quint, 0.7f, rot.x, Afterrot.x);
	enemyobj->SetRotation(rot);
}

void RightShose::App(int Timer) {

	XMFLOAT3 AfterPos{};
	XMFLOAT3 AfterRot{};

	if (Timer == 0) {
		pos = { 13.0f,0.0f,18.0f };
		rot = { 0.0f,315.0f,0.0f };
	}
	
	if (Timer == 150 || Timer == 280 || Timer == 300){
		appearMove++;
		frame = 0.0f;
		frame2 = 0.0f;
	}

	//�����V�[���ɂ����ăt���[�����ɂ���čs�������߂�
	switch (appearMove) {
	case 1:
		AfterPos = {
						0,
						0,
						-8,
		};
		if (frame < 1.0f) {
			frame += 0.005f;
			break;
		}
		else {
			frame = 0.0f;
			break;
		}

	case 2:
		pos = { 10.0f,0.0f,0.0f };
		rot = { 0,270,0 };
	case 3:
		if (rot.y >= -90) {
			rot.y -= 2.0f;
		}
		else {
			appearMove = 0;
			rot.y = 270;
		}
	}

	pos = {
	Ease(In,Cubic,frame,pos.x,AfterPos.x),
	Ease(In,Cubic,frame,pos.y,AfterPos.y),
	Ease(In,Cubic,frame,pos.z,AfterPos.z)
	};

	rot = {
	Ease(In,Cubic,frame2,rot.x,AfterRot.x),
	Ease(In,Cubic,frame2,rot.y,AfterRot.y),
	Ease(In,Cubic,frame2,rot.z,AfterRot.z)
	};
	enemyobj->SetPosition(pos);
	enemyobj->SetRotation(rot);
}

void RightShose::End(int Timer) {
	//�{�X��|�������Ƃ̋���(��ŋL�q)
	XMFLOAT3 scale = {0.8f,0.8f,0.8f};
	float RotPower = 0.0f;
	XMFLOAT3 AfterScale{};
	//float endframe = 0.0f;
	//�{�X��|�������Ƃ̋���(��ŋL�q)
	if (Timer == 300) {
		pos = { 5.0f,0.0f,0.0f };
		rot = { 0,270,0 };
	}

	if (Timer == 450) {
		EndMove++;
		endframe = 0.0f;
	}

	switch (EndMove) {
	case 1:
		AfterScale = {
						0.2f,
						0.2f,
						0.2f,
		};

		if (endframe < 1.0f) {
			endframe += 0.005f;
			break;
		}
		else {
			endframe = 1.0f;
			RotPower = 0.0f;
			EndMove++;
			break;
		}

	case 2:
		if (rot.x >= -90) {
			rot.x -= 2.0f;
		}

		//case 2:
		//	AfterPos = {
		//				pos.x,
		//				1,
		//				pos.z,
		//	};

		//	if (frame < 1.0f) {
		//		frame += 0.08f;
		//		break;
		//	}
		//	else {
		//		frame = 1.0f;
		//		break;
		//	}
	}

	RotPower = Ease(In, Cubic, endframe, RotPower, 20.0f);
	if (EndMove == 1) {
		rot.y -= RotPower;
	}

	scale = {
	Ease(In,Cubic,endframe,scale.x,0.2f),
	Ease(In,Cubic,endframe,scale.y,0.2f),
	Ease(In,Cubic,endframe,scale.z,0.2f),
	};

	enemyobj->SetScale(scale);
	enemyobj->SetPosition(pos);
	enemyobj->SetRotation(rot);
}
void RightShose::specialDraw() {
}

void RightShose::SetAct(LeftShose* leftshose) {
	int action = leftshose->GetAction();
	int AttackCount = leftshose->GetAttackCount();
	int pat = leftshose->GetPat();
	this->action = action;
	if (leftshose->GetHP() > 0) {
		this->AttackCount = AttackCount;
	}
	if (pat == 5 && pos.y == 0.0f) {
		AttackC = 101;
	}

	LeftAct = leftshose->GetActive();
}

bool RightShose::HitShose(LeftShose* leftshose) {
	XMFLOAT3 leftpos = leftshose->GetPosition();
	if (Collision::SphereCollision(pos.x, pos.y, pos.z, 1.5f, leftpos.x, leftpos.y, leftpos.z, 1.5f) && (action % 2) == 0) {
		this->stun = true;
		leftshose->SetStun(true);
		if (pos.z >= leftpos.z) {
			hitpoint = HitUp;
			Deadbound.y = 0.3f;
			Deadbound.z = -0.2f;
		}
		else {
			hitpoint = HitDown;
			Deadbound.y = 0.3f;
			Deadbound.z = 0.2f;
		}
		return true;
	}
	else {
		return false;
	}
}