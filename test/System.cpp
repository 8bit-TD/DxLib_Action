#include "pch.h"
#include "System.h"
#include "control.h"

System::System() {
	cursor = "images/system/cursor.png";
	gh = LoadGraph(cursor.c_str());//画像読み込み
}

void System::Update() {
	CONTROL *control = CONTROL::GetInstance();
	control->GetMousePos(&mx, &my);
}

void System::Draw() {
	DrawGraph(mx, my, gh, TRUE);
}

System::~System() {
	DeleteGraph(gh);//メモリから画像を削除
	gh = NULL;
	mx = NULL;
	my = NULL;
}