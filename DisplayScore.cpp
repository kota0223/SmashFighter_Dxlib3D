#include "DxLib.h"
#include "DisplayScore.h"

// コンストラクタ
DisplayScore::DisplayScore()
{
	// 変数初期化

	// Y座標値初期化
	goGraphMoveY = 0;

	// アルファ値初期化
	alpha = 0;

	// スコア表示画像
	scoreGraph = LoadGraph("data/image/Main/ScoreAdd.png");
}

// デストラクタ
DisplayScore::~DisplayScore()
{
	// 処理なし
}

void DisplayScore::InitializeForDisplay()
{
	// Y座標値初期化
	goGraphMoveY = 0;

	// アルファ値初期化
	alpha = 0;
}

// 更新処理
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

// 描画処理
void DisplayScore::Draw(int x, int y)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

	DrawExtendGraph(x - 32, y - 32 - (int)goGraphMoveY, x + 32, y + 32 - (int)goGraphMoveY, scoreGraph, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, NULL);
}
