#include <DxLib.h>
#include "CollisionParticle.h"

const int   CollisionParticle::DIRECTION_RAND_SCALE = 100;				// 方向ベクトルの乱数の大きさ
const float CollisionParticle::SPEED_DECREASE = 0.15f;					// 速度減衰
const float CollisionParticle::SIZE_CHANGE = 0.3f;						// サイズ変化量
const int	CollisionParticle::PARTICLE_SIZE = 10;						// パーティクル一つ一つの大きさ
const int	CollisionParticle::PARTICLE_SIZE_MIN = 5;					// パーティクル最小サイズ
const float CollisionParticle::ANGLE_ADD = 0.05f;						// 回転を加える量
const float CollisionParticle::PARTICLE_ROTATION_BEGIN_VELOCITY = 2.0f;	// 回転を始めるパーティクル自体の速度
const float CollisionParticle::BILLBOARD_CENTER_POSITION_X = 0.5f;		// ビルボード画像の中心X座標
const float CollisionParticle::BILLBOARD_CENTER_POSITION_Y = 0.5f;		// ビルボード画像の中心Y座標

/// CollisionParticleクラスのコンストラクタ
CollisionParticle::CollisionParticle() 
	: pos(VGet(0, 0, 0))
	, sizeMax((float)GetRand(PARTICLE_SIZE - PARTICLE_SIZE_MIN) + PARTICLE_SIZE_MIN)
	, size(0)
{
}

/// CollisionParticleクラスのデストラクタ
CollisionParticle::~CollisionParticle()
{
}

/// 衝突パーティクルを飛ばす処理
void CollisionParticle::DoParticleFly(VECTOR pos, int graphHandle, float firstSpeed)
{
	// 画像読み込み
	this->graphHandle = graphHandle;

	// 座標
	this->pos = pos;

	// 移動方向ベクトル
	DirectionsVec = VGet((GetRand(DIRECTION_RAND_SCALE * 2) - DIRECTION_RAND_SCALE) / 100.0f, 
						 (GetRand(DIRECTION_RAND_SCALE)) / 100.0f, 
						 (GetRand(DIRECTION_RAND_SCALE * 2) - DIRECTION_RAND_SCALE) / 100.0f);

	// 正規化
	if (VSize(DirectionsVec) > 0)
	{
		DirectionsVec = VNorm(DirectionsVec);
	}

	// 移動ベクトル
	moveVec = VGet(0, 0, 0);

	// 速度
	velocity = firstSpeed;

	// 回転率
	angle = 0;

	// 終了フラグ初期化
	isFinish = false;

	// 表示フラグを立てる
	isVisible = true;
}

/// 衝突パーティクルの状態を更新する
void CollisionParticle::Update()
{
	// 移動ベクトル計算
	moveVec = VScale(DirectionsVec, velocity);

	// 移動
	pos = VAdd(pos, moveVec);

	// 速度減衰
	if (velocity > 0)
	{
		velocity -= SPEED_DECREASE;
	}
	else
	{
		velocity = 0;
	}

	// サイズが最大サイズになったら、切り替えフラグを立てる
	if (size >= sizeMax)
	{
		isFinish = true;
	}

	// サイズ変位
	size += SIZE_CHANGE * (isFinish ? -1 : 1);

	// パーティクルの消失判定
	if (isFinish && size <= 0)
	{
		isVisible = false;
		size = 0;
	}

	// 速度が一定以下なら回転
	if (velocity < PARTICLE_ROTATION_BEGIN_VELOCITY)
		angle += ANGLE_ADD;
}

/// 衝突パーティクルを描画する
void CollisionParticle::Draw()
{
	// 表示フラグが立っているなら描画
	if (isVisible)
	{
		DrawBillboard3D(pos, BILLBOARD_CENTER_POSITION_X, BILLBOARD_CENTER_POSITION_Y, size, angle, graphHandle, TRUE);
	}
}

/// 衝突パーティクルの表示状態を取得する
bool CollisionParticle::IsVisible() const
{
	return isVisible;
}