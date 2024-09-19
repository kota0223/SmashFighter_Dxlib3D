#include <math.h>
#include "MoveEffect.h"

const int		MoveEffect::VS_CONST_MATRIX_NUM = 10;						// ���_�V�F�[�_�s��̒萔�ԍ�
const COLOR_U8	MoveEffect::EFFECT_COLOR = GetColorU8(230, 230, 110, 255);	// �G�t�F�N�g�J���[
const float		MoveEffect::POLYGON_INSIDE_SCALE = 40.0f;					// �|���S���̓����̃X�P�[���l
const float		MoveEffect::POLYGON_OUTSIDE_SCALE = 150.0f;					// �|���S���̊O���̃X�P�[���l
const float		MoveEffect::POLYGON_INSIDE_POSITION_Z = 300.0f;				// �|���S���̓�����Z���W
const float		MoveEffect::POLYGON_OUTSIDE_POSITION_Z = -50.0f;			// �|���S���̊O����Z���W
const float		MoveEffect::POLYGON_TEXTURE_POSITION_INTERVAL = 1.0 / 4.0;	// �|���S���̃e�N�X�`�����W�̃��[�v�Ԋu

MoveEffect::MoveEffect(VECTOR pos, int vertexShader, int pixelHandle)
	:vertexShaderHandle(vertexShader), pixelShaderHandle(pixelHandle)
{
	// �|���S�����_�ݒ�
	for (int i = 0; i < VERTEX_NUM; i++)
	{
		vertex[i].norm = VGet(0.0f, 0.0f, -1.0f);
		vertex[i].dif = EFFECT_COLOR;
		vertex[i].spc = GetColorU8(0, 0, 0, 0);
		vertex[i].su = 0;
		vertex[i].sv = 0;
	}

	for (int i = 0, j = 0; i < VERTEX_NUM; i += 2, j++)
	{
		vertex[i].pos = VGet(cosf(DX_PI_F * 2 / CIRCLE_VERTEX_NUM * j) * POLYGON_OUTSIDE_SCALE,
							 sinf(DX_PI_F * 2 / CIRCLE_VERTEX_NUM * j) * POLYGON_OUTSIDE_SCALE,
							 -POLYGON_OUTSIDE_POSITION_Z);

		vertex[i + 1].pos = VGet(cosf(DX_PI_F * 2 / CIRCLE_VERTEX_NUM * j) * POLYGON_INSIDE_SCALE,
								 sinf(DX_PI_F * 2 / CIRCLE_VERTEX_NUM * j) * POLYGON_INSIDE_SCALE,
								 POLYGON_INSIDE_POSITION_Z);

		vertex[i].u = POLYGON_TEXTURE_POSITION_INTERVAL * j;
		vertex[i].v = 0.0;

		vertex[i + 1].u = POLYGON_TEXTURE_POSITION_INTERVAL * j;
		vertex[i + 1].v = 1.0;
	}

	// �|���S���C���f�b�N�X
	for (int i = 0, k = 0; i < VERTEX_INDEX_NUM; i += 6) {
		index[0 + i] = k;
		index[1 + i] = k + 2;
		index[2 + i] = k + 1;
		index[3 + i] = k + 1;
		index[4 + i] = k + 2;
		index[5 + i] = k + 3;
		k += 2;
	}
	
	// �V�F�[�_�[�萔�ݒ�
	cindex = GetConstIndexToShader("num", pixelShaderHandle);
}

MoveEffect::~MoveEffect()
{
	// �����Ȃ�
}

void MoveEffect::Draw(MATRIX mat)
{

	// ���Z�`��
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

	// �萔�ݒ�
	SetVSConstFMtx(VS_CONST_MATRIX_NUM, mat);

	// �g�p���钸�_�V�F�[�_�[���Z�b�g
	SetUseVertexShader(vertexShaderHandle);

	// �萔�p�ϐ��Ƀ^�C�}�[���
	f4.y = timer;

	// �^�C�}�[����
	timer += 0.1f;

	// �萔�ݒ�
	SetPSConstF(cindex, f4);

	// �g�p����s�N�Z���V�F�[�_�[���Z�b�g
	SetUsePixelShader(pixelShaderHandle);

	// �|���S���`��
	DrawPolygonIndexed3DToShader(vertex, VERTEX_NUM, index, VERTEX_NUM - 2);

	// �u�����h�����ɕύX
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}
