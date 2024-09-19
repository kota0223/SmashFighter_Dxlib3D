#pragma once

#include <vector>
#include "ReviveEffect.h"
#include "HitEffect.h"
#include "ChargeEffect.h"

class MoveEffect;
class Character;

class EffectManager {

public:
	EffectManager();

	~EffectManager();

	void Initialize();

	// 各エフェクトの生成関数
	void CreateReviveEffect(VECTOR position);

	void CreateHitEffect(VECTOR position, int time);

	void Update();

	void Draw();

private:

	int i;

	// 復活エフェクトクラス
	std::vector<ReviveEffect*> reviveEffect;

	std::vector<MoveEffect*> moveEffect;

	std::vector<HitEffect*> hitEffect;

	std::vector<ChargeEffect*> chargeEffect;

	WORD indexCircle[(20 * 2 + 2) * 3];

	int lightGraphHandle;

	// 頂点シェーダーハンドル
	int moveEffectVertexShaderHandle;

	int hitEffectVertexShaderHandle;

	int chargeEffectVertexShaderHandle;

	// ピクセルシェーダーハンドル
	int pixelShaderHandle;

	FLOAT4 empty = { 0 };
};