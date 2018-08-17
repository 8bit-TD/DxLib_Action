#pragma once
#include "chara.h"

class ENEMY : public CHARA {
private:
	CHARA * enemy;
	int move_type;//敵の動きのタイプ
	double px, py;//プレイヤーの位置
	double tx, ty;//ターゲット位置

	void Move() override;
	void Draw() override;

public:
	ENEMY(
		std::string file,//画像
		int x,//x座標
		int y,//y座標
		int w,//w解像度
		int h,//h解像度
		int s,//キャラクターすり抜け用のサイズ
		int a,//向いている方向 
		double sp,//スピード
		double jp,//ジャンプ
		int mhp,//maxhp
		int mmp//maxmp
	);
	~ENEMY();
	void All() override;
};

///////////////////////// ENEMY_MANAGER /////////////////////////
class ENEMY_MANAGER {
	int enemy_num;//敵の数
	ENEMY *enemy[5000];
	std::vector<double> blank_block;//空いているブロック動的配列

public:
	ENEMY_MANAGER(int n, std::vector<double> gbb);
	~ENEMY_MANAGER();
	int GetEnemyNum();//敵の数を取得
	bool GetDeathFlag(int index);//死亡フラグを取得
	void GetEnemyPos(std::vector<VECTOR> *ep);//位置を取得
	void SetDamage(int index, int damage);//ダメージを設定
	void AutoRecovery();//自動回復
	void All();
};