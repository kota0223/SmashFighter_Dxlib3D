#include "player.h"
#include "EffectManager.h"
#include "DisplayScore.h"

// プレイヤーのスピードを増加させるための定数
const float Player::SPEED_ADD = 5.0f;

// 押すカウントの最大値
const int Player::PUSH_COUNT_MAX = 60;

const VECTOR Player::MODEL_SCALE = VGet(0.05f, 0.05f, 0.05f);	// モデルのスケールベクトル値

const double Player::PAD_DEAD_ZONE = 0.15;	// ジョイパッドのデッドゾーン値
			 
const int    Player::INIT_BUTTON_PUSH_COUNT = 10;	// ボタンを押したときのカウント変数初期値
			 
const float  Player::CHARGE_MOVE_VELOCITY_MIN = 0.2f;	// チャージ移動の速度最低値
			 
const float  Player::VELOCITY_MIN = 0.1f;			// 移動速度最低値
			 
const float  Player::VELOCITY_ATTENUATION = 0.97f;	// 速度減衰率

const float  Player::PAD_ANALOG_INPUT_VELOCITY_MAX = 1.0f;	// パッドのアナログスティックの入力を受け付ける速度最大値
			 
const float  Player::STAGE_CORRECTION_VELOCITY_MAX = 0.2f;	// ステージ外の補正がかかる速度の最大値

const VECTOR Player::SCORE_POSITION_ADJUSTMENT = VGet(-2, 20, 0);		// スコア表示位置調整ベクトル

const int    Player::SCORE_POSITION_BETWEEN = 10;		// スコア複数表示の間隔

// プレイヤークラスのコンストラクタ
Player::Player(int modelHandle) :Character()
{
	// モデルハンドル代入
	this->modelHandle = MV1DuplicateModel(modelHandle);

	MV1SetScale(this->modelHandle, MODEL_SCALE);

	// ゲームパッドの入力を回転ベクトルに反映するための変数
	padInputRotation = VGet(0, 0, 1);

	// ボタンを離したかどうかのフラグ
	isdetachedButton = false;

	// 前のフレームでボタンが押されていたかを記憶する変数
	prevPushButton = false;

	// ボタンが押されている状態が続いたフレーム数をカウントする変数
	pushLongButtonCount = 0;

	// タグ画像代入
	displayTag.InitGraph(LoadGraph("data/image/Main/DisplayTag_Player.png"), 0);

	// ジョイパッドのデッドゾーンを設定
	SetJoypadDeadZone(DX_INPUT_PAD1, PAD_DEAD_ZONE);
}

// プレイヤークラスのデストラクタ
Player::~Player()
{
	// 処理なし
}

// プレイヤーの更新処理
void Player::Update()
{
	displayTag.Update();		// タグ更新

	Character::UpdateReviveEffect();

	if (isRevive) return;

	// 入力処理
	InputAction();

	// チャージ移動中に速度が一定以下になったらフラグを降ろす
	if (isChargeMove && velocity <= CHARGE_MOVE_VELOCITY_MIN)
		isChargeMove = false;

	// 座標計算処理
	CalculationPosition();

	// ステージ外に出た場合の処理
	if (isStageOut)
	{
		UpdateStageOut();
	}
	// ステージ外ではない場合
	// プレイヤーの座標ベクトルのサイズが 基準値以上 かつ なす角が 正の値 か 速度が 基準値以下なら
	else if (VSize(position) >= 90.0 && (rad > 0 || velocity <= STAGE_CORRECTION_VELOCITY_MAX))
	{
		// ステージの外側に出た場合は、ステージの外側に位置を制限する
		position = VScale(VNorm(position), 89.9f);
	}

	DoLeap();	// ジャンプ処理

	// モデルの回転値設定
	MV1SetRotationXYZ(modelHandle, VGet(0, atan2f(padInputRotation.x, padInputRotation.z), 0));
}

void Player::InputAction()
{
	// ゲームパッド入力を取得
	int padInput = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// もしプレイヤーが飛ばされている最中であれば、ゲームパッド入力を無効化
	if (isLeaping)
	{
		padInput = 0;
	}

	// 前のフレームでボタンが押されていたかつ
	// 今のフレームでボタンが離された場合、フラグを立てる
	if (prevPushButton && !(padInput & PAD_INPUT_3))
	{
		// ボタンを離したフラグを立てる
		isdetachedButton = true;
	}
	// 前のフレームでボタンが押されていないか
	// 今のフレームでもボタンが押されている場合、フラグを下ろす
	else
	{
		isdetachedButton = false;
	}

	// ボタンが押されている場合、前のフレームで押されていたフラグを立てる
	if (padInput & PAD_INPUT_3)
	{
		// 押された瞬間（前のフレームで押されていない場合）
		if (!prevPushButton)
		{
			// カウントリセット
			pushLongButtonCount = INIT_BUTTON_PUSH_COUNT;

			// チャージエフェクトカウントをリセット
			chargeEffectCount = 0;

			// チャージフラグを立てる
			isCharge = true;

			PlaySoundMem(chargeSE, DX_PLAYTYPE_BACK);
		}

		// チャージカウント
		chargeEffectCount++;

		// カウントが最大になるまでカウントする
		if (pushLongButtonCount < PUSH_COUNT_MAX)
		{
			// カウント
			pushLongButtonCount++;
		}

		// 前フレームで押されていたフラグを立てる
		prevPushButton = true;
	}
	else
	{
		// 前フレームで押されていたフラグを下す
		prevPushButton = false;

		// チャージフラグを下す
		isCharge = false;

		StopSoundMem(chargeSE);
	}

	// 速度が基準値より下ならパッドのアナログスティックの入力量を取得
	if (velocity < PAD_ANALOG_INPUT_VELOCITY_MAX)
	{
		// アナログスティックの入力量を取得
		GetJoypadAnalogInput(&padAnalogInputX, &padAnalogInputY, DX_INPUT_PAD1);

		// 入力がある場合はベクトルに代入
		if (pow(padAnalogInputX, 2) + pow(padAnalogInputY, 2) > 0)
		{
			padInputRotation = VGet((float)padAnalogInputX, 0, (float)-padAnalogInputY);
		}
		// パッドの入力がない場合は、キーボード入力も受け付ける
		else
		{
			// 右キー入力で右回転
			if (padInput & PAD_INPUT_RIGHT)
			{
				padInputRotation = VTransform(padInputRotation, MGetRotY(DX_PI_F / 180 * 2));
			}

			// 左キー入力で左回転
			if (padInput & PAD_INPUT_LEFT)
			{
				padInputRotation = VTransform(padInputRotation, MGetRotY(-DX_PI_F / 180 * 2));
			}
		}

		// 正規化
		if (VSize(padInputRotation) > 0)
		{
			padInputRotation = VNorm(padInputRotation);
		}
	}

	// ボタンを離した場合、スピードを加算する
	if (isdetachedButton && !isLeaping)
	{
		// ボタンを押したカウントから速度を算出
		velocity = SPEED_ADD / PUSH_COUNT_MAX * pushLongButtonCount;

		// パッドのアナログスティックの回転値をプレイヤーの角度ベクトルに代入
		rotation = padInputRotation;

		// プレイヤーの座標からステージ真ん中に向かうベクトル
		verticalVector = VSub(VGet(0, 0, 0), position);

		// プレイヤーの座標からステージ真ん中に向かうベクトル と プレイヤーの方向とのなす角を求める
		rad = VDot(verticalVector, padInputRotation) / (VSize(verticalVector) * VSize(padInputRotation));

		isChargeMove = true;
	}
}

void Player::CalculationPosition()
{
	// 速度を足す
	velocityVector = VScale(rotation, velocity);

	// スピード減衰
	if (velocity > VELOCITY_MIN)
	{
		velocity *= VELOCITY_ATTENUATION;
	}
	else if (velocity > 0)
	{
		velocity = VELOCITY_MIN;
	}

	// プレイヤー座標と回転ベクトルを足して、プレイヤーの方向を算出
	// ベクトルの始点を繋ぎ、プレイヤーの方向を出す
	if (!isLeaping)
	{
		position = VAdd(position, velocityVector);
	}
}

void Player::DrawScore(int x, int y)
{
	scorePos = ConvWorldPosToScreenPos(VAdd(position, SCORE_POSITION_ADJUSTMENT));

	for (int i = 0; i < displayScore.size(); i++)
	{
		displayScore[i].Update();
		displayScore[i].Draw((int)scorePos.x, (int)(scorePos.y + i * SCORE_POSITION_BETWEEN));
	}
}
