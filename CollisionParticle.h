#pragma once

class CollisionParticle {
private:

	// �萔
	static const int   DIRECTION_RAND_SCALE;				// �����x�N�g���̗����̑傫��
	static const float SPEED_DECREASE;						// ���x����
	static const float SIZE_CHANGE;							// �T�C�Y�ω���
	static const int PARTICLE_SIZE;							// �p�[�e�B�N�����̑傫��
	static const int PARTICLE_SIZE_MIN;						// �p�[�e�B�N���ŏ��T�C�Y
	static const float ANGLE_ADD;							// ��]���������
	static const float PARTICLE_ROTATION_BEGIN_VELOCITY;	// ��]���n�߂�p�[�e�B�N�����̂̑��x
	static const float BILLBOARD_CENTER_POSITION_X;			// �r���{�[�h�摜�̒��SX���W
	static const float BILLBOARD_CENTER_POSITION_Y;			// �r���{�[�h�摜�̒��SY���W

	// �ϐ�
	int graphHandle;      // �摜�n���h��
	VECTOR pos;           // ���W
	VECTOR DirectionsVec; // �ړ������x�N�g��
	VECTOR moveVec;       // �ړ��x�N�g��
	float velocity;       // ���x
	float size;           // �T�C�Y
	float sizeMax;        // �T�C�Y�̍ő��
	float angle;          // ��]�p�x(���W�A��)

	bool isFinish;        // �A�j���[�V�������I��点�邩

	bool isVisible;       // �\������Ă��邩
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	CollisionParticle();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~CollisionParticle();

	/// <summary>
	/// �p�[�e�B�N���𔭎�
	/// </summary>
	/// <param name="pos">���ˈʒu�̍��W</param>
	/// <param name="graphHandle">�g�p����摜�̃n���h��</param>
	/// <param name="firstSpeed">�������x</param>
	void DoParticleFly(VECTOR pos, int graphHandle, float firstSpeed);

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
