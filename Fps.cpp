#include "Fps.h"
#include "Screen.h"

const int Fps::N = 60;		//平均を取るサンプル数
const int Fps::FPS = 60;	//設定したFPS

// コンストラクタ
Fps::Fps() 
	: mStartTime(0)
	, mCount(0)
	, mFps(0)
{
	// 処理なし
}

// デストラクタ
Fps::~Fps()
{
	// 処理なし
}

// 更新
bool Fps::Update() {
	if (mCount == 0) { //1フレーム目なら時刻を記憶
		mStartTime = GetNowCount();
	}
	if (mCount == N) { //60フレーム目なら平均を計算する
		int t = GetNowCount();
		mFps = 1000.f / ((t - mStartTime) / (float)N);
		mCount = 0;
		mStartTime = t;
	}
	mCount++;
	return true;
}

// 描画
void Fps::Draw() {
	DrawFormatString(SCREEN_WIDTH - 100, SCREEN_HEIGHT - 100, GetColor(255, 255, 255), "%.1f", mFps);
}

// 待機処理
void Fps::Wait() {
	int tookTime = GetNowCount() - mStartTime;	//かかった時間
	int waitTime = mCount * 1000 / FPS - tookTime;	//待つべき時間
	if (waitTime > 0) {
		Sleep(waitTime);	//待機
	}
}

