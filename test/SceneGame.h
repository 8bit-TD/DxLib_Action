#pragma once
#include "SceneBase.h"
#include "GameKeyConfig.h"

//�Q�[����ʃN���X
class SceneGame : public SceneBase {

public:
	
	SceneGame(SceneChanger* changer);
	GameKeyConfig *gkc;
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;

	void ShowKeyConfig(); //�L�[�R���t�B�O�ݒ��ʂ�\��
	void ShowMenu();      //���j���[��ʂ�\��
};