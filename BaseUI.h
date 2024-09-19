#pragma once

#include <DxLib.h>

// UIベースクラス
class BaseUI {
protected:
	int graphHandle;	// 画像ハンドル
	float x, y;			// 画像座標

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	BaseUI();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~BaseUI();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="graphHandle">画像ハンドル</param>
	/// <param name="x">X座標</param>
	/// <param name="y">Y座標</param>
	void Initialize(const int graphHandle, const int x, const int y);

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="frame">フレーム数</param>
	virtual void Update(int frame) = 0;

	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw();
};