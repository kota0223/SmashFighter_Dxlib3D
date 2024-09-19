#include "BaseUI.h"

// �R���X�g���N�^
BaseUI::BaseUI() :
	graphHandle(0),
	x(0),
	y(0)
{
	// �����Ȃ�
}

// �f�X�g���N�^
BaseUI::~BaseUI()
{
	// �����Ȃ�
}

// ������
void BaseUI::Initialize(const int graphHandle, const int x, const int y)
{
	this->graphHandle = graphHandle;
	this->x = (float)x;
	this->y = (float)y;
}

// �`��
void BaseUI::Draw()
{
	DrawGraph((int)x, (int)y, graphHandle, TRUE);
}
