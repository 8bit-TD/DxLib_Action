#pragma once
#include <windows.h>

#define MARGIN 10

//�v���C���[�̕����X�s�[�h
#define PLAYER_SPEED 4
#define PLAYER_INITX 180
#define PLAYER_INITY 400
#define PLAYER_LIFE 5

//�w�i�̃X�N���[���X�s�[�h
#define SCROLL_SPEED 2

//���b�Z�[�W�{�b�N�X
#define MSG(m) {\
	MessageBox(NULL,m,"���b�Z�[�W",MB_OK);}

//extern�錾����key�z��ɂǂ�����ł��A�N�Z�X�ł���悤�ɂ���
extern char key[256];

//extern�錾���ăJ�E���g���ɂǂ�����ł��A�N�Z�X�ł���悤�ɂ���
extern int g_count;

//�e�̍ő吔
#define PSHOT_NUM  50

//�e�̃X�s�[�h
#define PSHOT_SPEED 14

struct SHOT {
	bool flag;//�e�����˒����ǂ���
	double x;//x���W
	double y;//y���W
	int gh;//�O���t�B�b�N�n���h��
	int width, height;//�摜�̕��ƍ���
	double rad;//�p�x
	int type;//�e�̎��(0�Ȃ�ʏ�A1�Ȃ�ǐՒe)
};

struct E_SHOT {
	bool flag;//�e�����˒����ǂ���
	double x;//x���W
	double y;//y���W
	double rad;//�p�x(���W�A��)
	int gh;//�O���t�B�b�N�n���h��
	int width, height;//�摜�̕��ƍ���
	int pattern;//�V���b�g�p�^�[��
	int speed;//�e�̃X�s�[�h
	int gflag;//�O���C�Y����p�t���O
	int type;//�e�̎��
};

#define ENEMY_SNUM 50

#define BOSS_SHOTNUM 150

#define BOSS_SHAKE 20

struct ENEMYDATA {
	int type;//�G���
	int stype;//�e���
	int m_pattern;//�ړ��p�^�[��
	int s_pattern;//���˃p�^�[��
	int in_time;//�o������
	int stop_time;//��~����
	int shot_time;//�e���ˎ���
	int out_time;//�A�Ҏ���
	int x;//x���W
	int y;//y���W
	int speed;//�e�X�s�[�h
	int hp;//HP
	int item;//�A�C�e��
};

#define ENEMY_NUM 30
#define EFFECT_EDEADNUM 20
#define EFFECT_PDEADNUM 10

#define PI 3.1415

//�����蔻��p���a��`
#define PLAYER_COLLISION 4
#define ENEMY1_COLLISION 14

#define PSHOT_COLLISION 3
#define ESHOT0_COLLISION 10
#define ESHOT1_COLLISION 3
#define ESHOT2_COLLISION 2
#define ESHOT3_COLLISION 2
#define GRAZE_COLLISION 10

#define GRAZE_NUM 200

struct PEFFECT_EXPAND {
	double x, y;
	double rad;
	int speed;
};

//�X�R�A�̕����`��̊�ƂȂ�X���W
#define SCORE_X 390

//�A�C�e���̓����蔻��p���a
#define ITEM_COLLISION 16
//�A�C�e���̑���
#define ITEM_NUM 30

#define BALL_SHAKE 15

#define BALL_INITX 50
#define BALL_INITY 30

#define BOSS_COLLISION 60

#define BOSS_HP 500

