#pragma once

#include <DxLib.h>
#include <string>

class Stage {
private:
	//定数

	static const float RANGE;	//ステージの範囲の半径

	//変数

	VECTOR position;	//ステージの中心座標

	int modelHandle;	//ステージのモデルハンドル

	float range;		//ステージの範囲の半径

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Stage(const std::string filePath, VECTOR position);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Stage();

	/// <summary>
	/// ステージを描画
	/// </summary>
	void Draw();

	/// <summary>
	/// ステージの半径を取得
	/// </summary>
	/// <returns>Float ステージの半径</returns>
	const float GetRange() const { return RANGE; }

	/// <summary>
	/// ステージの座標を取得
	/// </summary>
	/// <returns>VECTOR型 ステージの座標</returns>
	const VECTOR GetPosition() const{ return position; }

	/// <summary>
	/// モデルの拡大率を設定
	/// </summary>
	/// <param name="scale">VECTOR型 モデルの拡大率</param>
	void SetModelScale(const VECTOR scale) { MV1SetScale(modelHandle, scale); }

	/// <summary>
	/// モデルの回転値を設定
	/// </summary>
	/// <param name="rotation">VECTOR型 モデルの回転値</param>
	void SetModelRotation(const VECTOR rotation) { MV1SetRotationXYZ(modelHandle, rotation); }
};