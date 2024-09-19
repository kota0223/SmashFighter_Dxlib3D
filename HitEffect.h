#pragma once

// �C���N���[�h
#include "DxLib.h"

/// <summary>
/// �q�b�g�G�t�F�N�g
/// </summary>
class HitEffect {
private:

	// �萔

	static const int CIRCLE_VERTEX_NUM = 22;				// ��̉~�̒��_�̐�
	static const int VERTEX_NUM = (CIRCLE_VERTEX_NUM*2)+2;	// �S�̂̒��_�̐�

	static const int		VS_CONST_MATRIX_NUM;				// ���_�V�F�[�_�s��̒萔�ԍ�
	static const int		VS_CONST_NUM;						// ���_�V�F�[�_�̒萔�ԍ�
	static const float		POLYGON_SCALE;						// �G�t�F�N�g�̃|���S���X�P�[���l
	static const COLOR_U8	EFFECT_COLOR;						// �G�t�F�N�g�J���[
	static const float		LIGHT_EFFECT_TIME;					// ����G�t�F�N�g�̎���
	static const float		POLYGON_TEXTURE_POSITION_INTERVAL;	// �|���S���̃e�N�X�`�����W�̃��[�v�Ԋu
	static const int		LIGHT_GRAPH_COLOR[3];				// ���C�g�摜�̐F
	static const float		SCALE_CHANGE_SIZE;					// �X�P�[���ω��̑傫��
	static const float		LIGHT_EFFECT_SCALE_X;				// ����G�t�F�N�g��X���̑傫��
	static const float		LIGHT_EFFECT_SCALE_Y;				// ����G�t�F�N�g��Y���̑傫��
	static const float		LIGTH_EFFECT_ROTATION_SPEED;		// ����G�t�F�N�g�̉�]���x
	static const float		EFFECT_TIME;						// �G�t�F�N�g����

	// �ϐ�

	VERTEX3DSHADER drawVertex[VERTEX_NUM]; // �|���S�����_

	VECTOR lightGraphPos[4] = { {-15,15,0} 
								,{15,15,0}
								,{15,-15,0}
								,{-15,-15,0} };	// ���摜���W

	VECTOR position;		// ���W
	int vertexShaderHandle;	// ���_�V�F�[�_�[�n���h��
	int timer;				// �^�C�}�[
	int lightTimer;			// ����G�t�F�N�g�^�C�}�[
	int lightGraphHandle;	// ���摜�n���h��
							
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�\�����W</param>
	/// <param name="time">�`�掞��</param>
	/// <param name="graphHandle">�摜�n���h��</param>
	/// <param name="vertexShader">���_�V�F�[�_�[�n���h��</param>
	HitEffect(VECTOR pos,int time, int graphHandle, int vertexShader);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~HitEffect();

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="index">�|���S���̃C���f�b�N�X�z��</param>
	void Draw(WORD index[]);

	/// <summary>
	/// ���Ԏ擾
	/// </summary>
	/// <returns>�G�t�F�N�g�̃^�C�}�[</returns>
	int GetTime() { return timer; }
};