#pragma once

// 衝突時のスコア加算する対象を受け渡すクラス
class ScoreAddClass {
public:

	/// <summary>
	/// スコア追加
	/// </summary>
	virtual void ScoreAdd() = 0;

	/// <summary>
	/// キャラクターインスタンスを取得する
	/// </summary>
	/// <returns>スコアを増加させるキャラクターインスタンス</returns>
	virtual ScoreAddClass* GetAddCharacter() = 0;

	/// <summary>
	/// 飛ばされているかのフラグを取得する
	/// </summary>
	/// <returns>飛ばされているかのフラグ</returns>
	virtual bool GetIsLeaping() const = 0;
};