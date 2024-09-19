#include "ReadyTextUI.h"

const int ReadyTextUI::ANIMATION_START_FRAME = 60;		// �A�j���[�V�����J�n�t���[��
const int ReadyTextUI::ANIMATION_END_FRAME = 2 * 60;	// �A�j���[�V�����I���t���[��
const int ReadyTextUI::SCALE_DECREASE_FRAME = 90;		// �X�P�[����������t���[����

const float ReadyTextUI::SCALE_INCREASE_MAX = 2.0;		// �X�P�[���g��ő�l
const float ReadyTextUI::SCALE_INCREASE_X = 0.12f;		// X�X�P�[���g�嗦
const float ReadyTextUI::SCALE_INCREASE_Y = 0.08f;		// Y�X�P�[���g�嗦

const float ReadyTextUI::SCALE_DECREASE_MAX = 1.0;		// �X�P�[���k���ő�l
const float ReadyTextUI::SCALE_DECREASE_X = 0.1f;		// X�X�P�[���k����
const float ReadyTextUI::SCALE_DECREASE_Y = 0.1f;		// Y�X�P�[���k����

// �R���X�g���N�^
ReadyTextUI::ReadyTextUI()
	: scaleX(0)
	, scaleY(0)
{
	// �����Ȃ�
}

// �f�X�g���N�^
ReadyTextUI::~ReadyTextUI()
{
	// �����Ȃ�
}

// �X�V
void ReadyTextUI::Update(int frame)
{
	// �t���[�����ɉ�����UI�A�j���[�V����
	if (frame > ANIMATION_START_FRAME && frame < ANIMATION_END_FRAME)
	{
		if (frame >= SCALE_DECREASE_FRAME)
		{
			scaleX += (SCALE_DECREASE_MAX - scaleX) * SCALE_DECREASE_X;
			scaleY += (SCALE_DECREASE_MAX - scaleY) * SCALE_DECREASE_Y;
		}
		else
		{
			scaleX += (SCALE_INCREASE_MAX - scaleX) * SCALE_INCREASE_X;
			scaleY += (SCALE_INCREASE_MAX - scaleY) * SCALE_INCREASE_Y;
		}
	}

}

// �`��
void ReadyTextUI::Draw()
{
	DrawRotaGraph3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2
		, scaleX, scaleY, 0, graphHandle, TRUE);
}
