#pragma once
//�e�N���X

class BALL {
	double mx, my;//�ړ���
	double angle;//�e�̃A���O��
	double player_x, player_y;//�v���C���[�̍��W

public:
	//double bx, by;//���W
	VECTOR pos;
	int radius;//�e�̑傫��
	int max_radius;
	double speed;//�e�̃X�s�[�h
	bool endflag;//�I���t���O
	int life;//���C�t
	int max_life;
	int color;
	
	void SetBallFlag(bool flag);//�t���O��ݒ�
	bool GetBallFlag();//�t���O���擾
	void SetBallPos(double x, double y, double angle);//�ʒu��ݒ�
	void SetBallParam(int speed, int radius, int lif, int col);//�p�����[�^�ݒ�
	int GetBallContact(double x, double y, double size);//�e�̐ڐG����
	void GetBallPos(double *x, double *y);//�ʒu���擾
	void Move();
	void Draw();
	void All();
	BALL();
};

///////////////////////// BALL_MANAGER /////////////////////////////

class BALL_MANAGER {
	BALL *ball[PSHOT_NUM];

private:
	double angle;

public:

	BALL_MANAGER();
	void SetBall(double x, double y, int width, int height, int mouse_x, int mouse_y);
	void SetBallFlag(int index, bool flag);//�t���O��ݒ�
	int GetBallNum();//�e�̐����擾
	int GetBallContact(double x, double y, double size);//�e�̐ڐG����
	void GetBallPos(std::vector<VECTOR> *bp);
	void Move();
	void Draw();
	void All();
	~BALL_MANAGER();
};
