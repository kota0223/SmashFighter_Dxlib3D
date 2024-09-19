#pragma once
#include "Screen.h"

class FadeManager
{
private:
	//定数

	static const int ALPHA_CHANGE;	// アルファを変動させる値

	static const unsigned int FADE_COLOR;	// フェード時の色

	static const int FADE_NUM_MAX;	// フェード最大値	

	//変数

	int fadeAlpha;			 // フェードの透明度
	bool isFadeIn;			 // フェードイン中かどうかのフラグ
	bool isFadeOut;			 // フェードアウト中かどうかのフラグ
	bool isFadeOutCompleted; // フェードアウトが完了したかどうかのフラグ
	bool isFadeInCompleted;	 // フェードインが完了したかどうかのフラグ

public:
	FadeManager();        // コンストラクタ
	void StartFadeIn();   // フェードインを開始するメソッド
	void StartFadeOut();  // フェードアウトを開始するメソッド

	bool IsFadingIn();			// フェードイン中かどうかを返すメソッド
	bool IsFadingOut();			// フェードアウト中かどうかを返すメソッド

	bool IsFadeOutCompleted();	//フェードアウトが完了したかどうかを返すメソッド
	bool IsFadeInCompleted();	//フェードインが完了したかどうかを返すメソッド


	void Draw();				// フェードエフェクトを描画するメソッド
	void Update();				// フェードマネージャーを更新するメソッド
};