#pragma once

/// <summary>
/// シーン抽象クラス
/// </summary>
class Scene {
public:
    /// <summary>
    /// 初期化処理を行う
    /// </summary>
    virtual void Initialize() = 0;

    /// <summary>
    /// 更新処理を行う
    /// </summary>
    virtual void Update() = 0;

    /// <summary>
    /// 描画処理を行う
    /// </summary>
    virtual void Draw() = 0;

    /// <summary>
    /// 終了処理を行う
    /// </summary>
    virtual void Finalize() = 0;
};
