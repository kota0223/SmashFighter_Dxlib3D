//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "DxLib.h"
#include "SceneManager.h"
#include "Screen.h"
#include "Fps.h"
#include "ModelManager.h"

//-----------------------------------------------------------------------------
//	@brief	���C������
//-----------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// �����������g�p���Ȃ�
	SetWaitVSyncFlag(FALSE);

	// ��������Ȃ��ƃV�F�[�_�[���g���Ȃ�
	SetUseDirect3DVersion(DX_DIRECT3D_9EX);

	// �c�w���C�u��������������
	if (DxLib_Init() == -1)
	{
		return -1;	// �G���[���N�����璼���ɏI��
	}

	// ��ʃ��[�h�̃Z�b�g
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);
	ChangeWindowMode(FALSE);

	// �`���𗠉�ʂɐݒ�
	SetDrawScreen(DX_SCREEN_BACK);

	//-----------------------------------------------------------------------------
	// �V�[���}�l�[�W���[�C���X�^���X
	//-----------------------------------------------------------------------------

	SceneManager sceneMgr;

	sceneMgr.Initialize();	// ������

	//-----------------------------------------------------------------------------
	// FPS����N���X�C���X�^���X
	//-----------------------------------------------------------------------------

	Fps fps;

	ModelManager::GetInstance();      // ���f���Ǘ��N���X�̐���

	//-----------------------------------------------------------------------------
	// ���C�����[�v
	//-----------------------------------------------------------------------------
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 &&
		CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		fps.Update();		// FPS����

		clsDx();			// �ȈՉ�ʏo�͂��N���A

		sceneMgr.Update();	// �V�[������

		sceneMgr.Draw();	// �V�[���`��
		
		fps.Wait();			// FPS����̂��߂̒�~����
	}

	DxLib_End();			// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}