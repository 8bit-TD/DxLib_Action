#include "DxLib.h"
#include "SceneConfigKey.h"
#include "SceneTitle.h"
#include "SceneGame.h"
#include "SceneMgr.h"
#include "SceneGameOver.h"
//#include "System.h"

SceneMgr::SceneMgr() :  mNextScene(eScene_None) //���̃V�[���Ǘ��ϐ�
{
    mScene = (SceneBase*) new SceneTitle(this);
	//system = new System;
}

//������
void SceneMgr::Initialize(){
    mScene->Initialize();
}

//�I������
void SceneMgr::Finalize(){
    mScene->Finalize();
}

//�X�V
void SceneMgr::Update(){
    if(mNextScene != eScene_None){    //���̃V�[�����Z�b�g����Ă�����
        mScene->Finalize();//���݂̃V�[���̏I�����������s
        delete mScene;
        switch(mNextScene){       //�V�[���ɂ���ď����𕪊�
        case eScene_Title:        //���̉�ʂ����j���[�Ȃ�
            mScene = (SceneBase*) new SceneTitle(this);   //�^�C�g����ʂ̃C���X�^���X�𐶐�����
            break;//�ȉ���
        case eScene_Config:
            mScene = (SceneBase*) new SceneConfigKey(this);
            break;
		case eScene_Game:
			mScene = (SceneBase*) new SceneGame(this);
			break;
		case eScene_GameOver:
			mScene = (SceneBase*) new SceneGameOver(this);
			break;
        }
        mNextScene = eScene_None;    //���̃V�[�������N���A
        mScene->Initialize();    //�V�[����������
    }

    mScene->Update(); //�V�[���̍X�V
	//system->Update();
}

//�`��
void SceneMgr::Draw(){
    mScene->Draw(); //�V�[���̕`��
	//system->Draw();
}

// ���� nextScene �ɃV�[����ύX����
void SceneMgr::ChangeScene(eScene NextScene){
    mNextScene = NextScene;    //���̃V�[�����Z�b�g����
}
