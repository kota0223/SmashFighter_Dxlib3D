#include "BaseUI.h"

// コンストラクタ
BaseUI::BaseUI() :
	graphHandle(0),
	x(0),
	y(0)
{
	// 処理なし
}

// デストラクタ
BaseUI::~BaseUI()
{
	// 処理なし
}

// 初期化
void BaseUI::Initialize(const int graphHandle, const int x, const int y)
{
	this->graphHandle = graphHandle;
	this->x = (float)x;
	this->y = (float)y;
}

// 描画
void BaseUI::Draw()
{
	DrawGraph((int)x, (int)y, graphHandle, TRUE);
}
