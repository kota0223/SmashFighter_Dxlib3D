#include "Stage.h"

//定数定義

const float Stage::RANGE = 80.0f;	//ステージ範囲の半径

Stage::Stage(const std::string filePath, VECTOR position)
	: position(position)
{
	// モデルハンドル読み込み
	modelHandle = MV1LoadModel(filePath.c_str());

	// 座標設定
	MV1SetPosition(modelHandle, position);
}

Stage::~Stage()
{
	MV1DeleteModel(modelHandle);
}

void Stage::Draw()
{
	//ステージの描画
	MV1DrawModel(modelHandle);
}