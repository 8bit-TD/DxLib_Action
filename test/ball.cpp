#include "pch.h"
#include "ball.h"
#include "control.h"
#include "se.h"

BALL::BALL() {
	pos.x = pos.y = speed = life = radius = mx = my = angle = 0;
	endflag = true;
	color = GetColor(255, 255, 255);
}

void BALL::SetBallFlag(bool flag) {//�t���O��ݒ�
	endflag = flag;
}

bool BALL::GetBallFlag() {//�t���O���擾
	return endflag;
}

int BALL::GetBallContact(double x, double y, double size) {//�e�̐ڐG����
	if ((x < pos.x) && (x + size > pos.x) && (y < pos.y) && (y + size > pos.y)) {
		return 1;
	}
	return 0;
}

void BALL::SetBallPos(double x, double y, double ang) {//�ʒu��ݒ�
	angle = ang;
	pos.x = x; pos.y = y; 
	mx = cos(angle) * speed;
	my = sin(angle) * speed;
}

void BALL::SetBallParam(int sp, int rd, int lf, int col) {//�p�����[�^�ݒ�
	speed = sp;	radius = rd; life = lf;	color = col;
}

void BALL::GetBallPos(double *x, double *y) {//�ʒu���擾
	*x = pos.x; *y = pos.y;
}

void BALL::Move() {
	if (!endflag) {
		CONTROL *control = CONTROL::GetInstance();
		if ((control->CheckMove(pos.x, pos.y, &mx, &my, radius, 0, false) == 3) || (control->CheckMove(pos.x, pos.y, &mx, &my, radius,0, false) == 4)) {
			my = my * -1 + GetRand(1) * 0.1; --life;
		};
		if ((control->CheckMove(pos.x, pos.y, &mx, &my, radius, 0, false) == 1) || (control->CheckMove(pos.x, pos.y, &mx, &my, radius, 0, false) == 2)) {
			mx = mx * -1 + GetRand(1) * 0.1; --life;
		};
		if (life < 1) {
			SE *se = SE::GetInstance();
			se->SE_Block();//�e���u���b�N�ɓ����������̉�
			endflag = true; 
			SetBallParam(0, 0, 0, 0);
			SetBallPos(0, 0, 0);
			
		}
		pos.x += mx; pos.y += my;
	}
}

void BALL::Draw() {
	if (!endflag) {
		DrawCircle(pos.x, pos.y, radius, color, 1);
	}
}

void BALL::All() {
	Move();	
	Draw();
}

////////////////////////////////////////////////// BALL_MANAGER //////////////////////////////////////////////////////

BALL_MANAGER::BALL_MANAGER() {
	for (int i = 0; i < PSHOT_NUM; ++i) {
		ball[i] = new BALL;
	}
}

void BALL_MANAGER::SetBall(double x, double y, int width, int height, int mouse_x, int mouse_y) {//�e��ݒ�
	SE *se = SE::GetInstance();
	for (int i = 0; i < PSHOT_NUM; ++i) {
		if (ball[i]->GetBallFlag()) {
			ball[i]->SetBallFlag(false);
			ball[i]->SetBallParam(6, 3, 1, GetColor(GetRand(255), GetRand(255), GetRand(255)));
			int px = (x + width / 2);
			int py = (y + height / 2);
			angle = (double)atan2((int)mouse_y - (int)py, (int)mouse_x - (int)px);
			ball[i]->SetBallPos(px, py, angle);
			se->SE_Shot();
			break;
		}
	}
}

int BALL_MANAGER::GetBallNum() {//�e�̐����擾
	int count = 0;
	for (int i = 0; i < PSHOT_NUM; ++i) {
		if (!ball[i]->GetBallFlag()) { ++count; }
	}
	return count;
}

void BALL_MANAGER::SetBallFlag(int index, bool flag) {//�t���O��ݒ�
	ball[index]->SetBallFlag(flag);
}

int BALL_MANAGER::GetBallContact(double x, double y, double size) {//�e�̐ڐG����
	for (int i = 0; i < PSHOT_NUM; ++i) {
		if (ball[i]->GetBallContact(x, y, size) == 1) {
			return i;
		}
	}
	return -1;
}

void BALL_MANAGER::GetBallPos(std::vector<VECTOR> *bp) {
	std::vector<VECTOR> pos;
	for (int i = 0; i < PSHOT_NUM; ++i) {
		double px; double py;
		ball[i]->GetBallPos(&px, &py);
		VECTOR p;
		p.x = px; p.y = py;
		pos.push_back(p);
	}
	*bp = pos;
}

void BALL_MANAGER::Move() {
	for (int i = 0; i < PSHOT_NUM; ++i) {
		ball[i]->Move();
	}
}

void BALL_MANAGER::Draw() {
	int count = 0;
	for (int i = 0; i < PSHOT_NUM; ++i) {
		ball[i]->Draw();
		if (!ball[i]->GetBallFlag()) { ++count; }
	}
}

void BALL_MANAGER::All() {
	Move(); Draw();
}

BALL_MANAGER::~BALL_MANAGER() {
	for (int i = 0; i < PSHOT_NUM; ++i) {
		ball[i] = NULL;
		delete ball[i];
	}
}

