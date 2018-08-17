#pragma once
#include "Task.h"
#include "pch.h"

class GameKeyConfig  {//ゲーム中にキーコンフィグ画面を表示
private:
	int mouse_x, mouse_y; //マウス座標
	bool edit;            //編集中かどうかのフラグ
	int num;              //上から何番目かの番号
	//std::vector<int> back = { 800, 900, 1100, 950 };
	int btns[10][4] = {//キーコンフィグ項目
		{ 980, 300, 1050, 330 },
		{ 980, 350, 1050, 380 },
		{ 980, 400, 1050, 430 },
		{ 980, 450, 1050, 480 },
		{ 980, 500, 1050, 530 },
		{ 980, 550, 1050, 580 },
		{ 980, 600, 1050, 630 },
		{ 980, 650, 1050, 680 },
		{ 980, 700, 1050, 730 },
		{ 980, 750, 1050, 780 },
	};
	int back[4] = { 800, 900, 1100, 950 };//ゲームモードに戻る範囲

public:
	GameKeyConfig();
	~GameKeyConfig();
	void Update();        //更新処理をオーバーライド
	void Draw();          //描画処理をオーバーライド
	void ShowKeyConfig(); //キーコンフィグ画面を表示
};