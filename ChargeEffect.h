#pragma once

// �C���N���[�h
#include "DxLib.h"

/// <summary>
/// �`���[�W�G�t�F�N�g
/// </summary>
class ChargeEffect {
private:

	// �萔

	static const int CIRCLE_VERTEX_NUM = 22;					// ��̉~�̒��_�̐�
	static const int VERTEX_NUM = (CIRCLE_VERTEX_NUM*2);		// �S�̂̒��_�̐�

	static const int	  VS_CONST_MATRIX_NUM;					// ���_�V�F�[�_�s��̒萔�ԍ�
	static const int	  VS_CONST_NUM;							// ���_�V�F�[�_�̒萔�ԍ�
	static const COLOR_U8 POLYGON_OUTSIDE_COLOR;				// �|���S���O���̃J���[
	static const COLOR_U8 POLYGON_INSIDE_COLOR;					// �|���S�������̃J���[
	static const float	  POLYGON_TEXTURE_POSITION_INTERVAL;	// �|���S���̃e�N�X�`�����W�̃��[�v�Ԋu
	static const float	  POLYGON_SCALE;						// �G�t�F�N�g�̃|���S���X�P�[���l
	static const int	  LIGHT_GRAPH_COLOR[3];					// ���C�g�摜�̐F
	static const float	  EFFECT_TIME;							// �G�t�F�N�g����

	// �ϐ�

	VERTEX3DSHADER drawVertex[VERTEX_NUM];	// �|���S�����_

	VECTOR lightGraphPos[4] = { {-50,50,0}	
								,{50,50,0}
								,{50,-50,0}
								,{-50,-50,0} };	// ���摜���W

	VECTOR position;			// ���W
	int	   vertexShaderHandle;	// ���_�V�F�[�_�[�n���h��
	int	   startTime;			// �J�n���ԕۑ��ϐ�
	int	   timer;				// �^�C�}�[
	int	   lightTimer;			// ����G�t�F�N�g�^�C�}�[
	int	   lightGraphHandle;	// ���摜�n���h��

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�\�����W</param>
	/// <param name="time">�\������</param>
	/// <param name="graphHandle">�摜�n���h��</param>
	/// <param name="vertexShader">���_�V�F�[�_�n���h��</param>
	ChargeEffect(VECTOR pos,int time, int graphHandle, int vertexShader);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ChargeEffect();

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="index">�|���S���̃C���f�b�N�X�z��</param>
	void Draw(WORD index[]);

	/// <summary>
	/// ���Ԃ̎擾
	/// </summary>
	/// <returns>�G�t�F�N�g�̃^�C�}�[</returns>
	int GetTime() { return timer; }
};