#pragma once

class DisplayScore {
private:
	float goGraphMoveY;	// ������Y���W�̒l

	int alpha;		// �A���t�@�l

	int scoreGraph;	// �X�R�A�\���摜

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	DisplayScore();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~DisplayScore();

	/// <summary>
	/// �\���̂��߂̏�����
	/// </summary>
	void InitializeForDisplay();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw(int x, int y);

	/// <summary>
	/// �\������Ă��邩�ǂ���
	/// </summary>
	/// <returns>�\������Ă��邩��Bool�^�t���O</returns>
	bool IsHidden() const
	{
		return goGraphMoveY >= 20 && alpha <= 0;
	}
};