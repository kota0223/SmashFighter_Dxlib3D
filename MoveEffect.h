#pragma once

#include "DxLib.h"

class MoveEffect {
private:

	// �萔

	static const int CIRCLE_VERTEX_NUM = 15;
	static const int VERTEX_NUM = (CIRCLE_VERTEX_NUM * 2) + 2;
	static const int VERTEX_INDEX_NUM = VERTEX_NUM * 3;

	static const int	  VS_CONST_MATRIX_NUM;					// ���_�V�F�[�_�s��̒萔�ԍ�
	static const COLOR_U8 EFFECT_COLOR;							// �G�t�F�N�g�J���[
	static const float	  POLYGON_INSIDE_SCALE;					// �|���S���̓����̃X�P�[���l
	static const float	  POLYGON_OUTSIDE_SCALE;				// �|���S���̊O���̃X�P�[���l
	static const float	  POLYGON_INSIDE_POSITION_Z;			// �|���S���̓�����Z���W
	static const float	  POLYGON_OUTSIDE_POSITION_Z;			// �|���S���̊O����Z���W
	static const float	  POLYGON_TEXTURE_POSITION_INTERVAL;	// �|���S���̃e�N�X�`�����W�̃��[�v�Ԋu

	// �ϐ�

	VERTEX3DSHADER vertex[VERTEX_NUM];

	WORD index[VERTEX_INDEX_NUM];

	float timer=0;

	int vertexShaderHandle;
	int pixelShaderHandle;

	int cindex;

	FLOAT4 f4 = { 0,0,0,0 };


public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�\�����W</param>
	/// <param name="vertexShader">���_�V�F�[�_�n���h��</param>
	/// <param name="pixelHandle">�s�N�Z���V�F�[�_�n���h��</param>
	MoveEffect(VECTOR pos, int vertexShader, int pixelHandle);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~MoveEffect();

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="mat">���f���̍��W�ϊ��p�s��</param>
	void Draw(MATRIX mat);
};