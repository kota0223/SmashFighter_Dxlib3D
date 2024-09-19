
// �C���N���[�h
#include <math.h>
#include "HitEffect.h"

// �萔
const int		HitEffect::VS_CONST_MATRIX_NUM = 62;						// ���_�V�F�[�_�s��̒萔�ԍ�
const int		HitEffect::VS_CONST_NUM = 57;								// ���_�V�F�[�_�̒萔�ԍ�
const float		HitEffect::POLYGON_SCALE = 2.0f;							// �G�t�F�N�g�̃|���S���X�P�[���l
const COLOR_U8	HitEffect::EFFECT_COLOR = GetColorU8(230, 230, 110, 255);	// �G�t�F�N�g�J���[
const float		HitEffect::LIGHT_EFFECT_TIME = 7.0f;						// ����G�t�F�N�g�̎���
const float		HitEffect::POLYGON_TEXTURE_POSITION_INTERVAL = 1.0 / 4.0;	// �|���S���̃e�N�X�`�����W�̃��[�v�Ԋu
const int		HitEffect::LIGHT_GRAPH_COLOR[3] = { 255,230,150 };			// ���C�g�摜�̐F
const float		HitEffect::SCALE_CHANGE_SIZE = 2.5f;						// �X�P�[���ω��̑傫��
const float		HitEffect::LIGHT_EFFECT_SCALE_X = 3.5f;						// ����G�t�F�N�g��X���̑傫��
const float		HitEffect::LIGHT_EFFECT_SCALE_Y = 1.0f;						// ����G�t�F�N�g��Y���̑傫��
const float		HitEffect::LIGTH_EFFECT_ROTATION_SPEED = 1.3f;				// ����G�t�F�N�g�̉�]���x
const float		HitEffect::EFFECT_TIME = 20.0f;								// �G�t�F�N�g����

HitEffect::HitEffect(VECTOR pos, int time, int graphHandle, int vertexShader)
	: timer(time),lightTimer((int)LIGHT_EFFECT_TIME), position(pos),lightGraphHandle(graphHandle), vertexShaderHandle(vertexShader)
{
	FLOAT4 position = { pos.x,pos.y,pos.z,1.0f };

	// �|���S�����_�ݒ�
	for (int i = 0; i < VERTEX_NUM; i++)
	{
		drawVertex[i].norm = VGet(0.0f, 0.0f, -1.0f);
		drawVertex[i].dif = EFFECT_COLOR;
		drawVertex[i].spc = GetColorU8(0, 0, 0, 0);
		drawVertex[i].su = 0;
		drawVertex[i].sv = 0;
		drawVertex[i].spos = position;
	}

	for (int i = 0, j = 0; i < VERTEX_NUM; i += 2, j++)
	{
		drawVertex[i].pos = VGet(0, 0, (float)i);
		drawVertex[i + 1].pos = VGet(0, 0, (float)(i + 1));

		drawVertex[i].u = POLYGON_TEXTURE_POSITION_INTERVAL * j;
		drawVertex[i].v = 0.0;

		drawVertex[i + 1].u = POLYGON_TEXTURE_POSITION_INTERVAL * j;
		drawVertex[i + 1].v = 1.0;
	}

	// �V�F�[�_�[�萔�ݒ�
	SetVSConstFMtx(VS_CONST_MATRIX_NUM, MGetScale(VGet(POLYGON_SCALE, POLYGON_SCALE, 0)));
}

HitEffect::~HitEffect()
{
	// �����Ȃ�
}

void HitEffect::Draw(WORD index[])
{
	// ���G�t�F�N�g����
	if (lightTimer >= 0)
	{
		// �F�ύX
		SetDrawBright(LIGHT_GRAPH_COLOR[0], LIGHT_GRAPH_COLOR[1], LIGHT_GRAPH_COLOR[2]);

		// ���Z�`��
		SetDrawBlendMode(DX_BLENDMODE_ADD, (int)(255 * (lightTimer / LIGHT_EFFECT_TIME + 0.2f)));

		// �`����W
		VECTOR drawPos[4];

		// �ϊ��s��
		MATRIX mat = MGetScale(VGet(LIGHT_EFFECT_SCALE_X - (SCALE_CHANGE_SIZE * (1.0f - lightTimer / LIGHT_EFFECT_TIME)),
								LIGHT_EFFECT_SCALE_Y + (SCALE_CHANGE_SIZE * (1.0f - lightTimer / LIGHT_EFFECT_TIME)), 0));

		mat = MMult(mat, MGetRotZ(DX_PI_F / LIGTH_EFFECT_ROTATION_SPEED * (lightTimer / LIGHT_EFFECT_TIME)));

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

	// ���Z�`��
	SetDrawBlendMode(DX_BLENDMODE_ADD,255);

	// �^�C�}�[����
	timer--;

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


