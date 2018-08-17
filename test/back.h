#pragma once
#include "pch.h"


class BACK {
	//���W
	double x, y;
	//�O���t�B�b�N�n���h��
	int gh[3];
	//�u���b�N�̐ݒ�
	char block[BLOCK_W_NUM][BLOCK_H_NUM] = {};
	std::vector<double> blank_block;


private:
	void Draw();
public:
	void All();
	void Move();
	std::vector<double> GetBlankBlock();//�󂢂Ă���u���b�N��Ԃ�
	int GetBlockFlag(double x, double y);
	int GetBlockContact(
		double x, //�ʒux
		double y, //�ʒuy
		double *move_x, //�ړ��lx
		double *move_y, //�ړ��ly
		int size, //�T�C�Y
		int offset, //�I�t�Z�b�g
		bool adjust //�ړ��l�̒���
	);
	BACK();
	~BACK();
};