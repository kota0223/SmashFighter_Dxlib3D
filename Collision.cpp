
// インクルード
#include <math.h>
#include "Collision.h"
#include "Character.h"

// 定数
const float Collision::REVIVE_COLLISION_SPEED = 1.5f;	// 復活時の衝突の速度調整値;
const float Collision::CAMERA_SHAKE_SPEED_NUM = 3.0f;	// カメラを揺らす基準の速度
const int	Collision::CAMERA_SHAKE_TIME	  = 30;		// カメラを揺らす時間

Collision::Collision()
{
	//処理なし
}

// 接触判定
void Collision::JudgCollision(Character* characters[], int size, Camera& camera)
{
	for (i = 0; i < size - 1; i++)
	{
		// ステージから落ちたら判定しない
		if (characters[i]->GetIsStageOut())
		{
			continue;
		}

		for (j = i + 1; j < size; j++)
		{
			// ステージから落ちたら判定しない
			if (characters[j]->GetIsStageOut())
			{
				continue;
			}

			//三平方の定理を利用した当たり判定
			if (VSquareSize(VSub(characters[i]->GetPosition(), characters[j]->GetPosition()))
				< pow(characters[i]->GetCollisionRange() + characters[j]->GetCollisionRange(), 2))
			{
				// 相手がいる方向
				VECTOR Directions = VSub(characters[j]->GetPosition(), characters[i]->GetPosition());

				// 代入する速度変数
				float velocity_i;
				float velocity_j;

				// 復活フラグが立っているときに処理する
				// 接触した距離分押し出す
				if (characters[i]->GetIsRivive() || characters[j]->GetIsRivive())
				{
					// キャラクターi番の当たり判定の半径 + キャラクターj番の当たり判定の半径 - キャラクター同士の距離 / キャラクターi番の当たり判定の半径 + キャラクターj番の当たり判定の半径
					// 接触している距離を算出
					float d = (characters[i]->GetCollisionRange() + characters[j]->GetCollisionRange() - VSize(Directions))
						/ (characters[i]->GetCollisionRange() + characters[j]->GetCollisionRange());

					// 速度調整
					velocity_i = REVIVE_COLLISION_SPEED * d;
					velocity_j = REVIVE_COLLISION_SPEED * d;
				}
				else
				{
					// 正規化
					if (VSize(Directions) > 0)
					{
						Directions = VNorm(Directions);
					}

					// キャラクターの速度ベクトルと衝突キャラクター同士の距離ベクトルの内積を算出
					float velocityDoti = VDot(characters[i]->GetVelocityVector(), Directions);
					float velocityDotj = VDot(characters[j]->GetVelocityVector(), VScale(Directions, -1));

					// 相対速度算出
					velocity_i = velocityDoti - (velocityDoti - velocityDotj);
					velocity_j = velocityDotj - (velocityDotj - velocityDoti);
				}

				// 正規化
				if (VSize(Directions) > 0)
				{
					Directions = VNorm(Directions);
				}

				// カメラを揺らす
				if (velocity_i + velocity_j >= CAMERA_SHAKE_SPEED_NUM)
				{
					camera.SetShakeTime(CAMERA_SHAKE_TIME);
				}

				//飛ばされる方角と飛ばされる速度を代入
				characters[i]->DoHit(VScale(Directions, -1), velocity_i, characters[j]);

				//飛ばされる方角と飛ばされる速度を代入
				characters[j]->DoHit(Directions, velocity_j, characters[i]);

				// 接触フラグを立てる
				characters[i]->EnableIsLeaping();

				// 接触フラグを立てる
				characters[j]->EnableIsLeaping();


			}

		}
	}

}