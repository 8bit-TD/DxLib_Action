#include "pch.h"
#include "chara.h"
#include "control.h"
#include "se.h"

CHARA::CHARA(std::string file, int xx, int yy, int w, int h, int s, int a, double sp, double jp, int mhp, int mmp) {
	gh = LoadGraph(file.c_str());//�摜�ǂݍ���
	width = w;//w�𑜓x
	height = h;//h�𑜓x
	ch_size = s;//�L�����N�^�[���蔲���p�̃T�C�Y
	aim = a; // �����Ă������
	pos.x = xx;
	pos.y = yy;
	move_x = 0;//�ړ���x
	move_y = 0;//�ړ���x
	death_flag = false;//�����Ă��邩�ǂ���
	damage_flag = false;//�_���[�W���󂯂����̃t���O
	fall_sp = 0;//�������x
	speed = BASE_SPEED;
	maxhp = mhp;//maxhp
	hp = maxhp; //hp
	maxmp = mmp;//maxmp
	mp = maxmp; //mp
	hp_gauge = width;//hp�Q�[�W
	mp_gauge = width;//mp�Q�[�W
}

void CHARA::CheckAim() {//�}�E�X���W���`�F�b�N
	CONTROL *control = CONTROL::GetInstance();
	control->GetMousePos(&mouse_x, &mouse_y);
}

bool CHARA::GetDeathFlag() {//���S�t���O���擾
	return death_flag;
}

void CHARA::GetPos(double *xx, double *yy) {//�ʒu���擾
	*xx = (double)pos.x; *yy = (double)pos.y;
}

double CHARA::GetMaxHP() {//MAXHP���擾
	return maxhp;
}

double CHARA::GetMaxMP() {//MAXMP���擾
	return maxmp;
}

int CHARA::GetMP() {//MP���擾
	return mp;
}

void CHARA::SetUseMP(int val) {//MP���g�p
	mp = mp - val; if (mp < 0) { mp = 0; }
}

void CHARA::SetDamage(int damage) {//�_���[�W��ݒ�
	SE *se = SE::GetInstance();
	hp = hp - damage;
	if (damage > 0) {
		se->SE_Damage();
		if (hp < 1) {
			hp = 0;
			death_flag = true;
			se->SE_Death();
		}
		damage_flag = true;
	}
	
}

bool CHARA::CheckContact(VECTOR tp, double size) {//�ڐG����
	int ex = tp.x + size / 2;
	int ey = tp.y + size / 2;
	int left   = (pos.x + width / 2) - ch_size / 2;
	int right  = (pos.x + width / 2) + ch_size / 2;
	int top    = (pos.y + height / 2) - ch_size / 2;
	int bottom = (pos.y + height / 2) + ch_size / 2;
	if ((left < ex) && (right > ex) && (top < ey) && (bottom > ey)) { return true; }
	return false;
}

void CHARA::SetRecoveryHP(int val) {//HP����
	hp = hp + val; if (hp > maxhp) { hp = maxhp; }
}

void CHARA::SetRecoveryMP(int val) {//MP����
	mp = mp + val; if (mp > maxmp) { mp = maxmp; }
}

void CHARA::AutoRecovery() {//������
	if (death_flag) return;
	SetRecoveryHP((int)(GetMaxHP() / 10));
	SetRecoveryMP((int)(GetMaxMP() / 10));
}


void CHARA::CheckMove() {//�ړ��ł��邩����
	CONTROL *control = CONTROL::GetInstance();
	double dummy = 0; side_contact = false;
	if (control->CheckMove(pos.x + width / 2 - ch_size / 2, pos.y + height, &dummy, &move_y, width, ch_size, true) == 3)
	{// �L�������� : �u���b�N���
		pos.y += move_y; move_y = 0; fall_sp = 0;
	}
	if (control->CheckMove(pos.x + width / 2 + ch_size / 2, pos.y + height, &dummy, &move_y, width, ch_size, true) == 3)
	{// �L�����E�� : �u���b�N���
		pos.y += move_y; move_y = 0; fall_sp = 0;
	}
	if (control->CheckMove(pos.x + width / 2 - ch_size / 2, pos.y + height / 2 - ch_size / 2, &dummy, &move_y, width, ch_size, true) == 4)
	{// �L�������� : �u���b�N����
		pos.y += move_y; move_y = 0;
	}
	if (control->CheckMove(pos.x + width / 2 + ch_size / 2, pos.y + height / 2 - ch_size / 2, &dummy, &move_y, width, ch_size, true) == 4)
	{// �L�����E�� : �u���b�N����
		pos.y += move_y; move_y = 0;
	}

	if (control->CheckMove(pos.x + width / 2 + ch_size / 2, pos.y + height / 2 - ch_size / 2, &move_x, &dummy, width, ch_size, true) == 1)
	{// �L�����E�� : �u���b�N����
		pos.x += move_x; move_x = 0; side_contact = true;
	}
	if (control->CheckMove(pos.x + width / 2 + ch_size / 2, pos.y + height, &move_x, &dummy, width, ch_size, true) == 1)
	{// �L�����E�� : �u���b�N����
		pos.x += move_x; move_x = 0;  side_contact = true;
	}

	if (control->CheckMove(pos.x + width / 2 - ch_size / 2, pos.y + height / 2 - ch_size / 2, &move_x, &dummy, width, ch_size, true) == 2)
	{// �L�������� : �u���b�N�E��
		pos.x += move_x; move_x = 0;  side_contact = true;
	}
	if (control->CheckMove(pos.x + width / 2 - ch_size / 2, pos.y + height, &move_x, &dummy, width, ch_size, true) == 2)
	{// �L�������� : �u���b�N�E��
		pos.x += move_x; move_x = 0;  side_contact = true;
	}
	pos.x += move_x; pos.y += move_y;
}

void CHARA::Move(){
	hp_gauge = width / (maxhp / hp);
	if (hp < 0) {
		hp = 0; 
		hp_gauge = 0;
	} if (hp > maxhp) { hp = maxhp; }
	mp_gauge = width / (maxmp / mp);
	if (mp < 0) {
		mp = 0;
		mp_gauge = 0;
	} if (mp > maxmp) { mp = maxmp; }
}

void CHARA::Draw(){
	if (aim == 1) { DrawGraph(pos.x, pos.y, gh, TRUE); } else { DrawTurnGraph(pos.x, pos.y, gh, TRUE); }
	if ((damage_flag)&&(g_count % 2 == 0)) {//�_���[�W���󂯂����͓_��
		SetDrawBlendMode(DX_BLENDMODE_INVSRC, 255);
		if (aim == 1) { DrawGraph(pos.x, pos.y, gh, TRUE); } else { DrawTurnGraph(pos.x, pos.y, gh, TRUE); }
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	
}

void CHARA::All() {
	if (!death_flag) { Move(); }
	if (!death_flag) { Draw(); }
	damage_flag = false;
}

CHARA::~CHARA(){
	DeleteGraph(gh);//����������摜���폜
	gh = NULL;
	width = NULL;
	height = NULL;
	ch_size = NULL;
	aim = NULL;
	move_x = NULL;
	move_y = NULL;
	fall_sp = NULL;
	death_flag = NULL;
}

