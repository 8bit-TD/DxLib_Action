#include "pch.h"
#include "chara.h"
#include "control.h"
#include "se.h"

CHARA::CHARA(std::string file, int xx, int yy, int w, int h, int s, int a, double sp, double jp, int mhp, int mmp) {
	gh = LoadGraph(file.c_str());//画像読み込み
	width = w;//w解像度
	height = h;//h解像度
	ch_size = s;//キャラクターすり抜け用のサイズ
	aim = a; // 向いている方向
	pos.x = xx;
	pos.y = yy;
	move_x = 0;//移動分x
	move_y = 0;//移動分x
	death_flag = false;//生きているかどうか
	damage_flag = false;//ダメージを受けた時のフラグ
	fall_sp = 0;//落下速度
	speed = BASE_SPEED;
	maxhp = mhp;//maxhp
	hp = maxhp; //hp
	maxmp = mmp;//maxmp
	mp = maxmp; //mp
	hp_gauge = width;//hpゲージ
	mp_gauge = width;//mpゲージ
}

void CHARA::CheckAim() {//マウス座標をチェック
	CONTROL *control = CONTROL::GetInstance();
	control->GetMousePos(&mouse_x, &mouse_y);
}

bool CHARA::GetDeathFlag() {//死亡フラグを取得
	return death_flag;
}

void CHARA::GetPos(double *xx, double *yy) {//位置を取得
	*xx = (double)pos.x; *yy = (double)pos.y;
}

double CHARA::GetMaxHP() {//MAXHPを取得
	return maxhp;
}

double CHARA::GetMaxMP() {//MAXMPを取得
	return maxmp;
}

int CHARA::GetMP() {//MPを取得
	return mp;
}

void CHARA::SetUseMP(int val) {//MPを使用
	mp = mp - val; if (mp < 0) { mp = 0; }
}

void CHARA::SetDamage(int damage) {//ダメージを設定
	SE *se = SE::GetInstance();
	hp = hp - damage;
	if (damage > 0) {
		se->SE_Damage();
		if (hp < 1) {
			hp = 0;
			death_flag = true;
			se->SE_Death();
		}
		damage_flag = true;
	}
	
}

bool CHARA::CheckContact(VECTOR tp, double size) {//接触判定
	int ex = tp.x + size / 2;
	int ey = tp.y + size / 2;
	int left   = (pos.x + width / 2) - ch_size / 2;
	int right  = (pos.x + width / 2) + ch_size / 2;
	int top    = (pos.y + height / 2) - ch_size / 2;
	int bottom = (pos.y + height / 2) + ch_size / 2;
	if ((left < ex) && (right > ex) && (top < ey) && (bottom > ey)) { return true; }
	return false;
}

void CHARA::SetRecoveryHP(int val) {//HPを回復
	hp = hp + val; if (hp > maxhp) { hp = maxhp; }
}

void CHARA::SetRecoveryMP(int val) {//MPを回復
	mp = mp + val; if (mp > maxmp) { mp = maxmp; }
}

void CHARA::AutoRecovery() {//自動回復
	if (death_flag) return;
	SetRecoveryHP((int)(GetMaxHP() / 10));
	SetRecoveryMP((int)(GetMaxMP() / 10));
}


void CHARA::CheckMove() {//移動できるか判定
	CONTROL *control = CONTROL::GetInstance();
	double dummy = 0; side_contact = false;
	if (control->CheckMove(pos.x + width / 2 - ch_size / 2, pos.y + height, &dummy, &move_y, width, ch_size, true) == 3)
	{// キャラ左下 : ブロック上辺
		pos.y += move_y; move_y = 0; fall_sp = 0;
	}
	if (control->CheckMove(pos.x + width / 2 + ch_size / 2, pos.y + height, &dummy, &move_y, width, ch_size, true) == 3)
	{// キャラ右下 : ブロック上辺
		pos.y += move_y; move_y = 0; fall_sp = 0;
	}
	if (control->CheckMove(pos.x + width / 2 - ch_size / 2, pos.y + height / 2 - ch_size / 2, &dummy, &move_y, width, ch_size, true) == 4)
	{// キャラ左上 : ブロック下辺
		pos.y += move_y; move_y = 0;
	}
	if (control->CheckMove(pos.x + width / 2 + ch_size / 2, pos.y + height / 2 - ch_size / 2, &dummy, &move_y, width, ch_size, true) == 4)
	{// キャラ右上 : ブロック下辺
		pos.y += move_y; move_y = 0;
	}

	if (control->CheckMove(pos.x + width / 2 + ch_size / 2, pos.y + height / 2 - ch_size / 2, &move_x, &dummy, width, ch_size, true) == 1)
	{// キャラ右上 : ブロック左辺
		pos.x += move_x; move_x = 0; side_contact = true;
	}
	if (control->CheckMove(pos.x + width / 2 + ch_size / 2, pos.y + height, &move_x, &dummy, width, ch_size, true) == 1)
	{// キャラ右下 : ブロック左辺
		pos.x += move_x; move_x = 0;  side_contact = true;
	}

	if (control->CheckMove(pos.x + width / 2 - ch_size / 2, pos.y + height / 2 - ch_size / 2, &move_x, &dummy, width, ch_size, true) == 2)
	{// キャラ左上 : ブロック右辺
		pos.x += move_x; move_x = 0;  side_contact = true;
	}
	if (control->CheckMove(pos.x + width / 2 - ch_size / 2, pos.y + height, &move_x, &dummy, width, ch_size, true) == 2)
	{// キャラ左下 : ブロック右辺
		pos.x += move_x; move_x = 0;  side_contact = true;
	}
	pos.x += move_x; pos.y += move_y;
}

void CHARA::Move(){
	hp_gauge = width / (maxhp / hp);
	if (hp < 0) {
		hp = 0; 
		hp_gauge = 0;
	} if (hp > maxhp) { hp = maxhp; }
	mp_gauge = width / (maxmp / mp);
	if (mp < 0) {
		mp = 0;
		mp_gauge = 0;
	} if (mp > maxmp) { mp = maxmp; }
}

void CHARA::Draw(){
	if (aim == 1) { DrawGraph(pos.x, pos.y, gh, TRUE); } else { DrawTurnGraph(pos.x, pos.y, gh, TRUE); }
	if ((damage_flag)&&(g_count % 2 == 0)) {//ダメージを受けた時は点滅
		SetDrawBlendMode(DX_BLENDMODE_INVSRC, 255);
		if (aim == 1) { DrawGraph(pos.x, pos.y, gh, TRUE); } else { DrawTurnGraph(pos.x, pos.y, gh, TRUE); }
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	
}

void CHARA::All() {
	if (!death_flag) { Move(); }
	if (!death_flag) { Draw(); }
	damage_flag = false;
}

CHARA::~CHARA(){
	DeleteGraph(gh);//メモリから画像を削除
	gh = NULL;
	width = NULL;
	height = NULL;
	ch_size = NULL;
	aim = NULL;
	move_x = NULL;
	move_y = NULL;
	fall_sp = NULL;
	death_flag = NULL;
}

