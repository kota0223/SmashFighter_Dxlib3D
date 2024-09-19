//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include <math.h>
#include "DxLib.h"
#include "TitleScene.h"
#include "Screen.h"
#include "ResultScore.h"
#include "ISceneChanger.h"

//-----------------------------------------------------------------------------
//	@brief	�ÓI�萔
//-----------------------------------------------------------------------------
const int Title::ALPHA_MAX_NUM = 255;				// �A���t�@�l�ő吔
const int Title::ALPHA_ADD_NUM = 5;				// �A���t�@�l������
const float Title::BLINKING_COUNT_ONE = 100.0f;		// ���̓_�łɂ�����J�E���g��
const int Title::TITLE_GRAPH_INITIAL_Y = 50;		// �^�C�g���摜�̏���Y���W

//-----------------------------------------------------------------------------
//	@brief	�R���X�g���N�^
//-----------------------------------------------------------------------------
Title::Title(ISceneChanger* changer) :BaseScene(changer)
{

	// �{�^�����������t���O��������
	isChangeScene = false;

	// UI������
	InitializeUI();

	// �T�E���h������
	InitializeSound();

	demo = new Main();
}

//-----------------------------------------------------------------------------
//	@brief	UI������
//-----------------------------------------------------------------------------
void Title::InitializeUI()
{
	// �^�C�g��UI������
	titleLogo.graphHandle = LoadGraph("data/image/Title/Title.png");
	titleLogo.x = 0;
	titleLogo.y = TITLE_GRAPH_INITIAL_Y;
	titleLogo.alpha = 0;

	// �Q�[���X�^�[�g�K�C�hUI������
	gameStartGuide.graphHandle = LoadGraph("data/image/Title/GameStart_Guide.png");
	gameStartGuide.x = 0;
	gameStartGuide.y = 0;
	gameStartGuide.alpha = 0;
	gameStartGuide.blinkingCount = 0;

	// ����K�C�hUI������
	controlGuide.graphHandle = LoadGraph("data/image/Title/Control_Guide.png");
	controlGuide.x = 0;
	controlGuide.y = 0;
}

//-----------------------------------------------------------------------------
//	@brief	�T�E���h������
//-----------------------------------------------------------------------------
void Title::InitializeSound()
{
	// BGM�ǂݍ���
	bgmSoundHandle = LoadSoundMem("data/sounds/Title/bgm.mp3");

	// �{�^�����ʉ��ǂݍ���
	buttonSoundHandle = LoadSoundMem("data/sounds/Title/button.mp3");
}

//-----------------------------------------------------------------------------
//	@brief	����������
//-----------------------------------------------------------------------------
void Title::Initialize()
{
	// BGM�����[�v�Đ�
	PlaySoundMem(bgmSoundHandle, DX_PLAYTYPE_LOOP);

	demo->InitDemo();
}

//-----------------------------------------------------------------------------
//	@brief	�I������
//-----------------------------------------------------------------------------
void Title::Finalize()
{
	demo->Finalize();
	delete demo;

	// �摜�I������
	InitGraph();

	// �T�E���h�I������
	StopSoundMem(bgmSoundHandle);
	InitSoundMem();
}

//-----------------------------------------------------------------------------
//	@brief	�X�V����
//-----------------------------------------------------------------------------
void Title::Update()
{
	// �V�[���̐؂�ւ�
	const bool isPressButton = GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_3;
	if (!isChangeScene && isPressButton)
	{
		isChangeScene = true;
		mSceneChanger->ChangeScene(mainScene, ResultScore());
		PlaySoundMem(buttonSoundHandle, DX_PLAYTYPE_BACK);
	}

	demo->UpdateDemo();

	// �^�C�g�����S�����X�ɕ\��������
	GradualDisplayUI(titleLogo);

	// �^�C�g�����S�̈ړ�����
	titleLogo.y = (int)(TITLE_GRAPH_INITIAL_Y - TITLE_GRAPH_INITIAL_Y * ((float)(titleLogo.alpha) / ALPHA_MAX_NUM));

	// �Q�[���X�^�[�g�K�C�hUI�̓_�ŕ`��
	BlinkingDraw(gameStartGuide);
}

//-----------------------------------------------------------------------------
//	@brief	�`�揈��
//-----------------------------------------------------------------------------
void Title::Draw() {

	demo->DrawDemo();

	// �^�C�g�����S�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, titleLogo.alpha);
	DrawGraph(titleLogo.x, titleLogo.y, titleLogo.graphHandle, TRUE);

	// �Q�[���X�^�[�g�K�C�h�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, gameStartGuide.alpha);
	DrawGraph(gameStartGuide.x, gameStartGuide.y, gameStartGuide.graphHandle, TRUE);

	// ����K�C�h�`��
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, NULL);
	DrawGraph(controlGuide.x, controlGuide.y, controlGuide.graphHandle, TRUE);

}

//-----------------------------------------------------------------------------
//	@brief	UI�����X�ɕ\��������
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
//	@brief	�_�ŕ`��
//-----------------------------------------------------------------------------
void Title::BlinkingDraw(UI& ui)
{
	ui.blinkingCount++;

	gameStartGuide.alpha = (int)(NormalizeSin(DX_TWO_PI / BLINKING_COUNT_ONE * ui.blinkingCount) * ALPHA_MAX_NUM);
}

//-----------------------------------------------------------------------------
//	@brief	���K������Sin�g��Ԃ��֐�
//-----------------------------------------------------------------------------
double Title::NormalizeSin(double radian)
{
	return (sin(radian) + 1.0) / 2.0;
}
