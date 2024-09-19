#pragma once

#include "DxLib.h"

class MoveEffect {
private:

	// 定数

	static const int CIRCLE_VERTEX_NUM = 15;
	static const int VERTEX_NUM = (CIRCLE_VERTEX_NUM * 2) + 2;
	static const int VERTEX_INDEX_NUM = VERTEX_NUM * 3;

	static const int	  VS_CONST_MATRIX_NUM;					// 頂点シェーダ行列の定数番号
	static const COLOR_U8 EFFECT_COLOR;							// エフェクトカラー
	static const float	  POLYGON_INSIDE_SCALE;					// ポリゴンの内側のスケール値
	static const float	  POLYGON_OUTSIDE_SCALE;				// ポリゴンの外側のスケール値
	static const float	  POLYGON_INSIDE_POSITION_Z;			// ポリゴンの内側のZ座標
	static const float	  POLYGON_OUTSIDE_POSITION_Z;			// ポリゴンの外側のZ座標
	static const float	  POLYGON_TEXTURE_POSITION_INTERVAL;	// ポリゴンのテクスチャ座標のループ間隔

	// 変数

	VERTEX3DSHADER vertex[VERTEX_NUM];

	WORD index[VERTEX_INDEX_NUM];

	float timer=0;

	int vertexShaderHandle;
	int pixelShaderHandle;

	int cindex;

	FLOAT4 f4 = { 0,0,0,0 };


public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">表示座標</param>
	/// <param name="vertexShader">頂点シェーダハンドル</param>
	/// <param name="pixelHandle">ピクセルシェーダハンドル</param>
	MoveEffect(VECTOR pos, int vertexShader, int pixelHandle);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~MoveEffect();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="mat">モデルの座標変換用行列</param>
	void Draw(MATRIX mat);
};