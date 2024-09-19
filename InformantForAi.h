#pragma once

#include <DxLib.h>

class Character;

//=========================
// enemy(AI)に情報を与えるクラス
// シングルトン
//=========================
class InformantForAi final
{
public:

    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="characters">キャラクターポインタ</param>
    /// <param name="size">キャラクター数</param>
    void Initialize(Character** characters, int size);

    /// <summary>
    /// インスタンス取得
    /// </summary>
    /// <returns>クラスのインスタンス</returns>
    static InformantForAi& GetInstance();

    /// <summary>
    /// 攻撃対象の取得
    /// </summary>
    /// <param name="position">自分の座標</param>
    /// <returns>ターゲットとなるキャラクターのポインタ</returns>
    Character* GetAttackTarget(const VECTOR& position) ;

private:

    // 定数

    static const float INIT_VECTOR_SIZE;	// 敵を探す際の距離の初期値

    // 変数

    Character** characters; // キャラクターポインタ
    int characterAmount;    // キャラクター数

    // 外部での実行を禁止する

    /// <summary>
    /// コンストラクタ
    /// </summary>
    InformantForAi();

    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name=""></param>
    InformantForAi(const InformantForAi&);

    /// <summary>
    /// 代入演算子
    /// </summary>
    /// <param name=""></param>
    void operator=(const InformantForAi&);

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~InformantForAi();

};
