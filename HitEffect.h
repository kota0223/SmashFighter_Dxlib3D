#pragma once

// インクルード
#include "DxLib.h"

/// <summary>
/// ヒットエフェクト
/// </summary>
class HitEffect {
private:

	// 定数

	static const int CIRCLE_VERTEX_NUM = 22;				// 一つの円の頂点の数
	static const int VERTEX_NUM = (CIRCLE_VERTEX_NUM*2)+2;	// 全体の頂点の数

	static const int		VS_CONST_MATRIX_NUM;				// 頂点シェーダ行列の定数番号
	static const int		VS_CONST_NUM;						// 頂点シェーダの定数番号
	static const float		POLYGON_SCALE;						// エフェクトのポリゴンスケール値
	static const COLOR_U8	EFFECT_COLOR;						// エフェクトカラー
	static const float		LIGHT_EFFECT_TIME;					// 光るエフェクトの時間
	static const float		POLYGON_TEXTURE_POSITION_INTERVAL;	// ポリゴンのテクスチャ座標のループ間隔
	static const int		LIGHT_GRAPH_COLOR[3];				// ライト画像の色
	static const float		SCALE_CHANGE_SIZE;					// スケール変化の大きさ
	static const float		LIGHT_EFFECT_SCALE_X;				// 光るエフェクトのX軸の大きさ
	static const float		LIGHT_EFFECT_SCALE_Y;				// 光るエフェクトのY軸の大きさ
	static const float		LIGTH_EFFECT_ROTATION_SPEED;		// 光るエフェクトの回転速度
	static const float		EFFECT_TIME;						// エフェクト時間

	// 変数

	VERTEX3DSHADER drawVertex[VERTEX_NUM]; // ポリゴン頂点

	VECTOR lightGraphPos[4] = { {-15,15,0} 
								,{15,15,0}
								,{15,-15,0}
								,{-15,-15,0} };	// 光画像座標

	VECTOR position;		// 座標
	int vertexShaderHandle;	// 頂点シェーダーハンドル
	int timer;				// タイマー
	int lightTimer;			// 光るエフェクトタイマー
	int lightGraphHandle;	// 光画像ハンドル
							
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">表示座標</param>
	/// <param name="time">描画時間</param>
	/// <param name="graphHandle">画像ハンドル</param>
	/// <param name="vertexShader">頂点シェーダーハンドル</param>
	HitEffect(VECTOR pos,int time, int graphHandle, int vertexShader);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~HitEffect();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="index">ポリゴンのインデックス配列</param>
	void Draw(WORD index[]);

	/// <summary>
	/// 時間取得
	/// </summary>
	/// <returns>エフェクトのタイマー</returns>
	int GetTime() { return timer; }
};