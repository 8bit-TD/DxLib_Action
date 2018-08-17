#pragma once
//�_���[�W�\���N���X
#include "pch.h"

class DAMAGE {

public:
	VECTOR pos;//�ʒu
	double my;//�ړ��ly
	double start_y;//�ŏ��̈ʒuy
	int bound;//�o�E���h�J�E���g
	double rise_value;//�㏸�l
	int damage;//�_���[�W
	bool endflag;//�I���t���O
	int color;//�J���[

	DAMAGE();

	void SetDamage(bool flag, VECTOR p, int d, int col);//�t���O��ݒ�
	bool GetDamageFlag();//�t���O���擾
	void Move();
	void Draw();
	void All();
};

///////////////////////// DAMAGE_MANAGER /////////////////////////////

class DAMAGE_MANAGER {
	DAMAGE *damage[DAMAGE_NUM];

private:
	int count;
	
public:
	DAMAGE_MANAGER();
	void SetDamage(VECTOR p, int d, int col);
	void Move();
	void Draw();
	void All();
	~DAMAGE_MANAGER();
};