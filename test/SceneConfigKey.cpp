#include "SceneConfigKey.h"
#include "pch.h"

SceneConfigKey::SceneConfigKey(SceneChanger* changer) : SceneBase(changer) {
}

//������
void SceneConfigKey::Initialize(){

}

//�X�V
void SceneConfigKey::Update(){
	if (key[KEY_INPUT_Z] != 0) {
		mSceneChanger->ChangeScene(eScene_Title);//�V�[�����^�C�g����ʂɕύX
	}
}

//�`��
void SceneConfigKey::Draw(){
    SceneBase::Draw();//�e�N���X�̕`�惁�\�b�h���Ă�
    DrawString(0, 0,"�R���t�B�O��ʂł��B",GetColor(255,255,255));
    DrawString(0,20,"Z�L�[�������ƃ^�C�g����ʂɖ߂�܂��B",GetColor(255,255,255));
}
