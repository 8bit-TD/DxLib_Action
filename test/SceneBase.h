#pragma once

#include "Task.h"
#include "SceneChanger.h"

//�V�[���̊��N���X�B
class SceneBase : public Task {

protected:
    //int mImageHandle;                //�摜�n���h���i�[�p�ϐ�
    SceneChanger* mSceneChanger;    //�N���X���L���ɃV�[���؂�ւ���`����C���^�[�t�F�C�X

public :
    SceneBase(SceneChanger* changer);
    virtual ~SceneBase(){}
    virtual void Initialize() override {}    //�������������I�[�o�[���C�h�B
    virtual void Finalize() override ;        //�I���������I�[�o�[���C�h�B
    virtual void Update() override {}        //�X�V�������I�[�o�[���C�h�B
    virtual void Draw() override ;            //�`�揈�����I�[�o�[���C�h�B

};
