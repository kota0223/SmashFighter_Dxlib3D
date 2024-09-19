#pragma once
#include <math.h>
#include "DxLib.h"

/// <summary>
/// FPS制御クラス
/// </summary>
class Fps {

	// 定数

	static const int N;		//平均を取るサンプル数
	static const int FPS;	//設定したFPS

	// 変数

	int mStartTime;	//測定開始時刻
	int mCount;		//カウンタ
	float mFps;		//fps

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Fps();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Fps();

	/// <summary>
	/// 更新
	/// </summary>
	bool Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 待機処理
	/// </summary>
	void Wait();
};