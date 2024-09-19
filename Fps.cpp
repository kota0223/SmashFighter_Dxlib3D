#include "Fps.h"
#include "Screen.h"

const int Fps::N = 60;		//���ς����T���v����
const int Fps::FPS = 60;	//�ݒ肵��FPS

// �R���X�g���N�^
Fps::Fps() 
	: mStartTime(0)
	, mCount(0)
	, mFps(0)
{
	// �����Ȃ�
}

// �f�X�g���N�^
Fps::~Fps()
{
	// �����Ȃ�
}

// �X�V
bool Fps::Update() {
	if (mCount == 0) { //1�t���[���ڂȂ玞�����L��
		mStartTime = GetNowCount();
	}
	if (mCount == N) { //60�t���[���ڂȂ畽�ς��v�Z����
		int t = GetNowCount();
		mFps = 1000.f / ((t - mStartTime) / (float)N);
		mCount = 0;
		mStartTime = t;
	}
	mCount++;
	return true;
}

// �`��
void Fps::Draw() {
	DrawFormatString(SCREEN_WIDTH - 100, SCREEN_HEIGHT - 100, GetColor(255, 255, 255), "%.1f", mFps);
}

// �ҋ@����
void Fps::Wait() {
	int tookTime = GetNowCount() - mStartTime;	//������������
	int waitTime = mCount * 1000 / FPS - tookTime;	//�҂ׂ�����
	if (waitTime > 0) {
		Sleep(waitTime);	//�ҋ@
	}
}

