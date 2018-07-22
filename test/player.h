#pragma once

#include "effect_pdead.h"
#include "ball.h"

class PLAYER {
private:
	//x���W,y���W
	double x, y;

	//�摜��
	int width, height;

	//�O���t�B�b�N�n���h���i�[�p�z��
	int gh[12];

	//�ړ��W��
	float move;

	//�������Əc�����̃J�E���g���B
	int xcount, ycount;
	//�Y���p�ϐ�
	int ix, iy, result;

	//�v���C���[�̃��C�t
	int life;
	bool damageflag;
	bool endflag;

	int power;

	//�_���[�W���̃J�E���g
	int dcount;

	//�e
	SHOT shot[PSHOT_NUM];

	//�J�E���g
	int count;

	//�T�E���h�֘A�t���O
	//�V���b�g��
	bool s_shot;

	EFFECT_PDEAD *effect_pdead;

	//�{�[���N���X
	BALL ball;

private:
	void Move();
	void Draw();
	void Shot();
	void Ball();
	void BallShotSet(int index);
	int NearEnemySerch();

public:
	PLAYER();
	bool GetShotSound();
	bool GetShotPosition(int index, double *x, double *y);
	void SetShotFlag(int index, bool flag);
	void GetPosition(double *x, double *y);
	void SetDamageFlag();
	bool GetDamageFlag();
	int GetLife();
	void SetPower(int p);
	int GetPower();
	void All();
};
