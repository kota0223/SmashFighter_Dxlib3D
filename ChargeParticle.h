#pragma once

class ChargeParticle{
private:
	//�萔
	static const float	SPEED_DECREASE;					// ���x����

	static const int	DIRECTION_RAND_SCALE;			// �����x�N�g���̗����̑傫��

	static const VECTOR	GRAPH_SCALE_CHARGED;			// �`���[�W��̉摜�X�P�[���l
	static const VECTOR GRAPH_SCALE;					// �摜�̃X�P�[���l

	static const float	INIT_SCALE_X;					// scaleX�ϐ��̏����l
	static const float	INIT_SCALE_Y;					// scaleY�ϐ��̏����l

	static const float	INIT_SCALE_X_CHARGED;			// �`���[�W���scaleX�ϐ��̏����l
	static const float	INIT_SCALE_Y_CHARGED;			// �`���[�W���scaleY�ϐ��̏����l

	static const float	CHARGED_SCALE_MAX;				// �`���[�W��̃X�P�[������l
	static const float	CHARGED_SCALE_ADD_AMOUNT;		// �`���[�W��̃X�P�[�������l
	
	static const float	PARTICLE_HIDDEN_SCALE_Y_MIN;	// �p�[�e�B�N�����\���ɂ���X�P�[����Y���W�Œ�l
	static const float	PARTICLE_HIDDEN_CROSS_MIN;		// �p�[�e�B�N�����\���ɂ���O�ς̍Œ�l

	// �ϐ�

	int graphHandle;			// �摜�n���h��
								  								   
	VECTOR pos;					// ���W
	VECTOR origin;				// ���S���W
	VECTOR DirectionsVec;		// �ړ������x�N�g��
	VECTOR moveVec;				// �ړ��x�N�g��
	float velocity;				// ���x
	float angle;				// �摜�̊p�x
	bool isVisible;				// �\������Ă��邩
	bool isCharged;				// �`���[�W�ォ

	float scaleX, scaleY;		// �X�P�[���l

	VECTOR horizonVector;		// �����x�N�g��
	VECTOR verticalVector;		// �����x�N�g��

	VECTOR graphPos[4]			// �摜���W
	{
		{-16,16},
		{16,16},
		{16,-16},
		{-16,-16},
	};
	VECTOR graphPosScale[4]		// �摜�X�P�[�����W
	{
		{-16,16},
		{16,16},
		{16,-16},
		{-16,-16},
	};
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	ChargeParticle();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ChargeParticle();

	/// <summary>
	/// �p�[�e�B�N���𔭎�
	/// </summary>
	/// <param name="pos">���ˈʒu�̍��W</param>
	/// <param name="cameraPos">�J�������W</param>
	/// <param name="graphHandle">�g�p����摜�̃n���h��</param>
	/// <param name="firstSpeed">�������x</param>
	/// <param name="range">�G�t�F�N�g�\�����a</param>
	void DoParticleFly(VECTOR pos, VECTOR cameraPos, int graphHandle, float firstSpeed, float range, bool isCharged);

	/// <summary>
	/// �p�[�e�B�N���̏�Ԃ��X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �p�[�e�B�N����`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �p�[�e�B�N�����\������Ă��邩�ǂ������擾
	/// </summary>
	/// <returns>�\������Ă��邩�ǂ���</returns>
	bool IsVisible() const;
};