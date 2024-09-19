#include "DxLib.h"
#include "FadeManager.h"

const int	FadeManager::ALPHA_CHANGE = 7;	// �A���t�@��ϓ�������l

const unsigned int FadeManager::FADE_COLOR = GetColor(255, 255, 255);	// �t�F�[�h���̐F

const int FadeManager::FADE_NUM_MAX = 255;	// �t�F�[�h�ő�l	

FadeManager::FadeManager()
{
	fadeAlpha = 0;    // �����̓����x��0
	isFadeIn = false;  // �t�F�[�h�C�����̃t���O��false
	isFadeOut = false; // �t�F�[�h�A�E�g���̃t���O��false
}

void FadeManager::StartFadeIn()
{
	if (!isFadeIn)
	{
		isFadeIn = true;		 // �t�F�[�h�C�����̃t���O�𗧂Ă�
		isFadeInCompleted = false;	 // �t�F�[�h�C�������t���O������
		fadeAlpha = FADE_NUM_MAX;
	}
}

void FadeManager::StartFadeOut()
{
	if (!isFadeOut)
	{
		isFadeOut = true; // �t�F�[�h�A�E�g���̃t���O�𗧂Ă�

		isFadeOutCompleted = false; // �t�F�[�h�A�E�g�����t���O������

		fadeAlpha = 0;
	}
}

bool FadeManager::IsFadingIn()
{
	return isFadeIn;  // �t�F�[�h�C�����̃t���O��Ԃ�
}

bool FadeManager::IsFadingOut()
{
	return isFadeOut; // �t�F�[�h�A�E�g���̃t���O��Ԃ�
}

bool FadeManager::IsFadeInCompleted()
{
	return 	isFadeInCompleted;
}

bool FadeManager::IsFadeOutCompleted()
{
	return isFadeOutCompleted;
}

void FadeManager::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeAlpha);  // �u�����h���[�h��ݒ肵�ē����x�𔽉f
	DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, FADE_COLOR, TRUE);  // �����l�p�`��`��
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, NULL);  // �u�����h���[�h�����ɖ߂�
}

void FadeManager::Update()
{
	if (isFadeIn)
	{
		fadeAlpha -= ALPHA_CHANGE;  // �s�����x������������

		if (fadeAlpha <= 0)
		{
			fadeAlpha = 0;
			isFadeIn = false;  // �t�F�[�h�C��������������t���O�����낷
			isFadeInCompleted = true;// �t�F�[�h�C�������������t���O�𗧂Ă�
		}
	}

	if (isFadeOut)
	{
		fadeAlpha += ALPHA_CHANGE;  // �s�����x�𑝉�������

		if (fadeAlpha >= FADE_NUM_MAX)
		{
			fadeAlpha = FADE_NUM_MAX;

			isFadeOut = false;  // �t�F�[�h�A�E�g������������t���O�����낷
			isFadeOutCompleted = true; // �t�F�[�h�A�E�g�����������t���O�𗧂Ă�
		}
	}
}


