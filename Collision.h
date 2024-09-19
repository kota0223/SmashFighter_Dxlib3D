#pragma once

// �C���N���[�h
#include "Camera.h"

// �O���錾
class Character;

/// <summary>
/// �Փ˔���N���X
/// </summary>
class Collision {
private:

	// �萔

	static const float REVIVE_COLLISION_SPEED;	// �������̏Փ˂̑��x�����l
	static const float CAMERA_SHAKE_SPEED_NUM;	// �J������h�炷��̑��x
	static const int   CAMERA_SHAKE_TIME;			// �J������h�炷����

	// �ϐ�

	int i, j;	// �ėp���[�v�ϐ�

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Collision();

	/// <summary>
	/// �ڐG����
	/// </summary>
	/// <param name="characters">Character*�^ �ڐG���������L�����N�^�[�̃|�C���^�z��</param>
	/// <param name="size">int�^ �z��̃T�C�Y</param>
	void JudgCollision(Character* characters[], int size, Camera& camera);
};