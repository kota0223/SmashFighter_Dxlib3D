#pragma once

#include <math.h>
#include "BaseUI.h"

// GoTextUI�N���X
class GoTextUI : public BaseUI {

private:
	// �萔

	static const int MOVE_Y_INIT_NUM;		// Y�ړ��ʏ����l
	static const int DRAW_FRAME;			// �`��t���[��
	static const int ANIMATION_SPEED;		// �A�j���[�V�������x
	static const float MOVE_Y_ATTENUATION;	// Y�ړ��ʂ̌�����

	// �ϐ�

	float moveY;	// Y���W�ړ���

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	GoTextUI();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~GoTextUI();

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="frame">�t���[����</param>
	void Update(int frame) override;
};