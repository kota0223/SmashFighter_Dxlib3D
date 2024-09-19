#pragma once

#include "Scene.h"

class ISceneChanger;

//�V�[���̊��N���X�B
class BaseScene : public Scene {

protected:
    ISceneChanger* mSceneChanger;    //�N���X���L���ɃV�[���؂�ւ���`����C���^�[�t�F�C�X

public:
    BaseScene(ISceneChanger* changer);
    BaseScene() {};
    virtual ~BaseScene() {}
    virtual void Initialize() override {}    //�������������I�[�o�[���C�h�B
    virtual void Finalize() override {};     //�I���������I�[�o�[���C�h�B
    virtual void Update() override {}        //�X�V�������I�[�o�[���C�h�B
    virtual void Draw() override {};         //�`�揈�����I�[�o�[���C�h�B

};