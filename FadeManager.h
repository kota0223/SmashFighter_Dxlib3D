#pragma once
#include "Screen.h"

class FadeManager
{
private:
	//�萔

	static const int ALPHA_CHANGE;	// �A���t�@��ϓ�������l

	static const unsigned int FADE_COLOR;	// �t�F�[�h���̐F

	static const int FADE_NUM_MAX;	// �t�F�[�h�ő�l	

	//�ϐ�

	int fadeAlpha;			 // �t�F�[�h�̓����x
	bool isFadeIn;			 // �t�F�[�h�C�������ǂ����̃t���O
	bool isFadeOut;			 // �t�F�[�h�A�E�g�����ǂ����̃t���O
	bool isFadeOutCompleted; // �t�F�[�h�A�E�g�������������ǂ����̃t���O
	bool isFadeInCompleted;	 // �t�F�[�h�C���������������ǂ����̃t���O

public:
	FadeManager();        // �R���X�g���N�^
	void StartFadeIn();   // �t�F�[�h�C�����J�n���郁�\�b�h
	void StartFadeOut();  // �t�F�[�h�A�E�g���J�n���郁�\�b�h

	bool IsFadingIn();			// �t�F�[�h�C�������ǂ�����Ԃ����\�b�h
	bool IsFadingOut();			// �t�F�[�h�A�E�g�����ǂ�����Ԃ����\�b�h

	bool IsFadeOutCompleted();	//�t�F�[�h�A�E�g�������������ǂ�����Ԃ����\�b�h
	bool IsFadeInCompleted();	//�t�F�[�h�C���������������ǂ�����Ԃ����\�b�h


	void Draw();				// �t�F�[�h�G�t�F�N�g��`�悷�郁�\�b�h
	void Update();				// �t�F�[�h�}�l�[�W���[���X�V���郁�\�b�h
};