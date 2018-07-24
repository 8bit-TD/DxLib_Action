#pragma once
#include "define.h"

class BOSS {
	//���W
	double x, y, prev_x, prev_y;
	//�O���t�B�b�N�n���h��
	int gh_face[2];
	int gh_shot[3];
	//���݂̈ړ��p�^�[��
	int move_pattern;
	int prev_move_pattern;
	//���݂̃V���b�g�p�^�[��
	int shot_pattern;
	int prev_shot_pattern;
	//�e�\����
	E_SHOT shot[BOSS_SHOTNUM];
	//���v�p�x�Ƒ�����
	int angle, raise;
	//���ړ����̑�����
	int raise2;
	int waitcount;
	bool wait;
	//���̈ړ��ꏊ�܂ł̋���
	double movex, movey;
	int p3_state;
	//�_���[�W�𕉂������ǂ����̃t���O
	bool damageflag;
	//�����Ă��邩�ǂ����̃t���O
	bool flag;
	//�V���b�g�t���O
	bool shotflag;
	//�V���b�g�J�E���g
	int scount;
	//�V���b�g�T�E���h�t���O
	bool s_shot;
	int temp_scount;

	int count;
	int hp;
	int prev_hp;

	//�_���[�W�𕉂�Ȃ��t���O
	bool no_damage;

private:
	void Move();
	void Appear();
	void MovePattern1();
	void MovePattern2();
	void MovePattern3();
	int ShotSerch();
	bool ShotOutCheck(int i);
	void MoveInit(double bx, double by, int state);
	void MoveToDefault();
	void Shot();
	void Draw();
public:
	BOSS();
	void SetDamageFlag();
	void SetDamageSetting();
	void SetFlag(bool f);
	bool GetFlag();
	void GetPosition(double *x, double *y);
	bool GetShotSound();
	void SetShotFlag(int index, bool flag);
	bool GetShotPosition(int index, double *x, double *y, int *type);
	bool GetGrazeFlag(int index);
	void SetGrazeFlag(int index);
	int HpSet(int i);
	int GetPrevHp();
	bool GetNodamageFlag();
	void SetMovePattern(int pattern);
	void SetShotPattern(int pattern);
	
	void All();
};
