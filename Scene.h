#pragma once

/// <summary>
/// �V�[�����ۃN���X
/// </summary>
class Scene {
public:
    /// <summary>
    /// �������������s��
    /// </summary>
    virtual void Initialize() = 0;

    /// <summary>
    /// �X�V�������s��
    /// </summary>
    virtual void Update() = 0;

    /// <summary>
    /// �`�揈�����s��
    /// </summary>
    virtual void Draw() = 0;

    /// <summary>
    /// �I���������s��
    /// </summary>
    virtual void Finalize() = 0;
};
