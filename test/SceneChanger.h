#pragma once

typedef enum {
    eScene_Title,   //�^�C�g�����
    eScene_Config,  //�ݒ���
	eScene_Game,    //�Q�[�����
	eScene_GameOver,//�Q�[���I�[�o�[���

    eScene_None,    //����
} eScene ;

//�V�[����ύX���邽�߂̃C���^�[�t�F�C�X�N���X
class SceneChanger {
public:
    virtual ~SceneChanger() = 0;
    virtual void ChangeScene(eScene NextScene) = 0;//�w��V�[���ɕύX����
};