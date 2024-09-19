#pragma once
#include <math.h>
#include "DxLib.h"

/// <summary>
/// FPS����N���X
/// </summary>
class Fps {

	// �萔

	static const int N;		//���ς����T���v����
	static const int FPS;	//�ݒ肵��FPS

	// �ϐ�

	int mStartTime;	//����J�n����
	int mCount;		//�J�E���^
	float mFps;		//fps

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Fps();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Fps();

	/// <summary>
	/// �X�V
	/// </summary>
	bool Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �ҋ@����
	/// </summary>
	void Wait();
};