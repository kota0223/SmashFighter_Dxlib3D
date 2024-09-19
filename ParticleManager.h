#pragma once

#include <vector>
#include "ChargeParticle.h"

class CollisionParticle;

class ParticleManager
{
public:

	// チャージ画像種類
	enum ChargeGraphKind
	{
		CHARGE_NORMAL = 0,
		CHARGE_MAX_1,
		CHARGE_MAX_2,
		CHARGE_GRAPH_AMOUNT
	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ParticleManager();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ParticleManager();

	///<summary>
	/// パーティクルの生成と設定を行います。
	///</summary>
	///<param name="pos">パーティクルの初期位置</param>
	///<param name="num">生成するパーティクルの数</param>
	///<param name="graphHandle">パーティクルのグラフィックハンドル</param>
	///<param name="firstSpeed">パーティクルの初期速度</param>
	void SetCollisionParticle(VECTOR pos, int num, float firstSpeed);

	///<summary>
	/// パーティクルの生成と設定を行います。
	///</summary>
	///<param name="pos">パーティクルの初期位置</param>
	///<param name="cameraPos">カメラの位置</param>
	///<param name="num">生成するパーティクルの数</param>
	///<param name="graphHandle">パーティクルのグラフィックハンドル</param>
	///<param name="firstSpeed">パーティクルの初期速度</param>
	void SetChargeParticle(ChargeGraphKind graphKind, VECTOR pos, VECTOR cameraPos, int num, float firstSpeed, float range, bool isCharged);

	///<summary>
	/// パーティクルの状態を更新します。
	///</summary>
	void Update();

	///<summary>
	/// パーティクルを描画します。
	///</summary>
	void Draw();
private:
	int chargeParticlesNum;								// チャージパーティクルの数
	int collisionParticlesNum;							// コリジョンパーティクルの数
	std::vector<ChargeParticle*> chargeParticles;		// チャージパーティクルを管理するためのベクター
	std::vector<CollisionParticle*> collisionParticles;	// コリジョンパーティクルを管理するためのベクター
	int collisionParticleGraph;							// コリジョンパーティクル画像ハンドル

	int chargeParticleGraphs[CHARGE_GRAPH_AMOUNT];		// チャージパーティクル画像配列
};
