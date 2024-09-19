#pragma once

// インクルード
#include "BaseScene.h"
#include "Screen.h"

// 前方宣言
class Collision;
class Camera;
class ReadyTextUI;
class GoTextUI;
class TimeUpUI;
class Character;
class ParticleManager;
class Stage;
struct Color_st;

// ゲーム画面クラス
class Main : public BaseScene {
private:

	// ゲーム状態を表す列挙体
	enum State
	{
		BEFORE_GAME,
		GAME,
		END,
	};

	// 定数

	static const int	  PLAYER_AMOUNT;                // プレイヤーの数
	static const int	  ENEMY_AMOUNT;                 // 敵の数
	static const int	  CHARACTER_AMOUNT;             // キャラ数合計
	static const Color_st ENEMY_TAG_COLOR_LIST[];		// 敵のタグのカラー情報の構造体配列
	static const float	  CHARACTER_DISPOSITION_RADIUS; // キャラを配置する中心からの半径
	static const float	  PLAYER_DISPOSITION_DEGREE;    // プレイヤーを配置する原点からの角度
	static const float	  CHARACTER_INTERVAL_DEGREE;    // キャラ間の配置間隔(度)

	static const VECTOR	  STAGE_MODEL_POSITION;			// ステージモデル位置座標
	static const VECTOR	  STAGE_MODEL_SCALE;			// ステージモデルスケール値
	static const VECTOR	  STAGE_MODEL_ROTATION;			// ステージモデル回転値

	static const int	  SHADOW_MAP_SIZE;				// シャドウマップサイズ
	static const VECTOR	  SHADOW_MAP_DRAW_AREA_MIN;		// シャドウマップの描画範囲座標の小さいほうの頂点座標
	static const VECTOR	  SHADOW_MAP_DRAW_AREA_MAX;		// シャドウマップの描画範囲座標の大きいほうの頂点座標
	static const VECTOR	  SHADOW_MAP_LIGHT_DIRECTION;	// シャドウマップのライトの方向

	static const int	  GAME_TIME;					// ゲームタイム
	static const int	  GAME_START_SE_PLAY_FRAME;		// ゲームスタート時のSEを鳴らすフレーム数
	static const int	  GAME_START_FRAME;				// ゲームスタートのフレーム数
	static const int	  COUNT_DOWN_TIME;				// カウントダウンを始めるタイム
	static const int	  TRANSITION_RESULT_FRAME;		// リザルトに移行するフレーム数
	static const int	  READY_UI_DRAW_FRAME;			// ReadyUIを描画するフレーム数

	static const unsigned int TIMER_COLOR;				// タイマー文字カラー
	static const unsigned int COUNT_DOWN_TIMER_COLOR;	// カウントダウンタイマー文字カラー
	static const unsigned int TIMER_EDGE_COLOR;			// タイマー文字の縁取りカラー
	static const int	  TIMER_FONT_EDGE_SIZE;			// タイマーフォントの縁取りサイズ

	// 変数

	int i;	// ループ用変数

	State				state;				// ゲーム状態変数
	Character**			characters;			// キャラクター
	ParticleManager*	particleManager;	// パーティクルマネージャー
	Collision*			collision;			// コリジョン
	Stage*				stage;				// ステージ
	Camera*				camera;				// カメラ

	int backGround;			// 背景画像
	int timerFrameGraph;	// タイマーフレーム画像

	int timerFont;	// タイマーフォント

	int bgm;			// BGMハンドル
	int whistleSE;		// ホイッスルSE
	int countDownSE;	// カウントダウンSE

	int CharaShadowMap;	// キャラクターのシャドウマップハンドル
	int StageShadowMap;	// ステージのシャドウマップハンドル

	ReadyTextUI*	readyTextUI;	// ReadyテキストUI
	GoTextUI*		goTextUI;		// GoテキストUI
	TimeUpUI*		timeUpUI;		// TimeUpテキストUI

	int frame;			// フレーム
	int cnt;			// カウント
	int Timer;			// タイマー
	int prevTimer;		// 前フレームの時間
	int prevCount;		// ゲーム前のタイマーカウンタ
	bool isGameActive;	// ゲームアクティブフラグ
	bool isGameEnd;		// ゲーム終了フラグ
	
	void UpdateStart();			// スタート時
	void UpdateGame();			// ゲーム中
	void UpdateEnd();			// 終了時
	void (Main::* pUpdate)();	// Update関数ポインタ

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="changer">シーン切り替えインターフェース</param>
	Main(ISceneChanger* changer);

	/// <summary>
	/// デストラクタ
	/// </summary>
	Main();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize() override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	/// <summary>
	/// デモプレイ時の初期化
	/// </summary>
	void InitDemo();

	/// <summary>
	/// デモプレイ時の更新
	/// </summary>
	void UpdateDemo();

	/// <summary>
	/// デモプレイ時の描画
	/// </summary>
	void DrawDemo();
};