#pragma once

// �C���N���[�h
#include "DxLib.h"

/// <summary>
/// �J�����N���X
/// </summary>
class Camera {
private:

	// �萔
	static const float CAMERA_POSITION_SHAKE_SCALE;	// �J�����|�W�V�����̗h��̑傫��
	static const float CAMERA_TARGET_SHAKE_SCALE;	// �J�����^�[�Q�b�g�̗h��̑傫��
	static const float SHAKE_WIDTH;					// �h��̕�
	static const float NEAR_DISTANCE;				// �J�����ɉf���O�͈̔�
	static const float FAR_DISTANCE;				// �J�����ɉf��ŉ��͈̔�
	static const int   SHAKE_INTERVAL;				// �h�炷�Ԋu�̃^�C��

	// �ϐ�
	int shakeTime;	// �J������h�炷����

public:

	static const VECTOR INIT_POSITION;				// �J���������ʒu

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Camera();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Camera();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �h�炷���Ԃ��Z�b�g����
	/// </summary>
	/// <param name="time"></param>
	void SetShakeTime(int time)
	{
		shakeTime = time;
	}
};