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

// 定数

const int Main::PLAYER_AMOUNT = 1;									// プレイヤーの数				
const int Main::ENEMY_AMOUNT = 3;									// 敵の数
const int Main::CHARACTER_AMOUNT = PLAYER_AMOUNT+ENEMY_AMOUNT;		// キャラ数合計
const Color_st Main::ENEMY_TAG_COLOR_LIST[] = { {255, 0  , 255 },
												{0  , 255, 255 },
												{0  , 255, 0   },
												{255, 255, 255 } }; // 敵のタグのカラー情報の構造体配列

const float Main::CHARACTER_DISPOSITION_RADIUS = 70.0f;				// キャラを配置する中心からの半径
const float Main::PLAYER_DISPOSITION_DEGREE = 270.0f;				// プレイヤーを配置する原点からの角度
const float Main::CHARACTER_INTERVAL_DEGREE = 90.0f;				// キャラ間の配置間隔(度)

const VECTOR Main::STAGE_MODEL_POSITION = VGet(0, -17, 0);							// ステージモデル位置座標
const VECTOR Main::STAGE_MODEL_SCALE = VGet(3.7f, 3.7f, 3.7f);							// ステージモデルスケール値
const VECTOR Main::STAGE_MODEL_ROTATION = VGet(90.0 * DX_PI_F / 180.0, 0.0, 0.0);	// ステージモデル回転値

const int Main::SHADOW_MAP_SIZE = 512;												// シャドウマップサイズ
const VECTOR Main::SHADOW_MAP_DRAW_AREA_MIN = VGet(-90.0f, -6.0f, -90.0f);			// シャドウマップの描画範囲座標の小さいほうの頂点座標
const VECTOR Main::SHADOW_MAP_DRAW_AREA_MAX = VGet(90.0f, 20.0f, 90.0f);			// シャドウマップの描画範囲座標の大きいほうの頂点座標
const VECTOR Main::SHADOW_MAP_LIGHT_DIRECTION = VGet(0.0f, -1.0f, 0.0f);			// シャドウマップのライトの方向

const int Main::GAME_TIME = 60;						// ゲームタイム
const int Main::GAME_START_SE_PLAY_FRAME = 3 * 60;	// ゲームスタート時のSEを鳴らすフレーム数
const int Main::GAME_START_FRAME = 4 * 60;			// ゲームスタートのフレーム数
const int Main::COUNT_DOWN_TIME = 5;				// カウントダウンを始めるタイム
const int Main::TRANSITION_RESULT_FRAME = 60 * 4;	// リザルトに移行するフレーム数
const int Main::READY_UI_DRAW_FRAME = 3 * 60;		// ReadyUIを描画するフレーム数

const unsigned int Main::TIMER_COLOR = GetColor(240, 145, 62);				// タイマー文字カラー
const unsigned int Main::COUNT_DOWN_TIMER_COLOR = GetColor(247, 68, 27);	// カウントダウンタイマー文字カラー
const unsigned int Main::TIMER_EDGE_COLOR = GetColor(255, 255, 255);		// タイマー文字の縁取りカラー
const int Main::TIMER_FONT_EDGE_SIZE = 3;									// タイマーフォントの縁取りサイズ


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
	// 背景画像
	backGround = LoadGraph("data/image/BackGrounds/BackGround.png");

	// タイマーフレーム画像
	timerFrameGraph = LoadGraph("data/image/Main/TimerFrame.png");

	// フォントファイル読み込み
	timerFont = LoadFontDataToHandle("data/fonts/Arial Black.dft", TIMER_FONT_EDGE_SIZE);

	bgm = LoadSoundMem("data/sounds/Main/bgm.mp3");

	whistleSE = LoadSoundMem("data/sounds/Main/whistle.mp3");

	countDownSE = LoadSoundMem("data/sounds/Main/countDown.mp3");

	// キャラクターモデル用のシャドウマップハンドルの作成
	CharaShadowMap = MakeShadowMap(SHADOW_MAP_SIZE, SHADOW_MAP_SIZE);

	// ステージモデル用のシャドウマップハンドルの作成
	StageShadowMap = MakeShadowMap(SHADOW_MAP_SIZE, SHADOW_MAP_SIZE);

	int texhandle = LoadGraph("data/shader/texture/hitEffect1.png");

	// 使用するテクスチャを０番にセット
	SetUseTextureToShader(0, texhandle);

	// テクスチャのアドレスモード変更
	SetTextureAddressMode(DX_TEXADDRESS_WRAP);
}

Main::Main()
{
	// 背景画像
	backGround = LoadGraph("data/image/BackGrounds/BackGround.png");
}

/// タイトルシーンの初期化処理
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
	// プレイヤーインスタンス
	//-----------------------------------------------------------------------------

	// プレイヤーインスタンス
	characters[0] = new Player(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER));

	//-----------------------------------------------------------------------------
	// 敵インスタンス
	//-----------------------------------------------------------------------------

	// エネミーインスタンス
	for (i = PLAYER_AMOUNT; i < CHARACTER_AMOUNT; i++)
	{
		characters[i] = new Enemy(ModelManager::GetInstance().GetModelHandle(ModelManager::ENEMY), ENEMY_TAG_COLOR_LIST[i - 1]);
	}

	for (i = 0; i < CHARACTER_AMOUNT; i++)
	{
		characters[i]->LoadSE();
	}

	//-----------------------------------------------------------------------------
	// キャラクター初期化
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
	// ステージインスタンス
	//-----------------------------------------------------------------------------

	stage = new Stage("data/object/Stage.mv1", STAGE_MODEL_POSITION);

	// 拡大値設定
	stage->SetModelScale(STAGE_MODEL_SCALE);

	// 回転値設定
	stage->SetModelRotation(STAGE_MODEL_ROTATION);

	//-----------------------------------------------------------------------------
	// シャドウマップ初期化設定
	//-----------------------------------------------------------------------------

	// シャドウマップに描画する範囲を設定
	SetShadowMapDrawArea(CharaShadowMap,SHADOW_MAP_DRAW_AREA_MIN, SHADOW_MAP_DRAW_AREA_MAX);
	SetShadowMapDrawArea(StageShadowMap,SHADOW_MAP_DRAW_AREA_MIN, SHADOW_MAP_DRAW_AREA_MAX);

	// シャドウマップが想定するライトの方向もセット
	SetShadowMapLightDirection(CharaShadowMap, SHADOW_MAP_LIGHT_DIRECTION);
	SetShadowMapLightDirection(StageShadowMap, SHADOW_MAP_LIGHT_DIRECTION);

	// ステージモデル用のシャドウマップへの描画の準備
	ShadowMap_DrawSetup(StageShadowMap);

	// ステージモデル用のシャドウマップへステージモデルの描画
	stage->Draw();

	// ステージモデル用のシャドウマップへの描画を終了
	ShadowMap_DrawEnd();

	//-----------------------------------------------------------------------------
	// その他の変数
	//-----------------------------------------------------------------------------

	readyTextUI->Initialize(LoadGraph("data/image/Main/Ready.png"), 0, 0);

	goTextUI->Initialize(LoadGraph("data/image/Main/Go.png"), 0, 0);

	timeUpUI->Initialize(LoadGraph("data/image/Main/TimeUp.png"), SCREEN_WIDTH, 0);

	// ゲームアクティブフラグ初期化
	isGameActive = false;

	// ゲーム終了フラグ初期化
	isGameEnd = false;

	// 前フレームの時間初期化
	prevTimer = GetNowCount();

	// ゲーム前のタイマー初期化
	prevCount = 0;

	// タイマー初期化
	Timer = GAME_TIME;

	// カウントリセット
	cnt = 0;

	// BGM再生
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

/// タイトルシーンの更新処理
void Main::Update()
{
	// 処理があれば
	if (pUpdate != nullptr)
	{
		(this->*pUpdate)(); // 状態ごとの更新処理
	}

	frame++;
}

// スタート時
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

// ゲーム中
void Main::UpdateGame()
{
	// 時間計測し、一秒ごとの処理
	if (GetNowCount() - prevTimer >= 1000)
	{
		// 現在の時間代入
		prevTimer = GetNowCount();

		// ゲームがアクティブならタイマーを減少させる
		if (isGameActive)
		{
			Timer--;
		}

		// 一定の数以下になったら、カウントダウンの音を再生する
		if (Timer <= COUNT_DOWN_TIME)
		{
			PlaySoundMem(countDownSE, DX_PLAYTYPE_BACK);
		}
	}

	// カメラ更新処理
	camera->Update();

	//キャラクターの更新 & ステージとの接触判定
	for (i = 0; i < CHARACTER_AMOUNT; i++)
	{
		characters[i]->Update();
		characters[i]->CollisionStage(stage);
		characters[i]->DrawParticle();
	}

	// パーティクルマネージャー更新
	particleManager->Update();

	// キャラクター接触判定
	collision->JudgCollision(characters, CHARACTER_AMOUNT, *camera);

	// キャラクターモデル用のシャドウマップへの描画の準備
	ShadowMap_DrawSetup(CharaShadowMap);

	// キャラクターモデル用のシャドウマップへキャラクターモデルの描画
	for (i = 0; i < CHARACTER_AMOUNT; i++)
	{
		characters[i]->DrawModel();
	}

	// キャラクターモデル用のシャドウマップへの描画を終了
	ShadowMap_DrawEnd();

	// タイマーが0の時
	if (Timer == 0)
	{
		// ホイッスル音を鳴らす
		PlaySoundMem(whistleSE, DX_PLAYTYPE_BACK);

		// チャージ音を止める
		for (i = 0; i < CHARACTER_AMOUNT; i++)
		{
			characters[i]->StopChargeSE();
		}

		// 終了時に状態を変更
		state = Main::END;

		// 終了フラグを立てる
		isGameEnd = true;

		// フレームリセット
		frame = 0;

		// ポインタ更新
		pUpdate = &Main::UpdateEnd;
	}
}

// 終了時
void Main::UpdateEnd()
{
	// TIMEUPの画像UI
	timeUpUI->Update(frame);

	// フレームが一定数経ったらリザルトに移行
	if (frame >= TRANSITION_RESULT_FRAME)
	{
		ResultScore resultScore;

		// スコア代入
		for (i = 0; i < CHARACTER_AMOUNT; i++)
		{
			resultScore.AddScore(characters[i]->GetScore(), characters[i]->GetCharaTag());
		}

		// シーン移行
		mSceneChanger->ChangeScene(resultScene, resultScore);
	}
}

/// タイトルシーンの描画処理
void Main::Draw() {

	// 背景描画
	DrawGraph(0, 0, backGround, TRUE);

	// タイマーフレーム描画
	DrawGraph(0, 0, timerFrameGraph, TRUE);

	// 描画にキャラクターモデル用のシャドウマップと
	// ステージモデル用のシャドウマップのどちらも使用する
	SetUseShadowMap(0, StageShadowMap);
	SetUseShadowMap(1, CharaShadowMap);

	// ステージ描画
	stage->Draw();

	// キャラクター描画
	for (i = 0; i < CHARACTER_AMOUNT; i++)
	{
		characters[i]->DrawModel();
		characters[i]->DrawScore(0, 0);
		characters[i]->Draw();
	}

	// 描画に使用するシャドウマップの設定を解除
	SetUseShadowMap(0, -1);
	SetUseShadowMap(1, -1);

	particleManager->Draw();

	//effectManager->Draw();

	// パーティクル描画
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
	// 敵インスタンス
	//-----------------------------------------------------------------------------

	// エネミー配列
	for (i = 0; i < CHARACTER_AMOUNT; i++)
	{
		characters[i] = new Enemy(ModelManager::GetInstance().GetModelHandle(ModelManager::ENEMY), ENEMY_TAG_COLOR_LIST[3]);
	}

	//-----------------------------------------------------------------------------
	// キャラクター初期化
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
	// ステージインスタンス
	//-----------------------------------------------------------------------------

	stage = new Stage("data/object/Stage.mv1", STAGE_MODEL_POSITION);

	// 拡大値設定
	stage->SetModelScale(STAGE_MODEL_SCALE);

	// 回転値設定
	stage->SetModelRotation(STAGE_MODEL_ROTATION);

	//-----------------------------------------------------------------------------
	// その他の変数
	//-----------------------------------------------------------------------------

	// ゲームアクティブフラグ初期化
	isGameActive = false;

	// ゲーム終了フラグ初期化
	isGameEnd = false;

	// 前フレームの時間初期化
	prevTimer = GetNowCount();

	// ゲーム前のタイマー初期化
	prevCount = 0;

	// タイマー初期化
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

	//キャラクターの更新 & ステージとの接触判定
	for (i = 0; i < CHARACTER_AMOUNT; i++)
	{
		characters[i]->Update();
		characters[i]->CollisionStage(stage);
	}

	particleManager->Update();

	// キャラクター接触判定
	collision->JudgCollision(characters, CHARACTER_AMOUNT, *camera);
}

void Main::DrawDemo()
{
	// 背景描画
	DrawGraph(0, 0, backGround, TRUE);

	// ステージ描画
	stage->Draw();

	// キャラクター描画
	for (i = 0; i < CHARACTER_AMOUNT; i++)
	{
		characters[i]->DrawModel();
		characters[i]->DrawScore(0, 0);
		characters[i]->Draw();
	}

	particleManager->Draw();

	// パーティクル描画
	for (i = 0; i < CHARACTER_AMOUNT; i++)
	{
		characters[i]->DrawParticle();
	}
}
