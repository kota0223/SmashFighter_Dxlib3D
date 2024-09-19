#pragma once

#include "Screen.h"
#include "BaseUI.h"

/// �Q�[���J�n�O��Ready�e�L�X�gUI�N���X
class ReadyTextUI : public BaseUI {
private:

	// �萔

	static const int ANIMATION_START_FRAME;	// �A�j���[�V�����J�n�t���[��
	static const int ANIMATION_END_FRAME;	// �A�j���[�V�����I���t���[��
	static const int SCALE_DECREASE_FRAME;	// �X�P�[����������t���[����
	static const float SCALE_INCREASE_MAX;	// �X�P�[���g��ő�l
	static const float SCALE_INCREASE_X;	// X�X�P�[���g�嗦
	static const float SCALE_INCREASE_Y;	// Y�X�P�[���g�嗦
	static const float SCALE_DECREASE_MAX;	// �X�P�[���k���ő�l
	static const float SCALE_DECREASE_X;	// X�X�P�[���k����
	static const float SCALE_DECREASE_Y;	// Y�X�P�[���k����

	// �ϐ�

	// �X�P�[���l
	float scaleX, scaleY;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	ReadyTextUI();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ReadyTextUI();

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="frame">�t���[����</param>
	void Update(int frame) override;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw() override;
};