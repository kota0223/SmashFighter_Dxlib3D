#pragma once

class DisplayScore {
private:
	float goGraphMoveY;	// 動かすY座標の値

	int alpha;		// アルファ値

	int scoreGraph;	// スコア表示画像

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	DisplayScore();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~DisplayScore();

	/// <summary>
	/// 表示のための初期化
	/// </summary>
	void InitializeForDisplay();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(int x, int y);

	/// <summary>
	/// 表示されているかどうか
	/// </summary>
	/// <returns>表示されているかのBool型フラグ</returns>
	bool IsHidden() const
	{
		return goGraphMoveY >= 20 && alpha <= 0;
	}
};