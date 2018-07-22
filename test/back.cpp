#include "back.h"
#include "pch.h"

BACK::BACK() {
	gh = LoadGraph("back1.png");
	x = y = MARGIN;
}

void BACK::Draw() {
	//1���ڕ`��
	DrawGraph(x, y, gh, FALSE);
	//2���ڕ`��
	DrawGraph(x, y - 460, gh, FALSE);
	//��ԉ��܂ŃX�N���[�������珉���l�ɖ߂�
	if (y == 460 + MARGIN)
		y = 10;
}

void BACK::Move() {
	y += SCROLL_SPEED;
}

void BACK::All() {
	Draw();
	Move();
}