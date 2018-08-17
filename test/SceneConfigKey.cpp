#include "SceneConfigKey.h"
#include "pch.h"

SceneConfigKey::SceneConfigKey(SceneChanger* changer) : SceneBase(changer) {
}

//初期化
void SceneConfigKey::Initialize(){

}

//更新
void SceneConfigKey::Update(){
	if (key[KEY_INPUT_Z] != 0) {
		mSceneChanger->ChangeScene(eScene_Title);//シーンをタイトル画面に変更
	}
}

//描画
void SceneConfigKey::Draw(){
    SceneBase::Draw();//親クラスの描画メソッドを呼ぶ
    DrawString(0, 0,"コンフィグ画面です。",GetColor(255,255,255));
    DrawString(0,20,"Zキーを押すとタイトル画面に戻ります。",GetColor(255,255,255));
}
