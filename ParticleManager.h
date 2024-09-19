#pragma once

#include <vector>
#include "ChargeParticle.h"

class CollisionParticle;

class ParticleManager
{
public:

	// �`���[�W�摜���
	enum ChargeGraphKind
	{
		CHARGE_NORMAL = 0,
		CHARGE_MAX_1,
		CHARGE_MAX_2,
		CHARGE_GRAPH_AMOUNT
	};

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	ParticleManager();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ParticleManager();

	///<summary>
	/// �p�[�e�B�N���̐����Ɛݒ���s���܂��B
	///</summary>
	///<param name="pos">�p�[�e�B�N���̏����ʒu</param>
	///<param name="num">��������p�[�e�B�N���̐�</param>
	///<param name="graphHandle">�p�[�e�B�N���̃O���t�B�b�N�n���h��</param>
	///<param name="firstSpeed">�p�[�e�B�N���̏������x</param>
	void SetCollisionParticle(VECTOR pos, int num, float firstSpeed);

	///<summary>
	/// �p�[�e�B�N���̐����Ɛݒ���s���܂��B
	///</summary>
	///<param name="pos">�p�[�e�B�N���̏����ʒu</param>
	///<param name="cameraPos">�J�����̈ʒu</param>
	///<param name="num">��������p�[�e�B�N���̐�</param>
	///<param name="graphHandle">�p�[�e�B�N���̃O���t�B�b�N�n���h��</param>
	///<param name="firstSpeed">�p�[�e�B�N���̏������x</param>
	void SetChargeParticle(ChargeGraphKind graphKind, VECTOR pos, VECTOR cameraPos, int num, float firstSpeed, float range, bool isCharged);

	///<summary>
	/// �p�[�e�B�N���̏�Ԃ��X�V���܂��B
	///</summary>
	void Update();

	///<summary>
	/// �p�[�e�B�N����`�悵�܂��B
	///</summary>
	void Draw();
private:
	int chargeParticlesNum;								// �`���[�W�p�[�e�B�N���̐�
	int collisionParticlesNum;							// �R���W�����p�[�e�B�N���̐�
	std::vector<ChargeParticle*> chargeParticles;		// �`���[�W�p�[�e�B�N�����Ǘ����邽�߂̃x�N�^�[
	std::vector<CollisionParticle*> collisionParticles;	// �R���W�����p�[�e�B�N�����Ǘ����邽�߂̃x�N�^�[
	int collisionParticleGraph;							// �R���W�����p�[�e�B�N���摜�n���h��

	int chargeParticleGraphs[CHARGE_GRAPH_AMOUNT];		// �`���[�W�p�[�e�B�N���摜�z��
};
