#include "SceneGameOver.h"
#include "pch.h"

SceneGameOver::SceneGameOver(SceneChanger* changer) : SceneBase(changer) {

}

void SceneGameOver::Initialize() {

}

void SceneGameOver::Update() {
	if (key[KEY_INPUT_Z] == 1) {
		mSceneChanger->ChangeScene(eScene_Title);//シーンをタイトル画面に変更
	}
}

void SceneGameOver::Draw() {
	SceneBase::Draw();
	DrawString(0, 0, "ゲームオーバー画面です。", GetColor(255, 255, 255));
	DrawString(0, 20, "Zキーを押すとタイトル画面に戻ります。", GetColor(255, 255, 255));
}