#include "LeftHand.h"
#include"Collision.h"
#include<sstream>
#include<iomanip>
#include <Easing.h>
using namespace DirectX;
#include"ImageManager.h"

//�R���X�g���N�^
LeftHand::LeftHand() {
	model = ModelManager::GetIns()->GetModel(ModelManager::LeftHand_Open);
	hand_closemodel = ModelManager::GetIns()->GetModel(ModelManager::LeftHand_Close);
	for (std::size_t i = 0; i < humanwave.size(); i++) {
		humanwave[i] = new HumanWave;
		humanwave[i]->Init();
	}
}

//������
void LeftHand::Initialize(bool shadow) {
	assert(player);
	this->shadow = shadow;
	IsAlive = 0;
	pos = { -10.0f,0.0f,0.0f };
	rot = { 0,270,0 };
	Afterrot.y = rot.y;

	//�G
	Object3d*enemyobj_ = new Object3d();
	enemyobj_ = Object3d::Create();
	enemyobj_->SetModel(model);
	enemyobj_->SetPosition(pos);
	enemyobj_->SetRotation(rot);
	enemyobj_->SetScale({ 0.8f,0.8f,0.8f });
	enemyobj.reset(enemyobj_);
	//�e(���̃I�u�W�F�N�g�ł͎g��Ȃ�)
	texture = Texture::Create(ImageManager::shadow, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	texture->TextureCreate();
	//texture->SetColor({ 1,1,1,1 });
	texture->SetPosition(pos.x, -100, pos.z);
	texture->SetRotation({ 90,0,0 });
	texture->SetScale({ 0.3f,0.3f,0.3f });

	////�X�^�����̂҂�҂�

	//for (std::size_t i = 0; i < Stuntexture.size(); i++) {
	//	Stuntexture[i] = Texture::Create(ImageManager::Stun, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	//	Stuntexture[i]->TextureCreate();
	//	Stuntexture[i]->SetRotation({ 0,0,0 });
	//	Stuntexture[i]->SetScale({ 0.05f,0.05f,0.05f });
	//	Stunscale[i] = 1.0f;
	//	StunSpeed[0] = 0.0f;
	//	StunSpeed[1] = 90.0f;
	//	StunSpeed[2] = 180.0f;
	//	StunSpeed[3] = 270.0f;
	//	Stunradius[i] = StunSpeed[i] * PI / 180.0f;
	//	StunCircleX[i] = cosf(Stunradius[i]) * Stunscale[i];
	//	StunCircleZ[i] = sinf(Stunradius[i]) * Stunscale[i];
	//	StunPos[i].x = StunCircleX[i] + pos.x;
	//	StunPos[i].z = StunCircleZ[i] + pos.z;
	//	StunPos[i].y = pos.y + 3;
	//	Stuntexture[i]->SetPosition(StunPos[i]);
	//	Stuntexture[i]->Update();
	//}
}

//�J��
void LeftHand::Finalize() {
	//delete enemyobj;
	for (std::size_t i = 0; i < humanwave.size(); i++) {
		humanwave[i]->Final();
	}
	delete texture;
}

//�{�X�̍s��
void LeftHand::Spec() {
	for (std::size_t i = 0; i < humanwave.size(); i++) {
		humanwave[i]->Upda();
		humanwave[i]->SetPlayer(player.get());
	}
	XMFLOAT3 AfterPos{};
	if (stateNumber == Open) {
		enemyobj->SetModel(model);
	}
	else if (stateNumber == Close) {
		enemyobj->SetModel(hand_closemodel);
	}
	//�����ōs�������߂�
	if (AttackCount == 180) {
		if (!active) {
			//action = (rand() % 2);
			AttackCount = 0;
			frame = 0;
			pat = 1;
			active = true;
		}
	}
	//�U��������܂ł̃C���^�[�o��
	else {
		if (!active) {
			//AttackCount++;
			/*angle += 2.0f;
			angle2 = angle * (3.14f / 180.0f);
			pos.y = sin(angle2) * 0.5f + 0.5f;
			enemyobj->SetPosition(pos);*/
		}
	}

	//�s���J�n
	if (active) {
		if (action == 0) {
			if (AttackC < 3) {
				switch (pat) {
				case 1:
					AfterPos = {
					pos.x,
					15.0f,
					pos.z
					};
					if (frame < 0.45f) {
						frame += 0.002f;
						break;
					}
					else {
						Afterrot.x = 90.0f;
						Afterrot.y = 180.0f;
						stateNumber = Close;
						frame = 0;
						pat++;
						break;
					}
				case 2:
					AfterPos.y = 0.0f;
					if (frame < 0.45f) {
						frame += 0.002f;
					}
					else {
						frame = 0;
						pat++;
					}
					pos.y = Ease(In, Cubic, frame, pos.y, AfterPos.y);
				case 3:
					AfterPos = {
					pos.x,
					3.0f,
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
				case 4:
					AfterPos = {
						player->GetPosition().x,
					7.0f,
						player->GetPosition().z
					};
					if (aiming < 20) {
						frame = 0.5f;
						aiming++;
						break;
					}
					else {
						frame = 0;
						aiming = 0;
						pat++;
						break;
					}
				case 5:
					AfterPos = {
						pos.x,
						0,
						pos.z,
					};
					if (frame < 1.0f) {
						frame += 0.08f;
						//Afterrot.z += vel;
						if (rot.z > 45) {
							rot.z = 45;
							//vel = -vel;
						}
						if (rot.z < -45) {
							rot.z = -45;
							//vel = -vel;
						}
						break;
					}
					else {
						for (std::size_t i = 0; i < humanwave.size(); i++) {
							if (!humanwave[i]->GetExpand()) {
								humanwave[i]->Set(pos);
								break;
							}
						}
						Afterrot.z = 0;
						frame = 1.0f;
						if (coolT < 20) {
							coolT++;
							break;
						}
						else {
							coolT = 0;
							frame = 0;
							pat = 3;
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
					3.0f,
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
					AfterPos = {
					0,
					3.0f,
					0
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
					-10,
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
						AttackCount = 0;
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
			rot.y = Ease(In, Quint, 0.7f, rot.y, Afterrot.y);
			enemyobj->SetRotation(rot);

		}
		//�v���C���[�����ޏ���
		else if (action == 1) {
			if (AttackC < 3) {
				switch (pat) {
				case 1:
					AfterPos = {
					pos.x,
					15.0f,
					pos.z
					};
					if (frame < 1.0f) {
						frame += 0.01f;
						break;
					}
					else {
						Afterrot.x = 270.0f;
						Afterrot.y = 360.0f;
						stateNumber = Open;
						frame = 0;
						pat++;
						break;
					}
				case 2:
					AfterPos = {
						player->GetPosition().x - 5,
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
						targetpos.x = player->GetPosition().x - 0.2f;
						aiming = 0;
						pat++;
						break;
					}
				case 3:
					AfterPos = {
						pos.x,
						0,
						pos.z,
					};
					if (frame < 1.0f) {
						frame += 0.02f;
						break;
					}
					else {
						frame = 0;
						pat++;
						break;
					}
				case 4:
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
						if (coolT < 50) {
							coolT++;
							break;
						}
						else {
							coolT = 0;
							frame = 0;
							pat = 2;
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
						stateNumber = Close;
						frame = 0;
						pat++;
						break;
					}
				case 2:
					Afterrot.x = 0.0f;
					Afterrot.y = 90.0f;
					AfterPos = {
					-10,
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
						AttackCount = 0;
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
			//hand_closeobj->SetPosition(pos);
		}

		//�˂��h���U��
		else if (action == 2) {
			if (AttackC < 3) {
				switch (pat) {
				case 1:
					AfterPos = {
					pos.x,
					15.0f,
					pos.z
					};
					if (frame < 0.45f) {
						frame += 0.002f;
						break;
					}
					else {
						Afterrot.x = 90.0f;
						Afterrot.y = 180.0f;
						stateNumber = Close;
						frame = 0;
						pat++;
						break;
					}
				case 2:
					AfterPos.y = 0.0f;
					if (frame < 0.45f) {
						frame += 0.002f;
					}
					else {
						frame = 0;
						pat++;
					}
					pos.y = Ease(In, Cubic, frame, pos.y, AfterPos.y);
				case 3:
					AfterPos = {
					pos.x,
					3.0f,
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
				case 4:
					AfterPos = {
						player->GetPosition().x,
					7.0f,
						player->GetPosition().z
					};
					if (aiming < 180) {
						frame = 0.5f;
						aiming++;
						break;
					}
					else {
						frame = 0;
						aiming = 0;
						pat++;
						break;
					}
				case 5:
					AfterPos = {
						pos.x,
						0,
						pos.z,
					};
					if (frame < 1.0f) {
						frame += 0.08f;
						//Afterrot.z += vel;
						if (rot.z > 45) {
							rot.z = 45;
							//vel = -vel;
						}
						if (rot.z < -45) {
							rot.z = -45;
							//vel = -vel;
						}
						break;
					}
					else {
						Afterrot.z = 0;
						frame = 1.0f;
						if (coolT < 90) {
							coolT++;
							break;
						}
						else {
							coolT = 0;
							frame = 0;
							pat = 3;
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
					3.0f,
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
					AfterPos = {
					0,
					3.0f,
					0
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
					-10,
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
						AttackCount = 0;
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
			rot.y = Ease(In, Quint, 0.7f, rot.y, Afterrot.y);
			enemyobj->SetRotation(rot);
		}
		
	}
	rot.y = Ease(In, Quint, 0.7f, rot.y, Afterrot.y);
	rot.x = Ease(In, Quint, 0.7f, rot.x, Afterrot.x);
	enemyobj->SetRotation(rot);
	//hand_closeobj->SetRotation(rot);
}

//����
void LeftHand::App(int Timer) {

	XMFLOAT3 AfterPos{};
	XMFLOAT3 AfterRot{};
	if (Timer == 0) {
		pos = { -13.0f,0.0f,18.0f };
		rot = { 0.0f,225.0f,0.0f };
	}

	if (Timer == 150 || Timer == 280 || Timer == 300) {
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
		pos = { -10.0f,0.0f,0.0f };
		rot = { 0,90,0 };
		AfterRot.y = 90.0f;
	case 3:
		stun = true;
		if (stun) {
			for (std::size_t i = 0; i < Stuntexture.size(); i++) {
				StunSpeed[i] += 2.0f;
			}
		}

		if (Timer == 500) {
			appearMove = 0;
			stun = false;
		}
	}

	//for (std::size_t i = 0; i < Stuntexture.size(); i++) {
	//	Stunradius[i] = StunSpeed[i] * PI / 180.0f;
	//	StunCircleX[i] = cosf(Stunradius[i]) * Stunscale[i];
	//	StunCircleZ[i] = sinf(Stunradius[i]) * Stunscale[i];
	//	StunPos[i].x = StunCircleX[i] + pos.x;
	//	StunPos[i].z = StunCircleZ[i] + pos.z;
	//	StunPos[i].y = pos.y + 2;
	//	Stuntexture[i]->SetPosition(StunPos[i]);
	//	Stuntexture[i]->Update();
	//}

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
	//hand_closeobj->SetPosition(pos);
	enemyobj->SetRotation(rot);
	//hand_closeobj->SetRotation(rot);
}

//���j
void LeftHand::End(int Timer) {
	//�{�X��|�������Ƃ̋���(��ŋL�q)
	XMFLOAT3 scale = { 0.8f,0.8f,0.8f };
	float RotPower = 0.0f;
	XMFLOAT3 AfterScale{};
	//float endframe = 0.0f;
	//�{�X��|�������Ƃ̋���(��ŋL�q)
	if (Timer == 300) {
		pos = { -5.0f,0.0f,0.0f };
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
		if (rot.x <= 90) {
			rot.x += 2.0f;
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
		rot.y += RotPower;
	}

	scale = {
	Ease(In,Cubic,endframe,scale.x,0.2f),
	Ease(In,Cubic,endframe,scale.y,0.2f),
	Ease(In,Cubic,endframe,scale.z,0.2f),
	};

	enemyobj->SetScale(scale);
	enemyobj->SetPosition(pos);
	//hand_closeobj->SetPosition(pos);
	enemyobj->SetRotation(rot);
	//hand_closeobj->SetRotation(rot);
}

//���ʂȕ`��(���̏ꍇ�҂�҂�)
void LeftHand::specialDraw() {
	if (BossHP > 0) {
		for (std::size_t i = 0; i < humanwave.size(); i++) {
			humanwave[i]->Draw();
		}
	}
}


void LeftHand::SetAct(Human* human) {
	int action = human->GetAction();
	int AttackCount = human->GetAttackCount();

	this->action = action;
	this->AttackCount = AttackCount;
}
