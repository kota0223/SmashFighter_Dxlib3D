#pragma once

#include <DxLib.h>

// UI�x�[�X�N���X
class BaseUI {
protected:
	int graphHandle;	// �摜�n���h��
	float x, y;			// �摜���W

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	BaseUI();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~BaseUI();

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="graphHandle">�摜�n���h��</param>
	/// <param name="x">X���W</param>
	/// <param name="y">Y���W</param>
	void Initialize(const int graphHandle, const int x, const int y);

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="frame">�t���[����</param>
	virtual void Update(int frame) = 0;

	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw();
};