#include "SceneGame.h"
#include "pch.h"
#include "control.h"
#include "GameKeyConfig.h"
#include "se.h"


SceneGame::SceneGame(SceneChanger* changer) : SceneBase(changer) {

}

void SceneGame::Initialize() {
	CONTROL *control = CONTROL::GetInstance();
	control->Create();
	gkc = new GameKeyConfig;
}

void SceneGame::Update() {
	if (key[KEY_INPUT_Z] == 1) {mSceneChanger->ChangeScene(eScene_Title);}//シーンを設定画面に変更

	CONTROL *control = CONTROL::GetInstance();
	control->All();

	if (key[KEY_INPUT_Q] == 1) {
		SE *se = SE::GetInstance();
		se->SE_Click();
		control->SetGameMode(control->KEYCONFIG); 
	} //ゲームモードをキー設定に変更
	if (key[KEY_INPUT_C] == 1) { 
		SE *se = SE::GetInstance();
		se->SE_Click();
		control->SetGameMode(control->MENU); 
	}      //ゲームモードをメニュー設定に変更
	if (key[KEY_INPUT_ESCAPE] == 1) {
		SE *se = SE::GetInstance();
		se->SE_Click();
		control->SetGameMode(control->GAME);
	}   //ゲームモードをゲーム画面に設定
	if (control->GetGameOverFlag()) {mSceneChanger->ChangeScene(eScene_GameOver);}//シーンをゲームオーバー画面に変更
	if (control->GetGameMode() == 2) { gkc->Update(); }
}

void SceneGame::ShowMenu() {//メニューを表示
	int x = 800; //ベースの横位置
	int oy = 5;
	int off_key = 7;
	SetFontSize(20);
	DrawFormatString(x, 200, GetColor(255, 255, 255), "メニュー設定");
}

void SceneGame::Draw() {
	CONTROL *control = CONTROL::GetInstance();
	SceneBase::Draw();//親クラスの描画メソッドを呼ぶ
	DrawString(0, 20, "Zキーを押すとタイトル画面に戻ります。", GetColor(255, 255, 255));
	DrawString(0, 0, "ゲーム画面です。", GetColor(255, 255, 255));
	if (control->GetGameMode() != 0) {//ゲームモードではなかったら画面を暗くする
		SetDrawBlendMode(DX_BLENDMODE_MULA, 225);
		DrawBox(0, 0, GAME_WIDTH, GAME_HEIGHT, GetColor(0, 10, 25), 1);//画面暗転
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		if (control->GetGameMode() == 1) { ShowMenu(); }
		if (control->GetGameMode() == 2) { gkc->Draw(); }
	}
}

void SceneGame::Finalize() {
	CONTROL *control = CONTROL::GetInstance();
	control->Finalize();
	delete gkc;
}