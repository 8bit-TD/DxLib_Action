#pragma once
#include "Task.h"
#include "pch.h"

class GameKeyConfig  {//�Q�[�����ɃL�[�R���t�B�O��ʂ�\��
private:
	int mouse_x, mouse_y; //�}�E�X���W
	bool edit;            //�ҏW�����ǂ����̃t���O
	int num;              //�ォ�牽�Ԗڂ��̔ԍ�
	//std::vector<int> back = { 800, 900, 1100, 950 };
	int btns[10][4] = {//�L�[�R���t�B�O����
		{ 980, 300, 1050, 330 },
		{ 980, 350, 1050, 380 },
		{ 980, 400, 1050, 430 },
		{ 980, 450, 1050, 480 },
		{ 980, 500, 1050, 530 },
		{ 980, 550, 1050, 580 },
		{ 980, 600, 1050, 630 },
		{ 980, 650, 1050, 680 },
		{ 980, 700, 1050, 730 },
		{ 980, 750, 1050, 780 },
	};
	int back[4] = { 800, 900, 1100, 950 };//�Q�[�����[�h�ɖ߂�͈�

public:
	GameKeyConfig();
	~GameKeyConfig();
	void Update();        //�X�V�������I�[�o�[���C�h
	void Draw();          //�`�揈�����I�[�o�[���C�h
	void ShowKeyConfig(); //�L�[�R���t�B�O��ʂ�\��
};