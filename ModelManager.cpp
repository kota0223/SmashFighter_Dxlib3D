#include "ModelManager.h"

#include "DxLib.h"

using std::string; // �g�����̂���using�錾

const string ModelManager::MODEL_FOLDER_PATH = "data/object/";  // model�t�H���_�܂ł̃p�X
const string ModelManager::STAGE_PATH = "Stage.mv1";            // background���f���t�@�C���̃p�X
const string ModelManager::PLAYER_PATH = "Player.mv1";          // field���f���t�@�C���̃p�X
const string ModelManager::ENEMY_PATH = "Enemy.mv1";            // player���f���t�@�C���̃p�X

//=========================
// �R���X�g���N�^
//=========================
ModelManager::ModelManager()
    : modelHandle()
{
    LoadAllModel();
}
//=========================
// �R�s�[�R���X�g���N�^
//=========================
ModelManager::ModelManager(const ModelManager&)
{
    // �g�p���Ȃ�
}

//=========================
// ������Z�q
//=========================
void ModelManager::operator=(const ModelManager&)
{
    // �g�p���Ȃ�
}

//=========================
// �f�X�g���N�^
//=========================
ModelManager::~ModelManager()
{
    DeleteAllModel();
}

//=========================
// �A�h���X�����ƎQ�ƕԂ�
//=========================
ModelManager& ModelManager::GetInstance()
{
    static ModelManager ModelManager;
    return ModelManager;
}

//=========================
// �S�Ẵ��f����ǂݍ���
//=========================
void ModelManager::LoadAllModel()
{
    // ���f���t�@�C���ւ̃p�X
    string fullPath = MODEL_FOLDER_PATH + STAGE_PATH;
    modelHandle[STAGE] = MV1LoadModel(fullPath.c_str());

    fullPath = MODEL_FOLDER_PATH + PLAYER_PATH;
    modelHandle[PLAYER] = MV1LoadModel(fullPath.c_str());

    fullPath = MODEL_FOLDER_PATH + ENEMY_PATH;
    modelHandle[ENEMY] = MV1LoadModel(fullPath.c_str());

    // �ǂݍ��ݎ��s�Ȃ�G���[
    for (int i = 0; i < MODEL_AMOUNT; ++i)
    {
        if (modelHandle[i] < 0)
        {
            printfDx("[���f���f�[�^�ǂݍ��݂Ɏ��s]_[%d]\n", i);
        }
    }
}

//=========================
// �S�Ẵ��f�����폜
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
// ���f���n���h���̎Q�Ƃ�Ԃ�
//=========================
const int& ModelManager::GetModelHandle(ModelKind modelKind) const
{
    if (modelKind == MODEL_AMOUNT)
    {
        printfDx("�s���Ȓl���Q�Ƃ��Ă��܂�_ModelManager");
        return modelHandle[0];
    }

    return modelHandle[modelKind];
}
