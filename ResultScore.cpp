#include "DxLib.h"
#include <algorithm>
#include "ResultScore.h"

const int ResultScore::SCORE_FONT_EDGE_SIZE = 3;	// スコアフォントの縁取りサイズ
const int ResultScore::NAME_FONT_EDGE_SIZE = 3;		// 名前フォントの縁取りサイズ

const int ResultScore::RANK_NUM = 4;				// 順位の数
const int ResultScore::MOVE_X_ADD_NUM = 5;			// X座標移動量の増加数
const int ResultScore::ALPHA_ADD_NUM = 10;			// アルファ値の増加数
const int ResultScore::MOVE_X_MAX = 200;			// X座標移動量の最大値
		  
const int ResultScore::RANK_X_INTERVAL = 110;		// 順位描画のX座標の間隔
const int ResultScore::RANK_Y_INTERVAL = 120;		// 順位描画のY座標の間隔
		  
const int ResultScore::FRAME_GRAPH_X = 700;			// フレーム画像のX座標基準値
const int ResultScore::FRAME_GRAPH_Y = 550;			// フレーム画像のY座標基準値
		  
const int ResultScore::RANK_GRAPH_X = 620;			// 順位画像のX座標基準値
const int ResultScore::RANK_GRAPH_Y = 500;			// 順位画像のY座標基準値
		  
const int ResultScore::TAG_GRAPH_X = 760;			// タグ画像のX座標基準値
const int ResultScore::TAG_GRAPH_Y = 550;			// タグ画像のY座標基準値
const int ResultScore::FRAME_GRAPH_WIDTH = 128;		// タグ画像の幅
const int ResultScore::FRAME_GRAPH_HEIGHT = 64;		// タグ画像の高さ
		  
const int ResultScore::SCORE_TEXT_X = 940;			// スコアテキストのX座標基準値
const int ResultScore::SCORE_TEXT_Y = 550;			// スコアテキストのY座標基準値
const int ResultScore::PT_TEXT_X = 1020;			// "pt"テキストのX座標基準値

// コンストラクタ
ResultScore::ResultScore()
{
	// 処理なし
}

// デストラクタ
ResultScore::~ResultScore()
{
	// 処理なし
}

// 初期化
void ResultScore::Initialize()
{
	frameGraph = LoadGraph("data/image/Result/ResultFrame.png");

	rankGraph[0] = LoadGraph("data/image/Result/1st.png");
	rankGraph[1] = LoadGraph("data/image/Result/2nd.png");
	rankGraph[2] = LoadGraph("data/image/Result/3rd.png");
	rankGraph[3] = LoadGraph("data/image/Result/4th.png");

	fontHandle = LoadFontDataToHandle("data/fonts/ResultScoreFont.dft", SCORE_FONT_EDGE_SIZE);
	nameFont = LoadFontDataToHandle("data/fonts/Impact.dft", NAME_FONT_EDGE_SIZE);

	drawSE = LoadSoundMem("data/sounds/Result/drawSE.mp3");

	drawSE2 = LoadSoundMem("data/sounds/Result/drawSE2.mp3");

	for (int i = 0; i < RANK_NUM; i++)
	{
		rankVisible[i] = false;
	}

	drawNum = 0;

	visibleNum = 0;

	alpha = 0;
}

// スコア追加
void ResultScore::AddScore(int score, Tag_st Tag)
{
	// スコア代入
	resultScore.push_back(std::make_pair(score, Tag));

	// スコアを降順に並び変える
	sort(resultScore.begin(), resultScore.end(), [&](std::pair<int, Tag_st> i, std::pair<int, Tag_st> j) {
		return j.first < i.first;
		});
}

// 描画
void ResultScore::Draw(int x, int y)
{
	// 描画するものが0なら描画するものを探す
	if (drawNum == 0)
	{
		for (i = 3; i >= 0; i--)
		{
			if (rankVisible[i])
				continue;

			for (j = 0; j < RANK_NUM; j++)
			{
				if (rank[j] == i + 1)
				{
					drawNum++;
				}
			}

			if (drawNum > 0)
			{
				PlaySoundMem(drawSE, DX_PLAYTYPE_BACK);
				rankVisible[i] = true;
				break;
			}
		}
	}
	else
	{
		// UIのアニメーション
		moveX += MOVE_X_ADD_NUM;
		alpha += ALPHA_ADD_NUM;

		// Xの移動地が最大量に達したとき
		if (moveX >= MOVE_X_MAX)
		{
			// SEを再生
			PlaySoundMem(drawSE2, DX_PLAYTYPE_BACK);

			// 表示数を加算
			visibleNum += drawNum;

			// 変数の初期化
			drawNum = 0;
			moveX = 0;
			alpha = 0;
		}

		// 透明度適用
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

		// フレーム画像描画
		for (i = 0; i < drawNum; i++)
		{
			DrawGraph(FRAME_GRAPH_X - RANK_X_INTERVAL * (i + visibleNum) + MOVE_X_MAX - moveX,
				FRAME_GRAPH_Y - RANK_Y_INTERVAL * (i + visibleNum), frameGraph, TRUE);
		}

		// 透明度リセット
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, NULL);
	}

	// 表示させたものを描画する
	for (i = 0; i < visibleNum; i++)
	{
		// フレーム描画
		DrawGraph(FRAME_GRAPH_X - RANK_X_INTERVAL * i,
			FRAME_GRAPH_Y - RANK_Y_INTERVAL * i, frameGraph, TRUE);

		// 順位描画
		DrawGraph(RANK_GRAPH_X - RANK_X_INTERVAL * i, RANK_GRAPH_Y - RANK_Y_INTERVAL * i, rankGraph[rank[3 - i] - 1], TRUE);

		// タグ背景描画
		DrawExtendGraph(TAG_GRAPH_X - RANK_X_INTERVAL * i,
						TAG_GRAPH_Y - RANK_Y_INTERVAL * i,
						TAG_GRAPH_X - RANK_X_INTERVAL * i + FRAME_GRAPH_WIDTH,
						TAG_GRAPH_Y - RANK_Y_INTERVAL * i + FRAME_GRAPH_HEIGHT, resultScore[3 - i].second.tagBaseGraph, TRUE);

		
		// 色設定
		SetDrawBright(resultScore[3 - i].second.red, resultScore[3 - i].second.green, resultScore[3 - i].second.blue);

		// タグ描画
		DrawExtendGraph(TAG_GRAPH_X - RANK_X_INTERVAL * i,
						TAG_GRAPH_Y - RANK_Y_INTERVAL * i,
						TAG_GRAPH_X - RANK_X_INTERVAL * i + FRAME_GRAPH_WIDTH,
						TAG_GRAPH_Y - RANK_Y_INTERVAL * i + FRAME_GRAPH_HEIGHT, resultScore[3 - i].second.tagGraph, TRUE);

		// 色リセット
		SetDrawBright(255, 255, 255);

		// スコア描画
		DrawStringToHandle(SCORE_TEXT_X - RANK_X_INTERVAL * i,
			SCORE_TEXT_Y - RANK_Y_INTERVAL * i, std::to_string(resultScore[3 - i].first).c_str(),
			GetColor(240, 145, 62), fontHandle, GetColor(255, 255, 255));

		// スコアの後につける"pt"の文字描画
		DrawStringToHandle(PT_TEXT_X - RANK_X_INTERVAL * i,
			SCORE_TEXT_Y - RANK_Y_INTERVAL * i, "pt",
			GetColor(240, 145, 62), fontHandle, GetColor(255, 255, 255));
	}
}

// 道立順位の設定
void ResultScore::SetRank()
{
	// 同率の順位が存在するかチェックし、並び変える
	for (i = 0; i < 3; i++)
	{
		if (resultScore[i].first == resultScore[i + 1].first)
		{
			rank[i + 1] = rank[i];
			for (j = i + 2; j < 4; j++)
			{
				rank[j] = rank[j - 1] + 1;
			}
		}
	}
}
