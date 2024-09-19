#include "EffectManager.h"
#include "MoveEffect.h"

EffectManager::EffectManager()
	: reviveEffect()
	, moveEffect()
	, hitEffect()
	, chargeEffect()
	, indexCircle()
	, lightGraphHandle()
	, moveEffectVertexShaderHandle()
	, hitEffectVertexShaderHandle()
	, chargeEffectVertexShaderHandle()
	, pixelShaderHandle()
{
}

EffectManager::~EffectManager()
{
}

void EffectManager::Initialize()
{
	lightGraphHandle = LoadGraph("data/image/particle/Star.png");

	moveEffectVertexShaderHandle = LoadVertexShader("data/shader/MoveEffect/MoveEffectVS.vso");

	pixelShaderHandle = LoadPixelShader("data/shader/MoveEffect/MoveEffectPS.pso");

	hitEffectVertexShaderHandle = LoadVertexShader("data/shader/HitEffect/HitEffectVS.vso");

	chargeEffectVertexShaderHandle = LoadVertexShader("data/shader/ChargeEffect/ChargeEffectVS.vso");

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

void EffectManager::CreateReviveEffect(VECTOR position)
{
	// 復活エフェクトの表示
	reviveEffect.emplace_back(new ReviveEffect(position));
}

void EffectManager::CreateHitEffect(VECTOR position, int time)
{
	hitEffect.emplace_back(new HitEffect(position, time, lightGraphHandle, hitEffectVertexShaderHandle));
}

void EffectManager::Update()
{
	for (int i = 0; i<reviveEffect.size(); i++)
	{
		reviveEffect[i]->Update();
		if (reviveEffect[i]->GetIsDelete())
		{
			reviveEffect.erase(reviveEffect.begin() + i--);
		}
	}
	for (int i = 0; i<hitEffect.size(); i++)
	{
		if (hitEffect[i]->GetTime()<0)
		{
			hitEffect.erase(hitEffect.begin() + i--);
		}
	}
	for (int i = 0; i<chargeEffect.size(); i++)
	{
		if (chargeEffect[i]->GetTime() < 0)
		{
			chargeEffect.erase(chargeEffect.begin() + i--);
		}
	}
}

void EffectManager::Draw()
{
	for (auto itr = reviveEffect.begin(); itr != reviveEffect.end(); ++itr)
	{
		(*itr)->Draw();
	}

	SetPSConstF(GetConstIndexToShader("num", pixelShaderHandle), empty);

	SetUsePixelShader(pixelShaderHandle);

	SetVSConstFMtx(58, GetCameraBillboardMatrix());

	for (auto itr = hitEffect.begin(); itr != hitEffect.end(); ++itr)
	{
		(*itr)->Draw(indexCircle);
	}

	SetUsePixelShader(0);

	for (auto itr = chargeEffect.begin(); itr != chargeEffect.end(); ++itr)
	{
		(*itr)->Draw(indexCircle);
	}
}