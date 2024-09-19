#pragma once

#include "DxLib.h"

class ReviveEffect
{
private:

	// 定数

	// 頂点とポリゴンの数
	static const int VERTEX_NUM = 8;
	static const int POLYGON_NUM = 8;

	// サイズの定数
	static const float X_SIZE;
	static const float Y_SIZE;
	static const float Z_SIZE;

	// ポリゴンの色
	static const int POLYGON_COLOR_RED;
	static const int POLYGON_COLOR_GREEN;
	static const int POLYGON_COLOR_BLUE;

	// アルファ値
	static const int TOP_ALPHA;
	static const int BOTTOM_ALPHA;

	// サイズの増加率
	static const float HEIGHT_ADD_SIZE;
	static const float WIDTH_ADD_SCALE;

	// サイズの最小値
	static const float WIDTH_MINIMUM_SIZE;

	// ブレンドモードに関する定数
	static const int BLEND_ADD_NUM;

	// 頂点情報
	VERTEX3D Vertex[VERTEX_NUM];

	// ポリゴンのインデックス
	WORD Index[POLYGON_NUM * 3];

	// 原点の位置
	VECTOR origin;

	// 可視性フラグ
	bool isVisible;

public:

	/// <summary>
	// コンストラクタ
	/// </summary>
	/// <param name="origin">原点の位置</param>
	ReviveEffect(VECTOR origin);

	/// <summary>
	/// 初期位置の設定
	/// </summary>
	void InitPos();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 再生開始
	/// </summary>
	void DoPlay();

	bool GetIsDelete() const { return !isVisible; }
};
