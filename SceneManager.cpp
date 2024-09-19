#include "DxLib.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "MainScene.h"
#include "ResultScene.h"

/// <summary>
/// �V�[���}�l�[�W���N���X�̃R���X�g���N�^
/// </summary>
SceneManager::SceneManager() :nextScene(Empty)
{
	// �����̓^�C�g���V�[�����Z�b�g
	currentScene = new Title(this);

	// �V�[���`�F���W�t���O������
	isSceneChange = false;
}

/// <summary>
/// �V�[���}�l�[�W���N���X�̃f�X�g���N�^
/// </summary>
SceneManager::~SceneManager() {

	// �V�[���������Ă�����A���������J������
	if (currentScene) {
		delete currentScene;
	}
}

/// <summary>
/// ���̃V�[���ɑJ�ڂ���
/// </summary>
/// <param name="NextScene">���̃V�[���̗񋓒l</param>
void SceneManager::ChangeScene(eScene NextScene, ResultScore score) {

	nextScene = NextScene;    //���̃V�[�����Z�b�g����

	isSceneChange = true;

	fadeMgr.StartFadeOut();

	// ���̃V�[�������U���g�V�[���Ȃ�΁A���U���g�X�R�A�̃C���X�^���X��ۑ�
	if (nextScene == resultScene)
		resultScore = score;
}

/// <summary>
/// �V�[���}�l�[�W���̏���������
/// </summary>
void SceneManager::Initialize()
{
	currentScene->Initialize();
}

/// <summary>
/// �V�[���}�l�[�W���̏I������
/// </summary>
void SceneManager::Finalize()
{
	currentScene->Finalize();
}

/// <summary>
/// �V�[���̍X�V����
/// </summary>
void SceneManager::Update() {
	if (isSceneChange)
	{
		fadeMgr.Update();

		if (fadeMgr.IsFadeOutCompleted()
			&& !fadeMgr.IsFadingIn())
		{
			// �������̃V�[�����w�肳��Ă���ꍇ
			if (nextScene != Empty) {

				// ���݂̃V�[�����I����������
				currentScene->Finalize();

				delete currentScene;

				// ���̃V�[���ɉ����ĐV�����V�[���𐶐�����
				switch (nextScene)
				{
					// �^�C�g���V�[���̏ꍇ
				case titleScene:
					currentScene = (BaseScene*)new Title(this);
					break;
					// ���C���V�[���̏ꍇ
				case mainScene:
					currentScene = (BaseScene*)new Main(this);
					break;
					// ���U���g�V�[���̏ꍇ�̓��U���g�X�R�A�C���X�^���X��n��
				case resultScene:
					currentScene = (BaseScene*)new Result(this, resultScore);
					break;
				}

				nextScene = Empty;

				// �V�����V�[��������������
				currentScene->Initialize();

				fadeMgr.StartFadeIn();
			}
		}

		if (!fadeMgr.IsFadeInCompleted())
			return;

	}

	// ���݂̃V�[�����X�V����
	currentScene->Update();
}


/// <summary>
/// �V�[���̕`�揈��
/// </summary>
void SceneManager::Draw() {

	currentScene->Draw();

	if (isSceneChange)
	{
		fadeMgr.Draw();
	}
}
