#pragma once

class ChargeParticle{
private:
	//定数
	static const float	SPEED_DECREASE;					// 速度減衰

	static const int	DIRECTION_RAND_SCALE;			// 方向ベクトルの乱数の大きさ

	static const VECTOR	GRAPH_SCALE_CHARGED;			// チャージ後の画像スケール値
	static const VECTOR GRAPH_SCALE;					// 画像のスケール値

	static const float	INIT_SCALE_X;					// scaleX変数の初期値
	static const float	INIT_SCALE_Y;					// scaleY変数の初期値

	static const float	INIT_SCALE_X_CHARGED;			// チャージ後のscaleX変数の初期値
	static const float	INIT_SCALE_Y_CHARGED;			// チャージ後のscaleY変数の初期値

	static const float	CHARGED_SCALE_MAX;				// チャージ後のスケール上限値
	static const float	CHARGED_SCALE_ADD_AMOUNT;		// チャージ後のスケール増加値
	
	static const float	PARTICLE_HIDDEN_SCALE_Y_MIN;	// パーティクルを非表示にするスケールのY座標最低値
	static const float	PARTICLE_HIDDEN_CROSS_MIN;		// パーティクルを非表示にする外積の最低値

	// 変数

	int graphHandle;			// 画像ハンドル
								  								   
	VECTOR pos;					// 座標
	VECTOR origin;				// 中心座標
	VECTOR DirectionsVec;		// 移動方向ベクトル
	VECTOR moveVec;				// 移動ベクトル
	float velocity;				// 速度
	float angle;				// 画像の角度
	bool isVisible;				// 表示されているか
	bool isCharged;				// チャージ後か

	float scaleX, scaleY;		// スケール値

	VECTOR horizonVector;		// 水平ベクトル
	VECTOR verticalVector;		// 垂直ベクトル

	VECTOR graphPos[4]			// 画像座標
	{
		{-16,16},
		{16,16},
		{16,-16},
		{-16,-16},
	};
	VECTOR graphPosScale[4]		// 画像スケール座標
	{
		{-16,16},
		{16,16},
		{16,-16},
		{-16,-16},
	};
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	ChargeParticle();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ChargeParticle();

	/// <summary>
	/// パーティクルを発射
	/// </summary>
	/// <param name="pos">発射位置の座標</param>
	/// <param name="cameraPos">カメラ座標</param>
	/// <param name="graphHandle">使用する画像のハンドル</param>
	/// <param name="firstSpeed">初期速度</param>
	/// <param name="range">エフェクト表示半径</param>
	void DoParticleFly(VECTOR pos, VECTOR cameraPos, int graphHandle, float firstSpeed, float range, bool isCharged);

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