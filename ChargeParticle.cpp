#include <DxLib.h>
#include <math.h>
#include "ChargeParticle.h"

const float	 ChargeParticle::SPEED_DECREASE = 0.01f;					// 速度減衰

const int	 ChargeParticle::DIRECTION_RAND_SCALE = 100;				// 方向ベクトルの乱数の大きさ

const VECTOR ChargeParticle::GRAPH_SCALE_CHARGED = VGet(0.1f, 0.6f, 0);	// チャージ後の画像スケール値
const VECTOR ChargeParticle::GRAPH_SCALE = VGet(0.15f, 0.15f, 0);		// 画像のスケール値

const float  ChargeParticle::INIT_SCALE_X = 0.9f;						// scaleX変数の初期値
const float  ChargeParticle::INIT_SCALE_Y = 1.1f;						// scaleY変数の初期値

const float	 ChargeParticle::INIT_SCALE_X_CHARGED = 1.0f;				// チャージ後のscaleX変数の初期値
const float	 ChargeParticle::INIT_SCALE_Y_CHARGED = 0.9f;				// チャージ後のscaleY変数の初期値

const float  ChargeParticle::CHARGED_SCALE_MAX = 1.5f;					// チャージ後のスケール上限値
const float  ChargeParticle::CHARGED_SCALE_ADD_AMOUNT = 1.1f;			// チャージ後のスケール増加値

const float  ChargeParticle::PARTICLE_HIDDEN_SCALE_Y_MIN = 0.5f;		// パーティクルを非表示にするスケールのY座標最低値
const float  ChargeParticle::PARTICLE_HIDDEN_CROSS_MIN = 1.0f;			// パーティクルを非表示にする外積の最低値

ChargeParticle::ChargeParticle() :pos(VGet(0, 0, 0))
{
}

ChargeParticle::~ChargeParticle()
{
}

void ChargeParticle::DoParticleFly(VECTOR pos, VECTOR cameraPos, int graphHandle, float firstSpeed, float range, bool isCharged)
{
	//画像読み込み
	this->graphHandle = graphHandle;

	// 原点保存
	origin = pos;

	//移動方向ベクトル
	DirectionsVec = VGet((GetRand(DIRECTION_RAND_SCALE * 2) - DIRECTION_RAND_SCALE) / 100.0f, pos.y, (GetRand(DIRECTION_RAND_SCALE * 2) - DIRECTION_RAND_SCALE) / 100.0f);

	//正規化
	if (VSize(DirectionsVec) > 0)
	{
		DirectionsVec = VNorm(DirectionsVec);
	}

	VECTOR screenPos1 = ConvWorldPosToScreenPos(VAdd(origin, VScale(DirectionsVec, range)));
	VECTOR screenPos2 = ConvWorldPosToScreenPos(origin);
	VECTOR angleVector = VGet(screenPos1.x - screenPos2.x, screenPos1.y - screenPos2.y, 0);

	//回転率
	angle = -atan2f(angleVector.y, angleVector.x) - DX_PI_F / 2;

	//座標
	this->pos = VAdd(origin,VScale(DirectionsVec, range));

	//移動ベクトル
	moveVec = VGet(0, 0, 0);

	//速度
	velocity = firstSpeed;

	//表示フラグを立てる
	isVisible = true;

	// チャージ後フラグを代入
	this->isCharged = isCharged;

	// 単位行列を代入
	MATRIX transMat = MGetIdent();

	// 拡大行列を掛ける
	if (isCharged)
	{
		transMat = MMult(transMat, MGetScale(GRAPH_SCALE_CHARGED));
	}
	else
	{
		transMat = MMult(transMat, MGetScale(GRAPH_SCALE));
	}

	// 行列による座標変換
	for (int i = 0; i < 4; i++)
	{
		graphPosScale[i] = VTransform(graphPosScale[i], transMat);
	}

	// 水平ベクトルを算出
	horizonVector = VTransform(DirectionsVec, MGetRotY(-DX_PI_F / 2.0));

	if (isCharged)
	{
		scaleX = INIT_SCALE_X_CHARGED;
		scaleY = INIT_SCALE_Y_CHARGED;
	}
	else
	{
		scaleX = INIT_SCALE_X;
		scaleY = INIT_SCALE_Y;
	}
}

void ChargeParticle::Update()
{
	// 表示フラグが立っていないなら処理をしない
	if (!isVisible)
	{
		return;
	}

	// 移動ベクトル計算
	moveVec = VScale(DirectionsVec, velocity);

	//速度減衰
	if (velocity > 0)
	{
		velocity -= SPEED_DECREASE;
	}
	else
	{
		velocity = 0;
	}

	if (isCharged)
	{
		if (fabs(graphPosScale[0].x) < CHARGED_SCALE_MAX)
		{
			scaleX = CHARGED_SCALE_ADD_AMOUNT;
		}
		else
		{
			scaleX = 1.0;
		}
	}

	// 拡大行列
	MATRIX transMat = MMult(MGetIdent(), MGetScale(VGet(scaleX, scaleY, 0)));

	//// 回転行列を求める
	MATRIX transRotationMat = MMult(MGetIdent(), MGetRotZ(angle));

	// 行列による座標変換
	for (int i = 0; i < 4; i++)
	{
		// 拡大縮小による変形
		graphPosScale[i] = VTransform(graphPosScale[i], transMat);
		 
		// 拡大縮小の変形をさせた画像を回転させる
		graphPos[i] = VTransform(graphPosScale[i], transRotationMat);
	}

	//移動
	if (isCharged)
	{
		pos = VAdd(pos, moveVec);

		if (graphPosScale[0].y <= PARTICLE_HIDDEN_SCALE_Y_MIN)
		{
			isVisible = false;
		}
	}
	else
	{
		pos = VSub(pos, moveVec);

		// 垂直ベクトルを算出
		verticalVector = VSub(pos, origin);

		// 外積ベクトルのy値が一定以下なら表示フラグを下す
		if (VCross(horizonVector, verticalVector).y <= PARTICLE_HIDDEN_CROSS_MIN)
		{
			isVisible = false;
		}
	}
}

void ChargeParticle::Draw()
{
	// 表示フラグが立って居たら表示
	if (isVisible)
	{
		DrawModiBillboard3D(pos
			, graphPos[0].x, graphPos[0].y
			, graphPos[1].x, graphPos[1].y
			, graphPos[2].x, graphPos[2].y
			, graphPos[3].x, graphPos[3].y
			, graphHandle, TRUE);
	}
}

bool ChargeParticle::IsVisible() const
{
	return isVisible;
}