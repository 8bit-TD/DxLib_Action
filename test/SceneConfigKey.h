#pragma once

#include "SceneBase.h"

//�ݒ��ʃN���X
class SceneConfigKey : public SceneBase {

public :
    SceneConfigKey(SceneChanger* changer);
    void Initialize() override; //�������������I�[�o�[���C�h
    //void Finalize() override; //�I���������I�[�o�[���C�h
    void Update() override;     //�X�V�������I�[�o�[���C�h
    void Draw() override;       //�`�揈�����I�[�o�[���C�h

};
