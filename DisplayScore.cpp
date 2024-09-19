#include "DxLib.h"
#include "DisplayScore.h"

// �R���X�g���N�^
DisplayScore::DisplayScore()
{
	// �ϐ�������

	// Y���W�l������
	goGraphMoveY = 0;

	// �A���t�@�l������
	alpha = 0;

	// �X�R�A�\���摜
	scoreGraph = LoadGraph("data/image/Main/ScoreAdd.png");
}

// �f�X�g���N�^
DisplayScore::~DisplayScore()
{
	// �����Ȃ�
}

void DisplayScore::InitializeForDisplay()
{
	// Y���W�l������
	goGraphMoveY = 0;

	// �A���t�@�l������
	alpha = 0;
}

// �X�V����
void DisplayScore::Update()
{
	goGraphMoveY += 0.5;

	if (goGraphMoveY >= 30)
	{
		alpha -= 10;
	}
	else
	{
		alpha += 10;
	}
}

// �`�揈��
void DisplayScore::Draw(int x, int y)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

	DrawExtendGraph(x - 32, y - 32 - (int)goGraphMoveY, x + 32, y + 32 - (int)goGraphMoveY, scoreGraph, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, NULL);
}
