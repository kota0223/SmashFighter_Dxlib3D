#include "player.h"
#include "EffectManager.h"
#include "DisplayScore.h"

// �v���C���[�̃X�s�[�h�𑝉������邽�߂̒萔
const float Player::SPEED_ADD = 5.0f;

// �����J�E���g�̍ő�l
const int Player::PUSH_COUNT_MAX = 60;

const VECTOR Player::MODEL_SCALE = VGet(0.05f, 0.05f, 0.05f);	// ���f���̃X�P�[���x�N�g���l

const double Player::PAD_DEAD_ZONE = 0.15;	// �W���C�p�b�h�̃f�b�h�]�[���l
			 
const int    Player::INIT_BUTTON_PUSH_COUNT = 10;	// �{�^�����������Ƃ��̃J�E���g�ϐ������l
			 
const float  Player::CHARGE_MOVE_VELOCITY_MIN = 0.2f;	// �`���[�W�ړ��̑��x�Œ�l
			 
const float  Player::VELOCITY_MIN = 0.1f;			// �ړ����x�Œ�l
			 
const float  Player::VELOCITY_ATTENUATION = 0.97f;	// ���x������

const float  Player::PAD_ANALOG_INPUT_VELOCITY_MAX = 1.0f;	// �p�b�h�̃A�i���O�X�e�B�b�N�̓��͂��󂯕t���鑬�x�ő�l
			 
const float  Player::STAGE_CORRECTION_VELOCITY_MAX = 0.2f;	// �X�e�[�W�O�̕␳�������鑬�x�̍ő�l

const VECTOR Player::SCORE_POSITION_ADJUSTMENT = VGet(-2, 20, 0);		// �X�R�A�\���ʒu�����x�N�g��

const int    Player::SCORE_POSITION_BETWEEN = 10;		// �X�R�A�����\���̊Ԋu

// �v���C���[�N���X�̃R���X�g���N�^
Player::Player(int modelHandle) :Character()
{
	// ���f���n���h�����
	this->modelHandle = MV1DuplicateModel(modelHandle);

	MV1SetScale(this->modelHandle, MODEL_SCALE);

	// �Q�[���p�b�h�̓��͂���]�x�N�g���ɔ��f���邽�߂̕ϐ�
	padInputRotation = VGet(0, 0, 1);

	// �{�^���𗣂������ǂ����̃t���O
	isdetachedButton = false;

	// �O�̃t���[���Ń{�^����������Ă��������L������ϐ�
	prevPushButton = false;

	// �{�^����������Ă����Ԃ��������t���[�������J�E���g����ϐ�
	pushLongButtonCount = 0;

	// �^�O�摜���
	displayTag.InitGraph(LoadGraph("data/image/Main/DisplayTag_Player.png"), 0);

	// �W���C�p�b�h�̃f�b�h�]�[����ݒ�
	SetJoypadDeadZone(DX_INPUT_PAD1, PAD_DEAD_ZONE);
}

// �v���C���[�N���X�̃f�X�g���N�^
Player::~Player()
{
	// �����Ȃ�
}

// �v���C���[�̍X�V����
void Player::Update()
{
	displayTag.Update();		// �^�O�X�V

	Character::UpdateReviveEffect();

	if (isRevive) return;

	// ���͏���
	InputAction();

	// �`���[�W�ړ����ɑ��x�����ȉ��ɂȂ�����t���O���~�낷
	if (isChargeMove && velocity <= CHARGE_MOVE_VELOCITY_MIN)
		isChargeMove = false;

	// ���W�v�Z����
	CalculationPosition();

	// �X�e�[�W�O�ɏo���ꍇ�̏���
	if (isStageOut)
	{
		UpdateStageOut();
	}
	// �X�e�[�W�O�ł͂Ȃ��ꍇ
	// �v���C���[�̍��W�x�N�g���̃T�C�Y�� ��l�ȏ� ���� �Ȃ��p�� ���̒l �� ���x�� ��l�ȉ��Ȃ�
	else if (VSize(position) >= 90.0 && (rad > 0 || velocity <= STAGE_CORRECTION_VELOCITY_MAX))
	{
		// �X�e�[�W�̊O���ɏo���ꍇ�́A�X�e�[�W�̊O���Ɉʒu�𐧌�����
		position = VScale(VNorm(position), 89.9f);
	}

	DoLeap();	// �W�����v����

	// ���f���̉�]�l�ݒ�
	MV1SetRotationXYZ(modelHandle, VGet(0, atan2f(padInputRotation.x, padInputRotation.z), 0));
}

void Player::InputAction()
{
	// �Q�[���p�b�h���͂��擾
	int padInput = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// �����v���C���[����΂���Ă���Œ��ł���΁A�Q�[���p�b�h���͂𖳌���
	if (isLeaping)
	{
		padInput = 0;
	}

	// �O�̃t���[���Ń{�^����������Ă�������
	// ���̃t���[���Ń{�^���������ꂽ�ꍇ�A�t���O�𗧂Ă�
	if (prevPushButton && !(padInput & PAD_INPUT_3))
	{
		// �{�^���𗣂����t���O�𗧂Ă�
		isdetachedButton = true;
	}
	// �O�̃t���[���Ń{�^����������Ă��Ȃ���
	// ���̃t���[���ł��{�^����������Ă���ꍇ�A�t���O�����낷
	else
	{
		isdetachedButton = false;
	}

	// �{�^����������Ă���ꍇ�A�O�̃t���[���ŉ�����Ă����t���O�𗧂Ă�
	if (padInput & PAD_INPUT_3)
	{
		// �����ꂽ�u�ԁi�O�̃t���[���ŉ�����Ă��Ȃ��ꍇ�j
		if (!prevPushButton)
		{
			// �J�E���g���Z�b�g
			pushLongButtonCount = INIT_BUTTON_PUSH_COUNT;

			// �`���[�W�G�t�F�N�g�J�E���g�����Z�b�g
			chargeEffectCount = 0;

			// �`���[�W�t���O�𗧂Ă�
			isCharge = true;

			PlaySoundMem(chargeSE, DX_PLAYTYPE_BACK);
		}

		// �`���[�W�J�E���g
		chargeEffectCount++;

		// �J�E���g���ő�ɂȂ�܂ŃJ�E���g����
		if (pushLongButtonCount < PUSH_COUNT_MAX)
		{
			// �J�E���g
			pushLongButtonCount++;
		}

		// �O�t���[���ŉ�����Ă����t���O�𗧂Ă�
		prevPushButton = true;
	}
	else
	{
		// �O�t���[���ŉ�����Ă����t���O������
		prevPushButton = false;

		// �`���[�W�t���O������
		isCharge = false;

		StopSoundMem(chargeSE);
	}

	// ���x����l��艺�Ȃ�p�b�h�̃A�i���O�X�e�B�b�N�̓��͗ʂ��擾
	if (velocity < PAD_ANALOG_INPUT_VELOCITY_MAX)
	{
		// �A�i���O�X�e�B�b�N�̓��͗ʂ��擾
		GetJoypadAnalogInput(&padAnalogInputX, &padAnalogInputY, DX_INPUT_PAD1);

		// ���͂�����ꍇ�̓x�N�g���ɑ��
		if (pow(padAnalogInputX, 2) + pow(padAnalogInputY, 2) > 0)
		{
			padInputRotation = VGet((float)padAnalogInputX, 0, (float)-padAnalogInputY);
		}
		// �p�b�h�̓��͂��Ȃ��ꍇ�́A�L�[�{�[�h���͂��󂯕t����
		else
		{
			// �E�L�[���͂ŉE��]
			if (padInput & PAD_INPUT_RIGHT)
			{
				padInputRotation = VTransform(padInputRotation, MGetRotY(DX_PI_F / 180 * 2));
			}

			// ���L�[���͂ō���]
			if (padInput & PAD_INPUT_LEFT)
			{
				padInputRotation = VTransform(padInputRotation, MGetRotY(-DX_PI_F / 180 * 2));
			}
		}

		// ���K��
		if (VSize(padInputRotation) > 0)
		{
			padInputRotation = VNorm(padInputRotation);
		}
	}

	// �{�^���𗣂����ꍇ�A�X�s�[�h�����Z����
	if (isdetachedButton && !isLeaping)
	{
		// �{�^�����������J�E���g���瑬�x���Z�o
		velocity = SPEED_ADD / PUSH_COUNT_MAX * pushLongButtonCount;

		// �p�b�h�̃A�i���O�X�e�B�b�N�̉�]�l���v���C���[�̊p�x�x�N�g���ɑ��
		rotation = padInputRotation;

		// �v���C���[�̍��W����X�e�[�W�^�񒆂Ɍ������x�N�g��
		verticalVector = VSub(VGet(0, 0, 0), position);

		// �v���C���[�̍��W����X�e�[�W�^�񒆂Ɍ������x�N�g�� �� �v���C���[�̕����Ƃ̂Ȃ��p�����߂�
		rad = VDot(verticalVector, padInputRotation) / (VSize(verticalVector) * VSize(padInputRotation));

		isChargeMove = true;
	}
}

void Player::CalculationPosition()
{
	// ���x�𑫂�
	velocityVector = VScale(rotation, velocity);

	// �X�s�[�h����
	if (velocity > VELOCITY_MIN)
	{
		velocity *= VELOCITY_ATTENUATION;
	}
	else if (velocity > 0)
	{
		velocity = VELOCITY_MIN;
	}

	// �v���C���[���W�Ɖ�]�x�N�g���𑫂��āA�v���C���[�̕������Z�o
	// �x�N�g���̎n�_���q���A�v���C���[�̕������o��
	if (!isLeaping)
	{
		position = VAdd(position, velocityVector);
	}
}

void Player::DrawScore(int x, int y)
{
	scorePos = ConvWorldPosToScreenPos(VAdd(position, SCORE_POSITION_ADJUSTMENT));

	for (int i = 0; i < displayScore.size(); i++)
	{
		displayScore[i].Update();
		displayScore[i].Draw((int)scorePos.x, (int)(scorePos.y + i * SCORE_POSITION_BETWEEN));
	}
}
