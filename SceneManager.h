#pragma once

#include "ISceneChanger.h"
#include "BaseScene.h"
#include "Scene.h"

#include "ResultScore.h"
#include "FadeManager.h"

class SceneManager : public ISceneChanger, Scene {
private:
    BaseScene* currentScene; // ���݂̃V�[���I�u�W�F�N�g�ւ̃|�C���^
    eScene nextScene;       // ���̃V�[���̗񋓌^

    ResultScore resultScore;

    FadeManager fadeMgr;    // �t�F�[�h�Ǘ��N���X

    bool isSceneChange;

public:
    SceneManager();
    ~SceneManager();

    void Initialize() override; ///< ����������
    void Finalize() override;   ///< �I������
    void Update() override;     ///< �X�V����
    void Draw() override;       ///< �`�揈��

    /// <summary>
    /// ���̃V�[���ւ̐؂�ւ����s��
    /// </summary>
    /// <param name="NextScene">���̃V�[��</param>
    void ChangeScene(eScene NextScene,ResultScore score) override;
};
