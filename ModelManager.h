#pragma once

#include <string>       // ������^�N���X

//=========================
// 3D���f���Ǘ��N���X
// �V���O���g��
//=========================
class ModelManager final
{
public:
    // �V�[����Ԓ�`
    enum ModelKind
    {
        STAGE = 0,      // �X�e�[�W
        PLAYER,         // �v���C���[
        ENEMY,          // �G�l�~�[
        MODEL_AMOUNT    // ���f���̐�
    };

    static ModelManager& GetInstance(); // �A�h���X��Ԃ�

    const int& GetModelHandle(ModelKind modelKind) const; // ���f���n���h���̎Q�Ƃ�Ԃ�

private:
    // �O���ł̎��s���֎~����
    ModelManager();                        // �R���X�g���N�^
    ModelManager(const ModelManager&);     // �R�s�[�R���X�g���N�^
    void operator=(const ModelManager&);   // ������Z�q
    ~ModelManager();                       // �f�X�g���N�^

    void LoadAllModel();    // �S�Ẵ��f����ǂݍ���
    void DeleteAllModel();  // �S�Ẵ��f�����폜

    // �萔
    static const std::string MODEL_FOLDER_PATH;  // model�t�H���_�܂ł̃p�X
    static const std::string STAGE_PATH;         // stage���f���t�@�C���̃p�X
    static const std::string PLAYER_PATH;        // player���f���t�@�C���̃p�X
    static const std::string ENEMY_PATH;         // enemy���f���t�@�C���̃p�X

    int modelHandle[MODEL_AMOUNT];   // ���f���n���h��
};
