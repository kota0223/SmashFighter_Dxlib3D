#pragma once

#include "BaseScene.h"
#include "ResultScore.h"

class Result : BaseScene{
private:

    // 定数

    static const int SCORE_DRAW_POS_X;  // スコア描画X座標
    static const int SCORE_DRAW_POS_Y;  // スコア描画Y座標

    // 変数

    ResultScore resultScore;

    int buttonSE;

    int backGround;

    bool pushFlg;
public:
    Result(ISceneChanger* changer,ResultScore resultScore);
    ~Result();

    /// <summary>初期化処理</summary>
    void Initialize() override;

    /// <summary>更新処理</summary>
    void Update() override;

    /// <summary>描画処理</summary>
    void Draw() override;

    /// <summary>終了処理</summary>
    void Finalize() override;
};