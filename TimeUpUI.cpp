#include "TimeUpUI.h"

const int	TimeUpUI::ANIMATION_END_FRAME = 120;	// �A�j���[�V�����I���t���[��
const float TimeUpUI::ANIMATION_SPEED = 60.0;		// �A�j���[�V�������x

// �R���X�g���N�^
TimeUpUI::TimeUpUI()
	: moveX(0)
{
	// �����Ȃ�
}

// �f�X�g���N�^
TimeUpUI::~TimeUpUI()
{
	// �����Ȃ�
}

// �X�V
void TimeUpUI::Update(int frame)
{
	if (moveX < SCREEN_WIDTH || frame >= ANIMATION_END_FRAME)
	{
		moveX += SCREEN_WIDTH / ANIMATION_SPEED;
		x = SCREEN_WIDTH - moveX;
	}
}
