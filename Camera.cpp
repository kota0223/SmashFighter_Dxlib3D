
// �C���N���[�h
#include <math.h>
#include "Camera.h"

// �萔
const VECTOR Camera::INIT_POSITION = VGet(0, 130, -130);	// �J���������ʒu
const float	 Camera::CAMERA_POSITION_SHAKE_SCALE = 0.05f;	// �J�����|�W�V�����̗h��̑傫��
const float  Camera::CAMERA_TARGET_SHAKE_SCALE = 0.10f;		// �J�����^�[�Q�b�g�̗h��̑傫��
const float  Camera::SHAKE_WIDTH = 20.0f;					// �h��̕�
const float  Camera::NEAR_DISTANCE = 0.1f;					// �J�����ɉf���O�͈̔�
const float  Camera::FAR_DISTANCE = 1000.0f;				// �J�����ɉf��ŉ��͈̔�
const int    Camera::SHAKE_INTERVAL = 4;					// �h�炷�Ԋu�̃^�C��

// �R���X�g���N�^
Camera::Camera()
{
	// �ϐ�������
	shakeTime = 0;

	//���s0.1�`1000�܂ł��J�����̕`��͈͂Ƃ���
	SetCameraNearFar(NEAR_DISTANCE, FAR_DISTANCE);

	//(0, 20, -100)�̎��_����(0.0f, 20.0f, 0.0f)�̃^�[�Q�b�g������p�x�ɃJ������ݒu
	SetCameraPositionAndTarget_UpVecY(INIT_POSITION, VGet(0.0f, 0.0f, 0.0f));
}

// �f�X�g���N�^
Camera::~Camera()
{
	// �����Ȃ�
}

// �X�V
void Camera::Update()
{
	if (shakeTime > 0)
	{
		shakeTime--;

		// ��萔�̊��o�ŗh�炷
		if (shakeTime % SHAKE_INTERVAL == 0)
		{
			VECTOR shakePos = VAdd(INIT_POSITION, VGet(cosf(DX_TWO_PI_F / SHAKE_WIDTH * shakeTime) * shakeTime* CAMERA_POSITION_SHAKE_SCALE,
									0, sinf(DX_TWO_PI_F / SHAKE_WIDTH * shakeTime) * shakeTime* CAMERA_POSITION_SHAKE_SCALE));

			SetCameraPositionAndTarget_UpVecY(shakePos, VGet(cosf(DX_TWO_PI_F / SHAKE_WIDTH * shakeTime) * shakeTime* CAMERA_TARGET_SHAKE_SCALE,
									0, sinf(DX_TWO_PI_F / SHAKE_WIDTH * shakeTime) * shakeTime* CAMERA_TARGET_SHAKE_SCALE));
		}
	}
	else
	{
		SetCameraPositionAndTarget_UpVecY(INIT_POSITION, VGet(0.000f, 0.000f, 0.000f));
	}
}
