#include <Dxlib.h>
#include "CollisionParticle.h"
#include "ParticleManager.h"

// コンストラクタ
ParticleManager::ParticleManager()
{
	// コリジョンパーティクル画像読み込み
	collisionParticleGraph = LoadGraph("data/image/particle/particle_star.png");

	// チャージパーティクル画像読み込み
	chargeParticleGraphs[0] = LoadGraph("data/image/particle/particle_charge.png");

	// チャージ最大パーティクル画像 1 読み込み
	chargeParticleGraphs[1] = LoadGraph("data/image/particle/particle_charge_max_1.png");

	// チャージ最大パーティクル画像 2 読み込み
	chargeParticleGraphs[2] = LoadGraph("data/image/particle/particle_charge_max_2.png");
}

// デストラクタ
ParticleManager::~ParticleManager()
{
	// メモリ解放処理
	for (int i = 0; i < collisionParticles.size(); i++)
	{
		delete[] collisionParticles[i];
	}
}

// チャージパーティクルを生成し、パラメータを設定する関数
void ParticleManager::SetChargeParticle(ChargeGraphKind graphKind, VECTOR pos, VECTOR cameraPos, int num, float firstSpeed, float range, bool isCharged)
{
	// パーティクルの個数を設定
	chargeParticlesNum = num;

	// 各チャージパーティクルに対して初期化とパーティクルの飛行処理を行う
	for (int i = 0; i < chargeParticlesNum; i++)
	{
		chargeParticles.emplace_back(new ChargeParticle);
		chargeParticles.back()->DoParticleFly(pos, cameraPos, chargeParticleGraphs[graphKind], firstSpeed, range, isCharged);
	}
}

// 衝突パーティクルを生成し、パラメータを設定する関数
void ParticleManager::SetCollisionParticle(VECTOR pos, int num, float firstSpeed)
{
	// パーティクルの個数を設定
	collisionParticlesNum = num;
	// 新しい衝突パーティクルの配列をcollisionParticlesに追加
	collisionParticles.push_back(new CollisionParticle[collisionParticlesNum]());

	// 各衝突パーティクルに対して初期化とパーティクルの飛行処理を行う
	for (int i = 0; i < collisionParticlesNum; i++)
		collisionParticles.back()[i].DoParticleFly(pos, collisionParticleGraph, firstSpeed);
}

// パーティクルの更新を行う関数
void ParticleManager::Update()
{
	// チャージパーティクルの更新
	for (int i = 0; i < chargeParticles.size(); i++)
	{
		chargeParticles[i]->Update();
	}

	// 衝突パーティクルの更新
	for (auto particle : collisionParticles)
	{
		for (int i = 0; i < collisionParticlesNum; i++)
		{
			particle[i].Update();
		}
	}
}

// パーティクルの描画を行う関数
void ParticleManager::Draw()
{
	int cnt = 0;

	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

	// チャージパーティクルの描画と不可視パーティクルの削除
	for (int i = 0; i < chargeParticles.size(); i++)
	{
		chargeParticles[i]->Draw();

		// パーティクルが不可視の場合、不可視パーティクルの数をカウント
		if (!chargeParticles[i]->IsVisible())
		{
			chargeParticles.erase(chargeParticles.begin() + i--);
		}
	}

	// 衝突パーティクルの描画と不可視パーティクルの削除
	for (int i = 0; i < collisionParticles.size(); i++)
	{
		cnt = 0;
		for (int j = 0; j < collisionParticlesNum; j++)
		{
			collisionParticles[i][j].Draw();

			// パーティクルが不可視の場合、不可視パーティクルの数をカウント
			// パーティクルが表示されているならbreakし、ループ変数 j がNumと同じなら削除する
			if (!collisionParticles[i][j].IsVisible())
			{
				cnt++;
			}
		}

		// パーティクルがすべて不可視になったら、その配列を削除してnullptrにする
		if (cnt == collisionParticlesNum)
		{
			delete[] collisionParticles[i];
			collisionParticles[i] = nullptr;
		}
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, NULL);

	for (int i = 0; i < collisionParticles.size(); i++)
	{
		if (collisionParticles[i] == nullptr)
			collisionParticles.erase(collisionParticles.begin() + i--);
	}
}
