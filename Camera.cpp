
// インクルード
#include <math.h>
#include "Camera.h"

// 定数
const VECTOR Camera::INIT_POSITION = VGet(0, 130, -130);	// カメラ初期位置
const float	 Camera::CAMERA_POSITION_SHAKE_SCALE = 0.05f;	// カメラポジションの揺れの大きさ
const float  Camera::CAMERA_TARGET_SHAKE_SCALE = 0.10f;		// カメラターゲットの揺れの大きさ
const float  Camera::SHAKE_WIDTH = 20.0f;					// 揺れの幅
const float  Camera::NEAR_DISTANCE = 0.1f;					// カメラに映る手前の範囲
const float  Camera::FAR_DISTANCE = 1000.0f;				// カメラに映る最奥の範囲
const int    Camera::SHAKE_INTERVAL = 4;					// 揺らす間隔のタイム

// コンストラクタ
Camera::Camera()
{
	// 変数初期化
	shakeTime = 0;

	//奥行0.1～1000までをカメラの描画範囲とする
	SetCameraNearFar(NEAR_DISTANCE, FAR_DISTANCE);

	//(0, 20, -100)の視点から(0.0f, 20.0f, 0.0f)のターゲットを見る角度にカメラを設置
	SetCameraPositionAndTarget_UpVecY(INIT_POSITION, VGet(0.0f, 0.0f, 0.0f));
}

// デストラクタ
Camera::~Camera()
{
	// 処理なし
}

// 更新
void Camera::Update()
{
	if (shakeTime > 0)
	{
		shakeTime--;

		// 一定数の感覚で揺らす
		if (shakeTime % SHAKE_INTERVAL == 0)
		{
			VECTOR shakePos = VAdd(INIT_POSITION, VGet(cosf(DX_TWO_PI_F / SHAKE_WIDTH * shakeTime) * shakeTime* CAMERA_POSITION_SHAKE_SCALE,
									0, sinf(DX_TWO_PI_F / SHAKE_WIDTH * shakeTime) * shakeTime* CAMERA_POSITION_SHAKE_SCALE));

			SetCameraPositionAndTarget_UpVecY(shakePos, VGet(cosf(DX_TWO_PI_F / SHAKE_WIDTH * shakeTime) * shakeTime* CAMERA_TARGET_SHAKE_SCALE,
									0, sinf(DX_TWO_PI_F / SHAKE_WIDTH * shakeTime) * shakeTime* CAMERA_TARGET_SHAKE_SCALE));
		}
	}
	else
	{
		SetCameraPositionAndTarget_UpVecY(INIT_POSITION, VGet(0.000f, 0.000f, 0.000f));
	}
}
