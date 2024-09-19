#pragma once

#include <string>       // ������^�N���X

//=========================
// �T�E���h�Ǘ��N���X
// �V���O���g��
//=========================
class SoundManager final
{
public:
    // �V�[����Ԓ�`
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

    static SoundManager& GetInstance(); // �A�h���X��Ԃ�

private:
    // �O���ł̎��s���֎~����
    SoundManager();                        // �R���X�g���N�^
    SoundManager(const SoundManager&);     // �R�s�[�R���X�g���N�^
    void operator=(const SoundManager&);   // ������Z�q
    ~SoundManager();                       // �f�X�g���N�^

    void LoadAllSound();    // �S�Ẵ��f����ǂݍ���
    void DeleteAllSound();  // �S�Ẵ��f�����폜

    // �萔
    static const std::string MODEL_FOLDER_PATH;  // model�t�H���_�܂ł̃p�X
    static const std::string STAGE_PATH;         // stage���f���t�@�C���̃p�X
    static const std::string PLAYER_PATH;        // player���f���t�@�C���̃p�X
    static const std::string ENEMY_PATH;         // enemy���f���t�@�C���̃p�X
};
