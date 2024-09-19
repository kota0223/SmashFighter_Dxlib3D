#pragma once

#include "DxLib.h"

class ReviveEffect
{
private:

	// �萔

	// ���_�ƃ|���S���̐�
	static const int VERTEX_NUM = 8;
	static const int POLYGON_NUM = 8;

	// �T�C�Y�̒萔
	static const float X_SIZE;
	static const float Y_SIZE;
	static const float Z_SIZE;

	// �|���S���̐F
	static const int POLYGON_COLOR_RED;
	static const int POLYGON_COLOR_GREEN;
	static const int POLYGON_COLOR_BLUE;

	// �A���t�@�l
	static const int TOP_ALPHA;
	static const int BOTTOM_ALPHA;

	// �T�C�Y�̑�����
	static const float HEIGHT_ADD_SIZE;
	static const float WIDTH_ADD_SCALE;

	// �T�C�Y�̍ŏ��l
	static const float WIDTH_MINIMUM_SIZE;

	// �u�����h���[�h�Ɋւ���萔
	static const int BLEND_ADD_NUM;

	// ���_���
	VERTEX3D Vertex[VERTEX_NUM];

	// �|���S���̃C���f�b�N�X
	WORD Index[POLYGON_NUM * 3];

	// ���_�̈ʒu
	VECTOR origin;

	// �����t���O
	bool isVisible;

public:

	/// <summary>
	// �R���X�g���N�^
	/// </summary>
	/// <param name="origin">���_�̈ʒu</param>
	ReviveEffect(VECTOR origin);

	/// <summary>
	/// �����ʒu�̐ݒ�
	/// </summary>
	void InitPos();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �Đ��J�n
	/// </summary>
	void DoPlay();

	bool GetIsDelete() const { return !isVisible; }
};
