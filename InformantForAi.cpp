#include "InformantForAi.h"
#include "Character.h"

const float InformantForAi::INIT_VECTOR_SIZE = 99999.0f;	// �G��T���ۂ̋����̏����l

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
	// ��ԋ߂��G��T���A�^�[�Q�b�g�ɐݒ肷��
	float VSizeMin = 99999.0f;
	float Size = 0.0f;

	Character* target = nullptr;

	for (int i = 0; i < characterAmount; i++)
	{
		// �^�[�Q�b�g���̍��W�Ǝ����̍��W�Ƃ̃T�C�Y���Z�o
		Size = VSize(VSub(characters[i]->GetPosition(), position));

		// ��΂���Ă��Ȃ� ���� �X�e�[�W���ɑ��݂��� ���� �������łȂ� ���� �������߂��Ȃ� �^�[�Q�b�g�ɂ���
		if (!characters[i]->GetIsLeaping() &&
			!characters[i]->GetIsStageOut() &&
			!characters[i]->GetIsRivive() &&
			Size > 0 && Size < VSizeMin)
		{
			// �T�C�Y�ŏ��l�X�V
			VSizeMin = Size;

			// �^�[�Q�b�g�ɂ���L�����N�^�[�̃|�C���^�擾
			target = characters[i];
		}
	}

	return target;
}

//=========================
// �R���X�g���N�^
//=========================
InformantForAi::InformantForAi()
    : characters(nullptr)
    , characterAmount(0)
{
}

//=========================
// �R�s�[�R���X�g���N�^
//=========================
InformantForAi::InformantForAi(const InformantForAi&)
{
    // �g�p���Ȃ�
}

//=========================
// ������Z�q
//=========================
void InformantForAi::operator=(const InformantForAi&)
{
    // �g�p���Ȃ�
}

//=========================
// �f�X�g���N�^
//=========================
InformantForAi::~InformantForAi()
{
}
