#include "SceneTitle.h"
#include "pch.h"

SceneTitle::SceneTitle(SceneChanger* changer) : SceneBase(changer) {
}

//������
void SceneTitle::Initialize(){

}

//�X�V
void SceneTitle::Update(){

	if (key[KEY_INPUT_G] == 1) {
		mSceneChanger->ChangeScene(eScene_Game);//�V�[����ݒ��ʂɕύX
    }
	if (key[KEY_INPUT_C] == 1) {
        mSceneChanger->ChangeScene(eScene_Config);//�V�[����ݒ��ʂɕύX
    }
}

//�`��
void SceneTitle::Draw(){
    SceneBase::Draw();//�e�N���X�̕`�惁�\�b�h���Ă�
    DrawString(0, 0,"�^�C�g����ʂł��B",GetColor(255,255,255));
    DrawString(0,20,"G�L�[�������ƃQ�[����ʂɐi�݂܂��B",GetColor(255,255,255));
    DrawString(0,40,"C�L�[�������Ɓ@�ݒ��ʂɐi�݂܂��B",GetColor(255,255,255));
}
