#include "DxLib.h"
#include <algorithm>
#include "ResultScore.h"

const int ResultScore::SCORE_FONT_EDGE_SIZE = 3;	// �X�R�A�t�H���g�̉����T�C�Y
const int ResultScore::NAME_FONT_EDGE_SIZE = 3;		// ���O�t�H���g�̉����T�C�Y

const int ResultScore::RANK_NUM = 4;				// ���ʂ̐�
const int ResultScore::MOVE_X_ADD_NUM = 5;			// X���W�ړ��ʂ̑�����
const int ResultScore::ALPHA_ADD_NUM = 10;			// �A���t�@�l�̑�����
const int ResultScore::MOVE_X_MAX = 200;			// X���W�ړ��ʂ̍ő�l
		  
const int ResultScore::RANK_X_INTERVAL = 110;		// ���ʕ`���X���W�̊Ԋu
const int ResultScore::RANK_Y_INTERVAL = 120;		// ���ʕ`���Y���W�̊Ԋu
		  
const int ResultScore::FRAME_GRAPH_X = 700;			// �t���[���摜��X���W��l
const int ResultScore::FRAME_GRAPH_Y = 550;			// �t���[���摜��Y���W��l
		  
const int ResultScore::RANK_GRAPH_X = 620;			// ���ʉ摜��X���W��l
const int ResultScore::RANK_GRAPH_Y = 500;			// ���ʉ摜��Y���W��l
		  
const int ResultScore::TAG_GRAPH_X = 760;			// �^�O�摜��X���W��l
const int ResultScore::TAG_GRAPH_Y = 550;			// �^�O�摜��Y���W��l
const int ResultScore::FRAME_GRAPH_WIDTH = 128;		// �^�O�摜�̕�
const int ResultScore::FRAME_GRAPH_HEIGHT = 64;		// �^�O�摜�̍���
		  
const int ResultScore::SCORE_TEXT_X = 940;			// �X�R�A�e�L�X�g��X���W��l
const int ResultScore::SCORE_TEXT_Y = 550;			// �X�R�A�e�L�X�g��Y���W��l
const int ResultScore::PT_TEXT_X = 1020;			// "pt"�e�L�X�g��X���W��l

// �R���X�g���N�^
ResultScore::ResultScore()
{
	// �����Ȃ�
}

// �f�X�g���N�^
ResultScore::~ResultScore()
{
	// �����Ȃ�
}

// ������
void ResultScore::Initialize()
{
	frameGraph = LoadGraph("data/image/Result/ResultFrame.png");

	rankGraph[0] = LoadGraph("data/image/Result/1st.png");
	rankGraph[1] = LoadGraph("data/image/Result/2nd.png");
	rankGraph[2] = LoadGraph("data/image/Result/3rd.png");
	rankGraph[3] = LoadGraph("data/image/Result/4th.png");

	fontHandle = LoadFontDataToHandle("data/fonts/ResultScoreFont.dft", SCORE_FONT_EDGE_SIZE);
	nameFont = LoadFontDataToHandle("data/fonts/Impact.dft", NAME_FONT_EDGE_SIZE);

	drawSE = LoadSoundMem("data/sounds/Result/drawSE.mp3");

	drawSE2 = LoadSoundMem("data/sounds/Result/drawSE2.mp3");

	for (int i = 0; i < RANK_NUM; i++)
	{
		rankVisible[i] = false;
	}

	drawNum = 0;

	visibleNum = 0;

	alpha = 0;
}

// �X�R�A�ǉ�
void ResultScore::AddScore(int score, Tag_st Tag)
{
	// �X�R�A���
	resultScore.push_back(std::make_pair(score, Tag));

	// �X�R�A���~���ɕ��ѕς���
	sort(resultScore.begin(), resultScore.end(), [&](std::pair<int, Tag_st> i, std::pair<int, Tag_st> j) {
		return j.first < i.first;
		});
}

// �`��
void ResultScore::Draw(int x, int y)
{
	// �`�悷����̂�0�Ȃ�`�悷����̂�T��
	if (drawNum == 0)
	{
		for (i = 3; i >= 0; i--)
		{
			if (rankVisible[i])
				continue;

			for (j = 0; j < RANK_NUM; j++)
			{
				if (rank[j] == i + 1)
				{
					drawNum++;
				}
			}

			if (drawNum > 0)
			{
				PlaySoundMem(drawSE, DX_PLAYTYPE_BACK);
				rankVisible[i] = true;
				break;
			}
		}
	}
	else
	{
		// UI�̃A�j���[�V����
		moveX += MOVE_X_ADD_NUM;
		alpha += ALPHA_ADD_NUM;

		// X�̈ړ��n���ő�ʂɒB�����Ƃ�
		if (moveX >= MOVE_X_MAX)
		{
			// SE���Đ�
			PlaySoundMem(drawSE2, DX_PLAYTYPE_BACK);

			// �\���������Z
			visibleNum += drawNum;

			// �ϐ��̏�����
			drawNum = 0;
			moveX = 0;
			alpha = 0;
		}

		// �����x�K�p
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

		// �t���[���摜�`��
		for (i = 0; i < drawNum; i++)
		{
			DrawGraph(FRAME_GRAPH_X - RANK_X_INTERVAL * (i + visibleNum) + MOVE_X_MAX - moveX,
				FRAME_GRAPH_Y - RANK_Y_INTERVAL * (i + visibleNum), frameGraph, TRUE);
		}

		// �����x���Z�b�g
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, NULL);
	}

	// �\�����������̂�`�悷��
	for (i = 0; i < visibleNum; i++)
	{
		// �t���[���`��
		DrawGraph(FRAME_GRAPH_X - RANK_X_INTERVAL * i,
			FRAME_GRAPH_Y - RANK_Y_INTERVAL * i, frameGraph, TRUE);

		// ���ʕ`��
		DrawGraph(RANK_GRAPH_X - RANK_X_INTERVAL * i, RANK_GRAPH_Y - RANK_Y_INTERVAL * i, rankGraph[rank[3 - i] - 1], TRUE);

		// �^�O�w�i�`��
		DrawExtendGraph(TAG_GRAPH_X - RANK_X_INTERVAL * i,
						TAG_GRAPH_Y - RANK_Y_INTERVAL * i,
						TAG_GRAPH_X - RANK_X_INTERVAL * i + FRAME_GRAPH_WIDTH,
						TAG_GRAPH_Y - RANK_Y_INTERVAL * i + FRAME_GRAPH_HEIGHT, resultScore[3 - i].second.tagBaseGraph, TRUE);

		
		// �F�ݒ�
		SetDrawBright(resultScore[3 - i].second.red, resultScore[3 - i].second.green, resultScore[3 - i].second.blue);

		// �^�O�`��
		DrawExtendGraph(TAG_GRAPH_X - RANK_X_INTERVAL * i,
						TAG_GRAPH_Y - RANK_Y_INTERVAL * i,
						TAG_GRAPH_X - RANK_X_INTERVAL * i + FRAME_GRAPH_WIDTH,
						TAG_GRAPH_Y - RANK_Y_INTERVAL * i + FRAME_GRAPH_HEIGHT, resultScore[3 - i].second.tagGraph, TRUE);

		// �F���Z�b�g
		SetDrawBright(255, 255, 255);

		// �X�R�A�`��
		DrawStringToHandle(SCORE_TEXT_X - RANK_X_INTERVAL * i,
			SCORE_TEXT_Y - RANK_Y_INTERVAL * i, std::to_string(resultScore[3 - i].first).c_str(),
			GetColor(240, 145, 62), fontHandle, GetColor(255, 255, 255));

		// �X�R�A�̌�ɂ���"pt"�̕����`��
		DrawStringToHandle(PT_TEXT_X - RANK_X_INTERVAL * i,
			SCORE_TEXT_Y - RANK_Y_INTERVAL * i, "pt",
			GetColor(240, 145, 62), fontHandle, GetColor(255, 255, 255));
	}
}

// �������ʂ̐ݒ�
void ResultScore::SetRank()
{
	// �����̏��ʂ����݂��邩�`�F�b�N���A���ѕς���
	for (i = 0; i < 3; i++)
	{
		if (resultScore[i].first == resultScore[i + 1].first)
		{
			rank[i + 1] = rank[i];
			for (j = i + 2; j < 4; j++)
			{
				rank[j] = rank[j - 1] + 1;
			}
		}
	}
}
