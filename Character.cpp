
// インクルード
#include <math.h>
#include "Character.h"
#include "Camera.h"
#include "ParticleManager.h"
#include "DisplayScore.h"
#include "ReviveEffect.h"
#include "Stage.h"
#include "MoveEffect.h"
#include "HitEffect.h"
#include "ChargeEffect.h"

// 定数
const float	Character::SPEED_MIN				  = 0.1f;	// 速度最低値
												  
const int	Character::REVIVE_TIME				  = 120;	// 復活にかかる時間
const float	Character::REVIVE_DRAW_POS_Y		  = 20.0f;	// 復活中のモデルの描画位置の高さ
const int	Character::BLINKING_INTERVAL_COUNT	  = 5;		// 点滅の間隔のカウント
												  
const int	Character::CHARGE_PARTICLE_NUM		  = 5;		// チャージパーティクルの数
const float	Character::CHARGE_PARTICLE_SPEED	  = 1.5f;	// チャージパーティクルの速度
const float	Character::CHARGE_PARTICLE_RANGE	  = 15.0f;	// チャージパーティクルの範囲の大きさ
const int	Character::CHARGE_DRAW_COUNT		  = 5;		// チャージパーティクルを表示するカウント数
const int	Character::CHARGE_SE_VOLUME			  = 150;	// チャージ効果音ボリューム
												  
const int	Character::MAX_CHARGE_DIFFUSION_NUM	  = 10;		// マックスチャージ拡散パーティクルの数
const float	Character::MAX_CHARGE_DIFFUSION_RANGE = 7.0;	// マックスチャージ拡散パーティクルの範囲の大きさ
const int	Character::MAX_CHARGE_COUNT			  = 60;		// マックスチャージのカウント数
const int	Character::MAX_CHARGE_DRAW_COUNT_1	  = 5;		// マックスチャージパーティクル1を表示するカウント数
const int	Character::MAX_CHARGE_DRAW_COUNT_2	  = 10;		// マックスチャージパーティクル2を表示するカウント数
												  
const float Character::COLLISION_RANGE			  = 10.0f;	// 当たり判定半径
const float	Character::COLLISION_DRAW_SPEED		  = 2.0f;	// 接触描画をするスピード規定値
const int	Character::COLLISION_PARTICLE_NUM	  = 15;		// 接触パーティクルの数
const float	Character::COLLISION_PARTICLE_SPEED	  = 2.5f;	// 接触パーティクル速度
												  
const float	Character::STAGE_FALL_SPEED			  = 0.5f;	// ステージ外の落ちる速度の値
const float	Character::STAGE_OUT_NUM			  = -30.0f;	// ステージ外とみなす値

// コンストラクタ
Character::Character()
{
	//初期化

	// スコア表示座標初期化
	scorePos = VGet(0, 0, 0);

	// スコア初期化
	score = 0;

	// チャージカウント初期化
	chargeEffectCount = 0;

	// 接触フラグ
	isLeaping = false;

	// ステージから落ちたかフラグ
	isStageOut = false;

	// チャージ中フラグ
	isCharge = false;

	// チャージ移動中フラグ
	isChargeMove = false;

	// コリジョンパーティクル画像読み込み
	collisionParticleGraph = LoadGraph("data/image/particle/particle_star.png");

	// チャージパーティクル画像読み込み
	chargeParticleGraph = LoadGraph("data/image/particle/particle_charge.png");

	// チャージ最大パーティクル画像 1 読み込み
	chargeMaxParticleGraph_1 = LoadGraph("data/image/particle/particle_charge_max_1.png");

	// チャージ最大パーティクル画像 2 読み込み
	chargeMaxParticleGraph_2 = LoadGraph("data/image/particle/particle_charge_max_2.png");

	// 光画像読み込み
	lightGraphHandle = LoadGraph("data/image/particle/Star.png");

	// 移動エフェクト頂点シェーダー読み込み
	moveEffectVertexShaderHandle = LoadVertexShader("data/shader/MoveEffect/MoveEffectVS.vso");

	// ピクセルシェーダー読み込み
	pixelShaderHandle = LoadPixelShader("data/shader/MoveEffect/MoveEffectPS.pso");

	// ヒットエフェクト頂点シェーダー読み込み
	hitEffectVertexShaderHandle = LoadVertexShader("data/shader/HitEffect/HitEffectVS.vso");

	// チャージエフェクト頂点シェーダー読み込み
	chargeEffectVertexShaderHandle = LoadVertexShader("data/shader/ChargeEffect/ChargeEffectVS.vso");

	// 移動エフェクト
	moveEffect = new MoveEffect(position, moveEffectVertexShaderHandle, pixelShaderHandle);

	// ポリゴンインデックス
	for (int i = 0, k = 0; i < (20 * 2 + 2) * 3; i += 6) {
		indexCircle[0 + i] = k;
		indexCircle[1 + i] = k + 2;
		indexCircle[2 + i] = k + 1;
		indexCircle[3 + i] = k + 1;
		indexCircle[4 + i] = k + 2;
		indexCircle[5 + i] = k + 3;
		k += 2;
	}
}

// デストラクタ
Character::~Character()
{
	// モデルハンドル削除
	MV1DeleteModel(modelHandle);

	// 復活エフェクト変数メモリ解放
	delete reviveEffect;
}

// 初期化
void Character::Initialize(const VECTOR& initPosition, ParticleManager* particleManager)
{
	// 初期座標
	position = initPos = initPosition;

	// パーティクルマネージャー取得
	particleMgr = particleManager;

	// 初期回転ベクトル
	rotation = initRotation = VNorm(VScale(position, -1.0f));

	// 復活エフェクト
	reviveEffect = new ReviveEffect(initPosition);

	// 3Dモデルのポジション設定
	MV1SetPosition(modelHandle, position);

	// Y軸の回転値を設定
	MV1SetRotationXYZ(modelHandle, VGet(0, atan2f(rotation.x, rotation.z), 0));
}

// 更新
void Character::Update()
{
	// 処理なし
}

// 描画
void Character::Draw()
{
	displayTag.Draw(position);	// タグ描画

}

// SE読み込み
void Character::LoadSE()
{
	// チャージ効果音読み込み
	chargeSE = LoadSoundMem("data/sounds/Main/charge.wav");

	// チャージ効果音の音量調整
	ChangeVolumeSoundMem(CHARGE_SE_VOLUME, chargeSE);

	// 衝突効果音読み込み
	collisionSE = LoadSoundMem("data/sounds/Main/collision.mp3");

	// スコア追加効果音読み込み
	scoreAddSE = LoadSoundMem("data/sounds/Main/ScoreAdd.mp3");

}

void Character::DrawModel()
{
	// 復活中ならモデルの描画位置を上から下に移動
	if (isRevive)
	{
		MV1SetPosition(modelHandle,
			VGet(position.x, position.y + REVIVE_DRAW_POS_Y - (REVIVE_DRAW_POS_Y * ((float)riviveTimer / (float)REVIVE_TIME)), position.z));
	}
	// 復活中でないならキャラの位置にモデルを描画する
	else
	{
		MV1SetPosition(modelHandle, position);
	}

	// モデルを描画
	MV1DrawModel(modelHandle);
}

// ステージの範囲外の判定
void Character::CollisionStage(const Stage* stage)
{
	// 三平方の定理を利用した当たり判定
	// キャラクターの座標がステージ外に出ているかを判定
	if (VSquareSize(VSub(position, VGet(0, 0, 0)))
		> pow(COLLISION_RANGE + stage->GetRange(), 2))
	{
		// ステージアウトフラグを立てる
		isStageOut = true;
	}
}

void Character::DoHit(VECTOR direction, float velocity, ScoreAddClass* collision)
{
	// 復活中なら衝突処理を行わない
	if (isRevive)
	{
		return;
	}

	// すでに接触フラグが立っている場合
	if (isLeaping)
	{
		// 接触した相手の速度 が 現在の自分の速度より 下なら 処理を行わない
		if (velocity <= this->velocity)
			return;

		// 接触した相手の速度 が 現在の自分の速度より 上なら 処理を行なう
		// 処理するなら接触フラグをリセットする
		isLeaping = false;
	}

	// 飛ばされる方向ベクトルのサイズが 0 より大きいなら角度ベクトルに代入
	if (VSize(direction) > 0)
	{
		collisionVector = direction;
	}

	// 速度補正
	if (velocity < 0.5f)
		velocity = 0.5f;

	// 速度代入
	this->velocity = velocity;

	// 相手が既に飛ばされている かつ 自分はまだ接触フラグが立っていないなら
	// 相手が保存しているスコア増加させるキャラクターを代入する
	if (collision->GetAddCharacter() != this && collision->GetIsLeaping() && !isLeaping)
	{
		scoreAddCharacter = collision->GetAddCharacter();
	}
	// そうでないなら、スコア増加キャラクター変数に相手のインスタンスのポインタを代入
	else
	{
		scoreAddCharacter = collision;
	}

	// 飛ばされる速度が規定値以上なら接触エフェクト表示、接触効果音を再生
	if (velocity >= COLLISION_DRAW_SPEED)
	{
		PlaySoundMem(collisionSE, DX_PLAYTYPE_BACK);	// 接触時の効果音を再生する

		// 接触エフェクトをセット
		particleMgr->SetCollisionParticle(position, COLLISION_PARTICLE_NUM, COLLISION_PARTICLE_SPEED);

		// ヒットエフェクト生成
		hitEffect.push_back(new HitEffect(position, 20, lightGraphHandle, hitEffectVertexShaderHandle));
	}

	isCharge = false;		// チャージフラグリセット

	isChargeMove = false;	// チャージ移動フラグリセット

	StopSoundMem(chargeSE);	// 接触時にチャージ効果音を止める

}

// 飛ばされているときの処理
void Character::DoLeap()
{
	// 接触フラグが立っているなら
	if (isLeaping)
	{
		// 速度ベクトルを計算
		velocityVector = VScale(collisionVector, velocity);

		// 座標を動かす
		position = VAdd(position, velocityVector);

		// 速度が一定以下 かつ ステージ内なら 接触フラグを下す
		if (velocity <= SPEED_MIN && isStageOut == false)
			isLeaping = false;
	}
}

void Character::UpdateStageOut()
{
	// Y座標を下げて画面下に移動させる
	position.y -= STAGE_FALL_SPEED;

	// 画面下に隠れたら初期位置に戻し、各種フラグとタイマーをリセットする
	if (position.y < STAGE_OUT_NUM)
	{
		// ステージ外に落ちた時の初期化処理
		InitStageOut();

		// タイマー初期化
		riviveTimer = 0;
	}
}

// ステージ外に落下した際の初期化処理
void Character::InitStageOut()
{
	// 座標初期化
	position = initPos;

	// ステージフラグ初期化
	isStageOut = false;

	//速度初期化
	velocity = 0;

	// 飛ばされてステージ外に落ちた場合は、飛ばした相手のスコアを増やす
	if (scoreAddCharacter != nullptr && isLeaping)
		scoreAddCharacter->ScoreAdd();

	// リセット
	scoreAddCharacter = nullptr;

	// 飛ばされているフラグをリセット
	isLeaping = false;

	// 速度ベクトルのリセット
	velocityVector = VGet(0, 0, 0);

	// 回転ベクトルを初期化する
	rotation = initRotation;

	// 復活フラグをセットする
	isRevive = true;

	// 復活エフェクトの表示
	reviveEffect->DoPlay();

	// タグ表示
	displayTag.DoDisplay();
}

// エフェクトの描画
void Character::DrawParticle()
{
	// チャージ中なら
	if (isCharge)
	{
		// チャージエフェクトのカウントが60以下なら
		if (chargeEffectCount <= MAX_CHARGE_COUNT)
		{
			// チャージパーティクルを一定時間ごとにセットする
			if (chargeEffectCount % CHARGE_DRAW_COUNT == 0)
			{
				// パーティクルセット
				particleMgr->SetChargeParticle(ParticleManager::CHARGE_NORMAL, position, Camera::INIT_POSITION, CHARGE_PARTICLE_NUM,  CHARGE_PARTICLE_SPEED, CHARGE_PARTICLE_RANGE, false);
			}
		}
		// 60以上なら チャージマックスエフェクトを表示
		else
		{
			// 画像ごとに交互に表示する
			
			if (chargeEffectCount % MAX_CHARGE_DRAW_COUNT_1 == 0)
			{
				particleMgr->SetChargeParticle(ParticleManager::CHARGE_MAX_1, position, Camera::INIT_POSITION, CHARGE_PARTICLE_NUM, CHARGE_PARTICLE_SPEED, CHARGE_PARTICLE_RANGE, false);
			}
			if (chargeEffectCount % MAX_CHARGE_DRAW_COUNT_2 == 0)
			{
				particleMgr->SetChargeParticle(ParticleManager::CHARGE_MAX_2, position, Camera::INIT_POSITION, CHARGE_PARTICLE_NUM, CHARGE_PARTICLE_SPEED, CHARGE_PARTICLE_RANGE, false);
			}
		}

		// チャージがマックスになった時の拡散パーティクルエフェクト
		if (chargeEffectCount == MAX_CHARGE_COUNT)
		{
			chargeEffect.push_back(new ChargeEffect(position, 20, lightGraphHandle, chargeEffectVertexShaderHandle));
			particleMgr->SetChargeParticle(ParticleManager::CHARGE_MAX_1, position, Camera::INIT_POSITION, MAX_CHARGE_DIFFUSION_NUM,  CHARGE_PARTICLE_SPEED, MAX_CHARGE_DIFFUSION_RANGE, true);
		}
	}
}

// エフェクト描画
void Character::DrawEffect()
{
	reviveEffect->Draw();		// 復活エフェクト描画

	// チャージ移動中なら移動エフェクト描画
	if (isChargeMove)
	{
		moveEffect->Draw(MV1GetMatrix(modelHandle));
	}

	// ピクセルシェーダー定数設定
	SetPSConstF(GetConstIndexToShader("num", pixelShaderHandle), empty);

	// ピクセルシェーダー使用
	SetUsePixelShader(pixelShaderHandle);

	// 頂点シェーダー定数設定
	SetVSConstFMtx(58, GetCameraBillboardMatrix());

	// ヒットエフェクト
	for (int i = 0; i < hitEffect.size(); i++)
	{
		// 描画
		hitEffect[i]->Draw(indexCircle);

		// 時間を取得し、0以下なら削除する
		if (hitEffect[i]->GetTime() < 0)
		{
			hitEffect.erase(hitEffect.begin() + i--);
		}
	}

	// 使用するピクセルシェーダーをリセット
	SetUsePixelShader(0);

	// チャージエフェクト
	for (int i = 0; i < chargeEffect.size(); i++)
	{
		// 描画
		chargeEffect[i]->Draw(indexCircle);

		// 時間を取得し、0以下なら削除する
		if (chargeEffect[i]->GetTime() < 0)
		{
			chargeEffect.erase(chargeEffect.begin() + i--);
		}
	}
}

void Character::ScoreAdd()
{
	score++;	// スコアを追加する

	// スコア増加の効果音が鳴っていない場合に、スコア増加の効果音を鳴らす
	if (!CheckSoundMem(scoreAddSE))
		PlaySoundMem(scoreAddSE, DX_PLAYTYPE_BACK);

	// スコア増加を表示する
	DrawScoreIfHidden();
}

void Character::DrawScoreIfHidden()
{
	int i;

	// 非表示のスコアを表示させる
	for (i = 0; i < displayScore.size(); i++)
	{
		if (displayScore[i].IsHidden())
		{
			displayScore[i].InitializeForDisplay();
			break;
		}
	}

	// 非表示のスコアがなければ、新たに要素を追加する
	if (i == displayScore.size())
	{
		displayScore.emplace_back();
	}
}

// チャージの効果音を止める
void Character::StopChargeSE()
{
	StopSoundMem(chargeSE);
}

void Character::UpdateReviveEffect()
{
	reviveEffect->Update();	// 復活エフェクト更新

	// 復活時の点滅処理
	if (isRevive)
	{
		// タイマーカウント
		riviveTimer++;

		// 点滅処理
		if (riviveTimer % BLINKING_INTERVAL_COUNT == 0)
		{
			MV1SetVisible(modelHandle, false);
		}
		else
		{
			MV1SetVisible(modelHandle, true);
		}

		// タイマーが最後の時は表示させる
		if (riviveTimer == REVIVE_TIME)
		{
			MV1SetVisible(modelHandle, true);
			isRevive = false;
		}

	}
}
