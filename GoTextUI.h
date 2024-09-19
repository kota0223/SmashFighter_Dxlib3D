#pragma once

#include <math.h>
#include "BaseUI.h"

// GoTextUIクラス
class GoTextUI : public BaseUI {

private:
	// 定数

	static const int MOVE_Y_INIT_NUM;		// Y移動量初期値
	static const int DRAW_FRAME;			// 描画フレーム
	static const int ANIMATION_SPEED;		// アニメーション速度
	static const float MOVE_Y_ATTENUATION;	// Y移動量の減衰量

	// 変数

	float moveY;	// Y座標移動量

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	GoTextUI();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GoTextUI();

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="frame">フレーム数</param>
	void Update(int frame) override;
};