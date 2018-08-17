#include "pch.h"
#include "player.h"
#include "control.h"


PLAYER::PLAYER(std::string file, int x, int y, int w, int h, int s, int a, double sp, double jp, int mhp, int mmp) : CHARA(file, x, y, w, h, s, a, sp, jp, mhp, mmp) {
	player = new CHARA(file, x, y, w, h, s, a, sp, jp, mhp, mmp);
	speed = BASE_SPEED + sp;
	jump = BASE_JUMP + jp;
}

void PLAYER::GetPlayerPos(double *xx, double *yy) {//�v���C���[�̈ʒu���擾
	*xx = pos.x; *yy = pos.y;
}

void PLAYER::GetPlayerHP(int *Hp, int *Maxhp) {//�v���C���[��HP���擾
	*Hp = hp; *Maxhp = maxhp;
}

void PLAYER::Move() {
	CONTROL *control = CONTROL::GetInstance();
	move_x = move_y = 0; //�ړ�������
	if (control->GetGameMode() == 0) { CHARA::CheckAim(); } //�}�E�X���W�擾
	fall_sp = fall_sp + GRAVITY;
	if (control->GetGameMode() == 0) {
		if (key[KEY_INPUT_A] == 1) {
			move_x -= speed;
		}
		if (key[KEY_INPUT_D] == 1) {
			move_x += speed;
		}
		if (key[KEY_INPUT_W] == 1) {
			move_y -= jump;
		}
		if (key[KEY_INPUT_S] == 1) {
			move_y += speed;
		}
		if (key[KEY_INPUT_F] == 1) {
			if (g_count % 10 == 0) {
				if (GetMP() > 10) {
					control->SetPlayerBall(pos.x, pos.y, width, height, mouse_x, mouse_y);
				}
			}
		}
	}
	move_y += fall_sp; //�d�͂����Z
	CHARA::CheckMove();//�ړ��ł��邩����
	if (mouse_x > pos.x) { aim = 1; } else { aim = -1; }
	CHARA::Move();
}

void PLAYER::Draw(){
	CHARA::Draw();
	DrawBox(pos.x - 2, pos.y - 10 - 2, pos.x + width + 2, pos.y - 5 - 2, GetColor(50, 25, 0), 1); //HP�Q�[�W�g
	DrawBox(pos.x, pos.y - 10, pos.x + (int)hp_gauge, pos.y - 5 - 2, GetColor(255, 150, 50), 1);  //HP�Q�[�W
	DrawBox(pos.x - 2, pos.y - 5 - 2, pos.x + width + 2, pos.y - 2, GetColor(0, 25, 50), 1); //HP�Q�[�W�g
	DrawBox(pos.x, pos.y - 5, pos.x + (int)mp_gauge, pos.y - 2, GetColor(50, 150, 255), 1);  //HP�Q�[�W
}

void PLAYER::All(){
	if (!death_flag) { Move(); }
	if (!death_flag) { Draw(); }
	damage_flag = false;
}

PLAYER::~PLAYER() {
	player = NULL;
	delete player;
}