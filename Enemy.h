#pragma once

#include "Character.h"

// �G�s����Ԃ̗񋓑�
enum State_e
{
	none,	// �s�����ݒ�
	move,	// �ړ���
	attack	// �U����
};

class Player;

// �G�N���X
class Enemy : public Character {
private:

	// �萔

	static const float	SPEED_ADD;						// �X�s�[�h

	static const float	VELOCITY_MINIMUM;				// ���x�Œ�l

	static const VECTOR MODEL_SCALE;					// ���f���̊g��l

	static const float	ATTENUATION_COEFFICIENT;		// �����W��

	static const float	STAGE_RANGE;					// �X�e�[�W�͈�

	static const float	CORRECTION_POSSIBLE_SPEED;		// �␳�\�ȑ��x
	static const float  CORRECTION_RANGE;				// �␳���锼�a�̑傫��

	static const VECTOR SCORE_POSITION_ADJUSTMENT;		// �X�R�A�\���ʒu�𒲐�����l
	static const int	SCORE_DRAW_POSITION_INTERVAL;	// �X�R�A�̕\���ʒu�Ԋu

	static const int	ACTION_RANDOM_MAX;				// �s�������ő�l

	static const int	ATTACK_MAX_COUNT;				// �U���J�E���g�ő�l
	static const float	ATTACK_VELOCITY;				// �U�����̑��x
	static const float	ATTACK_ATTENUATION_COEFFICIENT;	// �U�����̑��x�����W��

	static const float	ROTATE_ADD_SCALE;				// �����������]�̃X�P�[���l

	static const float	CIRCLE_ANGLE;					// �~�̊p�x

	static const float	MOVE_CIRCLE_RADIUS;				// �ړ�����~�̔��a
	static const float	MOVE_ROTATE_ANGLE;				// �ړ�����p�x�l
	static const float	MOVE_SCALE_RADIUS;				// �ړ����̔��a�̑傫��
	static const float	MOVE_VELOCITY_SCALE;			// �ړ����̑��x�̑傫��

	static const float  CHARGE_MOVE_MIN_SPEED;			// �`���[�W�ړ��̑��x�Œ�l

	// �ϐ��錾

	static int EnemyNum;	// �G�l�~�[�̃C���X�^���X��

	int Number;				// �C���X�^���X�ԍ�

	VECTOR aimPosition;		// �ړ���̃x�N�g��

	VECTOR moveRotation;	// �ړ���̉�]�x�N�g��

	VECTOR cross;			// �O�σx�N�g��

	Character* target;		//�^�[�Q�b�g�ɐݒ肷��Character�N���X�̃|�C���^�ϐ�

	State_e actState;		// �G�s����Ԃ̗񋓑̕ϐ�

	int attackActCount;		// �U���s�����̃J�E���g

	int i, j;				//�ėp���[�v�ϐ�

	// �f�o�b�O�p�s���\���ϐ�
	const char* actStatePrint[3] = { "����","�s��","�U��" };

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Enemy(int modelHandle,const Color_st &tagColor);

	/// <summary>
	/// �����f�X�g���N�^
	/// </summary>
	virtual ~Enemy();

	/// <summary>
	/// ��Ԃ̍X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �X�R�A�`��
	/// </summary>
	void DrawScore(int x, int y);

	/// <summary>
	/// �G�̍s����ݒ�
	/// </summary>
	/// <param name="characters">Character*�^ �ڐG���������L�����N�^�[�̃|�C���^�z��</param>
	/// <param name="size">int�^ �z��̃T�C�Y</param>
	void SetAction();

	/// <summary>
	/// �U����Ԃ̃Z�b�g
	/// </summary>
	/// <param name="characters">Character*�^ �ڐG���������L�����N�^�[�̃|�C���^�z��</param>
	/// <param name="size">int�^ �z��̃T�C�Y</param>
	void SetActAttack();

	/// <summary>
	/// �U���s��
	/// </summary>
	/// <param name="characters">Character*�^ �ڐG���������L�����N�^�[�̃|�C���^�z��</param>
	/// <param name="size">int�^ �z��̃T�C�Y</param>
	void ActAttack();

	/// <summary>
	/// �ړ���Ԃ̃Z�b�g
	/// </summary>
	void SetActMove();

	/// <summary>
	/// �ړ�����
	/// </summary>
	void ActMove();
};