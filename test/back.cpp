#include "back.h"
#include "pch.h"

BACK::BACK() {
	gh[1] = LoadGraph("images/bg/block_0.png");
	gh[2] = LoadGraph("images/bg/block_1.png");
	gh[3] = LoadGraph("images/bg/block_2.png");
	SRand(GetRand(123456)); // �����̏����l��123456�ɐݒ肷��
	for (int w = 0; w < BLOCK_W_NUM; ++w) {
		for (int h = 0; h < BLOCK_H_NUM; ++h) {
			if (w == 0 || h == 0 || w == (BLOCK_W_NUM - 1) || h == (BLOCK_H_NUM - 1)) {//�l����block2
				block[w][h] = 2;
				if (h == (BLOCK_H_NUM - 1)) {
					if (block[w][h - 1] == 0) {//(�󂢂Ă���u���b�N+�����u���b�N)���擾
						double hh = (double)(h - 1) / 100;
						blank_block.push_back(w + hh);
					}
				}
			} else if (GetRand(100) % 5 == 0) {
				if ((w * BLOCK_SIZE > (GAME_WIDTH / 2 - BLOCK_SIZE * 2)) && (w * BLOCK_SIZE < (GAME_WIDTH / 2 + BLOCK_SIZE * 2))
				&& (h * BLOCK_SIZE > (GAME_HEIGHT - BLOCK_SIZE * 5)) ) { block[w][h] = 0; continue; }//�L�����o���ʒu�Ƀu���b�N��u���Ȃ�����
				if (GetRand(2) % 2 == 0) {
					block[w][h] = 1;
				} else {
					block[w][h] = 2;
				}
				if ((h != 0) && (block[w][h - 1] == 0)) {//(�󂢂Ă���u���b�N+�����u���b�N)���擾
					double hh = (double)(h-1) / 100;
					blank_block.push_back(w + hh);
				}
			} else { 
				block[w][h] = 0;
				
			}
		}
	}
}

int BACK::GetBlockFlag(double x, double y) {//�u���b�N�����邩�ǂ����̔���
	int xx = (int)x / BLOCK_SIZE; 
	int yy = (int)y / BLOCK_SIZE;
	return block[xx][yy];
}

std::vector<double> BACK::GetBlankBlock() { return blank_block; }//�󂢂Ă���u���b�N��Ԃ�


int BACK::GetBlockContact(double x, double y, double *move_x, double *move_y, int size, int offset, bool adjust) {//�u���b�N�Փ˔���
	double xx = x + *move_x ;
	double yy = y + *move_y ;
	double blx, bty, brx, bby;
	if (GetBlockFlag((int)xx, (int)yy) != 0) {
		blx = (double)((int)xx / BLOCK_SIZE) * BLOCK_SIZE ;
		brx = (double)((int)xx / BLOCK_SIZE + 1) * BLOCK_SIZE ;
		bty = (double)((int)yy / BLOCK_SIZE) * BLOCK_SIZE;
		bby = (double)((int)yy / BLOCK_SIZE + 1) * BLOCK_SIZE;
		if ((*move_y > 0) && ((y - *move_y) < bty)) {//��ӂɓ��������ꍇ
			if (adjust){ *move_y = bty - y - 1.0; }
			return 3;
		}
		if ((*move_y < 0) && ((y - *move_y) > bby)) {//���ӂɓ��������ꍇ
			if (adjust) { *move_y = bby - y + 1.0; }
			return 4;
		}
		if ((*move_x > 0) && ((x - *move_x) < blx)) {//���ӂɓ��������ꍇ
			if (adjust) { *move_x = blx - x - 1.0; }
			return 1;
		}
		if ((*move_x < 0) && ((x - *move_x) > brx)) {//�E�ӂɓ��������ꍇ
			if (adjust) { *move_x = brx - x + 1.0; }
			return 2;
		}
	}
	return 0;
}

void BACK::Move() {

}

void BACK::Draw() {
	for (int w = 0; w < BLOCK_W_NUM; ++w) {
		for (int h = 0; h < BLOCK_H_NUM; ++h) {
			if (block[w][h] != 0){ DrawGraph(w * BLOCK_SIZE, h * BLOCK_SIZE, gh[block[w][h]], FALSE); }
		}
	}
	//for (int i = 0; i < blank_block.size(); ++i) {
		//DrawString(500, 15*i, blank_block[i].c_str(), GetColor(255,255,255));
	//}
	
}

void BACK::All() {
	Move();
	Draw();
}

BACK::~BACK() {
	for (int i = 0; i < 3; ++i) {DeleteGraph(gh[i]);}//����������摜���폜
	gh[3] = NULL;
	block[BLOCK_W_NUM][BLOCK_H_NUM] = NULL;
	x = NULL;
	y = NULL;
}