#include <Dxlib.h>
#include "CollisionParticle.h"
#include "ParticleManager.h"

// �R���X�g���N�^
ParticleManager::ParticleManager()
{
	// �R���W�����p�[�e�B�N���摜�ǂݍ���
	collisionParticleGraph = LoadGraph("data/image/particle/particle_star.png");

	// �`���[�W�p�[�e�B�N���摜�ǂݍ���
	chargeParticleGraphs[0] = LoadGraph("data/image/particle/particle_charge.png");

	// �`���[�W�ő�p�[�e�B�N���摜 1 �ǂݍ���
	chargeParticleGraphs[1] = LoadGraph("data/image/particle/particle_charge_max_1.png");

	// �`���[�W�ő�p�[�e�B�N���摜 2 �ǂݍ���
	chargeParticleGraphs[2] = LoadGraph("data/image/particle/particle_charge_max_2.png");
}

// �f�X�g���N�^
ParticleManager::~ParticleManager()
{
	// �������������
	for (int i = 0; i < collisionParticles.size(); i++)
	{
		delete[] collisionParticles[i];
	}
}

// �`���[�W�p�[�e�B�N���𐶐����A�p�����[�^��ݒ肷��֐�
void ParticleManager::SetChargeParticle(ChargeGraphKind graphKind, VECTOR pos, VECTOR cameraPos, int num, float firstSpeed, float range, bool isCharged)
{
	// �p�[�e�B�N���̌���ݒ�
	chargeParticlesNum = num;

	// �e�`���[�W�p�[�e�B�N���ɑ΂��ď������ƃp�[�e�B�N���̔�s�������s��
	for (int i = 0; i < chargeParticlesNum; i++)
	{
		chargeParticles.emplace_back(new ChargeParticle);
		chargeParticles.back()->DoParticleFly(pos, cameraPos, chargeParticleGraphs[graphKind], firstSpeed, range, isCharged);
	}
}

// �Փ˃p�[�e�B�N���𐶐����A�p�����[�^��ݒ肷��֐�
void ParticleManager::SetCollisionParticle(VECTOR pos, int num, float firstSpeed)
{
	// �p�[�e�B�N���̌���ݒ�
	collisionParticlesNum = num;
	// �V�����Փ˃p�[�e�B�N���̔z���collisionParticles�ɒǉ�
	collisionParticles.push_back(new CollisionParticle[collisionParticlesNum]());

	// �e�Փ˃p�[�e�B�N���ɑ΂��ď������ƃp�[�e�B�N���̔�s�������s��
	for (int i = 0; i < collisionParticlesNum; i++)
		collisionParticles.back()[i].DoParticleFly(pos, collisionParticleGraph, firstSpeed);
}

// �p�[�e�B�N���̍X�V���s���֐�
void ParticleManager::Update()
{
	// �`���[�W�p�[�e�B�N���̍X�V
	for (int i = 0; i < chargeParticles.size(); i++)
	{
		chargeParticles[i]->Update();
	}

	// �Փ˃p�[�e�B�N���̍X�V
	for (auto particle : collisionParticles)
	{
		for (int i = 0; i < collisionParticlesNum; i++)
		{
			particle[i].Update();
		}
	}
}

// �p�[�e�B�N���̕`����s���֐�
void ParticleManager::Draw()
{
	int cnt = 0;

	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

	// �`���[�W�p�[�e�B�N���̕`��ƕs���p�[�e�B�N���̍폜
	for (int i = 0; i < chargeParticles.size(); i++)
	{
		chargeParticles[i]->Draw();

		// �p�[�e�B�N�����s���̏ꍇ�A�s���p�[�e�B�N���̐����J�E���g
		if (!chargeParticles[i]->IsVisible())
		{
			chargeParticles.erase(chargeParticles.begin() + i--);
		}
	}

	// �Փ˃p�[�e�B�N���̕`��ƕs���p�[�e�B�N���̍폜
	for (int i = 0; i < collisionParticles.size(); i++)
	{
		cnt = 0;
		for (int j = 0; j < collisionParticlesNum; j++)
		{
			collisionParticles[i][j].Draw();

			// �p�[�e�B�N�����s���̏ꍇ�A�s���p�[�e�B�N���̐����J�E���g
			// �p�[�e�B�N�����\������Ă���Ȃ�break���A���[�v�ϐ� j ��Num�Ɠ����Ȃ�폜����
			if (!collisionParticles[i][j].IsVisible())
			{
				cnt++;
			}
		}

		// �p�[�e�B�N�������ׂĕs���ɂȂ�����A���̔z����폜����nullptr�ɂ���
		if (cnt == collisionParticlesNum)
		{
			delete[] collisionParticles[i];
			collisionParticles[i] = nullptr;
		}
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, NULL);

	for (int i = 0; i < collisionParticles.size(); i++)
	{
		if (collisionParticles[i] == nullptr)
			collisionParticles.erase(collisionParticles.begin() + i--);
	}
}
