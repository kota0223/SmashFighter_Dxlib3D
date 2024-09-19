#include "DxLib.h"
#include "ResultScene.h"
#include "ISceneChanger.h"

const int Result::SCORE_DRAW_POS_X = 300;  // スコア描画X座標
const int Result::SCORE_DRAW_POS_Y = 200;  // スコア描画Y座標

Result::Result(ISceneChanger* changer, ResultScore resultScore)
	: BaseScene(changer)
	, resultScore(resultScore)
	, backGround()
	, pushFlg()
{
	// 処理なし
	buttonSE = LoadSoundMem("data/sounds/Title/button.mp3");
}

Result::~Result()
{
}

// 初期化処理
void Result::Initialize()
{
	resultScore.Initialize();
	resultScore.SetRank();

	backGround = LoadGraph("data/image/Result/ResultBack.png");

	pushFlg = false;
}

// 更新処理
void Result::Update()
{
	if (!pushFlg && GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_3)
	{
		mSceneChanger->ChangeScene(titleScene, ResultScore());
		PlaySoundMem(buttonSE, DX_PLAYTYPE_BACK);
		pushFlg = true;
	}
}

// 描画処理
void Result::Draw()
{
	DrawGraph(0, 0, backGround, TRUE);

	resultScore.Draw(SCORE_DRAW_POS_X, SCORE_DRAW_POS_Y);

}

// 終了処理
void Result::Finalize()
{
	InitSoundMem();

	InitGraph();

	InitFontToHandle();

}
