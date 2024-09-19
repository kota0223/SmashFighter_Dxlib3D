#include "InformantForAi.h"
#include "Character.h"

const float InformantForAi::INIT_VECTOR_SIZE = 99999.0f;	// 敵を探す際の距離の初期値

void InformantForAi::Initialize(Character** characters, int size)
{
    this->characters = characters;
    characterAmount = size;
}

InformantForAi& InformantForAi::GetInstance()
{
    static InformantForAi InformantForAi;
    return InformantForAi;
}

Character* InformantForAi::GetAttackTarget(const VECTOR& position)
{
	// 一番近い敵を探し、ターゲットに設定する
	float VSizeMin = 99999.0f;
	float Size = 0.0f;

	Character* target = nullptr;

	for (int i = 0; i < characterAmount; i++)
	{
		// ターゲット候補の座標と自分の座標とのサイズを算出
		Size = VSize(VSub(characters[i]->GetPosition(), position));

		// 飛ばされていない かつ ステージ内に存在する かつ 復活中でない かつ 距離が近いなら ターゲットにする
		if (!characters[i]->GetIsLeaping() &&
			!characters[i]->GetIsStageOut() &&
			!characters[i]->GetIsRivive() &&
			Size > 0 && Size < VSizeMin)
		{
			// サイズ最小値更新
			VSizeMin = Size;

			// ターゲットにするキャラクターのポインタ取得
			target = characters[i];
		}
	}

	return target;
}

//=========================
// コンストラクタ
//=========================
InformantForAi::InformantForAi()
    : characters(nullptr)
    , characterAmount(0)
{
}

//=========================
// コピーコンストラクタ
//=========================
InformantForAi::InformantForAi(const InformantForAi&)
{
    // 使用しない
}

//=========================
// 代入演算子
//=========================
void InformantForAi::operator=(const InformantForAi&)
{
    // 使用しない
}

//=========================
// デストラクタ
//=========================
InformantForAi::~InformantForAi()
{
}
