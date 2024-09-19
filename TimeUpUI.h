#pragma once

#include <math.h>
#include "Screen.h"
#include "BaseUI.h"

// �^�C���A�b�v����UI�N���X
class TimeUpUI : public BaseUI {
private:

	// �ϐ�

	static const int	ANIMATION_END_FRAME;	// �A�j���[�V�����I���t���[��
	static const float	ANIMATION_SPEED;		// �A�j���[�V�������x

	// �ϐ�

	float moveX;	// X�̈ړ���

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	TimeUpUI();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~TimeUpUI();

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="frame">�t���[����</param>
	void Update(int frame) override;
};