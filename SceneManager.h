#pragma once

#include "ISceneChanger.h"
#include "BaseScene.h"
#include "Scene.h"

#include "ResultScore.h"
#include "FadeManager.h"

class SceneManager : public ISceneChanger, Scene {
private:
    BaseScene* currentScene; // 現在のシーンオブジェクトへのポインタ
    eScene nextScene;       // 次のシーンの列挙型

    ResultScore resultScore;

    FadeManager fadeMgr;    // フェード管理クラス

    bool isSceneChange;

public:
    SceneManager();
    ~SceneManager();

    void Initialize() override; ///< 初期化処理
    void Finalize() override;   ///< 終了処理
    void Update() override;     ///< 更新処理
    void Draw() override;       ///< 描画処理

    /// <summary>
    /// 次のシーンへの切り替えを行う
    /// </summary>
    /// <param name="NextScene">次のシーン</param>
    void ChangeScene(eScene NextScene,ResultScore score) override;
};
