#pragma once

// �Փˎ��̃X�R�A���Z����Ώۂ��󂯓n���N���X
class ScoreAddClass {
public:

	/// <summary>
	/// �X�R�A�ǉ�
	/// </summary>
	virtual void ScoreAdd() = 0;

	/// <summary>
	/// �L�����N�^�[�C���X�^���X���擾����
	/// </summary>
	/// <returns>�X�R�A�𑝉�������L�����N�^�[�C���X�^���X</returns>
	virtual ScoreAddClass* GetAddCharacter() = 0;

	/// <summary>
	/// ��΂���Ă��邩�̃t���O���擾����
	/// </summary>
	/// <returns>��΂���Ă��邩�̃t���O</returns>
	virtual bool GetIsLeaping() const = 0;
};