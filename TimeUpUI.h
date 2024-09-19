#pragma once

#include <math.h>
#include "Screen.h"
#include "BaseUI.h"

// タイムアップ時のUIクラス
class TimeUpUI : public BaseUI {
private:

	// 変数

	static const int	ANIMATION_END_FRAME;	// アニメーション終了フレーム
	static const float	ANIMATION_SPEED;		// アニメーション速度

	// 変数

	float moveX;	// Xの移動量

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	TimeUpUI();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TimeUpUI();

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="frame">フレーム数</param>
	void Update(int frame) override;
};