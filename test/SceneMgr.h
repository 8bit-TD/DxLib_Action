#pragma once

#include "SceneChanger.h"
#include "SceneBase.h"
#include "System.h"

class SceneMgr : public SceneChanger, Task {

private:
    SceneBase * mScene    ;    //�V�[���Ǘ��ϐ�
    eScene mNextScene;    //���̃V�[���Ǘ��ϐ�
	System *system;

public:
    SceneMgr();
    void Initialize() override;//������
    void Finalize() override;//�I������
    void Update() override;//�X�V
    void Draw() override;//�`��

    // ���� nextScene �ɃV�[����ύX����
    void ChangeScene(eScene NextScene) override;

};