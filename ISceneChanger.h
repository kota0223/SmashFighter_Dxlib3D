#pragma once

class ResultScore;

//�񋓑�
enum eScene
{
	titleScene,
	mainScene,
	resultScene,
	Empty
};

//�V�[����ύX���邽�߂̃C���^�[�t�F�C�X�N���X
class ISceneChanger {
public:
	virtual ~ISceneChanger() = 0;
	virtual void ChangeScene(eScene NextScene, ResultScore score) = 0; // �w��V�[���ɕύX����
};