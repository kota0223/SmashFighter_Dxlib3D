#include "ReadyTextUI.h"

const int ReadyTextUI::ANIMATION_START_FRAME = 60;		// アニメーション開始フレーム
const int ReadyTextUI::ANIMATION_END_FRAME = 2 * 60;	// アニメーション終了フレーム
const int ReadyTextUI::SCALE_DECREASE_FRAME = 90;		// スケール減少するフレーム数

const float ReadyTextUI::SCALE_INCREASE_MAX = 2.0;		// スケール拡大最大値
const float ReadyTextUI::SCALE_INCREASE_X = 0.12f;		// Xスケール拡大率
const float ReadyTextUI::SCALE_INCREASE_Y = 0.08f;		// Yスケール拡大率

const float ReadyTextUI::SCALE_DECREASE_MAX = 1.0;		// スケール縮小最大値
const float ReadyTextUI::SCALE_DECREASE_X = 0.1f;		// Xスケール縮小率
const float ReadyTextUI::SCALE_DECREASE_Y = 0.1f;		// Yスケール縮小率

// コンストラクタ
ReadyTextUI::ReadyTextUI()
	: scaleX(0)
	, scaleY(0)
{
	// 処理なし
}

// デストラクタ
ReadyTextUI::~ReadyTextUI()
{
	// 処理なし
}

// 更新
void ReadyTextUI::Update(int frame)
{
	// フレーム数に応じてUIアニメーション
	if (frame > ANIMATION_START_FRAME && frame < ANIMATION_END_FRAME)
	{
		if (frame >= SCALE_DECREASE_FRAME)
		{
			scaleX += (SCALE_DECREASE_MAX - scaleX) * SCALE_DECREASE_X;
			scaleY += (SCALE_DECREASE_MAX - scaleY) * SCALE_DECREASE_Y;
		}
		else
		{
			scaleX += (SCALE_INCREASE_MAX - scaleX) * SCALE_INCREASE_X;
			scaleY += (SCALE_INCREASE_MAX - scaleY) * SCALE_INCREASE_Y;
		}
	}

}

// 描画
void ReadyTextUI::Draw()
{
	DrawRotaGraph3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2
		, scaleX, scaleY, 0, graphHandle, TRUE);
}
