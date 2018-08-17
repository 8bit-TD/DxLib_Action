#include "SceneBase.h"
#include "DxLib.h"

SceneBase::SceneBase(SceneChanger* changer) {
    mSceneChanger = changer;
}

void SceneBase::Finalize(){
    //DeleteGraph(mImageHandle);
}

void SceneBase::Draw(){
    //DrawGraph(0,0,mImageHandle,FALSE);
}
