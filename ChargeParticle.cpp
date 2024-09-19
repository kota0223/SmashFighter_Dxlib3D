#include <DxLib.h>
#include <math.h>
#include "ChargeParticle.h"

const float	 ChargeParticle::SPEED_DECREASE = 0.01f;					// ���x����

const int	 ChargeParticle::DIRECTION_RAND_SCALE = 100;				// �����x�N�g���̗����̑傫��

const VECTOR ChargeParticle::GRAPH_SCALE_CHARGED = VGet(0.1f, 0.6f, 0);	// �`���[�W��̉摜�X�P�[���l
const VECTOR ChargeParticle::GRAPH_SCALE = VGet(0.15f, 0.15f, 0);		// �摜�̃X�P�[���l

const float  ChargeParticle::INIT_SCALE_X = 0.9f;						// scaleX�ϐ��̏����l
const float  ChargeParticle::INIT_SCALE_Y = 1.1f;						// scaleY�ϐ��̏����l

const float	 ChargeParticle::INIT_SCALE_X_CHARGED = 1.0f;				// �`���[�W���scaleX�ϐ��̏����l
const float	 ChargeParticle::INIT_SCALE_Y_CHARGED = 0.9f;				// �`���[�W���scaleY�ϐ��̏����l

const float  ChargeParticle::CHARGED_SCALE_MAX = 1.5f;					// �`���[�W��̃X�P�[������l
const float  ChargeParticle::CHARGED_SCALE_ADD_AMOUNT = 1.1f;			// �`���[�W��̃X�P�[�������l

const float  ChargeParticle::PARTICLE_HIDDEN_SCALE_Y_MIN = 0.5f;		// �p�[�e�B�N�����\���ɂ���X�P�[����Y���W�Œ�l
const float  ChargeParticle::PARTICLE_HIDDEN_CROSS_MIN = 1.0f;			// �p�[�e�B�N�����\���ɂ���O�ς̍Œ�l

ChargeParticle::ChargeParticle() :pos(VGet(0, 0, 0))
{
}

ChargeParticle::~ChargeParticle()
{
}

void ChargeParticle::DoParticleFly(VECTOR pos, VECTOR cameraPos, int graphHandle, float firstSpeed, float range, bool isCharged)
{
	//�摜�ǂݍ���
	this->graphHandle = graphHandle;

	// ���_�ۑ�
	origin = pos;

	//�ړ������x�N�g��
	DirectionsVec = VGet((GetRand(DIRECTION_RAND_SCALE * 2) - DIRECTION_RAND_SCALE) / 100.0f, pos.y, (GetRand(DIRECTION_RAND_SCALE * 2) - DIRECTION_RAND_SCALE) / 100.0f);

	//���K��
	if (VSize(DirectionsVec) > 0)
	{
		DirectionsVec = VNorm(DirectionsVec);
	}

	VECTOR screenPos1 = ConvWorldPosToScreenPos(VAdd(origin, VScale(DirectionsVec, range)));
	VECTOR screenPos2 = ConvWorldPosToScreenPos(origin);
	VECTOR angleVector = VGet(screenPos1.x - screenPos2.x, screenPos1.y - screenPos2.y, 0);

	//��]��
	angle = -atan2f(angleVector.y, angleVector.x) - DX_PI_F / 2;

	//���W
	this->pos = VAdd(origin,VScale(DirectionsVec, range));

	//�ړ��x�N�g��
	moveVec = VGet(0, 0, 0);

	//���x
	velocity = firstSpeed;

	//�\���t���O�𗧂Ă�
	isVisible = true;

	// �`���[�W��t���O����
	this->isCharged = isCharged;

	// �P�ʍs�����
	MATRIX transMat = MGetIdent();

	// �g��s����|����
	if (isCharged)
	{
		transMat = MMult(transMat, MGetScale(GRAPH_SCALE_CHARGED));
	}
	else
	{
		transMat = MMult(transMat, MGetScale(GRAPH_SCALE));
	}

	// �s��ɂ����W�ϊ�
	for (int i = 0; i < 4; i++)
	{
		graphPosScale[i] = VTransform(graphPosScale[i], transMat);
	}

	// �����x�N�g�����Z�o
	horizonVector = VTransform(DirectionsVec, MGetRotY(-DX_PI_F / 2.0));

	if (isCharged)
	{
		scaleX = INIT_SCALE_X_CHARGED;
		scaleY = INIT_SCALE_Y_CHARGED;
	}
	else
	{
		scaleX = INIT_SCALE_X;
		scaleY = INIT_SCALE_Y;
	}
}

void ChargeParticle::Update()
{
	// �\���t���O�������Ă��Ȃ��Ȃ珈�������Ȃ�
	if (!isVisible)
	{
		return;
	}

	// �ړ��x�N�g���v�Z
	moveVec = VScale(DirectionsVec, velocity);

	//���x����
	if (velocity > 0)
	{
		velocity -= SPEED_DECREASE;
	}
	else
	{
		velocity = 0;
	}

	if (isCharged)
	{
		if (fabs(graphPosScale[0].x) < CHARGED_SCALE_MAX)
		{
			scaleX = CHARGED_SCALE_ADD_AMOUNT;
		}
		else
		{
			scaleX = 1.0;
		}
	}

	// �g��s��
	MATRIX transMat = MMult(MGetIdent(), MGetScale(VGet(scaleX, scaleY, 0)));

	//// ��]�s������߂�
	MATRIX transRotationMat = MMult(MGetIdent(), MGetRotZ(angle));

	// �s��ɂ����W�ϊ�
	for (int i = 0; i < 4; i++)
	{
		// �g��k���ɂ��ό`
		graphPosScale[i] = VTransform(graphPosScale[i], transMat);
		 
		// �g��k���̕ό`���������摜����]������
		graphPos[i] = VTransform(graphPosScale[i], transRotationMat);
	}

	//�ړ�
	if (isCharged)
	{
		pos = VAdd(pos, moveVec);

		if (graphPosScale[0].y <= PARTICLE_HIDDEN_SCALE_Y_MIN)
		{
			isVisible = false;
		}
	}
	else
	{
		pos = VSub(pos, moveVec);

		// �����x�N�g�����Z�o
		verticalVector = VSub(pos, origin);

		// �O�σx�N�g����y�l�����ȉ��Ȃ�\���t���O������
		if (VCross(horizonVector, verticalVector).y <= PARTICLE_HIDDEN_CROSS_MIN)
		{
			isVisible = false;
		}
	}
}

void ChargeParticle::Draw()
{
	// �\���t���O�������ċ�����\��
	if (isVisible)
	{
		DrawModiBillboard3D(pos
			, graphPos[0].x, graphPos[0].y
			, graphPos[1].x, graphPos[1].y
			, graphPos[2].x, graphPos[2].y
			, graphPos[3].x, graphPos[3].y
			, graphHandle, TRUE);
	}
}

bool ChargeParticle::IsVisible() const
{
	return isVisible;
}