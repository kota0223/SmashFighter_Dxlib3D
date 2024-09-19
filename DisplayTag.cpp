
// インクルード
#include "DisplayTag.h"

// 定数
const int DisplayTag::RED_INIT			= 255;	// 赤成分初期化値
const int DisplayTag::GREEN_INIT		= 255;	// 緑成分初期化値
const int DisplayTag::BLUE_INIT			= 255;	// 青成分初期化値

const int DisplayTag::DISPLAY_TIME		= 5000;	// 表示時間 (ミリ秒)

const int DisplayTag::TAG_GRAPH_X_SIZE	= 100;	// タグ画像のX方向のサイズ
const int DisplayTag::TAG_GRAPH_Y_SIZE	= 50;	// タグ画像のY方向のサイズ

// DisplayTagクラスのコンストラクタ
DisplayTag::DisplayTag()
{
	// 色構造体初期化
	color.red = RED_INIT;
	color.green = GREEN_INIT;
	color.blue = BLUE_INIT;

	// フレーム時間初期化
	prevTimer = GetNowCount();

	// 表示フラグ初期化
	isVisible = true;
}

// タグ画像と背景画像の初期化
void DisplayTag::InitGraph(int tagGraphHandle, int tagBackGraphHandle)
{
    // タグ画像ハンドル代入
    this->tagGraphHandle = tagGraphHandle;

    // タグ背景ハンドル代入
    this->tagBackGraphHandle = tagBackGraphHandle;
}

// 色の設定
void DisplayTag::SetColor(const Color_st& tagColor)
{
    color = tagColor;
}

// 表示の更新
void DisplayTag::Update()
{
    if (!isVisible)
    {
        return; // 非表示の場合は何もしない
    }

    // DISPLAY_TIMEミリ秒以上経過したら非表示にする
    if (GetNowCount() - prevTimer >= DISPLAY_TIME)
    {
        isVisible = false;
    }
}

// タグの描画
void DisplayTag::Draw(VECTOR position)
{
    if (!isVisible)
    {
        return; // 非表示の場合は何もしない
    }

    // キャラクターの座標をスクリーン座標に変換する
    VECTOR drawPos = ConvWorldPosToScreenPos(VAdd(position, VGet(0, 25, 0)));

    // 背景画像を描画
    DrawExtendGraph((int)(drawPos.x - TAG_GRAPH_X_SIZE / 2.0), (int)(drawPos.y - TAG_GRAPH_Y_SIZE / 2.0),
        (int)(drawPos.x + TAG_GRAPH_X_SIZE / 2.0), (int)(drawPos.y + TAG_GRAPH_Y_SIZE / 2.0),
        tagBackGraphHandle, TRUE);

    // 色を設定してタグ画像を描画
    SetDrawBright(color.red, color.green, color.blue);
    DrawExtendGraph((int)(drawPos.x - TAG_GRAPH_X_SIZE / 2.0), (int)(drawPos.y - TAG_GRAPH_Y_SIZE / 2.0),
        (int)(drawPos.x + TAG_GRAPH_X_SIZE / 2.0), (int)(drawPos.y + TAG_GRAPH_Y_SIZE / 2.0),
        tagGraphHandle, TRUE);

    // 色を元に戻す
    SetDrawBright(255, 255, 255);
}

// タグを表示する処理
void DisplayTag::DoDisplay()
{
    prevTimer = GetNowCount();  // 前のフレームタイマーに現在の時間を代入

    isVisible = true;           // タグを表示状態にする
}