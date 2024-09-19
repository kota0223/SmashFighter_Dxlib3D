#include <math.h>
#include "MoveEffect.h"

const int		MoveEffect::VS_CONST_MATRIX_NUM = 10;						// 頂点シェーダ行列の定数番号
const COLOR_U8	MoveEffect::EFFECT_COLOR = GetColorU8(230, 230, 110, 255);	// エフェクトカラー
const float		MoveEffect::POLYGON_INSIDE_SCALE = 40.0f;					// ポリゴンの内側のスケール値
const float		MoveEffect::POLYGON_OUTSIDE_SCALE = 150.0f;					// ポリゴンの外側のスケール値
const float		MoveEffect::POLYGON_INSIDE_POSITION_Z = 300.0f;				// ポリゴンの内側のZ座標
const float		MoveEffect::POLYGON_OUTSIDE_POSITION_Z = -50.0f;			// ポリゴンの外側のZ座標
const float		MoveEffect::POLYGON_TEXTURE_POSITION_INTERVAL = 1.0 / 4.0;	// ポリゴンのテクスチャ座標のループ間隔

MoveEffect::MoveEffect(VECTOR pos, int vertexShader, int pixelHandle)
	:vertexShaderHandle(vertexShader), pixelShaderHandle(pixelHandle)
{
	// ポリゴン頂点設定
	for (int i = 0; i < VERTEX_NUM; i++)
	{
		vertex[i].norm = VGet(0.0f, 0.0f, -1.0f);
		vertex[i].dif = EFFECT_COLOR;
		vertex[i].spc = GetColorU8(0, 0, 0, 0);
		vertex[i].su = 0;
		vertex[i].sv = 0;
	}

	for (int i = 0, j = 0; i < VERTEX_NUM; i += 2, j++)
	{
		vertex[i].pos = VGet(cosf(DX_PI_F * 2 / CIRCLE_VERTEX_NUM * j) * POLYGON_OUTSIDE_SCALE,
							 sinf(DX_PI_F * 2 / CIRCLE_VERTEX_NUM * j) * POLYGON_OUTSIDE_SCALE,
							 -POLYGON_OUTSIDE_POSITION_Z);

		vertex[i + 1].pos = VGet(cosf(DX_PI_F * 2 / CIRCLE_VERTEX_NUM * j) * POLYGON_INSIDE_SCALE,
								 sinf(DX_PI_F * 2 / CIRCLE_VERTEX_NUM * j) * POLYGON_INSIDE_SCALE,
								 POLYGON_INSIDE_POSITION_Z);

		vertex[i].u = POLYGON_TEXTURE_POSITION_INTERVAL * j;
		vertex[i].v = 0.0;

		vertex[i + 1].u = POLYGON_TEXTURE_POSITION_INTERVAL * j;
		vertex[i + 1].v = 1.0;
	}

	// ポリゴンインデックス
	for (int i = 0, k = 0; i < VERTEX_INDEX_NUM; i += 6) {
		index[0 + i] = k;
		index[1 + i] = k + 2;
		index[2 + i] = k + 1;
		index[3 + i] = k + 1;
		index[4 + i] = k + 2;
		index[5 + i] = k + 3;
		k += 2;
	}
	
	// シェーダー定数設定
	cindex = GetConstIndexToShader("num", pixelShaderHandle);
}

MoveEffect::~MoveEffect()
{
	// 処理なし
}

void MoveEffect::Draw(MATRIX mat)
{

	// 加算描画
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

	// 定数設定
	SetVSConstFMtx(VS_CONST_MATRIX_NUM, mat);

	// 使用する頂点シェーダーをセット
	SetUseVertexShader(vertexShaderHandle);

	// 定数用変数にタイマー代入
	f4.y = timer;

	// タイマー増加
	timer += 0.1f;

	// 定数設定
	SetPSConstF(cindex, f4);

	// 使用するピクセルシェーダーをセット
	SetUsePixelShader(pixelShaderHandle);

	// ポリゴン描画
	DrawPolygonIndexed3DToShader(vertex, VERTEX_NUM, index, VERTEX_NUM - 2);

	// ブレンド無しに変更
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}
