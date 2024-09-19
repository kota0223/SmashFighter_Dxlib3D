//-----------------------------------------------------------------------------
//	@brief	�v���v���Z�b�T
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "BaseScene.h"
#include "MainScene.h"

//-----------------------------------------------------------------------------
//	@brief	�\���̐錾
//-----------------------------------------------------------------------------
struct UI {
    int graphHandle;    // �摜�n���h��
    int x, y;           // ���W
    int alpha;          // �A���t�@�l
    int blinkingCount;  // �_�ŗp�J�E���g
};

//-----------------------------------------------------------------------------
//	@brief	�^�C�g���V�[���N���X
//-----------------------------------------------------------------------------
class Title :public BaseScene {
private:

//===================== �ÓI�萔 ===================//

    static const int ALPHA_MAX_NUM;           // �A���t�@�l�ő吔
    static const int ALPHA_ADD_NUM;           // �A���t�@�l������
    static const float BLINKING_COUNT_ONE;      // ���̓_�łɂ�����J�E���g��
    static const int TITLE_GRAPH_INITIAL_Y;   // �^�C�g���摜�̏���Y���W

//===================== �����o�ϐ� ===================//

    UI titleLogo;                   // �^�C�g�����SUI
    UI gameStartGuide;              // �Q�[���X�^�[�g�K�C�hUI
    UI controlGuide;                // ������@UI
    int bgmSoundHandle;             // BGM�T�E���h�n���h��
    int buttonSoundHandle;          // �{�^�����ʉ��T�E���h�n���h��
    bool isChangeScene;             // �V�[���ڍs���邩�ǂ���

    Main* demo;

//===================== ���������֐� ===================//

    /// <summary>
    /// UI�ϐ��̏�����
    /// </summary>
    void InitializeUI();

    /// <summary>
    /// �T�E���h�n���h���ϐ��̏�����
    /// </summary>
    void InitializeSound();

    /// <summary>
    /// UI�����X�ɕ\��������
    /// </summary>
    void GradualDisplayUI(UI &ui);

    /// <summary>
    /// �_�ŕ`��
    /// </summary>
    /// <param name="ui">�_�ł�����UI�\����</param>
    void BlinkingDraw(UI& ui);

    /// <summary>
    /// ���K������Sin�g��Ԃ�
    /// </summary>
    /// <param name="radian">���W�A���l</param>
    /// <returns>0 ~ 1 �ɐ��K������Sin�g</returns>
    double NormalizeSin(double radian);

public:

//===================== �֐� ===================//

    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="changer">�V�[���ύX�C���^�[�t�F�C�X</param>
    Title(ISceneChanger* changer);

    /// <summary>
    /// ����������
    /// </summary>
    void Initialize() override;

    /// <summary>
    /// �X�V����
    /// </summary>
    void Update() override;

    /// <summary>
    /// �`�揈��
    /// </summary>
    void Draw() override;

    /// <summary>
    /// �I������
    /// </summary>
    void Finalize() override;

};