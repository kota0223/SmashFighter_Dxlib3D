#pragma once
#include <string>
#include <utility>
#include <vector>

#include "TagStruct.h"

// ���U���g�p�X�R�A�N���X
class ResultScore {
private:

	// �萔

	static const int SCORE_FONT_EDGE_SIZE;	// �X�R�A�t�H���g�̉����T�C�Y
	static const int NAME_FONT_EDGE_SIZE;	// ���O�t�H���g�̉����T�C�Y
	static const int RANK_NUM;				// ���ʂ̐�
	static const int MOVE_X_ADD_NUM;		// X���W�ړ��ʂ̑�����
	static const int ALPHA_ADD_NUM;			// �A���t�@�l�̑�����
	static const int MOVE_X_MAX;			// X���W�ړ��ʂ̍ő�l

	static const int RANK_X_INTERVAL;		// ���ʕ`���X���W�̊Ԋu
	static const int RANK_Y_INTERVAL;		// ���ʕ`���Y���W�̊Ԋu
	
	static const int FRAME_GRAPH_X;			// �t���[���摜��X���W��l
	static const int FRAME_GRAPH_Y;			// �t���[���摜��Y���W��l

	static const int RANK_GRAPH_X;			// ���ʉ摜��X���W��l
	static const int RANK_GRAPH_Y;			// ���ʉ摜��Y���W��l

	static const int TAG_GRAPH_X;			// �^�O�摜��X���W��l
	static const int TAG_GRAPH_Y;			// �^�O�摜��Y���W��l
	static const int FRAME_GRAPH_WIDTH;		// �^�O�摜�̕�
	static const int FRAME_GRAPH_HEIGHT;	// �^�O�摜�̍���

	static const int SCORE_TEXT_X;			// �X�R�A�e�L�X�g��X���W��l
	static const int SCORE_TEXT_Y;			// �X�R�A�e�L�X�g��Y���W��l
	static const int PT_TEXT_X;				// "pt"�e�L�X�g��X���W��l

	// �ϐ�

	std::vector<std::pair<int, Tag_st>> resultScore;	// ���U���g�X�R�A�z��

	int rank[4] = { 1,2,3,4 };	// ���ʔz��
	bool rankVisible[4];		// ���ʕ`��t���O

	int frameGraph;		// �t���[���摜�n���h��
	int rankGraph[4];	// ���ʕʉ摜�n���h��
	int fontHandle;		// �t�H���g�n���h��
	int nameFont;		// ���O�t�H���g

	int drawSE;		// �`�掞��SE
	int drawSE2;	// �`�掞��SE2

	int i, j;		// �ėp���[�v�ϐ�

	int drawNum;	// �`�搔
	int visibleNum;	// �\����

	int moveX;		// �ړ�X��
	int alpha;		// �����x

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	ResultScore();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ResultScore();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�R�A�ǉ�
	/// </summary>
	/// <param name="score">�X�R�A</param>
	/// <param name="Tag">�^�O�̍\����</param>
	void AddScore(int score, Tag_st Tag);

	/// <summary>
	/// ���U���g�X�R�A�`��
	/// </summary>
	/// <param name="x">X���W</param>
	/// <param name="y">Y���W</param>
	void Draw(int x, int y);

	/// <summary>
	/// �������ʂ̐ݒ�
	/// </summary>
	void SetRank();
};