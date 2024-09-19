#pragma once

#include <string>       // 文字列型クラス

//=========================
// サウンド管理クラス
// シングルトン
//=========================
class SoundManager final
{
public:
    // シーン状態定義
    enum BGM_Kind
    {
        TITLE = 0,
        MAIN
    };

    enum SE_Kind
    {
        START = 0,
        WHISTLE,
        CHARGE,
        COLLISION,
        SCORE_INCREASE,
        COUNT_DOWN,
        RESULT,
    };

    static SoundManager& GetInstance(); // アドレスを返す

private:
    // 外部での実行を禁止する
    SoundManager();                        // コンストラクタ
    SoundManager(const SoundManager&);     // コピーコンストラクタ
    void operator=(const SoundManager&);   // 代入演算子
    ~SoundManager();                       // デストラクタ

    void LoadAllSound();    // 全てのモデルを読み込み
    void DeleteAllSound();  // 全てのモデルを削除

    // 定数
    static const std::string MODEL_FOLDER_PATH;  // modelフォルダまでのパス
    static const std::string STAGE_PATH;         // stageモデルファイルのパス
    static const std::string PLAYER_PATH;        // playerモデルファイルのパス
    static const std::string ENEMY_PATH;         // enemyモデルファイルのパス
};
