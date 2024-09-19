#pragma once

// インクルード
#include <vector>
#include <DxLib.h>
#include "ScoreAdd.h"
#include "DisplayTag.h"
#include "TagStruct.h"

// 前方宣言
class ParticleManager;
class DisplayScore;
class ReviveEffect;
class Stage;
class MoveEffect;
class HitEffect;
class ChargeEffect;

/// <summary>
/// キャラクタークラス
/// </summary>
class Character : public ScoreAddClass
{
protected:

	// 定数

	static const float	SPEED_MIN;					// 速度最低値

	static const int	REVIVE_TIME;				// 復活にかかる時間
	static const float	REVIVE_DRAW_POS_Y;			// 復活中のモデルの描画位置の高さ
	static const int	BLINKING_INTERVAL_COUNT;	// 点滅の間隔のカウント

	static const int	CHARGE_PARTICLE_NUM;		// チャージパーティクルの数
	static const float	CHARGE_PARTICLE_SPEED;		// チャージパーティクルの速度
	static const float	CHARGE_PARTICLE_RANGE;		// チャージパーティクルの範囲の大きさ
	static const int	CHARGE_DRAW_COUNT;			// チャージパーティクルを表示するカウント数
	static const int	CHARGE_SE_VOLUME;			// チャージ効果音ボリューム

	static const int	MAX_CHARGE_DIFFUSION_NUM;	// マックスチャージ拡散パーティクルの数
	static const float	MAX_CHARGE_DIFFUSION_RANGE;	// マックスチャージ拡散パーティクルの範囲の大きさ
	static const int	MAX_CHARGE_COUNT;			// マックスチャージのカウント数
	static const int	MAX_CHARGE_DRAW_COUNT_1;	// チャージパーティクルを表示するカウント数
	static const int	MAX_CHARGE_DRAW_COUNT_2;	// チャージパーティクルを表示するカウント数

	static const float	COLLISION_RANGE;			// 当たり判定半径
	static const float	COLLISION_DRAW_SPEED;		// 接触描画をするスピード規定値
	static const int	COLLISION_PARTICLE_NUM;		// 接触パーティクルの数
	static const float	COLLISION_PARTICLE_SPEED;	// 接触パーティクルの速度

	static const float	STAGE_FALL_SPEED;			// ステージ外の落ちる速度の値
	static const float	STAGE_OUT_NUM;				// ステージ外とみなす値

	// 変数

	VECTOR position;		// 座標
	VECTOR rotation;		// 回転ベクトル
	VECTOR velocityVector;	// 速度ベクトル
	VECTOR collisionVector;	// 接触後の方向ベクトル
	VECTOR initPos;			// 初期座標
	VECTOR initRotation;	// 初期回転ベクトル
	VECTOR scorePos;		// スコア表示座標

	int score;				// スコア
	int chargeEffectCount;	// チャージエフェクトカウント
	int riviveTimer;		// 復活タイマー
	float velocity;			// 速度
	bool isLeaping;			// 飛ばされているか
	bool isStageOut;		// ステージから落ちたか
	bool isCharge;			// チャージ中か
	bool isChargeMove;		// チャージ移動中か
	bool isRevive;			// 復活中か

	ReviveEffect* reviveEffect;		// 復活エフェクト
	MoveEffect* moveEffect;			// 移動エフェクト
	ParticleManager* particleMgr;	// パーティクルマネージャー

	int modelHandle;				// キャラクターモデルハンドル
	int collisionParticleGraph;		// コリジョンパーティクル画像ハンドル
	int chargeParticleGraph;		// チャージパーティクル画像ハンドル
	int chargeMaxParticleGraph_1;	// マックスチャージパーティクル画像ハンドル_1
	int chargeMaxParticleGraph_2;	// マックスチャージパーティクル画像ハンドル_2
	int lightGraphHandle;			// 光画像ハンドル

	int moveEffectVertexShaderHandle;	// 移動エフェクト頂点シェーダーハンドル
	int hitEffectVertexShaderHandle;	// ヒットエフェクト頂点シェーダーハンドル
	int chargeEffectVertexShaderHandle;	// チャージエフェクト頂点シェーダハンドル
	int pixelShaderHandle;				// ピクセルシェーダーハンドル

	int chargeSE;		// チャージ効果音
	int collisionSE;	// 接触効果音
	int scoreAddSE;		// スコア追加効果音

	std::vector<DisplayScore> displayScore;		// スコア表示クラス
	std::vector<HitEffect*> hitEffect;			// ヒットエフェクト
	std::vector<ChargeEffect*> chargeEffect;	// チャージエフェクト

	DisplayTag displayTag;	// タグ表示クラス

	ScoreAddClass* scoreAddCharacter;	//スコア加算キャラクター保存クラス

	WORD indexCircle[(20*2+2)*3];	// ポリゴンインデックス配列

	FLOAT4 empty = { 0 };	// 空変数

public:

	/// <summary>
	/// コンストラクタ
	/// 初期化、各種データのロード
	/// </summary>
	/// <param name="initPosition">キャラクター初期位置</param>
	Character();

	/// <summary>
	/// 仮装デストラクタ
	/// ハンドルの削除、メモリの解放
	/// </summary>
	virtual ~Character();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(const VECTOR& initPosition, ParticleManager* particleManager);

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw();

	/// <summary>
	/// 効果音の読み込み
	/// デモプレイでは音を流さないため、切り離している
	/// </summary>
	void LoadSE();

	/// <summary>
	/// モデルの描画
	/// </summary>
	void DrawModel();

	/// <summary>
	/// ステージとの接触処理
	/// </summary>
	/// <param name="stage">Stageクラスインスタンスのポインタ</param>
	void CollisionStage(const Stage* stage);

	/// <summary>
	/// 接触時の処理
	/// </summary>
	/// <param name="direction">移動方向のベクトル</param>
	/// <param name="velocity">移動速度</param>
	/// <param name="collision"></param>
	void DoHit(VECTOR direction, float velocity, ScoreAddClass* collision);

	/// <summary>
	/// 接触後の処理
	/// </summary>
	void DoLeap();

	/// <summary>
	/// ステージ外に落下する処理
	/// </summary>
	void UpdateStageOut();

	/// <summary>
	/// ステージ外に落下した際の初期化処理
	/// </summary>
	void InitStageOut();

	/// <summary>
	/// パーティクル描画
	/// </summary>
	void DrawParticle();

	/// <summary>
	/// エフェクト描画
	/// </summary>
	void DrawEffect();

	/// <summary>
	/// スコア描画
	/// </summary>
	virtual void DrawScore(int x, int y) = 0;

	/// <summary>
	/// スコア増加
	/// </summary>
	void ScoreAdd();

	/// <summary>
	/// 非表示のスコアを描画する
	/// なければ、コンテナに要素を追加する
	/// </summary>
	void DrawScoreIfHidden();

	/// <summary>
	/// チャージの効果音を止める
	/// </summary>
	void StopChargeSE();

	/// <summary>
	/// 復活時のエフェクト描画
	/// </summary>
	void UpdateReviveEffect();

	/// <summary>
	/// 飛ばされたフラグを立てる
	/// </summary>
	void EnableIsLeaping() { isLeaping = true; }

	/// <summary>
	/// 座標を取得
	/// </summary>
	/// <returns>VECTOR型 キャラクターの座標ベクトル</returns>
	VECTOR GetPosition() const { return position; }

	/// <summary>
	/// 当たり判定半径を取得
	/// </summary>
	/// <returns>Float型 キャラクターの当たり判定の半径</returns>
	float GetCollisionRange() const { return COLLISION_RANGE; }

	/// <summary>
	/// 速度を取得
	/// </summary>
	/// <returns>Float型 キャラクターの速度</returns>
	float GetVelocity() const { return velocity; }

	/// <summary>
	/// (方向も含めた)速度ベクトルを取得
	/// </summary>
	/// <returns>VECTOR型 速度ベクトルベクトル</returns>
	VECTOR GetVelocityVector() const { return velocityVector; }

	/// <summary>
	/// (方向も含めた)速度ベクトルを取得
	/// </summary>
	/// <returns>VECTOR型 速度ベクトルベクトル</returns>
	MATRIX GetModelMatrix() const { return MV1GetMatrix(modelHandle); }

	/// <summary>
	/// 接触フラグを返す
	/// </summary>
	/// <returns>bool型 接触したかのフラグ</returns>
	bool GetIsLeaping() const { return isLeaping; }

	/// <summary>
	/// ステージ外にいるかを返す
	/// </summary>
	/// <returns>bool型 ステージ外にいるかのフラグ</returns>
	bool GetIsStageOut() const { return isStageOut; }

	/// <summary>
	/// 復活フラグを返す
	/// </summary>
	/// <returns>bool型 復活中かどうかのフラグ </returns>
	bool GetIsRivive() const { return isRevive; }

	/// <summary>
	/// チャージ移動フラグを返す
	/// </summary>
	/// <returns>bool型 チャージ移動中フラグ </returns>
	bool GetIsChargeMove() const { return isChargeMove; }

	/// <summary>
	/// 変数に保存されているキャラクターインスタンスポインタを返す
	/// </summary>
	/// <returns>ScoreAddClass*型 スコアを増加させるキャラクターポインタ</returns>
	ScoreAddClass* GetAddCharacter() { return scoreAddCharacter; }

	/// <summary>
	/// スコアを返す
	/// </summary>
	/// <returns>int型 キャラクターのスコア</returns>
	int GetScore() const { return score; }

	/// <summary>
	/// キャラクターのタグ構造体を取得する
	/// </summary>
	/// <returns>キャラクターのタグ構造体</returns>
	Tag_st GetCharaTag() { return displayTag.GetTag(); }
};