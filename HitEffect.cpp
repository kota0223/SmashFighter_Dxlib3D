
// インクルード
#include <math.h>
#include "HitEffect.h"

// 定数
const int		HitEffect::VS_CONST_MATRIX_NUM = 62;						// 頂点シェーダ行列の定数番号
const int		HitEffect::VS_CONST_NUM = 57;								// 頂点シェーダの定数番号
const float		HitEffect::POLYGON_SCALE = 2.0f;							// エフェクトのポリゴンスケール値
const COLOR_U8	HitEffect::EFFECT_COLOR = GetColorU8(230, 230, 110, 255);	// エフェクトカラー
const float		HitEffect::LIGHT_EFFECT_TIME = 7.0f;						// 光るエフェクトの時間
const float		HitEffect::POLYGON_TEXTURE_POSITION_INTERVAL = 1.0 / 4.0;	// ポリゴンのテクスチャ座標のループ間隔
const int		HitEffect::LIGHT_GRAPH_COLOR[3] = { 255,230,150 };			// ライト画像の色
const float		HitEffect::SCALE_CHANGE_SIZE = 2.5f;						// スケール変化の大きさ
const float		HitEffect::LIGHT_EFFECT_SCALE_X = 3.5f;						// 光るエフェクトのX軸の大きさ
const float		HitEffect::LIGHT_EFFECT_SCALE_Y = 1.0f;						// 光るエフェクトのY軸の大きさ
const float		HitEffect::LIGTH_EFFECT_ROTATION_SPEED = 1.3f;				// 光るエフェクトの回転速度
const float		HitEffect::EFFECT_TIME = 20.0f;								// エフェクト時間

HitEffect::HitEffect(VECTOR pos, int time, int graphHandle, int vertexShader)
	: timer(time),lightTimer((int)LIGHT_EFFECT_TIME), position(pos),lightGraphHandle(graphHandle), vertexShaderHandle(vertexShader)
{
	FLOAT4 position = { pos.x,pos.y,pos.z,1.0f };

	// ポリゴン頂点設定
	for (int i = 0; i < VERTEX_NUM; i++)
	{
		drawVertex[i].norm = VGet(0.0f, 0.0f, -1.0f);
		drawVertex[i].dif = EFFECT_COLOR;
		drawVertex[i].spc = GetColorU8(0, 0, 0, 0);
		drawVertex[i].su = 0;
		drawVertex[i].sv = 0;
		drawVertex[i].spos = position;
	}

	for (int i = 0, j = 0; i < VERTEX_NUM; i += 2, j++)
	{
		drawVertex[i].pos = VGet(0, 0, (float)i);
		drawVertex[i + 1].pos = VGet(0, 0, (float)(i + 1));

		drawVertex[i].u = POLYGON_TEXTURE_POSITION_INTERVAL * j;
		drawVertex[i].v = 0.0;

		drawVertex[i + 1].u = POLYGON_TEXTURE_POSITION_INTERVAL * j;
		drawVertex[i + 1].v = 1.0;
	}

	// シェーダー定数設定
	SetVSConstFMtx(VS_CONST_MATRIX_NUM, MGetScale(VGet(POLYGON_SCALE, POLYGON_SCALE, 0)));
}

HitEffect::~HitEffect()
{
	// 処理なし
}

void HitEffect::Draw(WORD index[])
{
	// 光エフェクト処理
	if (lightTimer >= 0)
	{
		// 色変更
		SetDrawBright(LIGHT_GRAPH_COLOR[0], LIGHT_GRAPH_COLOR[1], LIGHT_GRAPH_COLOR[2]);

		// 加算描画
		SetDrawBlendMode(DX_BLENDMODE_ADD, (int)(255 * (lightTimer / LIGHT_EFFECT_TIME + 0.2f)));

		// 描画座標
		VECTOR drawPos[4];

		// 変換行列
		MATRIX mat = MGetScale(VGet(LIGHT_EFFECT_SCALE_X - (SCALE_CHANGE_SIZE * (1.0f - lightTimer / LIGHT_EFFECT_TIME)),
								LIGHT_EFFECT_SCALE_Y + (SCALE_CHANGE_SIZE * (1.0f - lightTimer / LIGHT_EFFECT_TIME)), 0));

		mat = MMult(mat, MGetRotZ(DX_PI_F / LIGTH_EFFECT_ROTATION_SPEED * (lightTimer / LIGHT_EFFECT_TIME)));

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

	// 加算描画
	SetDrawBlendMode(DX_BLENDMODE_ADD,255);

	// タイマー減少
	timer--;

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


