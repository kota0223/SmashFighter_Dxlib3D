#pragma once

// �C���N���[�h
#include "DxLib.h"
#include "TagStruct.h" 

// RGB�J���[�\����
struct Color_st
{
    int red;    // �Ԑ���
    int green;  // �ΐ���
    int blue;   // ����
};

/// <summary>
/// �^�O�\���N���X
/// </summary>
class DisplayTag
{
private:

    // �萔

    static const int RED_INIT;          // �Ԑ����������l
    static const int GREEN_INIT;        // �ΐ����������l
    static const int BLUE_INIT;         // �����������l

    static const int DISPLAY_TIME;      // �\������ (�~���b)

    static const int TAG_GRAPH_X_SIZE;  // �^�O�摜��X�����̃T�C�Y
    static const int TAG_GRAPH_Y_SIZE;  // �^�O�摜��Y�����̃T�C�Y

    // �ϐ�

    int tagGraphHandle;         // �^�O�摜�n���h��
    int tagBackGraphHandle;     // �^�O�w�i�摜�n���h��
    int prevTimer;              // �O��̃^�C�}�[�l
    bool isVisible;             // �^�O�̉���
    Color_st color;             // �^�O�̐F���
    Tag_st tag;                 // �^�O���\����

public:

    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    DisplayTag();

    /// <summary>
    /// �O���t�B�b�N�̏�����
    /// </summary>
    /// <param name="tagGraphHandle">�^�O�摜�n���h��</param>
    /// <param name="tagBackGraphHandle">�^�O�w�i�摜�n���h��</param>
    void InitGraph(int tagGraphHandle, int tagBackGraphHandle);

    /// <summary>
    /// �\���F�̐ݒ�
    /// </summary>
    /// <param name="Red">�Ԑ���</param>
    /// <param name="Green">�ΐ���</param>
    /// <param name="Blue">����</param>
    void SetColor(const Color_st& tagColor);

    /// <summary>
    /// �X�V����
    /// </summary>
    void Update();

    /// <summary>
    /// �^�O�̕`��
    /// </summary>
    /// <param name="pos"></param>
    void Draw(VECTOR pos);

    /// <summary>
    /// ���ۂ̕\������
    /// </summary>
    void DoDisplay();

    /// <summary>
    /// �^�O���̎擾
    /// </summary>
    /// <returns>�^�O���\����</returns>
    Tag_st GetTag()
    {
        // �^�O���̍X�V
        tag.tagGraph = tagGraphHandle;
        tag.tagBaseGraph = tagBackGraphHandle;
        tag.red = color.red;
        tag.green = color.green;
        tag.blue = color.blue;

        return tag;
    }
};
