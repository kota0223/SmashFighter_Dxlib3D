#include "TimeUpUI.h"

const int	TimeUpUI::ANIMATION_END_FRAME = 120;	// アニメーション終了フレーム
const float TimeUpUI::ANIMATION_SPEED = 60.0;		// アニメーション速度

// コンストラクタ
TimeUpUI::TimeUpUI()
	: moveX(0)
{
	// 処理なし
}

// デストラクタ
TimeUpUI::~TimeUpUI()
{
	// 処理なし
}

// 更新
void TimeUpUI::Update(int frame)
{
	if (moveX < SCREEN_WIDTH || frame >= ANIMATION_END_FRAME)
	{
		moveX += SCREEN_WIDTH / ANIMATION_SPEED;
		x = SCREEN_WIDTH - moveX;
	}
}
