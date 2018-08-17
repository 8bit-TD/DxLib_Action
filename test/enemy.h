#pragma once
#include "chara.h"

class ENEMY : public CHARA {
private:
	CHARA * enemy;
	int move_type;//�G�̓����̃^�C�v
	double px, py;//�v���C���[�̈ʒu
	double tx, ty;//�^�[�Q�b�g�ʒu

	void Move() override;
	void Draw() override;

public:
	ENEMY(
		std::string file,//�摜
		int x,//x���W
		int y,//y���W
		int w,//w�𑜓x
		int h,//h�𑜓x
		int s,//�L�����N�^�[���蔲���p�̃T�C�Y
		int a,//�����Ă������ 
		double sp,//�X�s�[�h
		double jp,//�W�����v
		int mhp,//maxhp
		int mmp//maxmp
	);
	~ENEMY();
	void All() override;
};

///////////////////////// ENEMY_MANAGER /////////////////////////
class ENEMY_MANAGER {
	int enemy_num;//�G�̐�
	ENEMY *enemy[5000];
	std::vector<double> blank_block;//�󂢂Ă���u���b�N���I�z��

public:
	ENEMY_MANAGER(int n, std::vector<double> gbb);
	~ENEMY_MANAGER();
	int GetEnemyNum();//�G�̐����擾
	bool GetDeathFlag(int index);//���S�t���O���擾
	void GetEnemyPos(std::vector<VECTOR> *ep);//�ʒu���擾
	void SetDamage(int index, int damage);//�_���[�W��ݒ�
	void AutoRecovery();//������
	void All();
};