#pragma once

#include "Character.h"

class Player : public Character {
private:
	//定数

	static const float SPEED_ADD;		//スピード

	static const int PUSH_COUNT_MAX;	//押すカウントの最大値

	static const VECTOR MODEL_SCALE;	// モデルのスケールベクトル値
	
	static const double PAD_DEAD_ZONE;	// ジョイパッドのデッドゾーン値

	static const int   INIT_BUTTON_PUSH_COUNT;	// ボタンを押したときのカウント変数初期値

	static const float CHARGE_MOVE_VELOCITY_MIN;	// チャージ移動の速度最低値

	static const float VELOCITY_MIN;			// 移動速度最低値

	static const float VELOCITY_ATTENUATION;	// 速度減衰率

	static const float PAD_ANALOG_INPUT_VELOCITY_MAX;	// パッドのアナログスティックの入力を受け付ける速度

	static const float STAGE_CORRECTION_VELOCITY_MAX;	// ステージ外の補正がかかる速度の最大値

	static const VECTOR SCORE_POSITION_ADJUSTMENT;		// スコア表示位置調整ベクトル
	
	static const int SCORE_POSITION_BETWEEN;		// スコア複数表示の間隔

	// 変数

	// パッド入力による角度
	VECTOR padInputRotation;

	// 垂直ベクトル
	VECTOR verticalVector;

	double rad;

	//ボタンを押した長さのカウント数
	int pushLongButtonCount;

	//ジョイパッドのアナログスティックの左右入力量
	int padAnalogInputX;

	//ジョイパッドのアナログスティックの上下入力量
	int padAnalogInputY;

	//当たり判定の半径
	float collRange;

	//移動する前の自分のベクトルのサイズ
	float positionVectorSize;

	//前のフレームでボタンが押されていたか
	bool prevPushButton;

	//ボタンを離したか
	bool isdetachedButton;

	// 関数

	/// <summary>
	/// 入力処理
	/// </summary>
	void InputAction();

	/// <summary>
	/// 座標計算処理
	/// </summary>
	void CalculationPosition();

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Player(int modelHandle);

	/// <summary>
	/// 仮装デストラクタ
	/// </summary>
	virtual ~Player();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// スコア描画
	/// </summary>
	void DrawScore(int x, int y);

};