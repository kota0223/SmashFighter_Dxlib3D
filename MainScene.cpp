#include "DxLib.h"
#include "Player.h"
#include "Enemy.h"
#include "ModelManager.h"
#include "InformantForAi.h"
#include "MainScene.h"
#include "Collision.h"
#include "ParticleManager.h"
#include "Stage.h"
#include "ReadyTextUI.h"
#include "GoTextUI.h"
#include "TimeUpUI.h"
#include "ResultScore.h"
#include "ISceneChanger.h"

// �萔

const int Main::PLAYER_AMOUNT = 1;									// �v���C���[�̐�				
const int Main::ENEMY_AMOUNT = 3;									// �G�̐�
const int Main::CHARACTER_AMOUNT = PLAYER_AMOUNT+ENEMY_AMOUNT;		// �L���������v
const Color_st Main::ENEMY_TAG_COLOR_LIST[] = { {255, 0  , 255 },
												{0  , 255, 255 },
												{0  , 255, 0   },
												{255, 255, 255 } }; // �G�̃^�O�̃J���[���̍\���̔z��

const float Main::CHARACTER_DISPOSITION_RADIUS = 70.0f;				// �L������z�u���钆�S����̔��a
const float Main::PLAYER_DISPOSITION_DEGREE = 270.0f;				// �v���C���[��z�u���錴�_����̊p�x
const float Main::CHARACTER_INTERVAL_DEGREE = 90.0f;				// �L�����Ԃ̔z�u�Ԋu(�x)

const VECTOR Main::STAGE_MODEL_POSITION = VGet(0, -17, 0);							// �X�e�[�W���f���ʒu���W
const VECTOR Main::STAGE_MODEL_SCALE = VGet(3.7f, 3.7f, 3.7f);							// �X�e�[�W���f���X�P�[���l
const VECTOR Main::STAGE_MODEL_ROTATION = VGet(90.0 * DX_PI_F / 180.0, 0.0, 0.0);	// �X�e�[�W���f����]�l

const int Main::SHADOW_MAP_SIZE = 512;												// �V���h�E�}�b�v�T�C�Y
const VECTOR Main::SHADOW_MAP_DRAW_AREA_MIN = VGet(-90.0f, -6.0f, -90.0f);			// �V���h�E�}�b�v�̕`��͈͍��W�̏������ق��̒��_���W
const VECTOR Main::SHADOW_MAP_DRAW_AREA_MAX = VGet(90.0f, 20.0f, 90.0f);			// �V���h�E�}�b�v�̕`��͈͍��W�̑傫���ق��̒��_���W
const VECTOR Main::SHADOW_MAP_LIGHT_DIRECTION = VGet(0.0f, -1.0f, 0.0f);			// �V���h�E�}�b�v�̃��C�g�̕���

const int Main::GAME_TIME = 60;						// �Q�[���^�C��
const int Main::GAME_START_SE_PLAY_FRAME = 3 * 60;	// �Q�[���X�^�[�g����SE��炷�t���[����
const int Main::GAME_START_FRAME = 4 * 60;			// �Q�[���X�^�[�g�̃t���[����
const int Main::COUNT_DOWN_TIME = 5;				// �J�E���g�_�E�����n�߂�^�C��
const int Main::TRANSITION_RESULT_FRAME = 60 * 4;	// ���U���g�Ɉڍs����t���[����
const int Main::READY_UI_DRAW_FRAME = 3 * 60;		// ReadyUI��`�悷��t���[����

const unsigned int Main::TIMER_COLOR = GetColor(240, 145, 62);				// �^�C�}�[�����J���[
const unsigned int Main::COUNT_DOWN_TIMER_COLOR = GetColor(247, 68, 27);	// �J�E���g�_�E���^�C�}�[�����J���[
const unsigned int Main::TIMER_EDGE_COLOR = GetColor(255, 255, 255);		// �^�C�}�[�����̉����J���[
const int Main::TIMER_FONT_EDGE_SIZE = 3;									// �^�C�}�[�t�H���g�̉����T�C�Y


Main::Main(ISceneChanger* changer)
	: BaseScene(changer)
	, state(Main::BEFORE_GAME)
	, characters()
	, particleManager()
	, backGround()
	, timerFrameGraph()
	, timerFont()
	, bgm()
	, whistleSE()
	, countDownSE()
	, CharaShadowMap()
	, StageShadowMap()
	, collision()
	, stage()
	, readyTextUI()
	, goTextUI()
	, timeUpUI()
	, frame(0)
	, cnt()
	, Timer()
	, prevTimer()
	, prevCount()
	, isGameActive()
	, isGameEnd()
	, camera()
	, pUpdate(nullptr)
{
	// �w�i�摜
	backGround = LoadGraph("data/image/BackGrounds/BackGround.png");

	// �^�C�}�[�t���[���摜
	timerFrameGraph = LoadGraph("data/image/Main/TimerFrame.png");

	// �t�H���g�t�@�C���ǂݍ���
	timerFont = LoadFontDataToHandle("data/fonts/Arial Black.dft", TIMER_FONT_EDGE_SIZE);

	bgm = LoadSoundMem("data/sounds/Main/bgm.mp3");

	whistleSE = LoadSoundMem("data/sounds/Main/whistle.mp3");

	countDownSE = LoadSoundMem("data/sounds/Main/countDown.mp3");

	// �L�����N�^�[���f���p�̃V���h�E�}�b�v�n���h���̍쐬
	CharaShadowMap = MakeShadowMap(SHADOW_MAP_SIZE, SHADOW_MAP_SIZE);

	// �X�e�[�W���f���p�̃V���h�E�}�b�v�n���h���̍쐬
	StageShadowMap = MakeShadowMap(SHADOW_MAP_SIZE, SHADOW_MAP_SIZE);

	int texhandle = LoadGraph("data/shader/texture/hitEffect1.png");

	// �g�p����e�N�X�`�����O�ԂɃZ�b�g
	SetUseTextureToShader(0, texhandle);

	// �e�N�X�`���̃A�h���X���[�h�ύX
	SetTextureAddressMode(DX_TEXADDRESS_WRAP);
}

Main::Main()
{
	// �w�i�摜
	backGround = LoadGraph("data/image/BackGrounds/BackGround.png");
}

/// �^�C�g���V�[���̏���������
void Main::Initialize()
{
	particleManager = new ParticleManager();

	collision = new Collision();

	readyTextUI = new ReadyTextUI();
	goTextUI = new GoTextUI();
	timeUpUI = new TimeUpUI();

	camera = new Camera();

	characters = new Character*[CHARACTER_AMOUNT]();

	//-----------------------------------------------------------------------------
	// �v���C���[�C���X�^���X
	//-----------------------------------------------------------------------------

	// �v���C���[�C���X�^���X
	characters[0] = new Player(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER));

	//-----------------------------------------------------------------------------
	// �G�C���X�^���X
	//-----------------------------------------------------------------------------

	// �G�l�~�[�C���X�^���X
	for (i = PLAYER_AMOUNT; i < CHARACTER_AMOUNT; i++)
	{
		characters[i] = new Enemy(ModelManager::GetInstance().GetModelHandle(ModelManager::ENEMY), ENEMY_TAG_COLOR_LIST[i - 1]);
	}

	for (i = 0; i < CHARACTER_AMOUNT; i++)
	{
		characters[i]->LoadSE();
	}

	//-----------------------------------------------------------------------------
	// �L�����N�^�[������
	//-----------------------------------------------------------------------------

	VECTOR position = VGet(0, 0, 0);
	float dispositionRadian = PLAYER_DISPOSITION_DEGREE * DX_PI_F / 180.0f;

	for (i = 0; i < CHARACTER_AMOUNT; i++)
	{
		dispositionRadian += CHARACTER_INTERVAL_DEGREE * DX_PI_F / 180.0f * i;
		position.x = CHARACTER_DISPOSITION_RADIUS * cosf(dispositionRadian);
		position.z = CHARACTER_DISPOSITION_RADIUS * sinf(dispositionRadian);
		characters[i]->Initialize(position,particleManager);
	}

	//-----------------------------------------------------------------------------
	// �X�e�[�W�C���X�^���X
	//-----------------------------------------------------------------------------

	stage = new Stage("data/object/Stage.mv1", STAGE_MODEL_POSITION);

	// �g��l�ݒ�
	stage->SetModelScale(STAGE_MODEL_SCALE);

	// ��]�l�ݒ�
	stage->SetModelRotation(STAGE_MODEL_ROTATION);

	//-----------------------------------------------------------------------------
	// �V���h�E�}�b�v�������ݒ�
	//-----------------------------------------------------------------------------

	// �V���h�E�}�b�v�ɕ`�悷��͈͂�ݒ�
	SetShadowMapDrawArea(CharaShadowMap,SHADOW_MAP_DRAW_AREA_MIN, SHADOW_MAP_DRAW_AREA_MAX);
	SetShadowMapDrawArea(StageShadowMap,SHADOW_MAP_DRAW_AREA_MIN, SHADOW_MAP_DRAW_AREA_MAX);

	// �V���h�E�}�b�v���z�肷�郉�C�g�̕������Z�b�g
	SetShadowMapLightDirection(CharaShadowMap, SHADOW_MAP_LIGHT_DIRECTION);
	SetShadowMapLightDirection(StageShadowMap, SHADOW_MAP_LIGHT_DIRECTION);

	// �X�e�[�W���f���p�̃V���h�E�}�b�v�ւ̕`��̏���
	ShadowMap_DrawSetup(StageShadowMap);

	// �X�e�[�W���f���p�̃V���h�E�}�b�v�փX�e�[�W���f���̕`��
	stage->Draw();

	// �X�e�[�W���f���p�̃V���h�E�}�b�v�ւ̕`����I��
	ShadowMap_DrawEnd();

	//-----------------------------------------------------------------------------
	// ���̑��̕ϐ�
	//-----------------------------------------------------------------------------

	readyTextUI->Initialize(LoadGraph("data/image/Main/Ready.png"), 0, 0);

	goTextUI->Initialize(LoadGraph("data/image/Main/Go.png"), 0, 0);

	timeUpUI->Initialize(LoadGraph("data/image/Main/TimeUp.png"), SCREEN_WIDTH, 0);

	// �Q�[���A�N�e�B�u�t���O������
	isGameActive = false;

	// �Q�[���I���t���O������
	isGameEnd = false;

	// �O�t���[���̎��ԏ�����
	prevTimer = GetNowCount();

	// �Q�[���O�̃^�C�}�[������
	prevCount = 0;

	// �^�C�}�[������
	Timer = GAME_TIME;

	// �J�E���g���Z�b�g
	cnt = 0;

	// BGM�Đ�
	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);

	pUpdate = &Main::UpdateStart;

	InformantForAi::GetInstance().Initialize(characters, CHARACTER_AMOUNT);

}

void Main::Finalize()
{
	InitFontToHandle();

	StopSoundMem(bgm);

	InitSoundMem();

	for (i = 0; i < CHARACTER_AMOUNT; i++)
	{
		delete characters[i];
	}

	delete[] characters;

	delete stage;
}

/// �^�C�g���V�[���̍X�V����
void Main::Update()
{
	// �����������
	if (pUpdate != nullptr)
	{
		(this->*pUpdate)(); // ��Ԃ��Ƃ̍X�V����
	}

	frame++;
}

// �X�^�[�g��
void Main::UpdateStart()
{
	readyTextUI->Update(frame);

	if (frame == GAME_START_SE_PLAY_FRAME)
	{
		PlaySoundMem(whistleSE, DX_PLAYTYPE_BACK);
	}

	goTextUI->Update(frame);

	if (frame > GAME_START_FRAME)
	{
		isGameActive = true;
		state = Main::GAME;
		frame = 0;
		pUpdate = &Main::UpdateGame;
	}
}

// �Q�[����
void Main::UpdateGame()
{
	// ���Ԍv�����A��b���Ƃ̏���
	if (GetNowCount() - prevTimer >= 1000)
	{
		// ���݂̎��ԑ��
		prevTimer = GetNowCount();

		// �Q�[�����A�N�e�B�u�Ȃ�^�C�}�[������������
		if (isGameActive)
		{
			Timer--;
		}

		// ���̐��ȉ��ɂȂ�����A�J�E���g�_�E���̉����Đ�����
		if (Timer <= COUNT_DOWN_TIME)
		{
			PlaySoundMem(countDownSE, DX_PLAYTYPE_BACK);
		}
	}

	// �J�����X�V����
	camera->Update();

	//�L�����N�^�[�̍X�V & �X�e�[�W�Ƃ̐ڐG����
	for (i = 0; i < CHARACTER_AMOUNT; i++)
	{
		characters[i]->Update();
		characters[i]->CollisionStage(stage);
		characters[i]->DrawParticle();
	}

	// �p�[�e�B�N���}�l�[�W���[�X�V
	particleManager->Update();

	// �L�����N�^�[�ڐG����
	collision->JudgCollision(characters, CHARACTER_AMOUNT, *camera);

	// �L�����N�^�[���f���p�̃V���h�E�}�b�v�ւ̕`��̏���
	ShadowMap_DrawSetup(CharaShadowMap);

	// �L�����N�^�[���f���p�̃V���h�E�}�b�v�փL�����N�^�[���f���̕`��
	for (i = 0; i < CHARACTER_AMOUNT; i++)
	{
		characters[i]->DrawModel();
	}

	// �L�����N�^�[���f���p�̃V���h�E�}�b�v�ւ̕`����I��
	ShadowMap_DrawEnd();

	// �^�C�}�[��0�̎�
	if (Timer == 0)
	{
		// �z�C�b�X������炷
		PlaySoundMem(whistleSE, DX_PLAYTYPE_BACK);

		// �`���[�W�����~�߂�
		for (i = 0; i < CHARACTER_AMOUNT; i++)
		{
			characters[i]->StopChargeSE();
		}

		// �I�����ɏ�Ԃ�ύX
		state = Main::END;

		// �I���t���O�𗧂Ă�
		isGameEnd = true;

		// �t���[�����Z�b�g
		frame = 0;

		// �|�C���^�X�V
		pUpdate = &Main::UpdateEnd;
	}
}

// �I����
void Main::UpdateEnd()
{
	// TIMEUP�̉摜UI
	timeUpUI->Update(frame);

	// �t���[������萔�o�����烊�U���g�Ɉڍs
	if (frame >= TRANSITION_RESULT_FRAME)
	{
		ResultScore resultScore;

		// �X�R�A���
		for (i = 0; i < CHARACTER_AMOUNT; i++)
		{
			resultScore.AddScore(characters[i]->GetScore(), characters[i]->GetCharaTag());
		}

		// �V�[���ڍs
		mSceneChanger->ChangeScene(resultScene, resultScore);
	}
}

/// �^�C�g���V�[���̕`�揈��
void Main::Draw() {

	// �w�i�`��
	DrawGraph(0, 0, backGround, TRUE);

	// �^�C�}�[�t���[���`��
	DrawGraph(0, 0, timerFrameGraph, TRUE);

	// �`��ɃL�����N�^�[���f���p�̃V���h�E�}�b�v��
	// �X�e�[�W���f���p�̃V���h�E�}�b�v�̂ǂ�����g�p����
	SetUseShadowMap(0, StageShadowMap);
	SetUseShadowMap(1, CharaShadowMap);

	// �X�e�[�W�`��
	stage->Draw();

	// �L�����N�^�[�`��
	for (i = 0; i < CHARACTER_AMOUNT; i++)
	{
		characters[i]->DrawModel();
		characters[i]->DrawScore(0, 0);
		characters[i]->Draw();
	}

	// �`��Ɏg�p����V���h�E�}�b�v�̐ݒ������
	SetUseShadowMap(0, -1);
	SetUseShadowMap(1, -1);

	particleManager->Draw();

	//effectManager->Draw();

	// �p�[�e�B�N���`��
	if (Timer > 0)
	{
		for (i = 0; i < CHARACTER_AMOUNT; i++)
		{
			characters[i]->DrawEffect();
		}
	}

	if (!isGameActive)
	{
		if (frame <= READY_UI_DRAW_FRAME)
			readyTextUI->Draw();
		else
			goTextUI->Draw();
	}

	if (isGameEnd)
	{
		timeUpUI->Draw();
	}

	if (Timer > 5)
		DrawStringToHandle(90, 50, std::to_string(Timer).c_str(), TIMER_COLOR, timerFont, TIMER_EDGE_COLOR);
	else if (Timer != 0)
		DrawStringToHandle(SCREEN_WIDTH / 2 - 45, SCREEN_HEIGHT / 2 - 45, std::to_string(Timer).c_str(), COUNT_DOWN_TIMER_COLOR, timerFont, TIMER_EDGE_COLOR);
}

void Main::InitDemo()
{
	characters = new Character * [CHARACTER_AMOUNT];

	particleManager = new ParticleManager();

	collision = new Collision();

	camera = new Camera();

	//-----------------------------------------------------------------------------
	// �G�C���X�^���X
	//-----------------------------------------------------------------------------

	// �G�l�~�[�z��
	for (i = 0; i < CHARACTER_AMOUNT; i++)
	{
		characters[i] = new Enemy(ModelManager::GetInstance().GetModelHandle(ModelManager::ENEMY), ENEMY_TAG_COLOR_LIST[3]);
	}

	//-----------------------------------------------------------------------------
	// �L�����N�^�[������
	//-----------------------------------------------------------------------------

	VECTOR position = VGet(0, 0, 0);
	float dispositionRadian = PLAYER_DISPOSITION_DEGREE * DX_PI_F / 180.0f;

	for (i = 0; i < CHARACTER_AMOUNT; i++)
	{
		dispositionRadian += CHARACTER_INTERVAL_DEGREE * DX_PI_F / 180.0f * i;
		position.x = CHARACTER_DISPOSITION_RADIUS * cosf(dispositionRadian);
		position.z = CHARACTER_DISPOSITION_RADIUS * sinf(dispositionRadian);
		characters[i]->Initialize(position,particleManager);
	}

	//-----------------------------------------------------------------------------
	// �X�e�[�W�C���X�^���X
	//-----------------------------------------------------------------------------

	stage = new Stage("data/object/Stage.mv1", STAGE_MODEL_POSITION);

	// �g��l�ݒ�
	stage->SetModelScale(STAGE_MODEL_SCALE);

	// ��]�l�ݒ�
	stage->SetModelRotation(STAGE_MODEL_ROTATION);

	//-----------------------------------------------------------------------------
	// ���̑��̕ϐ�
	//-----------------------------------------------------------------------------

	// �Q�[���A�N�e�B�u�t���O������
	isGameActive = false;

	// �Q�[���I���t���O������
	isGameEnd = false;

	// �O�t���[���̎��ԏ�����
	prevTimer = GetNowCount();

	// �Q�[���O�̃^�C�}�[������
	prevCount = 0;

	// �^�C�}�[������
	Timer = GAME_TIME;

	InformantForAi::GetInstance().Initialize(characters, CHARACTER_AMOUNT);

}

void Main::UpdateDemo()
{

	if (GetNowCount() - prevTimer >= 1000)
	{
		prevTimer = GetNowCount();

		if (isGameActive)
			Timer--;
		else
			prevCount++;

		if (Timer == 0)
			cnt = 0;
	}

	if (!isGameActive)
	{
		if (prevCount > 4)
			isGameActive = true;

		return;
	}

	//�L�����N�^�[�̍X�V & �X�e�[�W�Ƃ̐ڐG����
	for (i = 0; i < CHARACTER_AMOUNT; i++)
	{
		characters[i]->Update();
		characters[i]->CollisionStage(stage);
	}

	particleManager->Update();

	// �L�����N�^�[�ڐG����
	collision->JudgCollision(characters, CHARACTER_AMOUNT, *camera);
}

void Main::DrawDemo()
{
	// �w�i�`��
	DrawGraph(0, 0, backGround, TRUE);

	// �X�e�[�W�`��
	stage->Draw();

	// �L�����N�^�[�`��
	for (i = 0; i < CHARACTER_AMOUNT; i++)
	{
		characters[i]->DrawModel();
		characters[i]->DrawScore(0, 0);
		characters[i]->Draw();
	}

	particleManager->Draw();

	// �p�[�e�B�N���`��
	for (i = 0; i < CHARACTER_AMOUNT; i++)
	{
		characters[i]->DrawParticle();
	}
}
