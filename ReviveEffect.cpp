#include "ReviveEffect.h"

// 立方体の各辺のサイズ設定
const float ReviveEffect::X_SIZE = 8.0f;
const float ReviveEffect::Y_SIZE = 30.0f;
const float ReviveEffect::Z_SIZE = 8.0f;

// 立方体の下の面の色設定
const int ReviveEffect::POLYGON_COLOR_RED = 255;
const int ReviveEffect::POLYGON_COLOR_GREEN = 255;
const int ReviveEffect::POLYGON_COLOR_BLUE = 0;

// 立方体の上下の面のアルファ値設定
const int ReviveEffect::TOP_ALPHA = 255;
const int ReviveEffect::BOTTOM_ALPHA = 0;

// 立方体の変形に関する設定
const float ReviveEffect::HEIGHT_ADD_SIZE = 3.0f;
const float ReviveEffect::WIDTH_ADD_SCALE = 0.1f;
const float ReviveEffect::WIDTH_MINIMUM_SIZE = 0.5f;

// ブレンドモード設定
const int ReviveEffect::BLEND_ADD_NUM = 255;

// ReviveEffectクラスのコンストラクタ
ReviveEffect::ReviveEffect(VECTOR origin) : origin(origin)
{
	// 立方体の下の面のディフューズカラーを設定
	for (int i = 0; i < VERTEX_NUM / 2; i++)
	{
		Vertex[i].dif = GetColorU8(POLYGON_COLOR_RED, POLYGON_COLOR_GREEN, POLYGON_COLOR_BLUE, TOP_ALPHA);
	}

	// 立方体の上の面のディフューズカラーを設定
	for (int i = VERTEX_NUM / 2; i < VERTEX_NUM; i++)
	{
		Vertex[i].dif = GetColorU8(POLYGON_COLOR_RED, POLYGON_COLOR_GREEN, POLYGON_COLOR_BLUE, BOTTOM_ALPHA);
	}

	InitPos();

	// 頂点初期化
	for (int i = 0; i < 8; i++)
	{
		Vertex[i].norm = VGet(0.0f, 0.0f, -1.0f);
		Vertex[i].spc = GetColorU8(0, 0, 0, 0);
		Vertex[i].u = 0.0f;
		Vertex[i].v = 0.0f;
		Vertex[i].su = 0.0f;
		Vertex[i].sv = 0.0f;
	}

	// 8ポリゴン分のインデックスデータをセット
	Index[0] = 0;
	Index[1] = 1;
	Index[2] = 4;

	Index[3] = 5;
	Index[4] = 4;
	Index[5] = 1;

	Index[6] = 1;
	Index[7] = 2;
	Index[8] = 5;

	Index[9] = 6;
	Index[10] = 5;
	Index[11] = 2;

	Index[12] = 2;
	Index[13] = 3;
	Index[14] = 6;

	Index[15] = 7;
	Index[16] = 6;
	Index[17] = 3;

	Index[18] = 3;
	Index[19] = 0;
	Index[20] = 7;

	Index[21] = 4;
	Index[22] = 7;
	Index[23] = 0;

	// 表示フラグ初期化
	isVisible = false;
}

// 初期位置設定関数
void ReviveEffect::InitPos()
{
	int i = 0;

	Vertex[0].pos = VAdd(origin, VGet(-X_SIZE / 2, 0, -Z_SIZE / 2));
	Vertex[1].pos = VAdd(origin, VGet(X_SIZE / 2, 0, -Z_SIZE / 2));
	Vertex[2].pos = VAdd(origin, VGet(X_SIZE / 2, 0, Z_SIZE / 2));
	Vertex[3].pos = VAdd(origin, VGet(-X_SIZE / 2, 0, Z_SIZE / 2));

	for (i = VERTEX_NUM / 2; i < VERTEX_NUM; i++)
	{
		Vertex[i].pos = VAdd(Vertex[i - VERTEX_NUM / 2].pos, VGet(0, Y_SIZE, 0));
	}
}

// アップデート関数
void ReviveEffect::Update()
{
	if (isVisible)
	{
		// 立方体の上の面の頂点の座標を上に移動させる
		for (int i = VERTEX_NUM / 2; i < VERTEX_NUM; i++)
		{
			Vertex[i].pos.y += HEIGHT_ADD_SIZE;
		}

		// 立方体の変形処理
		for (int i = 0; i < VERTEX_NUM; i++)
		{
			VECTOR v1 = VSub(VGet(origin.x, Vertex[i].pos.y, origin.z), Vertex[i].pos);
			if (VSize(v1) > 0)
			{
				v1 = VNorm(v1);
			}
			Vertex[i].pos = VAdd(Vertex[i].pos, VScale(v1, WIDTH_ADD_SCALE));
		}

		// 立方体が一定サイズ以下になったら非表示にする
		if (VSize(VSub(Vertex[0].pos, origin)) < WIDTH_MINIMUM_SIZE)
		{
			isVisible = false;
		}
	}
}

// 描画関数
void ReviveEffect::Draw()
{
	// 表示フラグが立っていたら
	if (isVisible)
	{
		SetDrawBlendMode(DX_BLENDMODE_ADD, BLEND_ADD_NUM);

		// ポリゴンの描画
		DrawPolygonIndexed3D(Vertex, VERTEX_NUM, Index, POLYGON_NUM, DX_NONE_GRAPH, FALSE);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, NULL);
	}
}

// 再生関数
void ReviveEffect::DoPlay()
{
	InitPos();
	isVisible = true;
}