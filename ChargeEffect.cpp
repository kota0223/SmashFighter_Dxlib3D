
// インクルード
#include <math.h>
#include "ChargeEffect.h"

// 定数
const int		ChargeEffect::VS_CONST_MATRIX_NUM = 62;									// 頂点シェーダ行列の定数番号
const int		ChargeEffect::VS_CONST_NUM = 57;										// 頂点シェーダの定数番号
const COLOR_U8	ChargeEffect::POLYGON_OUTSIDE_COLOR = GetColorU8(255, 255, 255, 255);	// ポリゴン外側のカラー
const COLOR_U8	ChargeEffect::POLYGON_INSIDE_COLOR = GetColorU8(150, 150, 150, 255);	// ポリゴン内側のカラー
const float		ChargeEffect::POLYGON_TEXTURE_POSITION_INTERVAL = 1.0 / 4.0;			// ポリゴンのテクスチャ座標のループ間隔
const float		ChargeEffect::POLYGON_SCALE = 2.0f;										// エフェクトのポリゴンスケール値
const int		ChargeEffect::LIGHT_GRAPH_COLOR[3] = {255,230,180};						// ライト画像の色
const float		ChargeEffect::EFFECT_TIME = 20.0f;										// エフェクト時間

ChargeEffect::ChargeEffect(VECTOR pos, int time, int graphHandle, int vertexShader)
	: timer(time), lightTimer(time), position(pos), lightGraphHandle(graphHandle), vertexShaderHandle(vertexShader)
{
	FLOAT4 position = { pos.x,pos.y,pos.z,1.0f };

	// ポリゴン頂点設定
	for (int i = 0; i < VERTEX_NUM; i++)
	{
		drawVertex[i].norm = VGet(0.0f, 0.0f, -1.0f);
		drawVertex[i].spc = GetColorU8(0, 0, 0, 0);
		drawVertex[i].su = (float)GetNowCount();
		drawVertex[i].sv = 0;
		drawVertex[i].spos = position;
	}

	for (int i = 0, j = 0; i < VERTEX_NUM; i += 2, j++)
	{
		drawVertex[i].pos = VGet(0, 0, (float)i);
		drawVertex[i + 1].pos = VGet(0, 0, (float)(i + 1));

		drawVertex[i].dif = POLYGON_OUTSIDE_COLOR;
		drawVertex[i+1].dif = POLYGON_INSIDE_COLOR;

		drawVertex[i].u = POLYGON_TEXTURE_POSITION_INTERVAL * j;
		drawVertex[i].v = 0.0;

		drawVertex[i + 1].u = POLYGON_TEXTURE_POSITION_INTERVAL * j;
		drawVertex[i + 1].v = 1.0;
	}

	// シェーダー定数設定
	MATRIX mat = MGetScale(VGet(POLYGON_SCALE, POLYGON_SCALE, 0));

	SetVSConstFMtx(VS_CONST_MATRIX_NUM, mat);

	// 時間取得
	startTime = GetNowCount();
}

ChargeEffect::~ChargeEffect()
{
	// 処理なし
}

void ChargeEffect::Draw(WORD index[])
{
	// 光エフェクト処理
	if (lightTimer >= 0)
	{
		// 色変更
		SetDrawBright(LIGHT_GRAPH_COLOR[0], LIGHT_GRAPH_COLOR[1], LIGHT_GRAPH_COLOR[2]);

		// 加算描画
		SetDrawBlendMode(DX_BLENDMODE_ADD, (int)(255 * (float)(timer) / EFFECT_TIME));

		// 描画座標
		VECTOR drawPos[4];

		// 変換行列
		MATRIX mat = MGetRotZ(DX_PI_F / 2.0f * (float)timer / EFFECT_TIME);

		// 座標変換
		for (int i = 0; i < 4; i++)
		{
			drawPos[i] = VTransform(lightGraphPos[i], mat);
		}

		// ビルボード描画
		DrawModiBillboard3D(position,
			drawPos[0].x, drawPos[0].y,
			drawPos[1].x, drawPos[1].y,
			drawPos[2].x, drawPos[2].y,
			drawPos[3].x, drawPos[3].y, lightGraphHandle, TRUE);

		// カラーを元に戻す
		SetDrawBright(255, 255, 255);

		// タイマー減少
		lightTimer--;
	}

	// タイマー減少
	timer--;

	// 加算描画
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

	// シェーダー定数用変数
	FLOAT4 f4num = { 1.0f - timer / EFFECT_TIME, 0, 0, 0 };

	// 定数設定
	SetVSConstF(VS_CONST_NUM, f4num);

	// 使用する頂点シェーダーをセット
	SetUseVertexShader(vertexShaderHandle);

	// ポリゴン描画
	DrawPolygonIndexed3DToShader(drawVertex, VERTEX_NUM, index, VERTEX_NUM - 2);

	// ブレンド無しに変更
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
