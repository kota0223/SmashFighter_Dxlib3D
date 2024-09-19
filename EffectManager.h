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

	// �e�G�t�F�N�g�̐����֐�
	void CreateReviveEffect(VECTOR position);

	void CreateHitEffect(VECTOR position, int time);

	void Update();

	void Draw();

private:

	int i;

	// �����G�t�F�N�g�N���X
	std::vector<ReviveEffect*> reviveEffect;

	std::vector<MoveEffect*> moveEffect;

	std::vector<HitEffect*> hitEffect;

	std::vector<ChargeEffect*> chargeEffect;

	WORD indexCircle[(20 * 2 + 2) * 3];

	int lightGraphHandle;

	// ���_�V�F�[�_�[�n���h��
	int moveEffectVertexShaderHandle;

	int hitEffectVertexShaderHandle;

	int chargeEffectVertexShaderHandle;

	// �s�N�Z���V�F�[�_�[�n���h��
	int pixelShaderHandle;

	FLOAT4 empty = { 0 };
};