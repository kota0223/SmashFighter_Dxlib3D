#include "Stage.h"

//�萔��`

const float Stage::RANGE = 80.0f;	//�X�e�[�W�͈͂̔��a

Stage::Stage(const std::string filePath, VECTOR position)
	: position(position)
{
	// ���f���n���h���ǂݍ���
	modelHandle = MV1LoadModel(filePath.c_str());

	// ���W�ݒ�
	MV1SetPosition(modelHandle, position);
}

Stage::~Stage()
{
	MV1DeleteModel(modelHandle);
}

void Stage::Draw()
{
	//�X�e�[�W�̕`��
	MV1DrawModel(modelHandle);
}