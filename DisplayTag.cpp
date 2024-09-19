
// �C���N���[�h
#include "DisplayTag.h"

// �萔
const int DisplayTag::RED_INIT			= 255;	// �Ԑ����������l
const int DisplayTag::GREEN_INIT		= 255;	// �ΐ����������l
const int DisplayTag::BLUE_INIT			= 255;	// �����������l

const int DisplayTag::DISPLAY_TIME		= 5000;	// �\������ (�~���b)

const int DisplayTag::TAG_GRAPH_X_SIZE	= 100;	// �^�O�摜��X�����̃T�C�Y
const int DisplayTag::TAG_GRAPH_Y_SIZE	= 50;	// �^�O�摜��Y�����̃T�C�Y

// DisplayTag�N���X�̃R���X�g���N�^
DisplayTag::DisplayTag()
{
	// �F�\���̏�����
	color.red = RED_INIT;
	color.green = GREEN_INIT;
	color.blue = BLUE_INIT;

	// �t���[�����ԏ�����
	prevTimer = GetNowCount();

	// �\���t���O������
	isVisible = true;
}

// �^�O�摜�Ɣw�i�摜�̏�����
void DisplayTag::InitGraph(int tagGraphHandle, int tagBackGraphHandle)
{
    // �^�O�摜�n���h�����
    this->tagGraphHandle = tagGraphHandle;

    // �^�O�w�i�n���h�����
    this->tagBackGraphHandle = tagBackGraphHandle;
}

// �F�̐ݒ�
void DisplayTag::SetColor(const Color_st& tagColor)
{
    color = tagColor;
}

// �\���̍X�V
void DisplayTag::Update()
{
    if (!isVisible)
    {
        return; // ��\���̏ꍇ�͉������Ȃ�
    }

    // DISPLAY_TIME�~���b�ȏ�o�߂������\���ɂ���
    if (GetNowCount() - prevTimer >= DISPLAY_TIME)
    {
        isVisible = false;
    }
}

// �^�O�̕`��
void DisplayTag::Draw(VECTOR position)
{
    if (!isVisible)
    {
        return; // ��\���̏ꍇ�͉������Ȃ�
    }

    // �L�����N�^�[�̍��W���X�N���[�����W�ɕϊ�����
    VECTOR drawPos = ConvWorldPosToScreenPos(VAdd(position, VGet(0, 25, 0)));

    // �w�i�摜��`��
    DrawExtendGraph((int)(drawPos.x - TAG_GRAPH_X_SIZE / 2.0), (int)(drawPos.y - TAG_GRAPH_Y_SIZE / 2.0),
        (int)(drawPos.x + TAG_GRAPH_X_SIZE / 2.0), (int)(drawPos.y + TAG_GRAPH_Y_SIZE / 2.0),
        tagBackGraphHandle, TRUE);

    // �F��ݒ肵�ă^�O�摜��`��
    SetDrawBright(color.red, color.green, color.blue);
    DrawExtendGraph((int)(drawPos.x - TAG_GRAPH_X_SIZE / 2.0), (int)(drawPos.y - TAG_GRAPH_Y_SIZE / 2.0),
        (int)(drawPos.x + TAG_GRAPH_X_SIZE / 2.0), (int)(drawPos.y + TAG_GRAPH_Y_SIZE / 2.0),
        tagGraphHandle, TRUE);

    // �F�����ɖ߂�
    SetDrawBright(255, 255, 255);
}

// �^�O��\�����鏈��
void DisplayTag::DoDisplay()
{
    prevTimer = GetNowCount();  // �O�̃t���[���^�C�}�[�Ɍ��݂̎��Ԃ���

    isVisible = true;           // �^�O��\����Ԃɂ���
}