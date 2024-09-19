#include "ReviveEffect.h"

// �����̂̊e�ӂ̃T�C�Y�ݒ�
const float ReviveEffect::X_SIZE = 8.0f;
const float ReviveEffect::Y_SIZE = 30.0f;
const float ReviveEffect::Z_SIZE = 8.0f;

// �����̂̉��̖ʂ̐F�ݒ�
const int ReviveEffect::POLYGON_COLOR_RED = 255;
const int ReviveEffect::POLYGON_COLOR_GREEN = 255;
const int ReviveEffect::POLYGON_COLOR_BLUE = 0;

// �����̂̏㉺�̖ʂ̃A���t�@�l�ݒ�
const int ReviveEffect::TOP_ALPHA = 255;
const int ReviveEffect::BOTTOM_ALPHA = 0;

// �����̂̕ό`�Ɋւ���ݒ�
const float ReviveEffect::HEIGHT_ADD_SIZE = 3.0f;
const float ReviveEffect::WIDTH_ADD_SCALE = 0.1f;
const float ReviveEffect::WIDTH_MINIMUM_SIZE = 0.5f;

// �u�����h���[�h�ݒ�
const int ReviveEffect::BLEND_ADD_NUM = 255;

// ReviveEffect�N���X�̃R���X�g���N�^
ReviveEffect::ReviveEffect(VECTOR origin) : origin(origin)
{
	// �����̂̉��̖ʂ̃f�B�t���[�Y�J���[��ݒ�
	for (int i = 0; i < VERTEX_NUM / 2; i++)
	{
		Vertex[i].dif = GetColorU8(POLYGON_COLOR_RED, POLYGON_COLOR_GREEN, POLYGON_COLOR_BLUE, TOP_ALPHA);
	}

	// �����̂̏�̖ʂ̃f�B�t���[�Y�J���[��ݒ�
	for (int i = VERTEX_NUM / 2; i < VERTEX_NUM; i++)
	{
		Vertex[i].dif = GetColorU8(POLYGON_COLOR_RED, POLYGON_COLOR_GREEN, POLYGON_COLOR_BLUE, BOTTOM_ALPHA);
	}

	InitPos();

	// ���_������
	for (int i = 0; i < 8; i++)
	{
		Vertex[i].norm = VGet(0.0f, 0.0f, -1.0f);
		Vertex[i].spc = GetColorU8(0, 0, 0, 0);
		Vertex[i].u = 0.0f;
		Vertex[i].v = 0.0f;
		Vertex[i].su = 0.0f;
		Vertex[i].sv = 0.0f;
	}

	// 8�|���S�����̃C���f�b�N�X�f�[�^���Z�b�g
	Index[0] = 0;
	Index[1] = 1;
	Index[2] = 4;

	Index[3] = 5;
	Index[4] = 4;
	Index[5] = 1;

	Index[6] = 1;
	Index[7] = 2;
	Index[8] = 5;

	Index[9] = 6;
	Index[10] = 5;
	Index[11] = 2;

	Index[12] = 2;
	Index[13] = 3;
	Index[14] = 6;

	Index[15] = 7;
	Index[16] = 6;
	Index[17] = 3;

	Index[18] = 3;
	Index[19] = 0;
	Index[20] = 7;

	Index[21] = 4;
	Index[22] = 7;
	Index[23] = 0;

	// �\���t���O������
	isVisible = false;
}

// �����ʒu�ݒ�֐�
void ReviveEffect::InitPos()
{
	int i = 0;

	Vertex[0].pos = VAdd(origin, VGet(-X_SIZE / 2, 0, -Z_SIZE / 2));
	Vertex[1].pos = VAdd(origin, VGet(X_SIZE / 2, 0, -Z_SIZE / 2));
	Vertex[2].pos = VAdd(origin, VGet(X_SIZE / 2, 0, Z_SIZE / 2));
	Vertex[3].pos = VAdd(origin, VGet(-X_SIZE / 2, 0, Z_SIZE / 2));

	for (i = VERTEX_NUM / 2; i < VERTEX_NUM; i++)
	{
		Vertex[i].pos = VAdd(Vertex[i - VERTEX_NUM / 2].pos, VGet(0, Y_SIZE, 0));
	}
}

// �A�b�v�f�[�g�֐�
void ReviveEffect::Update()
{
	if (isVisible)
	{
		// �����̂̏�̖ʂ̒��_�̍��W����Ɉړ�������
		for (int i = VERTEX_NUM / 2; i < VERTEX_NUM; i++)
		{
			Vertex[i].pos.y += HEIGHT_ADD_SIZE;
		}

		// �����̂̕ό`����
		for (int i = 0; i < VERTEX_NUM; i++)
		{
			VECTOR v1 = VSub(VGet(origin.x, Vertex[i].pos.y, origin.z), Vertex[i].pos);
			if (VSize(v1) > 0)
			{
				v1 = VNorm(v1);
			}
			Vertex[i].pos = VAdd(Vertex[i].pos, VScale(v1, WIDTH_ADD_SCALE));
		}

		// �����̂����T�C�Y�ȉ��ɂȂ������\���ɂ���
		if (VSize(VSub(Vertex[0].pos, origin)) < WIDTH_MINIMUM_SIZE)
		{
			isVisible = false;
		}
	}
}

// �`��֐�
void ReviveEffect::Draw()
{
	// �\���t���O�������Ă�����
	if (isVisible)
	{
		SetDrawBlendMode(DX_BLENDMODE_ADD, BLEND_ADD_NUM);

		// �|���S���̕`��
		DrawPolygonIndexed3D(Vertex, VERTEX_NUM, Index, POLYGON_NUM, DX_NONE_GRAPH, FALSE);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, NULL);
	}
}

// �Đ��֐�
void ReviveEffect::DoPlay()
{
	InitPos();
	isVisible = true;
}