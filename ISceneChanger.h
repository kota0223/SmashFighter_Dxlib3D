#pragma once

class ResultScore;

//列挙体
enum eScene
{
	titleScene,
	mainScene,
	resultScene,
	Empty
};

//シーンを変更するためのインターフェイスクラス
class ISceneChanger {
public:
	virtual ~ISceneChanger() = 0;
	virtual void ChangeScene(eScene NextScene, ResultScore score) = 0; // 指定シーンに変更する
};