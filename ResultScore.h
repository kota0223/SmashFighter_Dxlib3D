#pragma once
#include <string>
#include <utility>
#include <vector>

#include "TagStruct.h"

// リザルト用スコアクラス
class ResultScore {
private:

	// 定数

	static const int SCORE_FONT_EDGE_SIZE;	// スコアフォントの縁取りサイズ
	static const int NAME_FONT_EDGE_SIZE;	// 名前フォントの縁取りサイズ
	static const int RANK_NUM;				// 順位の数
	static const int MOVE_X_ADD_NUM;		// X座標移動量の増加数
	static const int ALPHA_ADD_NUM;			// アルファ値の増加数
	static const int MOVE_X_MAX;			// X座標移動量の最大値

	static const int RANK_X_INTERVAL;		// 順位描画のX座標の間隔
	static const int RANK_Y_INTERVAL;		// 順位描画のY座標の間隔
	
	static const int FRAME_GRAPH_X;			// フレーム画像のX座標基準値
	static const int FRAME_GRAPH_Y;			// フレーム画像のY座標基準値

	static const int RANK_GRAPH_X;			// 順位画像のX座標基準値
	static const int RANK_GRAPH_Y;			// 順位画像のY座標基準値

	static const int TAG_GRAPH_X;			// タグ画像のX座標基準値
	static const int TAG_GRAPH_Y;			// タグ画像のY座標基準値
	static const int FRAME_GRAPH_WIDTH;		// タグ画像の幅
	static const int FRAME_GRAPH_HEIGHT;	// タグ画像の高さ

	static const int SCORE_TEXT_X;			// スコアテキストのX座標基準値
	static const int SCORE_TEXT_Y;			// スコアテキストのY座標基準値
	static const int PT_TEXT_X;				// "pt"テキストのX座標基準値

	// 変数

	std::vector<std::pair<int, Tag_st>> resultScore;	// リザルトスコア配列

	int rank[4] = { 1,2,3,4 };	// 順位配列
	bool rankVisible[4];		// 順位描画フラグ

	int frameGraph;		// フレーム画像ハンドル
	int rankGraph[4];	// 順位別画像ハンドル
	int fontHandle;		// フォントハンドル
	int nameFont;		// 名前フォント

	int drawSE;		// 描画時のSE
	int drawSE2;	// 描画時のSE2

	int i, j;		// 汎用ループ変数

	int drawNum;	// 描画数
	int visibleNum;	// 表示数

	int moveX;		// 移動X量
	int alpha;		// 透明度

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ResultScore();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ResultScore();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// スコア追加
	/// </summary>
	/// <param name="score">スコア</param>
	/// <param name="Tag">タグの構造体</param>
	void AddScore(int score, Tag_st Tag);

	/// <summary>
	/// リザルトスコア描画
	/// </summary>
	/// <param name="x">X座標</param>
	/// <param name="y">Y座標</param>
	void Draw(int x, int y);

	/// <summary>
	/// 同率順位の設定
	/// </summary>
	void SetRank();
};