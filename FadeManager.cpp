#include "DxLib.h"
#include "FadeManager.h"

const int	FadeManager::ALPHA_CHANGE = 7;	// アルファを変動させる値

const unsigned int FadeManager::FADE_COLOR = GetColor(255, 255, 255);	// フェード時の色

const int FadeManager::FADE_NUM_MAX = 255;	// フェード最大値	

FadeManager::FadeManager()
{
	fadeAlpha = 0;    // 初期の透明度は0
	isFadeIn = false;  // フェードイン中のフラグはfalse
	isFadeOut = false; // フェードアウト中のフラグはfalse
}

void FadeManager::StartFadeIn()
{
	if (!isFadeIn)
	{
		isFadeIn = true;		 // フェードイン中のフラグを立てる
		isFadeInCompleted = false;	 // フェードイン完了フラグを下す
		fadeAlpha = FADE_NUM_MAX;
	}
}

void FadeManager::StartFadeOut()
{
	if (!isFadeOut)
	{
		isFadeOut = true; // フェードアウト中のフラグを立てる

		isFadeOutCompleted = false; // フェードアウト完了フラグを下す

		fadeAlpha = 0;
	}
}

bool FadeManager::IsFadingIn()
{
	return isFadeIn;  // フェードイン中のフラグを返す
}

bool FadeManager::IsFadingOut()
{
	return isFadeOut; // フェードアウト中のフラグを返す
}

bool FadeManager::IsFadeInCompleted()
{
	return 	isFadeInCompleted;
}

bool FadeManager::IsFadeOutCompleted()
{
	return isFadeOutCompleted;
}

void FadeManager::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeAlpha);  // ブレンドモードを設定して透明度を反映
	DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, FADE_COLOR, TRUE);  // 白い四角形を描画
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, NULL);  // ブレンドモードを元に戻す
}

void FadeManager::Update()
{
	if (isFadeIn)
	{
		fadeAlpha -= ALPHA_CHANGE;  // 不透明度を減少させる

		if (fadeAlpha <= 0)
		{
			fadeAlpha = 0;
			isFadeIn = false;  // フェードインが完了したらフラグを下ろす
			isFadeInCompleted = true;// フェードインが完了したフラグを立てる
		}
	}

	if (isFadeOut)
	{
		fadeAlpha += ALPHA_CHANGE;  // 不透明度を増加させる

		if (fadeAlpha >= FADE_NUM_MAX)
		{
			fadeAlpha = FADE_NUM_MAX;

			isFadeOut = false;  // フェードアウトが完了したらフラグを下ろす
			isFadeOutCompleted = true; // フェードアウトが完了したフラグを立てる
		}
	}
}


