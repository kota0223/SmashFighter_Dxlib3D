#pragma once

// �C���N���[�h
#include "BaseScene.h"
#include "Screen.h"

// �O���錾
class Collision;
class Camera;
class ReadyTextUI;
class GoTextUI;
class TimeUpUI;
class Character;
class ParticleManager;
class Stage;
struct Color_st;

// �Q�[����ʃN���X
class Main : public BaseScene {
private:

	// �Q�[����Ԃ�\���񋓑�
	enum State
	{
		BEFORE_GAME,
		GAME,
		END,
	};

	// �萔

	static const int	  PLAYER_AMOUNT;                // �v���C���[�̐�
	static const int	  ENEMY_AMOUNT;                 // �G�̐�
	static const int	  CHARACTER_AMOUNT;             // �L���������v
	static const Color_st ENEMY_TAG_COLOR_LIST[];		// �G�̃^�O�̃J���[���̍\���̔z��
	static const float	  CHARACTER_DISPOSITION_RADIUS; // �L������z�u���钆�S����̔��a
	static const float	  PLAYER_DISPOSITION_DEGREE;    // �v���C���[��z�u���錴�_����̊p�x
	static const float	  CHARACTER_INTERVAL_DEGREE;    // �L�����Ԃ̔z�u�Ԋu(�x)

	static const VECTOR	  STAGE_MODEL_POSITION;			// �X�e�[�W���f���ʒu���W
	static const VECTOR	  STAGE_MODEL_SCALE;			// �X�e�[�W���f���X�P�[���l
	static const VECTOR	  STAGE_MODEL_ROTATION;			// �X�e�[�W���f����]�l

	static const int	  SHADOW_MAP_SIZE;				// �V���h�E�}�b�v�T�C�Y
	static const VECTOR	  SHADOW_MAP_DRAW_AREA_MIN;		// �V���h�E�}�b�v�̕`��͈͍��W�̏������ق��̒��_���W
	static const VECTOR	  SHADOW_MAP_DRAW_AREA_MAX;		// �V���h�E�}�b�v�̕`��͈͍��W�̑傫���ق��̒��_���W
	static const VECTOR	  SHADOW_MAP_LIGHT_DIRECTION;	// �V���h�E�}�b�v�̃��C�g�̕���

	static const int	  GAME_TIME;					// �Q�[���^�C��
	static const int	  GAME_START_SE_PLAY_FRAME;		// �Q�[���X�^�[�g����SE��炷�t���[����
	static const int	  GAME_START_FRAME;				// �Q�[���X�^�[�g�̃t���[����
	static const int	  COUNT_DOWN_TIME;				// �J�E���g�_�E�����n�߂�^�C��
	static const int	  TRANSITION_RESULT_FRAME;		// ���U���g�Ɉڍs����t���[����
	static const int	  READY_UI_DRAW_FRAME;			// ReadyUI��`�悷��t���[����

	static const unsigned int TIMER_COLOR;				// �^�C�}�[�����J���[
	static const unsigned int COUNT_DOWN_TIMER_COLOR;	// �J�E���g�_�E���^�C�}�[�����J���[
	static const unsigned int TIMER_EDGE_COLOR;			// �^�C�}�[�����̉����J���[
	static const int	  TIMER_FONT_EDGE_SIZE;			// �^�C�}�[�t�H���g�̉����T�C�Y

	// �ϐ�

	int i;	// ���[�v�p�ϐ�

	State				state;				// �Q�[����ԕϐ�
	Character**			characters;			// �L�����N�^�[
	ParticleManager*	particleManager;	// �p�[�e�B�N���}�l�[�W���[
	Collision*			collision;			// �R���W����
	Stage*				stage;				// �X�e�[�W
	Camera*				camera;				// �J����

	int backGround;			// �w�i�摜
	int timerFrameGraph;	// �^�C�}�[�t���[���摜

	int timerFont;	// �^�C�}�[�t�H���g

	int bgm;			// BGM�n���h��
	int whistleSE;		// �z�C�b�X��SE
	int countDownSE;	// �J�E���g�_�E��SE

	int CharaShadowMap;	// �L�����N�^�[�̃V���h�E�}�b�v�n���h��
	int StageShadowMap;	// �X�e�[�W�̃V���h�E�}�b�v�n���h��

	ReadyTextUI*	readyTextUI;	// Ready�e�L�X�gUI
	GoTextUI*		goTextUI;		// Go�e�L�X�gUI
	TimeUpUI*		timeUpUI;		// TimeUp�e�L�X�gUI

	int frame;			// �t���[��
	int cnt;			// �J�E���g
	int Timer;			// �^�C�}�[
	int prevTimer;		// �O�t���[���̎���
	int prevCount;		// �Q�[���O�̃^�C�}�[�J�E���^
	bool isGameActive;	// �Q�[���A�N�e�B�u�t���O
	bool isGameEnd;		// �Q�[���I���t���O
	
	void UpdateStart();			// �X�^�[�g��
	void UpdateGame();			// �Q�[����
	void UpdateEnd();			// �I����
	void (Main::* pUpdate)();	// Update�֐��|�C���^

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="changer">�V�[���؂�ւ��C���^�[�t�F�[�X</param>
	Main(ISceneChanger* changer);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	Main();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// �I������
	/// </summary>
	void Finalize() override;

	/// <summary>
	/// �X�V
	/// </summary>
	void Update() override;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw() override;

	/// <summary>
	/// �f���v���C���̏�����
	/// </summary>
	void InitDemo();

	/// <summary>
	/// �f���v���C���̍X�V
	/// </summary>
	void UpdateDemo();

	/// <summary>
	/// �f���v���C���̕`��
	/// </summary>
	void DrawDemo();
};