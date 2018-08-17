#include "pch.h"
#include "GameKeyConfig.h"
#include "control.h"
#include "se.h"

GameKeyConfig::GameKeyConfig() {
	
}

//void GameKeyConfig::Initialize() {}

void GameKeyConfig::ShowKeyConfig() {//キーコンフィグ設定画面を表示
	int x = 800; //ベースの横位置
	int oy = 5;
	int off_key = 7;
	SetFontSize(20);
	DrawFormatString(x, 200, GetColor(255, 255, 255), "キーコンフィグ設定");
	DrawFormatString(x, 300, GetColor(255, 255, 255), "上移動");
	DrawBox(x + 180, 300 - oy, x + 250, 330 - oy, GetColor(255, 255, 255), 0);
	DrawFormatString(x + 180 + off_key, 300 - oy + off_key, GetColor(255, 255, 255), "W");

	DrawFormatString(x, 350, GetColor(255, 255, 255), "下移動");
	DrawBox(x + 180, 350 - oy, x + 250, 380 - oy, GetColor(255, 255, 255), 0);
	DrawFormatString(x + 180 + off_key, 350 - oy + off_key, GetColor(255, 255, 255), "S");

	DrawFormatString(x, 400, GetColor(255, 255, 255), "左移動");
	DrawBox(x + 180, 400 - oy, x + 250, 430 - oy, GetColor(255, 255, 255), 0);
	DrawFormatString(x + 180 + off_key, 400 - oy + off_key, GetColor(255, 255, 255), "A");

	DrawFormatString(x, 450, GetColor(255, 255, 255), "右移動");
	DrawBox(x + 180, 450 - oy, x + 250, 480 - oy, GetColor(255, 255, 255), 0);
	DrawFormatString(x + 180 + off_key, 450 - oy + off_key, GetColor(255, 255, 255), "D");

	DrawFormatString(x, 500, GetColor(255, 255, 255), "メニュー");
	DrawBox(x + 180, 500 - oy, x + 250, 530 - oy, GetColor(255, 255, 255), 0);
	DrawFormatString(x + 180 + off_key, 500 - oy + off_key, GetColor(255, 255, 255), "C");

	DrawFormatString(x, 550, GetColor(255, 255, 255), "キーコンフィグ");
	DrawBox(x + 180, 550 - oy, x + 250, 580 - oy, GetColor(255, 255, 255), 0);
	DrawFormatString(x + 180 + off_key, 550 - oy + off_key, GetColor(255, 255, 255), "Q");

	DrawFormatString(x, 600, GetColor(255, 255, 255), "スキル１");
	DrawBox(x + 180, 600 - oy, x + 250, 630 - oy, GetColor(255, 255, 255), 0);
	DrawFormatString(x + 180 + off_key, 600 - oy + off_key, GetColor(255, 255, 255), "F");

	DrawFormatString(x, 650, GetColor(255, 255, 255), "スキル２");
	DrawBox(x + 180, 650 - oy, x + 250, 680 - oy, GetColor(255, 255, 255), 0);
	DrawFormatString(x + 180 + off_key, 650 - oy + off_key, GetColor(255, 255, 255), "R");

	DrawFormatString(x, 700, GetColor(255, 255, 255), "スキル３");
	DrawBox(x + 180, 700 - oy, x + 250, 730 - oy, GetColor(255, 255, 255), 0);
	DrawFormatString(x + 180 + off_key, 700 - oy + off_key, GetColor(255, 255, 255), "V");

	DrawFormatString(x, 750, GetColor(255, 255, 255), "スキル４");
	DrawBox(x + 180, 750 - oy, x + 250, 780 - oy, GetColor(255, 255, 255), 0);
	DrawFormatString(x + 180 + off_key, 750 - oy + off_key, GetColor(255, 255, 255), "G");

	DrawBox(back[0], back[1], back[2], back[3], GetColor(255, 255, 255), 0);

}

void GameKeyConfig::Update() {
	CONTROL *control = CONTROL::GetInstance();
	control->GetMousePos(&mouse_x, &mouse_y);
	
	if ((mouse_x > back[0]) && (mouse_x < back[2]) && (mouse_y > back[1]) && (mouse_y < back[3])) {
		if ((MouseInput & MOUSE_INPUT_LEFT) != 0) {
			SE *se = SE::GetInstance();
			se->SE_Click();
			control->SetGameMode(control->GAME);
		}
	}
}

void GameKeyConfig::Draw() {
	ShowKeyConfig();
}

GameKeyConfig::~GameKeyConfig() {
	mouse_x = NULL;
	mouse_y = NULL;
	num = NULL;
	edit = NULL;
}
