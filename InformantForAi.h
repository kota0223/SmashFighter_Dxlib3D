#pragma once

#include <DxLib.h>

class Character;

//=========================
// enemy(AI)�ɏ���^����N���X
// �V���O���g��
//=========================
class InformantForAi final
{
public:

    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="characters">�L�����N�^�[�|�C���^</param>
    /// <param name="size">�L�����N�^�[��</param>
    void Initialize(Character** characters, int size);

    /// <summary>
    /// �C���X�^���X�擾
    /// </summary>
    /// <returns>�N���X�̃C���X�^���X</returns>
    static InformantForAi& GetInstance();

    /// <summary>
    /// �U���Ώۂ̎擾
    /// </summary>
    /// <param name="position">�����̍��W</param>
    /// <returns>�^�[�Q�b�g�ƂȂ�L�����N�^�[�̃|�C���^</returns>
    Character* GetAttackTarget(const VECTOR& position) ;

private:

    // �萔

    static const float INIT_VECTOR_SIZE;	// �G��T���ۂ̋����̏����l

    // �ϐ�

    Character** characters; // �L�����N�^�[�|�C���^
    int characterAmount;    // �L�����N�^�[��

    // �O���ł̎��s���֎~����

    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    InformantForAi();

    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name=""></param>
    InformantForAi(const InformantForAi&);

    /// <summary>
    /// ������Z�q
    /// </summary>
    /// <param name=""></param>
    void operator=(const InformantForAi&);

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~InformantForAi();

};
