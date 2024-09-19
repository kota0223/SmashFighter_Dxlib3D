//-----------------------------------------------------------------------------
//	@brief	プリプロセッサ
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "BaseScene.h"
#include "MainScene.h"

//-----------------------------------------------------------------------------
//	@brief	構造体宣言
//-----------------------------------------------------------------------------
struct UI {
    int graphHandle;    // 画像ハンドル
    int x, y;           // 座標
    int alpha;          // アルファ値
    int blinkingCount;  // 点滅用カウント
};

//-----------------------------------------------------------------------------
//	@brief	タイトルシーンクラス
//-----------------------------------------------------------------------------
class Title :public BaseScene {
private:

//===================== 静的定数 ===================//

    static const int ALPHA_MAX_NUM;           // アルファ値最大数
    static const int ALPHA_ADD_NUM;           // アルファ値増加数
    static const float BLINKING_COUNT_ONE;      // 一回の点滅にかかるカウント数
    static const int TITLE_GRAPH_INITIAL_Y;   // タイトル画像の初期Y座標

//===================== メンバ変数 ===================//

    UI titleLogo;                   // タイトルロゴUI
    UI gameStartGuide;              // ゲームスタートガイドUI
    UI controlGuide;                // 操作方法UI
    int bgmSoundHandle;             // BGMサウンドハンドル
    int buttonSoundHandle;          // ボタン効果音サウンドハンドル
    bool isChangeScene;             // シーン移行するかどうか

    Main* demo;

//===================== 内部処理関数 ===================//

    /// <summary>
    /// UI変数の初期化
    /// </summary>
    void InitializeUI();

    /// <summary>
    /// サウンドハンドル変数の初期化
    /// </summary>
    void InitializeSound();

    /// <summary>
    /// UIを徐々に表示させる
    /// </summary>
    void GradualDisplayUI(UI &ui);

    /// <summary>
    /// 点滅描画
    /// </summary>
    /// <param name="ui">点滅させるUI構造体</param>
    void BlinkingDraw(UI& ui);

    /// <summary>
    /// 正規化したSin波を返す
    /// </summary>
    /// <param name="radian">ラジアン値</param>
    /// <returns>0 ~ 1 に正規化したSin波</returns>
    double NormalizeSin(double radian);

public:

//===================== 関数 ===================//

    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="changer">シーン変更インターフェイス</param>
    Title(ISceneChanger* changer);

    /// <summary>
    /// 初期化処理
    /// </summary>
    void Initialize() override;

    /// <summary>
    /// 更新処理
    /// </summary>
    void Update() override;

    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw() override;

    /// <summary>
    /// 終了処理
    /// </summary>
    void Finalize() override;

};