#pragma once

#include <DxLib.h>
#include <string>

class Stage {
private:
	//�萔

	static const float RANGE;	//�X�e�[�W�͈̔͂̔��a

	//�ϐ�

	VECTOR position;	//�X�e�[�W�̒��S���W

	int modelHandle;	//�X�e�[�W�̃��f���n���h��

	float range;		//�X�e�[�W�͈̔͂̔��a

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Stage(const std::string filePath, VECTOR position);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Stage();

	/// <summary>
	/// �X�e�[�W��`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �X�e�[�W�̔��a���擾
	/// </summary>
	/// <returns>Float �X�e�[�W�̔��a</returns>
	const float GetRange() const { return RANGE; }

	/// <summary>
	/// �X�e�[�W�̍��W���擾
	/// </summary>
	/// <returns>VECTOR�^ �X�e�[�W�̍��W</returns>
	const VECTOR GetPosition() const{ return position; }

	/// <summary>
	/// ���f���̊g�嗦��ݒ�
	/// </summary>
	/// <param name="scale">VECTOR�^ ���f���̊g�嗦</param>
	void SetModelScale(const VECTOR scale) { MV1SetScale(modelHandle, scale); }

	/// <summary>
	/// ���f���̉�]�l��ݒ�
	/// </summary>
	/// <param name="rotation">VECTOR�^ ���f���̉�]�l</param>
	void SetModelRotation(const VECTOR rotation) { MV1SetRotationXYZ(modelHandle, rotation); }
};