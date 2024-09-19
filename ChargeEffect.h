#pragma once

// インクルード
#include "DxLib.h"

/// <summary>
/// チャージエフェクト
/// </summary>
class ChargeEffect {
private:

	// 定数

	static const int CIRCLE_VERTEX_NUM = 22;					// 一つの円の頂点の数
	static const int VERTEX_NUM = (CIRCLE_VERTEX_NUM*2);		// 全体の頂点の数

	static const int	  VS_CONST_MATRIX_NUM;					// 頂点シェーダ行列の定数番号
	static const int	  VS_CONST_NUM;							// 頂点シェーダの定数番号
	static const COLOR_U8 POLYGON_OUTSIDE_COLOR;				// ポリゴン外側のカラー
	static const COLOR_U8 POLYGON_INSIDE_COLOR;					// ポリゴン内側のカラー
	static const float	  POLYGON_TEXTURE_POSITION_INTERVAL;	// ポリゴンのテクスチャ座標のループ間隔
	static const float	  POLYGON_SCALE;						// エフェクトのポリゴンスケール値
	static const int	  LIGHT_GRAPH_COLOR[3];					// ライト画像の色
	static const float	  EFFECT_TIME;							// エフェクト時間

	// 変数

	VERTEX3DSHADER drawVertex[VERTEX_NUM];	// ポリゴン頂点

	VECTOR lightGraphPos[4] = { {-50,50,0}	
								,{50,50,0}
								,{50,-50,0}
								,{-50,-50,0} };	// 光画像座標

	VECTOR position;			// 座標
	int	   vertexShaderHandle;	// 頂点シェーダーハンドル
	int	   startTime;			// 開始時間保存変数
	int	   timer;				// タイマー
	int	   lightTimer;			// 光るエフェクトタイマー
	int	   lightGraphHandle;	// 光画像ハンドル

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">表示座標</param>
	/// <param name="time">表示時間</param>
	/// <param name="graphHandle">画像ハンドル</param>
	/// <param name="vertexShader">頂点シェーダハンドル</param>
	ChargeEffect(VECTOR pos,int time, int graphHandle, int vertexShader);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ChargeEffect();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="index">ポリゴンのインデックス配列</param>
	void Draw(WORD index[]);

	/// <summary>
	/// 時間の取得
	/// </summary>
	/// <returns>エフェクトのタイマー</returns>
	int GetTime() { return timer; }
};