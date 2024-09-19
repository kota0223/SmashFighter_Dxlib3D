#pragma once

#include <string>       // 文字列型クラス

//=========================
// 3Dモデル管理クラス
// シングルトン
//=========================
class ModelManager final
{
public:
    // シーン状態定義
    enum ModelKind
    {
        STAGE = 0,      // ステージ
        PLAYER,         // プレイヤー
        ENEMY,          // エネミー
        MODEL_AMOUNT    // モデルの数
    };

    static ModelManager& GetInstance(); // アドレスを返す

    const int& GetModelHandle(ModelKind modelKind) const; // モデルハンドルの参照を返す

private:
    // 外部での実行を禁止する
    ModelManager();                        // コンストラクタ
    ModelManager(const ModelManager&);     // コピーコンストラクタ
    void operator=(const ModelManager&);   // 代入演算子
    ~ModelManager();                       // デストラクタ

    void LoadAllModel();    // 全てのモデルを読み込み
    void DeleteAllModel();  // 全てのモデルを削除

    // 定数
    static const std::string MODEL_FOLDER_PATH;  // modelフォルダまでのパス
    static const std::string STAGE_PATH;         // stageモデルファイルのパス
    static const std::string PLAYER_PATH;        // playerモデルファイルのパス
    static const std::string ENEMY_PATH;         // enemyモデルファイルのパス

    int modelHandle[MODEL_AMOUNT];   // モデルハンドル
};
