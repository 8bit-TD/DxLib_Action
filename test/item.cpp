#include "item.h"
#include "pch.h"

ITEM::ITEM() {
	gh[0] = ghs[0] = gh[1] = ghs[1] = 0;
	//0���F�œ��_�n�A1�����F�Ńp���[�A�b�v�n
	gh[0] = LoadGraph("item1.png");
	gh[1] = LoadGraph("item2.png");
	ghs[0] = LoadGraph("items1.png");
	ghs[1] = LoadGraph("items2.png");
	
	x = y = 0;
	rad = 0;
	count = 0;
	type = 0;
	fall_flag = false;
	flag = false;
}

void ITEM::SetFlag(double x, double y, int type) {
	this->x = x;
	this->y = y - 8;
	prev_y = y;
	this->type = type;
	flag = true;
}

bool ITEM::GetFlag() {
	return flag;
}

void ITEM::GetPosition(double *x, double *y) {
	*x = this->x-20;
	*y = this->y-20;
}

int ITEM::GetType() {
	return type;
}

void ITEM::Move() {
	double tempy;

	//0.04���W�A��(��2�x)����]������B
	rad = 0.04*count;
	++count;
	if (!fall_flag) {
		tempy = y;
		y += (y- prev_y) + 1;
		//���_�܂ł�������t���O�𗧂Ă�
		if ((y - prev_y) + 1 == 0){
			fall_flag = true;
		}
		prev_y = tempy;
	}else {
		//�������͈�葬�x�ŗ���
		y += 1.5;
	}
	//��ʂ̊O�ɂ͂ݏo����t���O��߂��B
	if (y > 500) {
		Delete();
	}
}

void ITEM::Delete() {
	count = 0;
	fall_flag = false;
	flag = false;
}

void ITEM::Draw() {
	DrawRotaGraph(x, y, 1.0, rad, gh[type], TRUE);
	DrawRotaGraph(x, y, 1.0, 0, ghs[type], TRUE);
}

void ITEM::All() {
	Move();
	Draw();
}