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
		std::string file, //画像
		int x,     //x座標
		int y,     //y座標 
		int w,     //w解像度
		int h,     //h解像度
		int s,     //キャラクターすり抜け用のサイズ
		int a,     //向いている方向 
		double sp, //スピード
		double jp, //ジャンプ
		int mhp,   //maxhp
		int mmp    //maxmp
	);
	void GetPlayerPos(double *x, double *y); //プレイヤーの位置を取得
	void GetPlayerHP(int *Hp, int *Maxhp);   //プレイヤーのhpを取得
	void All() override;
	~PLAYER();
};
