#include "pch.h"
#include "System.h"
#include "control.h"

System::System() {
	cursor = "images/system/cursor.png";
	gh = LoadGraph(cursor.c_str());//‰æ‘œ“Ç‚İ‚İ
}

void System::Update() {
	CONTROL *control = CONTROL::GetInstance();
	control->GetMousePos(&mx, &my);
}

void System::Draw() {
	DrawGraph(mx, my, gh, TRUE);
}

System::~System() {
	DeleteGraph(gh);//ƒƒ‚ƒŠ‚©‚ç‰æ‘œ‚ğíœ
	gh = NULL;
	mx = NULL;
	my = NULL;
}