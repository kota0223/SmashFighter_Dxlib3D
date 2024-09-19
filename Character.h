#pragma once

// �C���N���[�h
#include <vector>
#include <DxLib.h>
#include "ScoreAdd.h"
#include "DisplayTag.h"
#include "TagStruct.h"

// �O���錾
class ParticleManager;
class DisplayScore;
class ReviveEffect;
class Stage;
class MoveEffect;
class HitEffect;
class ChargeEffect;

/// <summary>
/// �L�����N�^�[�N���X
/// </summary>
class Character : public ScoreAddClass
{
protected:

	// �萔

	static const float	SPEED_MIN;					// ���x�Œ�l

	static const int	REVIVE_TIME;				// �����ɂ����鎞��
	static const float	REVIVE_DRAW_POS_Y;			// �������̃��f���̕`��ʒu�̍���
	static const int	BLINKING_INTERVAL_COUNT;	// �_�ł̊Ԋu�̃J�E���g

	static const int	CHARGE_PARTICLE_NUM;		// �`���[�W�p�[�e�B�N���̐�
	static const float	CHARGE_PARTICLE_SPEED;		// �`���[�W�p�[�e�B�N���̑��x
	static const float	CHARGE_PARTICLE_RANGE;		// �`���[�W�p�[�e�B�N���͈̔͂̑傫��
	static const int	CHARGE_DRAW_COUNT;			// �`���[�W�p�[�e�B�N����\������J�E���g��
	static const int	CHARGE_SE_VOLUME;			// �`���[�W���ʉ��{�����[��

	static const int	MAX_CHARGE_DIFFUSION_NUM;	// �}�b�N�X�`���[�W�g�U�p�[�e�B�N���̐�
	static const float	MAX_CHARGE_DIFFUSION_RANGE;	// �}�b�N�X�`���[�W�g�U�p�[�e�B�N���͈̔͂̑傫��
	static const int	MAX_CHARGE_COUNT;			// �}�b�N�X�`���[�W�̃J�E���g��
	static const int	MAX_CHARGE_DRAW_COUNT_1;	// �`���[�W�p�[�e�B�N����\������J�E���g��
	static const int	MAX_CHARGE_DRAW_COUNT_2;	// �`���[�W�p�[�e�B�N����\������J�E���g��

	static const float	COLLISION_RANGE;			// �����蔻�蔼�a
	static const float	COLLISION_DRAW_SPEED;		// �ڐG�`�������X�s�[�h�K��l
	static const int	COLLISION_PARTICLE_NUM;		// �ڐG�p�[�e�B�N���̐�
	static const float	COLLISION_PARTICLE_SPEED;	// �ڐG�p�[�e�B�N���̑��x

	static const float	STAGE_FALL_SPEED;			// �X�e�[�W�O�̗����鑬�x�̒l
	static const float	STAGE_OUT_NUM;				// �X�e�[�W�O�Ƃ݂Ȃ��l

	// �ϐ�

	VECTOR position;		// ���W
	VECTOR rotation;		// ��]�x�N�g��
	VECTOR velocityVector;	// ���x�x�N�g��
	VECTOR collisionVector;	// �ڐG��̕����x�N�g��
	VECTOR initPos;			// �������W
	VECTOR initRotation;	// ������]�x�N�g��
	VECTOR scorePos;		// �X�R�A�\�����W

	int score;				// �X�R�A
	int chargeEffectCount;	// �`���[�W�G�t�F�N�g�J�E���g
	int riviveTimer;		// �����^�C�}�[
	float velocity;			// ���x
	bool isLeaping;			// ��΂���Ă��邩
	bool isStageOut;		// �X�e�[�W���痎������
	bool isCharge;			// �`���[�W����
	bool isChargeMove;		// �`���[�W�ړ�����
	bool isRevive;			// ��������

	ReviveEffect* reviveEffect;		// �����G�t�F�N�g
	MoveEffect* moveEffect;			// �ړ��G�t�F�N�g
	ParticleManager* particleMgr;	// �p�[�e�B�N���}�l�[�W���[

	int modelHandle;				// �L�����N�^�[���f���n���h��
	int collisionParticleGraph;		// �R���W�����p�[�e�B�N���摜�n���h��
	int chargeParticleGraph;		// �`���[�W�p�[�e�B�N���摜�n���h��
	int chargeMaxParticleGraph_1;	// �}�b�N�X�`���[�W�p�[�e�B�N���摜�n���h��_1
	int chargeMaxParticleGraph_2;	// �}�b�N�X�`���[�W�p�[�e�B�N���摜�n���h��_2
	int lightGraphHandle;			// ���摜�n���h��

	int moveEffectVertexShaderHandle;	// �ړ��G�t�F�N�g���_�V�F�[�_�[�n���h��
	int hitEffectVertexShaderHandle;	// �q�b�g�G�t�F�N�g���_�V�F�[�_�[�n���h��
	int chargeEffectVertexShaderHandle;	// �`���[�W�G�t�F�N�g���_�V�F�[�_�n���h��
	int pixelShaderHandle;				// �s�N�Z���V�F�[�_�[�n���h��

	int chargeSE;		// �`���[�W���ʉ�
	int collisionSE;	// �ڐG���ʉ�
	int scoreAddSE;		// �X�R�A�ǉ����ʉ�

	std::vector<DisplayScore> displayScore;		// �X�R�A�\���N���X
	std::vector<HitEffect*> hitEffect;			// �q�b�g�G�t�F�N�g
	std::vector<ChargeEffect*> chargeEffect;	// �`���[�W�G�t�F�N�g

	DisplayTag displayTag;	// �^�O�\���N���X

	ScoreAddClass* scoreAddCharacter;	//�X�R�A���Z�L�����N�^�[�ۑ��N���X

	WORD indexCircle[(20*2+2)*3];	// �|���S���C���f�b�N�X�z��

	FLOAT4 empty = { 0 };	// ��ϐ�

public:

	/// <summary>
	/// �R���X�g���N�^
	/// �������A�e��f�[�^�̃��[�h
	/// </summary>
	/// <param name="initPosition">�L�����N�^�[�����ʒu</param>
	Character();

	/// <summary>
	/// �����f�X�g���N�^
	/// �n���h���̍폜�A�������̉��
	/// </summary>
	virtual ~Character();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(const VECTOR& initPosition, ParticleManager* particleManager);

	/// <summary>
	/// �X�V����
	/// </summary>
	virtual void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	virtual void Draw();

	/// <summary>
	/// ���ʉ��̓ǂݍ���
	/// �f���v���C�ł͉��𗬂��Ȃ����߁A�؂藣���Ă���
	/// </summary>
	void LoadSE();

	/// <summary>
	/// ���f���̕`��
	/// </summary>
	void DrawModel();

	/// <summary>
	/// �X�e�[�W�Ƃ̐ڐG����
	/// </summary>
	/// <param name="stage">Stage�N���X�C���X�^���X�̃|�C���^</param>
	void CollisionStage(const Stage* stage);

	/// <summary>
	/// �ڐG���̏���
	/// </summary>
	/// <param name="direction">�ړ������̃x�N�g��</param>
	/// <param name="velocity">�ړ����x</param>
	/// <param name="collision"></param>
	void DoHit(VECTOR direction, float velocity, ScoreAddClass* collision);

	/// <summary>
	/// �ڐG��̏���
	/// </summary>
	void DoLeap();

	/// <summary>
	/// �X�e�[�W�O�ɗ������鏈��
	/// </summary>
	void UpdateStageOut();

	/// <summary>
	/// �X�e�[�W�O�ɗ��������ۂ̏���������
	/// </summary>
	void InitStageOut();

	/// <summary>
	/// �p�[�e�B�N���`��
	/// </summary>
	void DrawParticle();

	/// <summary>
	/// �G�t�F�N�g�`��
	/// </summary>
	void DrawEffect();

	/// <summary>
	/// �X�R�A�`��
	/// </summary>
	virtual void DrawScore(int x, int y) = 0;

	/// <summary>
	/// �X�R�A����
	/// </summary>
	void ScoreAdd();

	/// <summary>
	/// ��\���̃X�R�A��`�悷��
	/// �Ȃ���΁A�R���e�i�ɗv�f��ǉ�����
	/// </summary>
	void DrawScoreIfHidden();

	/// <summary>
	/// �`���[�W�̌��ʉ����~�߂�
	/// </summary>
	void StopChargeSE();

	/// <summary>
	/// �������̃G�t�F�N�g�`��
	/// </summary>
	void UpdateReviveEffect();

	/// <summary>
	/// ��΂��ꂽ�t���O�𗧂Ă�
	/// </summary>
	void EnableIsLeaping() { isLeaping = true; }

	/// <summary>
	/// ���W���擾
	/// </summary>
	/// <returns>VECTOR�^ �L�����N�^�[�̍��W�x�N�g��</returns>
	VECTOR GetPosition() const { return position; }

	/// <summary>
	/// �����蔻�蔼�a���擾
	/// </summary>
	/// <returns>Float�^ �L�����N�^�[�̓����蔻��̔��a</returns>
	float GetCollisionRange() const { return COLLISION_RANGE; }

	/// <summary>
	/// ���x���擾
	/// </summary>
	/// <returns>Float�^ �L�����N�^�[�̑��x</returns>
	float GetVelocity() const { return velocity; }

	/// <summary>
	/// (�������܂߂�)���x�x�N�g�����擾
	/// </summary>
	/// <returns>VECTOR�^ ���x�x�N�g���x�N�g��</returns>
	VECTOR GetVelocityVector() const { return velocityVector; }

	/// <summary>
	/// (�������܂߂�)���x�x�N�g�����擾
	/// </summary>
	/// <returns>VECTOR�^ ���x�x�N�g���x�N�g��</returns>
	MATRIX GetModelMatrix() const { return MV1GetMatrix(modelHandle); }

	/// <summary>
	/// �ڐG�t���O��Ԃ�
	/// </summary>
	/// <returns>bool�^ �ڐG�������̃t���O</returns>
	bool GetIsLeaping() const { return isLeaping; }

	/// <summary>
	/// �X�e�[�W�O�ɂ��邩��Ԃ�
	/// </summary>
	/// <returns>bool�^ �X�e�[�W�O�ɂ��邩�̃t���O</returns>
	bool GetIsStageOut() const { return isStageOut; }

	/// <summary>
	/// �����t���O��Ԃ�
	/// </summary>
	/// <returns>bool�^ ���������ǂ����̃t���O </returns>
	bool GetIsRivive() const { return isRevive; }

	/// <summary>
	/// �`���[�W�ړ��t���O��Ԃ�
	/// </summary>
	/// <returns>bool�^ �`���[�W�ړ����t���O </returns>
	bool GetIsChargeMove() const { return isChargeMove; }

	/// <summary>
	/// �ϐ��ɕۑ�����Ă���L�����N�^�[�C���X�^���X�|�C���^��Ԃ�
	/// </summary>
	/// <returns>ScoreAddClass*�^ �X�R�A�𑝉�������L�����N�^�[�|�C���^</returns>
	ScoreAddClass* GetAddCharacter() { return scoreAddCharacter; }

	/// <summary>
	/// �X�R�A��Ԃ�
	/// </summary>
	/// <returns>int�^ �L�����N�^�[�̃X�R�A</returns>
	int GetScore() const { return score; }

	/// <summary>
	/// �L�����N�^�[�̃^�O�\���̂��擾����
	/// </summary>
	/// <returns>�L�����N�^�[�̃^�O�\����</returns>
	Tag_st GetCharaTag() { return displayTag.GetTag(); }
};