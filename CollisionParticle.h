#pragma once

class CollisionParticle {
private:

	// 定数
	static const int   DIRECTION_RAND_SCALE;				// 方向ベクトルの乱数の大きさ
	static const float SPEED_DECREASE;						// 速度減衰
	static const float SIZE_CHANGE;							// サイズ変化量
	static const int PARTICLE_SIZE;							// パーティクル一つ一つの大きさ
	static const int PARTICLE_SIZE_MIN;						// パーティクル最小サイズ
	static const float ANGLE_ADD;							// 回転を加える量
	static const float PARTICLE_ROTATION_BEGIN_VELOCITY;	// 回転を始めるパーティクル自体の速度
	static const float BILLBOARD_CENTER_POSITION_X;			// ビルボード画像の中心X座標
	static const float BILLBOARD_CENTER_POSITION_Y;			// ビルボード画像の中心Y座標

	// 変数
	int graphHandle;      // 画像ハンドル
	VECTOR pos;           // 座標
	VECTOR DirectionsVec; // 移動方向ベクトル
	VECTOR moveVec;       // 移動ベクトル
	float velocity;       // 速度
	float size;           // サイズ
	float sizeMax;        // サイズの最大量
	float angle;          // 回転角度(ラジアン)

	bool isFinish;        // アニメーションを終わらせるか

	bool isVisible;       // 表示されているか
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CollisionParticle();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~CollisionParticle();

	/// <summary>
	/// パーティクルを発射
	/// </summary>
	/// <param name="pos">発射位置の座標</param>
	/// <param name="graphHandle">使用する画像のハンドル</param>
	/// <param name="firstSpeed">初期速度</param>
	void DoParticleFly(VECTOR pos, int graphHandle, float firstSpeed);

	/// <summary>
	/// パーティクルの状態を更新
	/// </summary>
	void Update();

	/// <summary>
	/// パーティクルを描画
	/// </summary>
	void Draw();

	/// <summary>
	/// パーティクルが表示されているかどうかを取得
	/// </summary>
	/// <returns>表示されているかどうか</returns>
	bool IsVisible() const;
};
