
// �C���N���[�h
#include <math.h>
#include "Collision.h"
#include "Character.h"

// �萔
const float Collision::REVIVE_COLLISION_SPEED = 1.5f;	// �������̏Փ˂̑��x�����l;
const float Collision::CAMERA_SHAKE_SPEED_NUM = 3.0f;	// �J������h�炷��̑��x
const int	Collision::CAMERA_SHAKE_TIME	  = 30;		// �J������h�炷����

Collision::Collision()
{
	//�����Ȃ�
}

// �ڐG����
void Collision::JudgCollision(Character* characters[], int size, Camera& camera)
{
	for (i = 0; i < size - 1; i++)
	{
		// �X�e�[�W���痎�����画�肵�Ȃ�
		if (characters[i]->GetIsStageOut())
		{
			continue;
		}

		for (j = i + 1; j < size; j++)
		{
			// �X�e�[�W���痎�����画�肵�Ȃ�
			if (characters[j]->GetIsStageOut())
			{
				continue;
			}

			//�O�����̒藝�𗘗p���������蔻��
			if (VSquareSize(VSub(characters[i]->GetPosition(), characters[j]->GetPosition()))
				< pow(characters[i]->GetCollisionRange() + characters[j]->GetCollisionRange(), 2))
			{
				// ���肪�������
				VECTOR Directions = VSub(characters[j]->GetPosition(), characters[i]->GetPosition());

				// ������鑬�x�ϐ�
				float velocity_i;
				float velocity_j;

				// �����t���O�������Ă���Ƃ��ɏ�������
				// �ڐG���������������o��
				if (characters[i]->GetIsRivive() || characters[j]->GetIsRivive())
				{
					// �L�����N�^�[i�Ԃ̓����蔻��̔��a + �L�����N�^�[j�Ԃ̓����蔻��̔��a - �L�����N�^�[���m�̋��� / �L�����N�^�[i�Ԃ̓����蔻��̔��a + �L�����N�^�[j�Ԃ̓����蔻��̔��a
					// �ڐG���Ă��鋗�����Z�o
					float d = (characters[i]->GetCollisionRange() + characters[j]->GetCollisionRange() - VSize(Directions))
						/ (characters[i]->GetCollisionRange() + characters[j]->GetCollisionRange());

					// ���x����
					velocity_i = REVIVE_COLLISION_SPEED * d;
					velocity_j = REVIVE_COLLISION_SPEED * d;
				}
				else
				{
					// ���K��
					if (VSize(Directions) > 0)
					{
						Directions = VNorm(Directions);
					}

					// �L�����N�^�[�̑��x�x�N�g���ƏՓ˃L�����N�^�[���m�̋����x�N�g���̓��ς��Z�o
					float velocityDoti = VDot(characters[i]->GetVelocityVector(), Directions);
					float velocityDotj = VDot(characters[j]->GetVelocityVector(), VScale(Directions, -1));

					// ���Α��x�Z�o
					velocity_i = velocityDoti - (velocityDoti - velocityDotj);
					velocity_j = velocityDotj - (velocityDotj - velocityDoti);
				}

				// ���K��
				if (VSize(Directions) > 0)
				{
					Directions = VNorm(Directions);
				}

				// �J������h�炷
				if (velocity_i + velocity_j >= CAMERA_SHAKE_SPEED_NUM)
				{
					camera.SetShakeTime(CAMERA_SHAKE_TIME);
				}

				//��΂������p�Ɣ�΂���鑬�x����
				characters[i]->DoHit(VScale(Directions, -1), velocity_i, characters[j]);

				//��΂������p�Ɣ�΂���鑬�x����
				characters[j]->DoHit(Directions, velocity_j, characters[i]);

				// �ڐG�t���O�𗧂Ă�
				characters[i]->EnableIsLeaping();

				// �ڐG�t���O�𗧂Ă�
				characters[j]->EnableIsLeaping();


			}

		}
	}

}