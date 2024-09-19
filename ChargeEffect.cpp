
// �C���N���[�h
#include <math.h>
#include "ChargeEffect.h"

// �萔
const int		ChargeEffect::VS_CONST_MATRIX_NUM = 62;									// ���_�V�F�[�_�s��̒萔�ԍ�
const int		ChargeEffect::VS_CONST_NUM = 57;										// ���_�V�F�[�_�̒萔�ԍ�
const COLOR_U8	ChargeEffect::POLYGON_OUTSIDE_COLOR = GetColorU8(255, 255, 255, 255);	// �|���S���O���̃J���[
const COLOR_U8	ChargeEffect::POLYGON_INSIDE_COLOR = GetColorU8(150, 150, 150, 255);	// �|���S�������̃J���[
const float		ChargeEffect::POLYGON_TEXTURE_POSITION_INTERVAL = 1.0 / 4.0;			// �|���S���̃e�N�X�`�����W�̃��[�v�Ԋu
const float		ChargeEffect::POLYGON_SCALE = 2.0f;										// �G�t�F�N�g�̃|���S���X�P�[���l
const int		ChargeEffect::LIGHT_GRAPH_COLOR[3] = {255,230,180};						// ���C�g�摜�̐F
const float		ChargeEffect::EFFECT_TIME = 20.0f;										// �G�t�F�N�g����

ChargeEffect::ChargeEffect(VECTOR pos, int time, int graphHandle, int vertexShader)
	: timer(time), lightTimer(time), position(pos), lightGraphHandle(graphHandle), vertexShaderHandle(vertexShader)
{
	FLOAT4 position = { pos.x,pos.y,pos.z,1.0f };

	// �|���S�����_�ݒ�
	for (int i = 0; i < VERTEX_NUM; i++)
	{
		drawVertex[i].norm = VGet(0.0f, 0.0f, -1.0f);
		drawVertex[i].spc = GetColorU8(0, 0, 0, 0);
		drawVertex[i].su = (float)GetNowCount();
		drawVertex[i].sv = 0;
		drawVertex[i].spos = position;
	}

	for (int i = 0, j = 0; i < VERTEX_NUM; i += 2, j++)
	{
		drawVertex[i].pos = VGet(0, 0, (float)i);
		drawVertex[i + 1].pos = VGet(0, 0, (float)(i + 1));

		drawVertex[i].dif = POLYGON_OUTSIDE_COLOR;
		drawVertex[i+1].dif = POLYGON_INSIDE_COLOR;

		drawVertex[i].u = POLYGON_TEXTURE_POSITION_INTERVAL * j;
		drawVertex[i].v = 0.0;

		drawVertex[i + 1].u = POLYGON_TEXTURE_POSITION_INTERVAL * j;
		drawVertex[i + 1].v = 1.0;
	}

	// �V�F�[�_�[�萔�ݒ�
	MATRIX mat = MGetScale(VGet(POLYGON_SCALE, POLYGON_SCALE, 0));

	SetVSConstFMtx(VS_CONST_MATRIX_NUM, mat);

	// ���Ԏ擾
	startTime = GetNowCount();
}

ChargeEffect::~ChargeEffect()
{
	// �����Ȃ�
}

void ChargeEffect::Draw(WORD index[])
{
	// ���G�t�F�N�g����
	if (lightTimer >= 0)
	{
		// �F�ύX
		SetDrawBright(LIGHT_GRAPH_COLOR[0], LIGHT_GRAPH_COLOR[1], LIGHT_GRAPH_COLOR[2]);

		// ���Z�`��
		SetDrawBlendMode(DX_BLENDMODE_ADD, (int)(255 * (float)(timer) / EFFECT_TIME));

		// �`����W
		VECTOR drawPos[4];

		// �ϊ��s��
		MATRIX mat = MGetRotZ(DX_PI_F / 2.0f * (float)timer / EFFECT_TIME);

		// ���W�ϊ�
		for (int i = 0; i < 4; i++)
		{
			drawPos[i] = VTransform(lightGraphPos[i], mat);
		}

		// �r���{�[�h�`��
		DrawModiBillboard3D(position,
			drawPos[0].x, drawPos[0].y,
			drawPos[1].x, drawPos[1].y,
			drawPos[2].x, drawPos[2].y,
			drawPos[3].x, drawPos[3].y, lightGraphHandle, TRUE);

		// �J���[�����ɖ߂�
		SetDrawBright(255, 255, 255);

		// �^�C�}�[����
		lightTimer--;
	}

	// �^�C�}�[����
	timer--;

	// ���Z�`��
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

	// �V�F�[�_�[�萔�p�ϐ�
	FLOAT4 f4num = { 1.0f - timer / EFFECT_TIME, 0, 0, 0 };

	// �萔�ݒ�
	SetVSConstF(VS_CONST_NUM, f4num);

	// �g�p���钸�_�V�F�[�_�[���Z�b�g
	SetUseVertexShader(vertexShaderHandle);

	// �|���S���`��
	DrawPolygonIndexed3DToShader(drawVertex, VERTEX_NUM, index, VERTEX_NUM - 2);

	// �u�����h�����ɕύX
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
