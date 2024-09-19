#include "DxLib.h"
#include "ResultScene.h"
#include "ISceneChanger.h"

const int Result::SCORE_DRAW_POS_X = 300;  // �X�R�A�`��X���W
const int Result::SCORE_DRAW_POS_Y = 200;  // �X�R�A�`��Y���W

Result::Result(ISceneChanger* changer, ResultScore resultScore)
	: BaseScene(changer)
	, resultScore(resultScore)
	, backGround()
	, pushFlg()
{
	// �����Ȃ�
	buttonSE = LoadSoundMem("data/sounds/Title/button.mp3");
}

Result::~Result()
{
}

// ����������
void Result::Initialize()
{
	resultScore.Initialize();
	resultScore.SetRank();

	backGround = LoadGraph("data/image/Result/ResultBack.png");

	pushFlg = false;
}

// �X�V����
void Result::Update()
{
	if (!pushFlg && GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_3)
	{
		mSceneChanger->ChangeScene(titleScene, ResultScore());
		PlaySoundMem(buttonSE, DX_PLAYTYPE_BACK);
		pushFlg = true;
	}
}

// �`�揈��
void Result::Draw()
{
	DrawGraph(0, 0, backGround, TRUE);

	resultScore.Draw(SCORE_DRAW_POS_X, SCORE_DRAW_POS_Y);

}

// �I������
void Result::Finalize()
{
	InitSoundMem();

	InitGraph();

	InitFontToHandle();

}
