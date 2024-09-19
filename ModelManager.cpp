#include "ModelManager.h"

#include "DxLib.h"

using std::string; // 使うものだけusing宣言

const string ModelManager::MODEL_FOLDER_PATH = "data/object/";  // modelフォルダまでのパス
const string ModelManager::STAGE_PATH = "Stage.mv1";            // backgroundモデルファイルのパス
const string ModelManager::PLAYER_PATH = "Player.mv1";          // fieldモデルファイルのパス
const string ModelManager::ENEMY_PATH = "Enemy.mv1";            // playerモデルファイルのパス

//=========================
// コンストラクタ
//=========================
ModelManager::ModelManager()
    : modelHandle()
{
    LoadAllModel();
}
//=========================
// コピーコンストラクタ
//=========================
ModelManager::ModelManager(const ModelManager&)
{
    // 使用しない
}

//=========================
// 代入演算子
//=========================
void ModelManager::operator=(const ModelManager&)
{
    // 使用しない
}

//=========================
// デストラクタ
//=========================
ModelManager::~ModelManager()
{
    DeleteAllModel();
}

//=========================
// アドレス生成と参照返し
//=========================
ModelManager& ModelManager::GetInstance()
{
    static ModelManager ModelManager;
    return ModelManager;
}

//=========================
// 全てのモデルを読み込み
//=========================
void ModelManager::LoadAllModel()
{
    // モデルファイルへのパス
    string fullPath = MODEL_FOLDER_PATH + STAGE_PATH;
    modelHandle[STAGE] = MV1LoadModel(fullPath.c_str());

    fullPath = MODEL_FOLDER_PATH + PLAYER_PATH;
    modelHandle[PLAYER] = MV1LoadModel(fullPath.c_str());

    fullPath = MODEL_FOLDER_PATH + ENEMY_PATH;
    modelHandle[ENEMY] = MV1LoadModel(fullPath.c_str());

    // 読み込み失敗ならエラー
    for (int i = 0; i < MODEL_AMOUNT; ++i)
    {
        if (modelHandle[i] < 0)
        {
            printfDx("[モデルデータ読み込みに失敗]_[%d]\n", i);
        }
    }
}

//=========================
// 全てのモデルを削除
//=========================
void ModelManager::DeleteAllModel()
{
    for (int i = 0; i < MODEL_AMOUNT; ++i)
    {
        if (modelHandle[i] != NULL)
        {
            MV1DeleteModel(modelHandle[i]);
            modelHandle[i] = NULL;
        }
    }
}

//=========================
// モデルハンドルの参照を返す
//=========================
const int& ModelManager::GetModelHandle(ModelKind modelKind) const
{
    if (modelKind == MODEL_AMOUNT)
    {
        printfDx("不正な値を参照しています_ModelManager");
        return modelHandle[0];
    }

    return modelHandle[modelKind];
}
