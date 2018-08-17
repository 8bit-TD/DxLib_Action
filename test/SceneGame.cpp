#include "SceneGame.h"
#include "pch.h"
#include "control.h"
#include "GameKeyConfig.h"
#include "se.h"


SceneGame::SceneGame(SceneChanger* changer) : SceneBase(changer) {

}

void SceneGame::Initialize() {
	CONTROL *control = CONTROL::GetInstance();
	control->Create();
	gkc = new GameKeyConfig;
}

void SceneGame::Update() {
	if (key[KEY_INPUT_Z] == 1) {mSceneChanger->ChangeScene(eScene_Title);}//�V�[����ݒ��ʂɕύX

	CONTROL *control = CONTROL::GetInstance();
	control->All();

	if (key[KEY_INPUT_Q] == 1) {
		SE *se = SE::GetInstance();
		se->SE_Click();
		control->SetGameMode(control->KEYCONFIG); 
	} //�Q�[�����[�h���L�[�ݒ�ɕύX
	if (key[KEY_INPUT_C] == 1) { 
		SE *se = SE::GetInstance();
		se->SE_Click();
		control->SetGameMode(control->MENU); 
	}      //�Q�[�����[�h�����j���[�ݒ�ɕύX
	if (key[KEY_INPUT_ESCAPE] == 1) {
		SE *se = SE::GetInstance();
		se->SE_Click();
		control->SetGameMode(control->GAME);
	}   //�Q�[�����[�h���Q�[����ʂɐݒ�
	if (control->GetGameOverFlag()) {mSceneChanger->ChangeScene(eScene_GameOver);}//�V�[�����Q�[���I�[�o�[��ʂɕύX
	if (control->GetGameMode() == 2) { gkc->Update(); }
}

void SceneGame::ShowMenu() {//���j���[��\��
	int x = 800; //�x�[�X�̉��ʒu
	int oy = 5;
	int off_key = 7;
	SetFontSize(20);
	DrawFormatString(x, 200, GetColor(255, 255, 255), "���j���[�ݒ�");
}

void SceneGame::Draw() {
	CONTROL *control = CONTROL::GetInstance();
	SceneBase::Draw();//�e�N���X�̕`�惁�\�b�h���Ă�
	DrawString(0, 20, "Z�L�[�������ƃ^�C�g����ʂɖ߂�܂��B", GetColor(255, 255, 255));
	DrawString(0, 0, "�Q�[����ʂł��B", GetColor(255, 255, 255));
	if (control->GetGameMode() != 0) {//�Q�[�����[�h�ł͂Ȃ��������ʂ��Â�����
		SetDrawBlendMode(DX_BLENDMODE_MULA, 225);
		DrawBox(0, 0, GAME_WIDTH, GAME_HEIGHT, GetColor(0, 10, 25), 1);//��ʈÓ]
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		if (control->GetGameMode() == 1) { ShowMenu(); }
		if (control->GetGameMode() == 2) { gkc->Draw(); }
	}
}

void SceneGame::Finalize() {
	CONTROL *control = CONTROL::GetInstance();
	control->Finalize();
	delete gkc;
}