#pragma once

#include "Character.h"

class Player : public Character {
private:
	//�萔

	static const float SPEED_ADD;		//�X�s�[�h

	static const int PUSH_COUNT_MAX;	//�����J�E���g�̍ő�l

	static const VECTOR MODEL_SCALE;	// ���f���̃X�P�[���x�N�g���l
	
	static const double PAD_DEAD_ZONE;	// �W���C�p�b�h�̃f�b�h�]�[���l

	static const int   INIT_BUTTON_PUSH_COUNT;	// �{�^�����������Ƃ��̃J�E���g�ϐ������l

	static const float CHARGE_MOVE_VELOCITY_MIN;	// �`���[�W�ړ��̑��x�Œ�l

	static const float VELOCITY_MIN;			// �ړ����x�Œ�l

	static const float VELOCITY_ATTENUATION;	// ���x������

	static const float PAD_ANALOG_INPUT_VELOCITY_MAX;	// �p�b�h�̃A�i���O�X�e�B�b�N�̓��͂��󂯕t���鑬�x

	static const float STAGE_CORRECTION_VELOCITY_MAX;	// �X�e�[�W�O�̕␳�������鑬�x�̍ő�l

	static const VECTOR SCORE_POSITION_ADJUSTMENT;		// �X�R�A�\���ʒu�����x�N�g��
	
	static const int SCORE_POSITION_BETWEEN;		// �X�R�A�����\���̊Ԋu

	// �ϐ�

	// �p�b�h���͂ɂ��p�x
	VECTOR padInputRotation;

	// �����x�N�g��
	VECTOR verticalVector;

	double rad;

	//�{�^���������������̃J�E���g��
	int pushLongButtonCount;

	//�W���C�p�b�h�̃A�i���O�X�e�B�b�N�̍��E���͗�
	int padAnalogInputX;

	//�W���C�p�b�h�̃A�i���O�X�e�B�b�N�̏㉺���͗�
	int padAnalogInputY;

	//�����蔻��̔��a
	float collRange;

	//�ړ�����O�̎����̃x�N�g���̃T�C�Y
	float positionVectorSize;

	//�O�̃t���[���Ń{�^����������Ă�����
	bool prevPushButton;

	//�{�^���𗣂�����
	bool isdetachedButton;

	// �֐�

	/// <summary>
	/// ���͏���
	/// </summary>
	void InputAction();

	/// <summary>
	/// ���W�v�Z����
	/// </summary>
	void CalculationPosition();

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Player(int modelHandle);

	/// <summary>
	/// �����f�X�g���N�^
	/// </summary>
	virtual ~Player();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �X�R�A�`��
	/// </summary>
	void DrawScore(int x, int y);

};