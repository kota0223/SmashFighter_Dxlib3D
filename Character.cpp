
// �C���N���[�h
#include <math.h>
#include "Character.h"
#include "Camera.h"
#include "ParticleManager.h"
#include "DisplayScore.h"
#include "ReviveEffect.h"
#include "Stage.h"
#include "MoveEffect.h"
#include "HitEffect.h"
#include "ChargeEffect.h"

// �萔
const float	Character::SPEED_MIN				  = 0.1f;	// ���x�Œ�l
												  
const int	Character::REVIVE_TIME				  = 120;	// �����ɂ����鎞��
const float	Character::REVIVE_DRAW_POS_Y		  = 20.0f;	// �������̃��f���̕`��ʒu�̍���
const int	Character::BLINKING_INTERVAL_COUNT	  = 5;		// �_�ł̊Ԋu�̃J�E���g
												  
const int	Character::CHARGE_PARTICLE_NUM		  = 5;		// �`���[�W�p�[�e�B�N���̐�
const float	Character::CHARGE_PARTICLE_SPEED	  = 1.5f;	// �`���[�W�p�[�e�B�N���̑��x
const float	Character::CHARGE_PARTICLE_RANGE	  = 15.0f;	// �`���[�W�p�[�e�B�N���͈̔͂̑傫��
const int	Character::CHARGE_DRAW_COUNT		  = 5;		// �`���[�W�p�[�e�B�N����\������J�E���g��
const int	Character::CHARGE_SE_VOLUME			  = 150;	// �`���[�W���ʉ��{�����[��
												  
const int	Character::MAX_CHARGE_DIFFUSION_NUM	  = 10;		// �}�b�N�X�`���[�W�g�U�p�[�e�B�N���̐�
const float	Character::MAX_CHARGE_DIFFUSION_RANGE = 7.0;	// �}�b�N�X�`���[�W�g�U�p�[�e�B�N���͈̔͂̑傫��
const int	Character::MAX_CHARGE_COUNT			  = 60;		// �}�b�N�X�`���[�W�̃J�E���g��
const int	Character::MAX_CHARGE_DRAW_COUNT_1	  = 5;		// �}�b�N�X�`���[�W�p�[�e�B�N��1��\������J�E���g��
const int	Character::MAX_CHARGE_DRAW_COUNT_2	  = 10;		// �}�b�N�X�`���[�W�p�[�e�B�N��2��\������J�E���g��
												  
const float Character::COLLISION_RANGE			  = 10.0f;	// �����蔻�蔼�a
const float	Character::COLLISION_DRAW_SPEED		  = 2.0f;	// �ڐG�`�������X�s�[�h�K��l
const int	Character::COLLISION_PARTICLE_NUM	  = 15;		// �ڐG�p�[�e�B�N���̐�
const float	Character::COLLISION_PARTICLE_SPEED	  = 2.5f;	// �ڐG�p�[�e�B�N�����x
												  
const float	Character::STAGE_FALL_SPEED			  = 0.5f;	// �X�e�[�W�O�̗����鑬�x�̒l
const float	Character::STAGE_OUT_NUM			  = -30.0f;	// �X�e�[�W�O�Ƃ݂Ȃ��l

// �R���X�g���N�^
Character::Character()
{
	//������

	// �X�R�A�\�����W������
	scorePos = VGet(0, 0, 0);

	// �X�R�A������
	score = 0;

	// �`���[�W�J�E���g������
	chargeEffectCount = 0;

	// �ڐG�t���O
	isLeaping = false;

	// �X�e�[�W���痎�������t���O
	isStageOut = false;

	// �`���[�W���t���O
	isCharge = false;

	// �`���[�W�ړ����t���O
	isChargeMove = false;

	// �R���W�����p�[�e�B�N���摜�ǂݍ���
	collisionParticleGraph = LoadGraph("data/image/particle/particle_star.png");

	// �`���[�W�p�[�e�B�N���摜�ǂݍ���
	chargeParticleGraph = LoadGraph("data/image/particle/particle_charge.png");

	// �`���[�W�ő�p�[�e�B�N���摜 1 �ǂݍ���
	chargeMaxParticleGraph_1 = LoadGraph("data/image/particle/particle_charge_max_1.png");

	// �`���[�W�ő�p�[�e�B�N���摜 2 �ǂݍ���
	chargeMaxParticleGraph_2 = LoadGraph("data/image/particle/particle_charge_max_2.png");

	// ���摜�ǂݍ���
	lightGraphHandle = LoadGraph("data/image/particle/Star.png");

	// �ړ��G�t�F�N�g���_�V�F�[�_�[�ǂݍ���
	moveEffectVertexShaderHandle = LoadVertexShader("data/shader/MoveEffect/MoveEffectVS.vso");

	// �s�N�Z���V�F�[�_�[�ǂݍ���
	pixelShaderHandle = LoadPixelShader("data/shader/MoveEffect/MoveEffectPS.pso");

	// �q�b�g�G�t�F�N�g���_�V�F�[�_�[�ǂݍ���
	hitEffectVertexShaderHandle = LoadVertexShader("data/shader/HitEffect/HitEffectVS.vso");

	// �`���[�W�G�t�F�N�g���_�V�F�[�_�[�ǂݍ���
	chargeEffectVertexShaderHandle = LoadVertexShader("data/shader/ChargeEffect/ChargeEffectVS.vso");

	// �ړ��G�t�F�N�g
	moveEffect = new MoveEffect(position, moveEffectVertexShaderHandle, pixelShaderHandle);

	// �|���S���C���f�b�N�X
	for (int i = 0, k = 0; i < (20 * 2 + 2) * 3; i += 6) {
		indexCircle[0 + i] = k;
		indexCircle[1 + i] = k + 2;
		indexCircle[2 + i] = k + 1;
		indexCircle[3 + i] = k + 1;
		indexCircle[4 + i] = k + 2;
		indexCircle[5 + i] = k + 3;
		k += 2;
	}
}

// �f�X�g���N�^
Character::~Character()
{
	// ���f���n���h���폜
	MV1DeleteModel(modelHandle);

	// �����G�t�F�N�g�ϐ����������
	delete reviveEffect;
}

// ������
void Character::Initialize(const VECTOR& initPosition, ParticleManager* particleManager)
{
	// �������W
	position = initPos = initPosition;

	// �p�[�e�B�N���}�l�[�W���[�擾
	particleMgr = particleManager;

	// ������]�x�N�g��
	rotation = initRotation = VNorm(VScale(position, -1.0f));

	// �����G�t�F�N�g
	reviveEffect = new ReviveEffect(initPosition);

	// 3D���f���̃|�W�V�����ݒ�
	MV1SetPosition(modelHandle, position);

	// Y���̉�]�l��ݒ�
	MV1SetRotationXYZ(modelHandle, VGet(0, atan2f(rotation.x, rotation.z), 0));
}

// �X�V
void Character::Update()
{
	// �����Ȃ�
}

// �`��
void Character::Draw()
{
	displayTag.Draw(position);	// �^�O�`��

}

// SE�ǂݍ���
void Character::LoadSE()
{
	// �`���[�W���ʉ��ǂݍ���
	chargeSE = LoadSoundMem("data/sounds/Main/charge.wav");

	// �`���[�W���ʉ��̉��ʒ���
	ChangeVolumeSoundMem(CHARGE_SE_VOLUME, chargeSE);

	// �Փˌ��ʉ��ǂݍ���
	collisionSE = LoadSoundMem("data/sounds/Main/collision.mp3");

	// �X�R�A�ǉ����ʉ��ǂݍ���
	scoreAddSE = LoadSoundMem("data/sounds/Main/ScoreAdd.mp3");

}

void Character::DrawModel()
{
	// �������Ȃ烂�f���̕`��ʒu���ォ�牺�Ɉړ�
	if (isRevive)
	{
		MV1SetPosition(modelHandle,
			VGet(position.x, position.y + REVIVE_DRAW_POS_Y - (REVIVE_DRAW_POS_Y * ((float)riviveTimer / (float)REVIVE_TIME)), position.z));
	}
	// �������łȂ��Ȃ�L�����̈ʒu�Ƀ��f����`�悷��
	else
	{
		MV1SetPosition(modelHandle, position);
	}

	// ���f����`��
	MV1DrawModel(modelHandle);
}

// �X�e�[�W�͈̔͊O�̔���
void Character::CollisionStage(const Stage* stage)
{
	// �O�����̒藝�𗘗p���������蔻��
	// �L�����N�^�[�̍��W���X�e�[�W�O�ɏo�Ă��邩�𔻒�
	if (VSquareSize(VSub(position, VGet(0, 0, 0)))
		> pow(COLLISION_RANGE + stage->GetRange(), 2))
	{
		// �X�e�[�W�A�E�g�t���O�𗧂Ă�
		isStageOut = true;
	}
}

void Character::DoHit(VECTOR direction, float velocity, ScoreAddClass* collision)
{
	// �������Ȃ�Փˏ������s��Ȃ�
	if (isRevive)
	{
		return;
	}

	// ���łɐڐG�t���O�������Ă���ꍇ
	if (isLeaping)
	{
		// �ڐG��������̑��x �� ���݂̎����̑��x��� ���Ȃ� �������s��Ȃ�
		if (velocity <= this->velocity)
			return;

		// �ڐG��������̑��x �� ���݂̎����̑��x��� ��Ȃ� �������s�Ȃ�
		// ��������Ȃ�ڐG�t���O�����Z�b�g����
		isLeaping = false;
	}

	// ��΂��������x�N�g���̃T�C�Y�� 0 ���傫���Ȃ�p�x�x�N�g���ɑ��
	if (VSize(direction) > 0)
	{
		collisionVector = direction;
	}

	// ���x�␳
	if (velocity < 0.5f)
		velocity = 0.5f;

	// ���x���
	this->velocity = velocity;

	// ���肪���ɔ�΂���Ă��� ���� �����͂܂��ڐG�t���O�������Ă��Ȃ��Ȃ�
	// ���肪�ۑ����Ă���X�R�A����������L�����N�^�[��������
	if (collision->GetAddCharacter() != this && collision->GetIsLeaping() && !isLeaping)
	{
		scoreAddCharacter = collision->GetAddCharacter();
	}
	// �����łȂ��Ȃ�A�X�R�A�����L�����N�^�[�ϐ��ɑ���̃C���X�^���X�̃|�C���^����
	else
	{
		scoreAddCharacter = collision;
	}

	// ��΂���鑬�x���K��l�ȏ�Ȃ�ڐG�G�t�F�N�g�\���A�ڐG���ʉ����Đ�
	if (velocity >= COLLISION_DRAW_SPEED)
	{
		PlaySoundMem(collisionSE, DX_PLAYTYPE_BACK);	// �ڐG���̌��ʉ����Đ�����

		// �ڐG�G�t�F�N�g���Z�b�g
		particleMgr->SetCollisionParticle(position, COLLISION_PARTICLE_NUM, COLLISION_PARTICLE_SPEED);

		// �q�b�g�G�t�F�N�g����
		hitEffect.push_back(new HitEffect(position, 20, lightGraphHandle, hitEffectVertexShaderHandle));
	}

	isCharge = false;		// �`���[�W�t���O���Z�b�g

	isChargeMove = false;	// �`���[�W�ړ��t���O���Z�b�g

	StopSoundMem(chargeSE);	// �ڐG���Ƀ`���[�W���ʉ����~�߂�

}

// ��΂���Ă���Ƃ��̏���
void Character::DoLeap()
{
	// �ڐG�t���O�������Ă���Ȃ�
	if (isLeaping)
	{
		// ���x�x�N�g�����v�Z
		velocityVector = VScale(collisionVector, velocity);

		// ���W�𓮂���
		position = VAdd(position, velocityVector);

		// ���x�����ȉ� ���� �X�e�[�W���Ȃ� �ڐG�t���O������
		if (velocity <= SPEED_MIN && isStageOut == false)
			isLeaping = false;
	}
}

void Character::UpdateStageOut()
{
	// Y���W�������ĉ�ʉ��Ɉړ�������
	position.y -= STAGE_FALL_SPEED;

	// ��ʉ��ɉB�ꂽ�珉���ʒu�ɖ߂��A�e��t���O�ƃ^�C�}�[�����Z�b�g����
	if (position.y < STAGE_OUT_NUM)
	{
		// �X�e�[�W�O�ɗ��������̏���������
		InitStageOut();

		// �^�C�}�[������
		riviveTimer = 0;
	}
}

// �X�e�[�W�O�ɗ��������ۂ̏���������
void Character::InitStageOut()
{
	// ���W������
	position = initPos;

	// �X�e�[�W�t���O������
	isStageOut = false;

	//���x������
	velocity = 0;

	// ��΂���ăX�e�[�W�O�ɗ������ꍇ�́A��΂�������̃X�R�A�𑝂₷
	if (scoreAddCharacter != nullptr && isLeaping)
		scoreAddCharacter->ScoreAdd();

	// ���Z�b�g
	scoreAddCharacter = nullptr;

	// ��΂���Ă���t���O�����Z�b�g
	isLeaping = false;

	// ���x�x�N�g���̃��Z�b�g
	velocityVector = VGet(0, 0, 0);

	// ��]�x�N�g��������������
	rotation = initRotation;

	// �����t���O���Z�b�g����
	isRevive = true;

	// �����G�t�F�N�g�̕\��
	reviveEffect->DoPlay();

	// �^�O�\��
	displayTag.DoDisplay();
}

// �G�t�F�N�g�̕`��
void Character::DrawParticle()
{
	// �`���[�W���Ȃ�
	if (isCharge)
	{
		// �`���[�W�G�t�F�N�g�̃J�E���g��60�ȉ��Ȃ�
		if (chargeEffectCount <= MAX_CHARGE_COUNT)
		{
			// �`���[�W�p�[�e�B�N������莞�Ԃ��ƂɃZ�b�g����
			if (chargeEffectCount % CHARGE_DRAW_COUNT == 0)
			{
				// �p�[�e�B�N���Z�b�g
				particleMgr->SetChargeParticle(ParticleManager::CHARGE_NORMAL, position, Camera::INIT_POSITION, CHARGE_PARTICLE_NUM,  CHARGE_PARTICLE_SPEED, CHARGE_PARTICLE_RANGE, false);
			}
		}
		// 60�ȏ�Ȃ� �`���[�W�}�b�N�X�G�t�F�N�g��\��
		else
		{
			// �摜���ƂɌ��݂ɕ\������
			
			if (chargeEffectCount % MAX_CHARGE_DRAW_COUNT_1 == 0)
			{
				particleMgr->SetChargeParticle(ParticleManager::CHARGE_MAX_1, position, Camera::INIT_POSITION, CHARGE_PARTICLE_NUM, CHARGE_PARTICLE_SPEED, CHARGE_PARTICLE_RANGE, false);
			}
			if (chargeEffectCount % MAX_CHARGE_DRAW_COUNT_2 == 0)
			{
				particleMgr->SetChargeParticle(ParticleManager::CHARGE_MAX_2, position, Camera::INIT_POSITION, CHARGE_PARTICLE_NUM, CHARGE_PARTICLE_SPEED, CHARGE_PARTICLE_RANGE, false);
			}
		}

		// �`���[�W���}�b�N�X�ɂȂ������̊g�U�p�[�e�B�N���G�t�F�N�g
		if (chargeEffectCount == MAX_CHARGE_COUNT)
		{
			chargeEffect.push_back(new ChargeEffect(position, 20, lightGraphHandle, chargeEffectVertexShaderHandle));
			particleMgr->SetChargeParticle(ParticleManager::CHARGE_MAX_1, position, Camera::INIT_POSITION, MAX_CHARGE_DIFFUSION_NUM,  CHARGE_PARTICLE_SPEED, MAX_CHARGE_DIFFUSION_RANGE, true);
		}
	}
}

// �G�t�F�N�g�`��
void Character::DrawEffect()
{
	reviveEffect->Draw();		// �����G�t�F�N�g�`��

	// �`���[�W�ړ����Ȃ�ړ��G�t�F�N�g�`��
	if (isChargeMove)
	{
		moveEffect->Draw(MV1GetMatrix(modelHandle));
	}

	// �s�N�Z���V�F�[�_�[�萔�ݒ�
	SetPSConstF(GetConstIndexToShader("num", pixelShaderHandle), empty);

	// �s�N�Z���V�F�[�_�[�g�p
	SetUsePixelShader(pixelShaderHandle);

	// ���_�V�F�[�_�[�萔�ݒ�
	SetVSConstFMtx(58, GetCameraBillboardMatrix());

	// �q�b�g�G�t�F�N�g
	for (int i = 0; i < hitEffect.size(); i++)
	{
		// �`��
		hitEffect[i]->Draw(indexCircle);

		// ���Ԃ��擾���A0�ȉ��Ȃ�폜����
		if (hitEffect[i]->GetTime() < 0)
		{
			hitEffect.erase(hitEffect.begin() + i--);
		}
	}

	// �g�p����s�N�Z���V�F�[�_�[�����Z�b�g
	SetUsePixelShader(0);

	// �`���[�W�G�t�F�N�g
	for (int i = 0; i < chargeEffect.size(); i++)
	{
		// �`��
		chargeEffect[i]->Draw(indexCircle);

		// ���Ԃ��擾���A0�ȉ��Ȃ�폜����
		if (chargeEffect[i]->GetTime() < 0)
		{
			chargeEffect.erase(chargeEffect.begin() + i--);
		}
	}
}

void Character::ScoreAdd()
{
	score++;	// �X�R�A��ǉ�����

	// �X�R�A�����̌��ʉ������Ă��Ȃ��ꍇ�ɁA�X�R�A�����̌��ʉ���炷
	if (!CheckSoundMem(scoreAddSE))
		PlaySoundMem(scoreAddSE, DX_PLAYTYPE_BACK);

	// �X�R�A������\������
	DrawScoreIfHidden();
}

void Character::DrawScoreIfHidden()
{
	int i;

	// ��\���̃X�R�A��\��������
	for (i = 0; i < displayScore.size(); i++)
	{
		if (displayScore[i].IsHidden())
		{
			displayScore[i].InitializeForDisplay();
			break;
		}
	}

	// ��\���̃X�R�A���Ȃ���΁A�V���ɗv�f��ǉ�����
	if (i == displayScore.size())
	{
		displayScore.emplace_back();
	}
}

// �`���[�W�̌��ʉ����~�߂�
void Character::StopChargeSE()
{
	StopSoundMem(chargeSE);
}

void Character::UpdateReviveEffect()
{
	reviveEffect->Update();	// �����G�t�F�N�g�X�V

	// �������̓_�ŏ���
	if (isRevive)
	{
		// �^�C�}�[�J�E���g
		riviveTimer++;

		// �_�ŏ���
		if (riviveTimer % BLINKING_INTERVAL_COUNT == 0)
		{
			MV1SetVisible(modelHandle, false);
		}
		else
		{
			MV1SetVisible(modelHandle, true);
		}

		// �^�C�}�[���Ō�̎��͕\��������
		if (riviveTimer == REVIVE_TIME)
		{
			MV1SetVisible(modelHandle, true);
			isRevive = false;
		}

	}
}
