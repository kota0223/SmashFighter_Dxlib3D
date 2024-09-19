#include <DxLib.h>
#include "CollisionParticle.h"

const int   CollisionParticle::DIRECTION_RAND_SCALE = 100;				// �����x�N�g���̗����̑傫��
const float CollisionParticle::SPEED_DECREASE = 0.15f;					// ���x����
const float CollisionParticle::SIZE_CHANGE = 0.3f;						// �T�C�Y�ω���
const int	CollisionParticle::PARTICLE_SIZE = 10;						// �p�[�e�B�N�����̑傫��
const int	CollisionParticle::PARTICLE_SIZE_MIN = 5;					// �p�[�e�B�N���ŏ��T�C�Y
const float CollisionParticle::ANGLE_ADD = 0.05f;						// ��]���������
const float CollisionParticle::PARTICLE_ROTATION_BEGIN_VELOCITY = 2.0f;	// ��]���n�߂�p�[�e�B�N�����̂̑��x
const float CollisionParticle::BILLBOARD_CENTER_POSITION_X = 0.5f;		// �r���{�[�h�摜�̒��SX���W
const float CollisionParticle::BILLBOARD_CENTER_POSITION_Y = 0.5f;		// �r���{�[�h�摜�̒��SY���W

/// CollisionParticle�N���X�̃R���X�g���N�^
CollisionParticle::CollisionParticle() 
	: pos(VGet(0, 0, 0))
	, sizeMax((float)GetRand(PARTICLE_SIZE - PARTICLE_SIZE_MIN) + PARTICLE_SIZE_MIN)
	, size(0)
{
}

/// CollisionParticle�N���X�̃f�X�g���N�^
CollisionParticle::~CollisionParticle()
{
}

/// �Փ˃p�[�e�B�N�����΂�����
void CollisionParticle::DoParticleFly(VECTOR pos, int graphHandle, float firstSpeed)
{
	// �摜�ǂݍ���
	this->graphHandle = graphHandle;

	// ���W
	this->pos = pos;

	// �ړ������x�N�g��
	DirectionsVec = VGet((GetRand(DIRECTION_RAND_SCALE * 2) - DIRECTION_RAND_SCALE) / 100.0f, 
						 (GetRand(DIRECTION_RAND_SCALE)) / 100.0f, 
						 (GetRand(DIRECTION_RAND_SCALE * 2) - DIRECTION_RAND_SCALE) / 100.0f);

	// ���K��
	if (VSize(DirectionsVec) > 0)
	{
		DirectionsVec = VNorm(DirectionsVec);
	}

	// �ړ��x�N�g��
	moveVec = VGet(0, 0, 0);

	// ���x
	velocity = firstSpeed;

	// ��]��
	angle = 0;

	// �I���t���O������
	isFinish = false;

	// �\���t���O�𗧂Ă�
	isVisible = true;
}

/// �Փ˃p�[�e�B�N���̏�Ԃ��X�V����
void CollisionParticle::Update()
{
	// �ړ��x�N�g���v�Z
	moveVec = VScale(DirectionsVec, velocity);

	// �ړ�
	pos = VAdd(pos, moveVec);

	// ���x����
	if (velocity > 0)
	{
		velocity -= SPEED_DECREASE;
	}
	else
	{
		velocity = 0;
	}

	// �T�C�Y���ő�T�C�Y�ɂȂ�����A�؂�ւ��t���O�𗧂Ă�
	if (size >= sizeMax)
	{
		isFinish = true;
	}

	// �T�C�Y�ψ�
	size += SIZE_CHANGE * (isFinish ? -1 : 1);

	// �p�[�e�B�N���̏�������
	if (isFinish && size <= 0)
	{
		isVisible = false;
		size = 0;
	}

	// ���x�����ȉ��Ȃ��]
	if (velocity < PARTICLE_ROTATION_BEGIN_VELOCITY)
		angle += ANGLE_ADD;
}

/// �Փ˃p�[�e�B�N����`�悷��
void CollisionParticle::Draw()
{
	// �\���t���O�������Ă���Ȃ�`��
	if (isVisible)
	{
		DrawBillboard3D(pos, BILLBOARD_CENTER_POSITION_X, BILLBOARD_CENTER_POSITION_Y, size, angle, graphHandle, TRUE);
	}
}

/// �Փ˃p�[�e�B�N���̕\����Ԃ��擾����
bool CollisionParticle::IsVisible() const
{
	return isVisible;
}