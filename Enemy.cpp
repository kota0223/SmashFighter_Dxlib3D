#include "Player.h"
#include "Enemy.h"
#include "EffectManager.h"
#include "InformantForAi.h"
#include <math.h>
#include "DisplayScore.h"

// 敵の加速度の定数
const float	 Enemy::SPEED_ADD = 1.0f;								// スピード
const float	 Enemy::VELOCITY_MINIMUM = 0.1f;						// 速度最低値
const VECTOR Enemy::MODEL_SCALE = VGet(0.05f, 0.05f, 0.05f);		// モデルの拡大値
const float  Enemy::ATTENUATION_COEFFICIENT = 0.98f;				// 減衰係数
const float  Enemy::STAGE_RANGE = 85.0f;							// ステージ範囲
const float  Enemy::CORRECTION_POSSIBLE_SPEED = 1.0f;				// 補正可能な速度
const float  Enemy::CORRECTION_RANGE = 0.1f;						// 補正する半径の大きさ
const VECTOR Enemy::SCORE_POSITION_ADJUSTMENT = VGet(-2, 20, 0);	// スコア表示位置を調整する値
const int	 Enemy::SCORE_DRAW_POSITION_INTERVAL = 10;				// スコアの表示位置間隔
const int	 Enemy::ACTION_RANDOM_MAX = 4;							// 行動乱数最大値
const int	 Enemy::ATTACK_MAX_COUNT = 180;							// 攻撃カウント最大値
const float  Enemy::ATTACK_VELOCITY = 6.0f;							// 攻撃時の速度
const float  Enemy::ATTACK_ATTENUATION_COEFFICIENT = 0.97f;			// 攻撃時の速度減衰係数
const float  Enemy::ROTATE_ADD_SCALE = 0.1f;						// 増加させる回転のスケール値
const float  Enemy::CIRCLE_ANGLE = 360.0f;							// 円の角度
const float  Enemy::MOVE_CIRCLE_RADIUS = 60.0f;						// 移動する円の半径
const float  Enemy::MOVE_ROTATE_ANGLE = 20.0f;						// 移動する角度値
const float  Enemy::MOVE_SCALE_RADIUS = 50.0f;						// 移動時の半径の大きさ
const float  Enemy::MOVE_VELOCITY_SCALE = 0.05f;					// 移動時の速度の大きさ
const float  Enemy::CHARGE_MOVE_MIN_SPEED = 0.2f;					// チャージ移動の速度最低値

// 敵のインスタンス数初期値
int Enemy::EnemyNum = 0;

// コンストラクタ：敵キャラクターの初期化を行います
Enemy::Enemy(int modelHandle, const Color_st &tagColor) :Character()
{
	// 番号を設定
	Number = ++EnemyNum;

	// モデルハンドル代入
	this->modelHandle = MV1DuplicateModel(modelHandle);

	// モデル拡大値設定
	MV1SetScale(this->modelHandle, MODEL_SCALE);

	// 行動状態の初期化
	actState = none;

	// 敵の速度初期化
	velocity = 0;

	// タイマー初期化
	riviveTimer = 0;

	// タグ画像代入
	displayTag.InitGraph(LoadGraph("data/image/Main/DisplayTag_CP.png"), LoadGraph("data/image/Main/DisplayTag_CP_Back.png"));

	displayTag.SetColor(tagColor);
}

// デストラクタ：特に処理は行いません
Enemy::~Enemy()
{
	// 処理なし
}

// 敵キャラクターの更新処理
void Enemy::Update()
{
	SetAction();

	displayTag.Update();		// タグ更新

	Character::UpdateReviveEffect();

	if (isRevive) return;

	if (isChargeMove && velocity <= CHARGE_MOVE_MIN_SPEED)
		isChargeMove = false;

	// 飛ばされている場合は速度を減衰させる
	if (actState == none)
		velocity *= ATTENUATION_COEFFICIENT;

	// 飛ばされる処理
	DoLeap();

	// 行動状態がnoneで、飛ばされてない場合は位置を更新する
	if (actState == none && !isLeaping)
		position = VAdd(position, velocityVector);

	// 画面外に出た場合の処理
	if (isStageOut)
	{
		UpdateStageOut();
	}
	// 一定以下の速度で ステージ外に出たら 座標を補正
	else if (VSize(position) >= STAGE_RANGE && velocity < CORRECTION_POSSIBLE_SPEED)
	{
		// 画面内に収めるために位置を補正する
		position = VScale(VNorm(position), STAGE_RANGE - CORRECTION_RANGE);
	}

	// モデルの回転値設定
	MV1SetRotationXYZ(modelHandle, VGet(0, atan2f(rotation.x, rotation.z), 0));
}

void Enemy::DrawScore(int x, int y)
{
	// スコアを描画
	//DrawFormatStringToHandle(x, y, GetColor(255, 255, 255), scoreFont, "No %d Enemy Score : %d", Number, score);

	// キャラクターの三次元座標をスクリーン座標に変換する
	VECTOR scorePos = ConvWorldPosToScreenPos(VAdd(position, SCORE_POSITION_ADJUSTMENT));

	// スコア増加の描画
	for (int i = 0; i < displayScore.size(); i++)
	{
		displayScore[i].Update();
		displayScore[i].Draw((int)scorePos.x, (int)scorePos.y + i * SCORE_DRAW_POSITION_INTERVAL);
	}
}

// 敵キャラクターの行動を設定する関数
void Enemy::SetAction()
{
	// 飛ばされている最中 か タイマーが200未満の場合は行動なしで終了
	if (isLeaping || isRevive)
	{
		actState = none;
		return;
	}

	// 行動が未設定の場合はランダムに行動を決定
	if (actState == none)
	{
		// 乱数で行動を設定
		switch (GetRand(ACTION_RANDOM_MAX))
		{
		case 0:
			SetActAttack(); // 攻撃行動を設定
			break;
		default:
			SetActMove(); // 移動行動を設定
			break;
		}
	}
	else
	{
		// 行動がattackまたはmoveの場合はそれぞれの行動を実行
		switch (actState)
		{
		case attack:
			ActAttack(); // 攻撃行動を実行
			break;
		case move:
			ActMove(); // 移動行動を実行
			break;
		}
	}
}

// 攻撃行動を設定する関数
void Enemy::SetActAttack()
{
	// 攻撃行動時のカウントをリセット
	attackActCount = 0;

	// チャージカウントリセット
	chargeEffectCount = 0;

	// 攻撃対象を探索し、ターゲットに設定する
	target = InformantForAi::GetInstance().GetAttackTarget(position);

	// 攻撃チャージフラグを立てる
	isCharge = true;

	// チャージ音を止める
	PlaySoundMem(chargeSE, DX_PLAYTYPE_BACK);

	// 行動状態を攻撃時に変更
	actState = attack;
}

// 攻撃行動を実行する関数
void Enemy::ActAttack()
{
	// 攻撃カウント
	attackActCount++;

	// targetがnullptrでないか確認
	if (target != nullptr)
	{
		// 飛ばされている か ステージ外 ならターゲットから外す
		if (target->GetIsLeaping()
			|| target->GetIsStageOut())
		{
			target = nullptr;
		}
	}

	// カウントが基準値を超えたら 攻撃する
	if (attackActCount >= ATTACK_MAX_COUNT)
	{
		// 基準のカウントになった瞬間
		if (attackActCount == ATTACK_MAX_COUNT)
		{
			// 速度設定
			velocity = ATTACK_VELOCITY;

			// 攻撃チャージフラグを下す
			isCharge = false;

			// チャージ移動フラグを立てる
			isChargeMove = true;

			// チャージ音を止める
			StopSoundMem(chargeSE);

			// targetがnullptrの場合はステージ中央に向かって攻撃する
			if (target == nullptr)
			{
				// 現在地から中心へのベクトル
				rotation = VSub(VGet(0, 0, 0), position);

				// 正規化
				if (VSize(rotation) > 0)
				{
					rotation = VNorm(rotation);
				}
			}
		}

		// 速度ベクトル算出
		velocityVector = VScale(rotation, velocity);

		// 座標移動
		position = VAdd(position, velocityVector);

		// 速度が一定以下になったら行動をやめる
		if (velocity < VELOCITY_MINIMUM)
		{
			// 行動を未設定
			actState = none;

			// ターゲットを外す
			target = nullptr;

		}
		else
		{
			// 速度減衰
			velocity *= ATTACK_ATTENUATION_COEFFICIENT;
		}
	}
	else
	{
		// targetがnullptrでない場合はターゲットのほうを向く
		if (target != nullptr)
		{
			// 方向ベクトルを計算
			moveRotation = VSub(target->GetPosition(), position);

			// エネミーの向いている角度 と 移動後の角度 との外積を計算する
			cross = VCross(rotation, moveRotation);

			// sinの値を計算する
			float sita = VSize(cross) / (VSize(rotation) * VSize(moveRotation));

			if (cross.y < 0)
			{
				// 外積のy成分が負の場合はsitaに-0.1をかけた角度の回転行列を求め
				// 敵の角度ベクトルを行列を使用して変換させる
				rotation = VTransform(rotation, MGetRotY(-sita * ROTATE_ADD_SCALE));
			}
			else
			{
				// 外積のy成分が正の場合はsitaに0.1をかけた角度の回転行列を求め
				// 敵の角度ベクトルを行列を使用して変換させる
				rotation = VTransform(rotation, MGetRotY(sita * ROTATE_ADD_SCALE));
			}

			if (VSize(rotation) > 0)
			{
				// 回転ベクトルの正規化
				rotation = VNorm(rotation);
			}
		}
		else
		{
			// targetがnullptrの場合は再度攻撃対象を探索する
			target = InformantForAi::GetInstance().GetAttackTarget(position);
		}

		// チャージカウント
		chargeEffectCount++;
	}
}

// 移動行動を設定する関数
void Enemy::SetActMove()
{
	// スピード代入
	velocity = SPEED_ADD;

	// 移動後の角度を算出
	// 扇形の弧の長さ / 半径 = ラジアン
	float rad = ((2 * DX_PI_F * MOVE_CIRCLE_RADIUS) * (MOVE_ROTATE_ANGLE / CIRCLE_ANGLE)) / MOVE_CIRCLE_RADIUS;

	// 正規化
	if (VSize(position) > 0)
		aimPosition = VNorm(position);

	// 回転行列によるベクトルの変換
	aimPosition = VTransform(VScale(aimPosition, MOVE_SCALE_RADIUS), MGetRotY(rad));

	// 移動先の方向ベクトルを算出
	moveRotation = VSub(aimPosition, position);

	// エネミーの向いている角度 と 移動後の角度 との外積を計算する
	cross = VCross(rotation, moveRotation);

	// 行動状態をmoveに変更
	actState = move;
}

// 移動行動を実行する関数
void Enemy::ActMove()
{
	// エネミーの向いている角度 と 移動後の角度 との外積を計算する
	cross = VCross(rotation, moveRotation);

	// sinの値を計算する
	float sita = VSize(cross) / (VSize(rotation) * VSize(moveRotation));

	if (cross.y < 0)
	{
		// 外積のy成分が負の場合はsitaに-0.1をかけた角度の回転行列を求め
		// 敵の角度ベクトルを行列を使用して変換させる
		rotation = VTransform(rotation, MGetRotY(-sita * ROTATE_ADD_SCALE));
	}
	else
	{
		// 外積のy成分が正の場合はsitaに0.1をかけた角度の回転行列を求め
		// 敵の角度ベクトルを行列を使用して変換させる
		rotation = VTransform(rotation, MGetRotY(sita * ROTATE_ADD_SCALE));
	}

	// 回転ベクトルの正規化
	if (VSize(rotation) > 0)
	{
		rotation = VNorm(rotation);
	}

	// 現在地から移動先のベクトルへのベクトルを算出し、速度ベクトルを求める
	velocityVector = VScale((VSub(aimPosition, position)), MOVE_VELOCITY_SCALE);

	// 速度ベクトル算出
	//velocityVector = VScale(rotation, velocity);

	// 座標ベクトル算出
	position = VAdd(position, velocityVector);

	// 速度減衰
	//velocity *= 0.96f;

	// 速度が一定以下になったら行動をやめる
	if (VSize(velocityVector) <= VELOCITY_MINIMUM)
	{
		actState = none;
	}
}
