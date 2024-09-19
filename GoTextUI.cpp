#include "GoTextUI.h"

const int GoTextUI::MOVE_Y_INIT_NUM = 30;			// Y�ړ��ʏ����l
const int GoTextUI::DRAW_FRAME = 3 * 60;			// �`��t���[��
const int GoTextUI::ANIMATION_SPEED = 10;			// �A�j���[�V�������x
const float GoTextUI::MOVE_Y_ATTENUATION = 0.05f;	// Y�ړ��ʂ̌�����

// �R���X�g���N�^
GoTextUI::GoTextUI()
	: moveY(MOVE_Y_INIT_NUM)
{
}

// �f�X�g���N�^
GoTextUI::~GoTextUI()
{
}

// �X�V
void GoTextUI::Update(int frame)
{
	if (frame > DRAW_FRAME)
	{
		y = sinf(DX_PI_F / ANIMATION_SPEED * frame) * moveY;
		moveY += (0.0f - moveY) * MOVE_Y_ATTENUATION;
	}
}
