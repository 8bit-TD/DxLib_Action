#include "SceneTitle.h"
#include "pch.h"

SceneTitle::SceneTitle(SceneChanger* changer) : SceneBase(changer) {
}

//初期化
void SceneTitle::Initialize(){

}

//更新
void SceneTitle::Update(){

	if (key[KEY_INPUT_G] == 1) {
		mSceneChanger->ChangeScene(eScene_Game);//シーンを設定画面に変更
    }
	if (key[KEY_INPUT_C] == 1) {
        mSceneChanger->ChangeScene(eScene_Config);//シーンを設定画面に変更
    }
}

//描画
void SceneTitle::Draw(){
    SceneBase::Draw();//親クラスの描画メソッドを呼ぶ
    DrawString(0, 0,"タイトル画面です。",GetColor(255,255,255));
    DrawString(0,20,"Gキーを押すとゲーム画面に進みます。",GetColor(255,255,255));
    DrawString(0,40,"Cキーを押すと　設定画面に進みます。",GetColor(255,255,255));
}
