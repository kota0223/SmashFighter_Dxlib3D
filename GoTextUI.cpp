#include "GoTextUI.h"

const int GoTextUI::MOVE_Y_INIT_NUM = 30;			// Y移動量初期値
const int GoTextUI::DRAW_FRAME = 3 * 60;			// 描画フレーム
const int GoTextUI::ANIMATION_SPEED = 10;			// アニメーション速度
const float GoTextUI::MOVE_Y_ATTENUATION = 0.05f;	// Y移動量の減衰量

// コンストラクタ
GoTextUI::GoTextUI()
	: moveY(MOVE_Y_INIT_NUM)
{
}

// デストラクタ
GoTextUI::~GoTextUI()
{
}

// 更新
void GoTextUI::Update(int frame)
{
	if (frame > DRAW_FRAME)
	{
		y = sinf(DX_PI_F / ANIMATION_SPEED * frame) * moveY;
		moveY += (0.0f - moveY) * MOVE_Y_ATTENUATION;
	}
}
