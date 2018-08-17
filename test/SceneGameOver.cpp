#include "SceneGameOver.h"
#include "pch.h"

SceneGameOver::SceneGameOver(SceneChanger* changer) : SceneBase(changer) {

}

void SceneGameOver::Initialize() {

}

void SceneGameOver::Update() {
	if (key[KEY_INPUT_Z] == 1) {
		mSceneChanger->ChangeScene(eScene_Title);//�V�[�����^�C�g����ʂɕύX
	}
}

void SceneGameOver::Draw() {
	SceneBase::Draw();
	DrawString(0, 0, "�Q�[���I�[�o�[��ʂł��B", GetColor(255, 255, 255));
	DrawString(0, 20, "Z�L�[�������ƃ^�C�g����ʂɖ߂�܂��B", GetColor(255, 255, 255));
}