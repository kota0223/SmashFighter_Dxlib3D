#pragma once

#include "Character.h"

// 敵行動状態の列挙体
enum State_e
{
	none,	// 行動未設定
	move,	// 移動中
	attack	// 攻撃中
};

class Player;

// 敵クラス
class Enemy : public Character {
private:

	// 定数

	static const float	SPEED_ADD;						// スピード

	static const float	VELOCITY_MINIMUM;				// 速度最低値

	static const VECTOR MODEL_SCALE;					// モデルの拡大値

	static const float	ATTENUATION_COEFFICIENT;		// 減衰係数

	static const float	STAGE_RANGE;					// ステージ範囲

	static const float	CORRECTION_POSSIBLE_SPEED;		// 補正可能な速度
	static const float  CORRECTION_RANGE;				// 補正する半径の大きさ

	static const VECTOR SCORE_POSITION_ADJUSTMENT;		// スコア表示位置を調整する値
	static const int	SCORE_DRAW_POSITION_INTERVAL;	// スコアの表示位置間隔

	static const int	ACTION_RANDOM_MAX;				// 行動乱数最大値

	static const int	ATTACK_MAX_COUNT;				// 攻撃カウント最大値
	static const float	ATTACK_VELOCITY;				// 攻撃時の速度
	static const float	ATTACK_ATTENUATION_COEFFICIENT;	// 攻撃時の速度減衰係数

	static const float	ROTATE_ADD_SCALE;				// 増加させる回転のスケール値

	static const float	CIRCLE_ANGLE;					// 円の角度

	static const float	MOVE_CIRCLE_RADIUS;				// 移動する円の半径
	static const float	MOVE_ROTATE_ANGLE;				// 移動する角度値
	static const float	MOVE_SCALE_RADIUS;				// 移動時の半径の大きさ
	static const float	MOVE_VELOCITY_SCALE;			// 移動時の速度の大きさ

	static const float  CHARGE_MOVE_MIN_SPEED;			// チャージ移動の速度最低値

	// 変数宣言

	static int EnemyNum;	// エネミーのインスタンス数

	int Number;				// インスタンス番号

	VECTOR aimPosition;		// 移動先のベクトル

	VECTOR moveRotation;	// 移動後の回転ベクトル

	VECTOR cross;			// 外積ベクトル

	Character* target;		//ターゲットに設定するCharacterクラスのポインタ変数

	State_e actState;		// 敵行動状態の列挙体変数

	int attackActCount;		// 攻撃行動時のカウント

	int i, j;				//汎用ループ変数

	// デバッグ用行動表示変数
	const char* actStatePrint[3] = { "無し","行動","攻撃" };

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Enemy(int modelHandle,const Color_st &tagColor);

	/// <summary>
	/// 仮装デストラクタ
	/// </summary>
	virtual ~Enemy();

	/// <summary>
	/// 状態の更新
	/// </summary>
	void Update();

	/// <summary>
	/// スコア描画
	/// </summary>
	void DrawScore(int x, int y);

	/// <summary>
	/// 敵の行動を設定
	/// </summary>
	/// <param name="characters">Character*型 接触判定をするキャラクターのポインタ配列</param>
	/// <param name="size">int型 配列のサイズ</param>
	void SetAction();

	/// <summary>
	/// 攻撃状態のセット
	/// </summary>
	/// <param name="characters">Character*型 接触判定をするキャラクターのポインタ配列</param>
	/// <param name="size">int型 配列のサイズ</param>
	void SetActAttack();

	/// <summary>
	/// 攻撃行動
	/// </summary>
	/// <param name="characters">Character*型 接触判定をするキャラクターのポインタ配列</param>
	/// <param name="size">int型 配列のサイズ</param>
	void ActAttack();

	/// <summary>
	/// 移動状態のセット
	/// </summary>
	void SetActMove();

	/// <summary>
	/// 移動する
	/// </summary>
	void ActMove();
};