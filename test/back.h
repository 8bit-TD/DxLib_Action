#pragma once
#include "pch.h"


class BACK {
	//座標
	double x, y;
	//グラフィックハンドル
	int gh[3];
	//ブロックの設定
	char block[BLOCK_W_NUM][BLOCK_H_NUM] = {};
	std::vector<double> blank_block;


private:
	void Draw();
public:
	void All();
	void Move();
	std::vector<double> GetBlankBlock();//空いているブロックを返す
	int GetBlockFlag(double x, double y);
	int GetBlockContact(
		double x, //位置x
		double y, //位置y
		double *move_x, //移動値x
		double *move_y, //移動値y
		int size, //サイズ
		int offset, //オフセット
		bool adjust //移動値の調整
	);
	BACK();
	~BACK();
};