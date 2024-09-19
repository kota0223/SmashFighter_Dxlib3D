#pragma once

// インクルード
#include "DxLib.h"
#include "TagStruct.h" 

// RGBカラー構造体
struct Color_st
{
    int red;    // 赤成分
    int green;  // 緑成分
    int blue;   // 青成分
};

/// <summary>
/// タグ表示クラス
/// </summary>
class DisplayTag
{
private:

    // 定数

    static const int RED_INIT;          // 赤成分初期化値
    static const int GREEN_INIT;        // 緑成分初期化値
    static const int BLUE_INIT;         // 青成分初期化値

    static const int DISPLAY_TIME;      // 表示時間 (ミリ秒)

    static const int TAG_GRAPH_X_SIZE;  // タグ画像のX方向のサイズ
    static const int TAG_GRAPH_Y_SIZE;  // タグ画像のY方向のサイズ

    // 変数

    int tagGraphHandle;         // タグ画像ハンドル
    int tagBackGraphHandle;     // タグ背景画像ハンドル
    int prevTimer;              // 前回のタイマー値
    bool isVisible;             // タグの可視性
    Color_st color;             // タグの色情報
    Tag_st tag;                 // タグ情報構造体

public:

    /// <summary>
    /// コンストラクタ
    /// </summary>
    DisplayTag();

    /// <summary>
    /// グラフィックの初期化
    /// </summary>
    /// <param name="tagGraphHandle">タグ画像ハンドル</param>
    /// <param name="tagBackGraphHandle">タグ背景画像ハンドル</param>
    void InitGraph(int tagGraphHandle, int tagBackGraphHandle);

    /// <summary>
    /// 表示色の設定
    /// </summary>
    /// <param name="Red">赤成分</param>
    /// <param name="Green">緑成分</param>
    /// <param name="Blue">青成分</param>
    void SetColor(const Color_st& tagColor);

    /// <summary>
    /// 更新処理
    /// </summary>
    void Update();

    /// <summary>
    /// タグの描画
    /// </summary>
    /// <param name="pos"></param>
    void Draw(VECTOR pos);

    /// <summary>
    /// 実際の表示処理
    /// </summary>
    void DoDisplay();

    /// <summary>
    /// タグ情報の取得
    /// </summary>
    /// <returns>タグ情報構造体</returns>
    Tag_st GetTag()
    {
        // タグ情報の更新
        tag.tagGraph = tagGraphHandle;
        tag.tagBaseGraph = tagBackGraphHandle;
        tag.red = color.red;
        tag.green = color.green;
        tag.blue = color.blue;

        return tag;
    }
};
