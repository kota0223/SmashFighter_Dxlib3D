#include "Player.h"
#include "Enemy.h"
#include "EffectManager.h"
#include "InformantForAi.h"
#include <math.h>
#include "DisplayScore.h"

// �G�̉����x�̒萔
const float	 Enemy::SPEED_ADD = 1.0f;								// �X�s�[�h
const float	 Enemy::VELOCITY_MINIMUM = 0.1f;						// ���x�Œ�l
const VECTOR Enemy::MODEL_SCALE = VGet(0.05f, 0.05f, 0.05f);		// ���f���̊g��l
const float  Enemy::ATTENUATION_COEFFICIENT = 0.98f;				// �����W��
const float  Enemy::STAGE_RANGE = 85.0f;							// �X�e�[�W�͈�
const float  Enemy::CORRECTION_POSSIBLE_SPEED = 1.0f;				// �␳�\�ȑ��x
const float  Enemy::CORRECTION_RANGE = 0.1f;						// �␳���锼�a�̑傫��
const VECTOR Enemy::SCORE_POSITION_ADJUSTMENT = VGet(-2, 20, 0);	// �X�R�A�\���ʒu�𒲐�����l
const int	 Enemy::SCORE_DRAW_POSITION_INTERVAL = 10;				// �X�R�A�̕\���ʒu�Ԋu
const int	 Enemy::ACTION_RANDOM_MAX = 4;							// �s�������ő�l
const int	 Enemy::ATTACK_MAX_COUNT = 180;							// �U���J�E���g�ő�l
const float  Enemy::ATTACK_VELOCITY = 6.0f;							// �U�����̑��x
const float  Enemy::ATTACK_ATTENUATION_COEFFICIENT = 0.97f;			// �U�����̑��x�����W��
const float  Enemy::ROTATE_ADD_SCALE = 0.1f;						// �����������]�̃X�P�[���l
const float  Enemy::CIRCLE_ANGLE = 360.0f;							// �~�̊p�x
const float  Enemy::MOVE_CIRCLE_RADIUS = 60.0f;						// �ړ�����~�̔��a
const float  Enemy::MOVE_ROTATE_ANGLE = 20.0f;						// �ړ�����p�x�l
const float  Enemy::MOVE_SCALE_RADIUS = 50.0f;						// �ړ����̔��a�̑傫��
const float  Enemy::MOVE_VELOCITY_SCALE = 0.05f;					// �ړ����̑��x�̑傫��
const float  Enemy::CHARGE_MOVE_MIN_SPEED = 0.2f;					// �`���[�W�ړ��̑��x�Œ�l

// �G�̃C���X�^���X�������l
int Enemy::EnemyNum = 0;

// �R���X�g���N�^�F�G�L�����N�^�[�̏��������s���܂�
Enemy::Enemy(int modelHandle, const Color_st &tagColor) :Character()
{
	// �ԍ���ݒ�
	Number = ++EnemyNum;

	// ���f���n���h�����
	this->modelHandle = MV1DuplicateModel(modelHandle);

	// ���f���g��l�ݒ�
	MV1SetScale(this->modelHandle, MODEL_SCALE);

	// �s����Ԃ̏�����
	actState = none;

	// �G�̑��x������
	velocity = 0;

	// �^�C�}�[������
	riviveTimer = 0;

	// �^�O�摜���
	displayTag.InitGraph(LoadGraph("data/image/Main/DisplayTag_CP.png"), LoadGraph("data/image/Main/DisplayTag_CP_Back.png"));

	displayTag.SetColor(tagColor);
}

// �f�X�g���N�^�F���ɏ����͍s���܂���
Enemy::~Enemy()
{
	// �����Ȃ�
}

// �G�L�����N�^�[�̍X�V����
void Enemy::Update()
{
	SetAction();

	displayTag.Update();		// �^�O�X�V

	Character::UpdateReviveEffect();

	if (isRevive) return;

	if (isChargeMove && velocity <= CHARGE_MOVE_MIN_SPEED)
		isChargeMove = false;

	// ��΂���Ă���ꍇ�͑��x������������
	if (actState == none)
		velocity *= ATTENUATION_COEFFICIENT;

	// ��΂���鏈��
	DoLeap();

	// �s����Ԃ�none�ŁA��΂���ĂȂ��ꍇ�͈ʒu���X�V����
	if (actState == none && !isLeaping)
		position = VAdd(position, velocityVector);

	// ��ʊO�ɏo���ꍇ�̏���
	if (isStageOut)
	{
		UpdateStageOut();
	}
	// ���ȉ��̑��x�� �X�e�[�W�O�ɏo���� ���W��␳
	else if (VSize(position) >= STAGE_RANGE && velocity < CORRECTION_POSSIBLE_SPEED)
	{
		// ��ʓ��Ɏ��߂邽�߂Ɉʒu��␳����
		position = VScale(VNorm(position), STAGE_RANGE - CORRECTION_RANGE);
	}

	// ���f���̉�]�l�ݒ�
	MV1SetRotationXYZ(modelHandle, VGet(0, atan2f(rotation.x, rotation.z), 0));
}

void Enemy::DrawScore(int x, int y)
{
	// �X�R�A��`��
	//DrawFormatStringToHandle(x, y, GetColor(255, 255, 255), scoreFont, "No %d Enemy Score : %d", Number, score);

	// �L�����N�^�[�̎O�������W���X�N���[�����W�ɕϊ�����
	VECTOR scorePos = ConvWorldPosToScreenPos(VAdd(position, SCORE_POSITION_ADJUSTMENT));

	// �X�R�A�����̕`��
	for (int i = 0; i < displayScore.size(); i++)
	{
		displayScore[i].Update();
		displayScore[i].Draw((int)scorePos.x, (int)scorePos.y + i * SCORE_DRAW_POSITION_INTERVAL);
	}
}

// �G�L�����N�^�[�̍s����ݒ肷��֐�
void Enemy::SetAction()
{
	// ��΂���Ă���Œ� �� �^�C�}�[��200�����̏ꍇ�͍s���Ȃ��ŏI��
	if (isLeaping || isRevive)
	{
		actState = none;
		return;
	}

	// �s�������ݒ�̏ꍇ�̓����_���ɍs��������
	if (actState == none)
	{
		// �����ōs����ݒ�
		switch (GetRand(ACTION_RANDOM_MAX))
		{
		case 0:
			SetActAttack(); // �U���s����ݒ�
			break;
		default:
			SetActMove(); // �ړ��s����ݒ�
			break;
		}
	}
	else
	{
		// �s����attack�܂���move�̏ꍇ�͂��ꂼ��̍s�������s
		switch (actState)
		{
		case attack:
			ActAttack(); // �U���s�������s
			break;
		case move:
			ActMove(); // �ړ��s�������s
			break;
		}
	}
}

// �U���s����ݒ肷��֐�
void Enemy::SetActAttack()
{
	// �U���s�����̃J�E���g�����Z�b�g
	attackActCount = 0;

	// �`���[�W�J�E���g���Z�b�g
	chargeEffectCount = 0;

	// �U���Ώۂ�T�����A�^�[�Q�b�g�ɐݒ肷��
	target = InformantForAi::GetInstance().GetAttackTarget(position);

	// �U���`���[�W�t���O�𗧂Ă�
	isCharge = true;

	// �`���[�W�����~�߂�
	PlaySoundMem(chargeSE, DX_PLAYTYPE_BACK);

	// �s����Ԃ��U�����ɕύX
	actState = attack;
}

// �U���s�������s����֐�
void Enemy::ActAttack()
{
	// �U���J�E���g
	attackActCount++;

	// target��nullptr�łȂ����m�F
	if (target != nullptr)
	{
		// ��΂���Ă��� �� �X�e�[�W�O �Ȃ�^�[�Q�b�g����O��
		if (target->GetIsLeaping()
			|| target->GetIsStageOut())
		{
			target = nullptr;
		}
	}

	// �J�E���g����l�𒴂����� �U������
	if (attackActCount >= ATTACK_MAX_COUNT)
	{
		// ��̃J�E���g�ɂȂ����u��
		if (attackActCount == ATTACK_MAX_COUNT)
		{
			// ���x�ݒ�
			velocity = ATTACK_VELOCITY;

			// �U���`���[�W�t���O������
			isCharge = false;

			// �`���[�W�ړ��t���O�𗧂Ă�
			isChargeMove = true;

			// �`���[�W�����~�߂�
			StopSoundMem(chargeSE);

			// target��nullptr�̏ꍇ�̓X�e�[�W�����Ɍ������čU������
			if (target == nullptr)
			{
				// ���ݒn���璆�S�ւ̃x�N�g��
				rotation = VSub(VGet(0, 0, 0), position);

				// ���K��
				if (VSize(rotation) > 0)
				{
					rotation = VNorm(rotation);
				}
			}
		}

		// ���x�x�N�g���Z�o
		velocityVector = VScale(rotation, velocity);

		// ���W�ړ�
		position = VAdd(position, velocityVector);

		// ���x�����ȉ��ɂȂ�����s������߂�
		if (velocity < VELOCITY_MINIMUM)
		{
			// �s���𖢐ݒ�
			actState = none;

			// �^�[�Q�b�g���O��
			target = nullptr;

		}
		else
		{
			// ���x����
			velocity *= ATTACK_ATTENUATION_COEFFICIENT;
		}
	}
	else
	{
		// target��nullptr�łȂ��ꍇ�̓^�[�Q�b�g�̂ق�������
		if (target != nullptr)
		{
			// �����x�N�g�����v�Z
			moveRotation = VSub(target->GetPosition(), position);

			// �G�l�~�[�̌����Ă���p�x �� �ړ���̊p�x �Ƃ̊O�ς��v�Z����
			cross = VCross(rotation, moveRotation);

			// sin�̒l���v�Z����
			float sita = VSize(cross) / (VSize(rotation) * VSize(moveRotation));

			if (cross.y < 0)
			{
				// �O�ς�y���������̏ꍇ��sita��-0.1���������p�x�̉�]�s�������
				// �G�̊p�x�x�N�g�����s����g�p���ĕϊ�������
				rotation = VTransform(rotation, MGetRotY(-sita * ROTATE_ADD_SCALE));
			}
			else
			{
				// �O�ς�y���������̏ꍇ��sita��0.1���������p�x�̉�]�s�������
				// �G�̊p�x�x�N�g�����s����g�p���ĕϊ�������
				rotation = VTransform(rotation, MGetRotY(sita * ROTATE_ADD_SCALE));
			}

			if (VSize(rotation) > 0)
			{
				// ��]�x�N�g���̐��K��
				rotation = VNorm(rotation);
			}
		}
		else
		{
			// target��nullptr�̏ꍇ�͍ēx�U���Ώۂ�T������
			target = InformantForAi::GetInstance().GetAttackTarget(position);
		}

		// �`���[�W�J�E���g
		chargeEffectCount++;
	}
}

// �ړ��s����ݒ肷��֐�
void Enemy::SetActMove()
{
	// �X�s�[�h���
	velocity = SPEED_ADD;

	// �ړ���̊p�x���Z�o
	// ��`�̌ʂ̒��� / ���a = ���W�A��
	float rad = ((2 * DX_PI_F * MOVE_CIRCLE_RADIUS) * (MOVE_ROTATE_ANGLE / CIRCLE_ANGLE)) / MOVE_CIRCLE_RADIUS;

	// ���K��
	if (VSize(position) > 0)
		aimPosition = VNorm(position);

	// ��]�s��ɂ��x�N�g���̕ϊ�
	aimPosition = VTransform(VScale(aimPosition, MOVE_SCALE_RADIUS), MGetRotY(rad));

	// �ړ���̕����x�N�g�����Z�o
	moveRotation = VSub(aimPosition, position);

	// �G�l�~�[�̌����Ă���p�x �� �ړ���̊p�x �Ƃ̊O�ς��v�Z����
	cross = VCross(rotation, moveRotation);

	// �s����Ԃ�move�ɕύX
	actState = move;
}

// �ړ��s�������s����֐�
void Enemy::ActMove()
{
	// �G�l�~�[�̌����Ă���p�x �� �ړ���̊p�x �Ƃ̊O�ς��v�Z����
	cross = VCross(rotation, moveRotation);

	// sin�̒l���v�Z����
	float sita = VSize(cross) / (VSize(rotation) * VSize(moveRotation));

	if (cross.y < 0)
	{
		// �O�ς�y���������̏ꍇ��sita��-0.1���������p�x�̉�]�s�������
		// �G�̊p�x�x�N�g�����s����g�p���ĕϊ�������
		rotation = VTransform(rotation, MGetRotY(-sita * ROTATE_ADD_SCALE));
	}
	else
	{
		// �O�ς�y���������̏ꍇ��sita��0.1���������p�x�̉�]�s�������
		// �G�̊p�x�x�N�g�����s����g�p���ĕϊ�������
		rotation = VTransform(rotation, MGetRotY(sita * ROTATE_ADD_SCALE));
	}

	// ��]�x�N�g���̐��K��
	if (VSize(rotation) > 0)
	{
		rotation = VNorm(rotation);
	}

	// ���ݒn����ړ���̃x�N�g���ւ̃x�N�g�����Z�o���A���x�x�N�g�������߂�
	velocityVector = VScale((VSub(aimPosition, position)), MOVE_VELOCITY_SCALE);

	// ���x�x�N�g���Z�o
	//velocityVector = VScale(rotation, velocity);

	// ���W�x�N�g���Z�o
	position = VAdd(position, velocityVector);

	// ���x����
	//velocity *= 0.96f;

	// ���x�����ȉ��ɂȂ�����s������߂�
	if (VSize(velocityVector) <= VELOCITY_MINIMUM)
	{
		actState = none;
	}
}
