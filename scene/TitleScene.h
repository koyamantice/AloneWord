#pragma once
#include "SceneManager.h"
#include "ExpandChange.h"
/// <summary>
/// �^�C�g���V�[��
/// </summary>

class TitleScene : public BaseScene {
	public:

		/// <summary>
		/// ������
		/// </summary>
		void Initialize(DirectXCommon* dxCommon) override;
		/// <summary>
		/// �I��
		/// </summary>
		void Finalize() override;

		/// <summary>
		/// ���t���[���X�V
		/// </summary>
		void Update(DirectXCommon* dxCommon) override;
		/// <summary>
		/// �`��
		/// </summary>
		void Draw(DirectXCommon* dxCommon) override;

	private:
		Sprite* sprite[10]{};
		enum {
			back,
			button1,
			button2,
			sky,
			ground,
			tutorial,
			select,
		};
		ExpandChange* expandchange = nullptr;
		DebugCamera* camera = { nullptr };
		Player* player = nullptr;
		enum Select {
			Start,
			Select,
			Exit,
		};
		XMFLOAT2 buttonPos[2]{
			{ 160.0f,600.0f },
			{ 430.0f,600.0f }
		};
		int SelectNumber = 0;
};

