#pragma once

// インクルード
#include "Camera.h"

// 前方宣言
class Character;

/// <summary>
/// 衝突判定クラス
/// </summary>
class Collision {
private:

	// 定数

	static const float REVIVE_COLLISION_SPEED;	// 復活時の衝突の速度調整値
	static const float CAMERA_SHAKE_SPEED_NUM;	// カメラを揺らす基準の速度
	static const int   CAMERA_SHAKE_TIME;			// カメラを揺らす時間

	// 変数

	int i, j;	// 汎用ループ変数

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Collision();

	/// <summary>
	/// 接触判定
	/// </summary>
	/// <param name="characters">Character*型 接触判定をするキャラクターのポインタ配列</param>
	/// <param name="size">int型 配列のサイズ</param>
	void JudgCollision(Character* characters[], int size, Camera& camera);
};