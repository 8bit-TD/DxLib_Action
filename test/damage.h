#pragma once
//ダメージ表示クラス
#include "pch.h"

class DAMAGE {

public:
	VECTOR pos;//位置
	double my;//移動値y
	double start_y;//最初の位置y
	int bound;//バウンドカウント
	double rise_value;//上昇値
	int damage;//ダメージ
	bool endflag;//終了フラグ
	int color;//カラー

	DAMAGE();

	void SetDamage(bool flag, VECTOR p, int d, int col);//フラグを設定
	bool GetDamageFlag();//フラグを取得
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