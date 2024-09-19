#pragma once

#include "BaseScene.h"
#include "ResultScore.h"

class Result : BaseScene{
private:

    // �萔

    static const int SCORE_DRAW_POS_X;  // �X�R�A�`��X���W
    static const int SCORE_DRAW_POS_Y;  // �X�R�A�`��Y���W

    // �ϐ�

    ResultScore resultScore;

    int buttonSE;

    int backGround;

    bool pushFlg;
public:
    Result(ISceneChanger* changer,ResultScore resultScore);
    ~Result();

    /// <summary>����������</summary>
    void Initialize() override;

    /// <summary>�X�V����</summary>
    void Update() override;

    /// <summary>�`�揈��</summary>
    void Draw() override;

    /// <summary>�I������</summary>
    void Finalize() override;
};