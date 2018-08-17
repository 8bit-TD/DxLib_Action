#include "pch.h"
#include "control.h"
#include "se.h"
#include "SceneMgr.h"

char key[256];      //キー取得用配列
int g_count;        //カウント数
int MouseInput;     //マウスのボタンの状態
int FrameStartTime; //60FPS固定用、時間保存用変数


// プログラムは WinMain から始まります
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow )
{
	SetDrawScreen(DX_SCREEN_BACK);// 描画先を裏画面にセット
	SetWaitVSyncFlag(FALSE);// 垂直同期信号を待たない	
	//	SetWaitVSyncFlag(true);
	FrameStartTime = GetNowCount();// ６０ＦＰＳ固定用、時間保存用変数を現在のカウント値にセット
	ChangeWindowMode(TRUE);//ウインドウモード
	//SetWindowSizeChangeEnableFlag(TRUE);
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, 32);//画面解像度設定
	SetMouseDispFlag(TRUE);
	if( DxLib_Init() == -1 ) {return -1;}// エラーが起きたら直ちに終了
	CONTROL *control = CONTROL::GetInstance();

	SceneMgr sceneMgr;
	sceneMgr.Initialize();

	while(ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 && GetHitKeyStateAll(key)==0){	
		MouseInput = GetMouseInput();
		//WaitVSync(60);
		while (GetNowCount() - FrameStartTime < 1000 / 60) {}// 1/60秒立つまで待つ
		ClsDrawScreen();// 画面のクリア
		// 現在のカウント値を保存
		FrameStartTime = GetNowCount();
		

		//control.All();
		control->FpsTimeFanction();
		if (control->GameEndCheck()) { break; }

		sceneMgr.Update();  //更新
		sceneMgr.Draw();    //描画
		//WaitVSync(60);
		ScreenFlip(); //裏画面を表画面に反映
		++g_count;//カウントを加算
	}
	DxLib_End();// ＤＸライブラリ使用の終了処理
	return 0;// ソフトの終了 
}