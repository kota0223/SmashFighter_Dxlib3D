#pragma once

#include "Screen.h"
#include "BaseUI.h"

/// ゲーム開始前のReadyテキストUIクラス
class ReadyTextUI : public BaseUI {
private:

	// 定数

	static const int ANIMATION_START_FRAME;	// アニメーション開始フレーム
	static const int ANIMATION_END_FRAME;	// アニメーション終了フレーム
	static const int SCALE_DECREASE_FRAME;	// スケール減少するフレーム数
	static const float SCALE_INCREASE_MAX;	// スケール拡大最大値
	static const float SCALE_INCREASE_X;	// Xスケール拡大率
	static const float SCALE_INCREASE_Y;	// Yスケール拡大率
	static const float SCALE_DECREASE_MAX;	// スケール縮小最大値
	static const float SCALE_DECREASE_X;	// Xスケール縮小率
	static const float SCALE_DECREASE_Y;	// Yスケール縮小率

	// 変数

	// スケール値
	float scaleX, scaleY;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ReadyTextUI();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ReadyTextUI();

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="frame">フレーム数</param>
	void Update(int frame) override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;
};