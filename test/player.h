#pragma once
#include "chara.h"
#include "ball.h"

class PLAYER : public CHARA {
private:
	double angle;

	CHARA * player;
	void Move() override;
	void Draw() override;

public:
	PLAYER(
		std::string file, //�摜
		int x,     //x���W
		int y,     //y���W 
		int w,     //w�𑜓x
		int h,     //h�𑜓x
		int s,     //�L�����N�^�[���蔲���p�̃T�C�Y
		int a,     //�����Ă������ 
		double sp, //�X�s�[�h
		double jp, //�W�����v
		int mhp,   //maxhp
		int mmp    //maxmp
	);
	void GetPlayerPos(double *x, double *y); //�v���C���[�̈ʒu���擾
	void GetPlayerHP(int *Hp, int *Maxhp);   //�v���C���[��hp���擾
	void All() override;
	~PLAYER();
};
