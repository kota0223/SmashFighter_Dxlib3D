#pragma once

// インクルード
#include "DxLib.h"

/// <summary>
/// カメラクラス
/// </summary>
class Camera {
private:

	// 定数
	static const float CAMERA_POSITION_SHAKE_SCALE;	// カメラポジションの揺れの大きさ
	static const float CAMERA_TARGET_SHAKE_SCALE;	// カメラターゲットの揺れの大きさ
	static const float SHAKE_WIDTH;					// 揺れの幅
	static const float NEAR_DISTANCE;				// カメラに映る手前の範囲
	static const float FAR_DISTANCE;				// カメラに映る最奥の範囲
	static const int   SHAKE_INTERVAL;				// 揺らす間隔のタイム

	// 変数
	int shakeTime;	// カメラを揺らす時間

public:

	static const VECTOR INIT_POSITION;				// カメラ初期位置

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Camera();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Camera();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 揺らす時間をセットする
	/// </summary>
	/// <param name="time"></param>
	void SetShakeTime(int time)
	{
		shakeTime = time;
	}
};