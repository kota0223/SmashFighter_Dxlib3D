//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include <math.h>
#include "DxLib.h"
#include "TitleScene.h"
#include "Screen.h"
#include "ResultScore.h"
#include "ISceneChanger.h"

//-----------------------------------------------------------------------------
//	@brief	静的定数
//-----------------------------------------------------------------------------
const int Title::ALPHA_MAX_NUM = 255;				// アルファ値最大数
const int Title::ALPHA_ADD_NUM = 5;				// アルファ値増加数
const float Title::BLINKING_COUNT_ONE = 100.0f;		// 一回の点滅にかかるカウント数
const int Title::TITLE_GRAPH_INITIAL_Y = 50;		// タイトル画像の初期Y座標

//-----------------------------------------------------------------------------
//	@brief	コンストラクタ
//-----------------------------------------------------------------------------
Title::Title(ISceneChanger* changer) :BaseScene(changer)
{

	// ボタンを押したフラグを初期化
	isChangeScene = false;

	// UI初期化
	InitializeUI();

	// サウンド初期化
	InitializeSound();

	demo = new Main();
}

//-----------------------------------------------------------------------------
//	@brief	UI初期化
//-----------------------------------------------------------------------------
void Title::InitializeUI()
{
	// タイトルUI初期化
	titleLogo.graphHandle = LoadGraph("data/image/Title/Title.png");
	titleLogo.x = 0;
	titleLogo.y = TITLE_GRAPH_INITIAL_Y;
	titleLogo.alpha = 0;

	// ゲームスタートガイドUI初期化
	gameStartGuide.graphHandle = LoadGraph("data/image/Title/GameStart_Guide.png");
	gameStartGuide.x = 0;
	gameStartGuide.y = 0;
	gameStartGuide.alpha = 0;
	gameStartGuide.blinkingCount = 0;

	// 操作ガイドUI初期化
	controlGuide.graphHandle = LoadGraph("data/image/Title/Control_Guide.png");
	controlGuide.x = 0;
	controlGuide.y = 0;
}

//-----------------------------------------------------------------------------
//	@brief	サウンド初期化
//-----------------------------------------------------------------------------
void Title::InitializeSound()
{
	// BGM読み込み
	bgmSoundHandle = LoadSoundMem("data/sounds/Title/bgm.mp3");

	// ボタン効果音読み込み
	buttonSoundHandle = LoadSoundMem("data/sounds/Title/button.mp3");
}

//-----------------------------------------------------------------------------
//	@brief	初期化処理
//-----------------------------------------------------------------------------
void Title::Initialize()
{
	// BGMをループ再生
	PlaySoundMem(bgmSoundHandle, DX_PLAYTYPE_LOOP);

	demo->InitDemo();
}

//-----------------------------------------------------------------------------
//	@brief	終了処理
//-----------------------------------------------------------------------------
void Title::Finalize()
{
	demo->Finalize();
	delete demo;

	// 画像終了処理
	InitGraph();

	// サウンド終了処理
	StopSoundMem(bgmSoundHandle);
	InitSoundMem();
}

//-----------------------------------------------------------------------------
//	@brief	更新処理
//-----------------------------------------------------------------------------
void Title::Update()
{
	// シーンの切り替え
	const bool isPressButton = GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_3;
	if (!isChangeScene && isPressButton)
	{
		isChangeScene = true;
		mSceneChanger->ChangeScene(mainScene, ResultScore());
		PlaySoundMem(buttonSoundHandle, DX_PLAYTYPE_BACK);
	}

	demo->UpdateDemo();

	// タイトルロゴを徐々に表示させる
	GradualDisplayUI(titleLogo);

	// タイトルロゴの移動処理
	titleLogo.y = (int)(TITLE_GRAPH_INITIAL_Y - TITLE_GRAPH_INITIAL_Y * ((float)(titleLogo.alpha) / ALPHA_MAX_NUM));

	// ゲームスタートガイドUIの点滅描画
	BlinkingDraw(gameStartGuide);
}

//-----------------------------------------------------------------------------
//	@brief	描画処理
//-----------------------------------------------------------------------------
void Title::Draw() {

	demo->DrawDemo();

	// タイトルロゴ描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, titleLogo.alpha);
	DrawGraph(titleLogo.x, titleLogo.y, titleLogo.graphHandle, TRUE);

	// ゲームスタートガイド描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, gameStartGuide.alpha);
	DrawGraph(gameStartGuide.x, gameStartGuide.y, gameStartGuide.graphHandle, TRUE);

	// 操作ガイド描画
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, NULL);
	DrawGraph(controlGuide.x, controlGuide.y, controlGuide.graphHandle, TRUE);

}

//-----------------------------------------------------------------------------
//	@brief	UIを徐々に表示させる
//-----------------------------------------------------------------------------
void Title::GradualDisplayUI(UI& ui)
{
	if (ui.alpha < ALPHA_MAX_NUM)
	{
		ui.alpha += ALPHA_ADD_NUM;
		if (ui.alpha >= ALPHA_MAX_NUM)
			ui.alpha = ALPHA_MAX_NUM;
	}
}

//-----------------------------------------------------------------------------
//	@brief	点滅描画
//-----------------------------------------------------------------------------
void Title::BlinkingDraw(UI& ui)
{
	ui.blinkingCount++;

	gameStartGuide.alpha = (int)(NormalizeSin(DX_TWO_PI / BLINKING_COUNT_ONE * ui.blinkingCount) * ALPHA_MAX_NUM);
}

//-----------------------------------------------------------------------------
//	@brief	正規化したSin波を返す関数
//-----------------------------------------------------------------------------
double Title::NormalizeSin(double radian)
{
	return (sin(radian) + 1.0) / 2.0;
}
