#include "pch.h"
#include "enemy.h"
#include "control.h"

ENEMY::ENEMY(std::string file, int x, int y, int w, int h, int s, int a,double sp, double jp, int mhp, int mmp) : CHARA(file, x, y, w, h, s, a, sp, jp, mhp, mmp) {
	enemy = new CHARA(file, x, y, w, h, s, a, sp, jp, mhp, mmp);
	speed = BASE_SPEED + sp;
	jump = BASE_JUMP + jp;
}

void ENEMY::Move() {
	CONTROL *control = CONTROL::GetInstance();
	move_x = move_y = 0;//移動初期化

	int xx = pos.x + width / 2;
	int yy = pos.y + BLOCK_SIZE + BLOCK_SIZE ;

	move_x += (aim * speed);
	fall_sp = fall_sp + GRAVITY;
	move_y += fall_sp;
	
	CHARA::CheckMove();//移動できるか判定
	if (side_contact == true) { aim = aim * -1; }//壁に接触したら向きを変える
	if (aim == 1) { if (control->GetBlockFlag(pos.x + width/2 + move_x, pos.y + height + 1) == 0) { aim = aim * -1; }} //落下しそうになったら向きを変える
	else {if (control->GetBlockFlag(pos.x + width / 2 + move_x, pos.y + height + 1) == 0) { aim = aim * -1; }}
	CHARA::Move();
}

void ENEMY::Draw() {
	CHARA::Draw();
	DrawBox(pos.x - 2, pos.y - 5 - 2, pos.x + width + 2, pos.y - 2, GetColor(50, 25, 0), 1); //HPゲージ枠
	DrawBox(pos.x, pos.y - 5, pos.x + (int)hp_gauge, pos.y - 2, GetColor(255, 150, 50), 1);   //HPゲージ
	SetFontSize(10);
	DrawFormatString(pos.x, pos.y - 16, GetColor(255, 255, 255), "%d/%d", (int)hp, (int)maxhp);//HP
}

void ENEMY::All() {
	CHARA::All();
}

ENEMY::~ENEMY() {
	enemy = NULL;
	delete enemy;
}

////////////////////////////////////////////////// ENEMY_MANAGER //////////////////////////////////////////////////

ENEMY_MANAGER::ENEMY_MANAGER(int n, std::vector<double> gbb) {
	enemy_num = n;//敵の数
	std::string ene_file1 = "images/enemy/slime.png";
	std::string ene_file2 = "images/enemy/mage.png";
	std::string ene;
	blank_block = gbb;//空いているブロックを取得
	for (int i = 0; i < enemy_num; ++i) {
		int aim = 1; if (GetRand(100) % 2 == 0) { aim = -1; }
		int rnd = GetRand(blank_block.size() - 1);
		int ex = (int)(blank_block[rnd]) * BLOCK_SIZE;
		int ey = (blank_block[rnd] - (int)(blank_block[rnd])) * 100 * BLOCK_SIZE;
		if (GetRand(100) % 2 == 0) { ene = ene_file1; } else { ene = ene_file2; }
		enemy[i] = new ENEMY(
			ene, //画像
			ex, //x座標
			ey, //y座標 
			32, //w解像度
			32, //h解像度
			16, //キャラクターすり抜け用のサイズ
			aim,//向いている方向 
			GetRand(10) / 100.00,//スピード
			GetRand(100) / 10.0, //ジャンプ
			GetRand(500) + 1,//maxhp
			GetRand(500) + 1//maxmp
		);
	}
}

int ENEMY_MANAGER::GetEnemyNum() {
	int count = 0;
	for (int i = 0; i < enemy_num; ++i) {
		if (!enemy[i]->GetDeathFlag()) { ++count; }
	}
	return count;
}

bool ENEMY_MANAGER::GetDeathFlag(int index) {//死亡フラグを取得
	return enemy[index]->GetDeathFlag();
}

void ENEMY_MANAGER::GetEnemyPos(std::vector<VECTOR> *ep) {
	std::vector<VECTOR> eep;
	for (int i = 0; i < enemy_num; ++i) {
		double ex; double ey; VECTOR p;
		enemy[i]->GetPos(&ex, &ey);
		p.x = ex; p.y = ey;
		eep.push_back(p);
	}
	*ep = eep;
}

void ENEMY_MANAGER::SetDamage(int index, int damage) {
	enemy[index]->SetDamage(damage);
}

void ENEMY_MANAGER::AutoRecovery() {//自動回復
	for (int i = 0; i < enemy_num; ++i) {
		enemy[i]->AutoRecovery();
	}
}

void ENEMY_MANAGER::All() {
	for (int i = 0; i < enemy_num; ++i) {
		enemy[i]->All();
	}
}

ENEMY_MANAGER::~ENEMY_MANAGER() {
	for (int i = 0; i < enemy_num; ++i) {
		enemy[i] = NULL;
		delete enemy[i];
	}
}

