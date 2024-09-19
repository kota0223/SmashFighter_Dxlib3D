#include "DxLib.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "MainScene.h"
#include "ResultScene.h"

/// <summary>
/// シーンマネージャクラスのコンストラクタ
/// </summary>
SceneManager::SceneManager() :nextScene(Empty)
{
	// 初期はタイトルシーンをセット
	currentScene = new Title(this);

	// シーンチェンジフラグ初期化
	isSceneChange = false;
}

/// <summary>
/// シーンマネージャクラスのデストラクタ
/// </summary>
SceneManager::~SceneManager() {

	// シーンが入っていたら、メモリを開放する
	if (currentScene) {
		delete currentScene;
	}
}

/// <summary>
/// 次のシーンに遷移する
/// </summary>
/// <param name="NextScene">次のシーンの列挙値</param>
void SceneManager::ChangeScene(eScene NextScene, ResultScore score) {

	nextScene = NextScene;    //次のシーンをセットする

	isSceneChange = true;

	fadeMgr.StartFadeOut();

	// 次のシーンがリザルトシーンならば、リザルトスコアのインスタンスを保存
	if (nextScene == resultScene)
		resultScore = score;
}

/// <summary>
/// シーンマネージャの初期化処理
/// </summary>
void SceneManager::Initialize()
{
	currentScene->Initialize();
}

/// <summary>
/// シーンマネージャの終了処理
/// </summary>
void SceneManager::Finalize()
{
	currentScene->Finalize();
}

/// <summary>
/// シーンの更新処理
/// </summary>
void SceneManager::Update() {
	if (isSceneChange)
	{
		fadeMgr.Update();

		if (fadeMgr.IsFadeOutCompleted()
			&& !fadeMgr.IsFadingIn())
		{
			// もし次のシーンが指定されている場合
			if (nextScene != Empty) {

				// 現在のシーンを終了処理する
				currentScene->Finalize();

				delete currentScene;

				// 次のシーンに応じて新しいシーンを生成する
				switch (nextScene)
				{
					// タイトルシーンの場合
				case titleScene:
					currentScene = (BaseScene*)new Title(this);
					break;
					// メインシーンの場合
				case mainScene:
					currentScene = (BaseScene*)new Main(this);
					break;
					// リザルトシーンの場合はリザルトスコアインスタンスを渡す
				case resultScene:
					currentScene = (BaseScene*)new Result(this, resultScore);
					break;
				}

				nextScene = Empty;

				// 新しいシーンを初期化する
				currentScene->Initialize();

				fadeMgr.StartFadeIn();
			}
		}

		if (!fadeMgr.IsFadeInCompleted())
			return;

	}

	// 現在のシーンを更新する
	currentScene->Update();
}


/// <summary>
/// シーンの描画処理
/// </summary>
void SceneManager::Draw() {

	currentScene->Draw();

	if (isSceneChange)
	{
		fadeMgr.Draw();
	}
}
