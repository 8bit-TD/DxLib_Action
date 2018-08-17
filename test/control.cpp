#include "pch.h"
#include "control.h"

CONTROL::CONTROL(){

}

void CONTROL::Create() {
	gameover_flag = false; //ゲームオーバーフラグ
	death_count = 0;       //プレイヤーが死んだ後のカウント
	game_mode = GAME;//ゲームモード設定
	back = new BACK;
	//enemy_num = GetRand(190)+10;//敵の数
	enemy_num = 100;
	enemy = new ENEMY_MANAGER(enemy_num, GetBlankBlock());//敵作成(敵の数, 空いているブロックの配列)
	std::string ch_file = "images/ch/ch_01.png";
	int px = (GAME_WIDTH / 2); int py = (GAME_HEIGHT - BLOCK_SIZE * 3);
	player = new PLAYER(
		ch_file,//画像
		px,//x座標
		py,//y座標 
		32,//w解像度
		32,//h解像度
		16,//キャラクターすり抜け用のサイズ
		1, //向いている方向
		2, //スピード
		8, //ジャンプ
		500,//maxhp
		500//maxmp
	);
	ball = new BALL_MANAGER;
	damage = new DAMAGE_MANAGER;
}

void CONTROL::GetEnemyPos(std::vector<VECTOR> *ep) {//敵座標の動的配列を取得
	enemy->GetEnemyPos(ep);
}

void CONTROL::GetBallPos(std::vector<VECTOR> *bp) {//弾の位置を取得
	ball->GetBallPos(bp);
}

void CONTROL::SetPlayerBall(double x, double y, int width, int height, int mouse_x, int mouse_y) {//プレイヤーの弾パラメータ設定
	ball->SetBall(x, y, width, height, mouse_x, mouse_y);
}

int CONTROL::GetBlockFlag(double x, double y) {//ブロックがあるかどうかの判定
	return back->GetBlockFlag(x, y);
}

int CONTROL::CheckMove(double x, double y, double *move_x, double *move_y, int size, int offset, bool adjust) {//移動できるか判定
	return back->GetBlockContact(x, y, move_x, move_y, size, offset, adjust);
}

void CONTROL::GetMousePos(int *x, int *y) {//マウス座標を取得
	GetMousePoint(x, y);
}

void CONTROL::GetPlayerPos(double *x, double *y) {//プレイヤー座標を取得
	player->GetPlayerPos(x, y);
}

void CONTROL::SetEnemyDamage(int index, int damage) {//敵にダメージを設定
	enemy->SetDamage(index, damage);
}

bool CONTROL::GameEndCheck() {//ゲームの終了判定
	if (key[KEY_INPUT_F4] == 1) {
		return true;//ESCキーを押したらゲーム終了
	}
	return false;
}

std::vector<double> CONTROL::GetBlankBlock() { return back->GetBlankBlock(); }//空いているブロックを返す

void CONTROL::FpsTimeFanction() {// フレームレートを算出
	SetFontSize(13);
	if (FpsTime_i == 0)
		FpsTime[0] = GetNowCount();               //1周目の時間取得
	if (FpsTime_i == 49) {
		FpsTime[1] = GetNowCount();               //50周目の時間取得
		Fps = 1000.0f / ((FpsTime[1] - FpsTime[0]) / 50.0f);//測定した値からfpsを計算
		FpsTime_i = 0;//カウントを初期化
	} else
		FpsTime_i++;//現在何周目かカウント
	if (Fps != 0)
		DrawFormatString(GAME_WIDTH - 70, GAME_HEIGHT - 20, GetColor(255,255,255), "FPS %.1f", Fps); //fpsを表示
	return;
}

void CONTROL::GetPlayerHP(int *Hp, int *Maxhp) {//プレイヤーのhpを取得
	player->GetPlayerHP(Hp, Maxhp);
}

int CONTROL::GetEnemyNum() {//敵の数を取得
	return enemy->GetEnemyNum();
}

int CONTROL::GetBallNum() {//弾の数を取得
	return ball->GetBallNum();
}

void CONTROL::ShowDamage(VECTOR p, int d, int col) {
	damage->SetDamage(p, d, col);
}

void CONTROL::CheckAttackContact() {//攻撃の接触判定
	for (int e = 0; e < enemy_num; ++e) {//敵のプレイヤーの弾の接触判定
		if (enemy->GetDeathFlag(e)) { continue; }
		for (int b = 0; b < GetBallNum(); ++b) {
			if ((enemy_p[e].x < ball_p[b].x) && (enemy_p[e].x + BLOCK_SIZE > ball_p[b].x) && (enemy_p[e].y < ball_p[b].y) && (enemy_p[e].y + BLOCK_SIZE > ball_p[b].y)) {
				int dam = GetRand(50)+1;
				VECTOR pos;
				pos.x = enemy_p[e].x + BLOCK_SIZE / 2;
				pos.y = enemy_p[e].y - 20;
				SetEnemyDamage(e, dam); //敵にダメージを設定
				ball->SetBallFlag(b, true); //弾のフラグを設定
				player->SetUseMP(1);        //MP消費
				ShowDamage(pos, dam, GetColor(255,255,255)); //ダメージを表示
			}
		}
	}
	double px; double py;
	player->GetPlayerPos(&px, &py);
	for (int e = 0; e < enemy_num; ++e) {
		if (enemy->GetDeathFlag(e)) { continue; }
		if ((player->CheckContact(enemy_p[e], BLOCK_SIZE))&&(!player->GetDeathFlag())) {
			int dam = GetRand(10) + 1;
			player->SetDamage(dam);
			VECTOR pos;
			pos.x = px + BLOCK_SIZE / 2;
			pos.y = py - 20;
			ShowDamage(pos, dam, GetColor(255,0,0));
		}
	}
}

void CONTROL::AutoRecovery() {//自動回復処理
	if (g_count % 60 == 0) {
		player->AutoRecovery();//プレイヤーの自動回復
		enemy->AutoRecovery();//敵の自動回復
	}
}

bool CONTROL::GetGameOverFlag() {//ゲームオーバーフラグを取得
	return gameover_flag;
}

void CONTROL::ScreenDark() {//死亡時に画面を徐々に暗くする
	if (player_hp == 0) {++death_count;	}
	if (death_count > 300) {gameover_flag = true;}
}

CONTROL::eGame CONTROL::GetGameMode() {//ゲームモードを取得
	return game_mode;
}

void CONTROL::SetGameMode(CONTROL::eGame eg) {//ゲームモードを設定
	game_mode = eg;
}

void CONTROL::ShowInfo() {//情報を表示
	int mouse_x, mouse_y;      GetMousePos(&mouse_x, &mouse_y);
	double player_x, player_y; GetPlayerPos(&player_x, &player_y);
	int maxhp;             GetPlayerHP(&player_hp, &maxhp);
	
	SetFontSize(13);
	DrawFormatString(10, GAME_HEIGHT - 20, GetColor(255, 255, 255), "マウス位置: %d,%d", mouse_x, mouse_y);
	DrawFormatString(180, GAME_HEIGHT - 20, GetColor(255, 255, 255), "プレイヤー位置: %d,%d", (int)player_x, (int)player_y);
	DrawFormatString(380, GAME_HEIGHT - 20, GetColor(255, 255, 255), "HP: %d/%d", player_hp, maxhp);
	DrawFormatString(480, GAME_HEIGHT - 20, GetColor(255, 255, 255), "弾: %d/%d", GetBallNum(), (int)PSHOT_NUM);
	DrawFormatString(580, GAME_HEIGHT - 20, GetColor(255, 255, 255), "敵: %d/%d", GetEnemyNum(), enemy_num);
	DrawFormatString(700, GAME_HEIGHT - 20, GetColor(255, 255, 255), "モード: %d", game_mode);
	DrawFormatString(1600, GAME_HEIGHT - 20, GetColor(255, 255, 255), "フレーム: %d", g_count);
	SetDrawBlendMode(DX_BLENDMODE_MULA, death_count);
	DrawBox(0, 0, GAME_WIDTH, GAME_HEIGHT, GetColor(0, 0, 0), 1);//死亡時の画面暗転
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

void CONTROL::All(){
	GetEnemyPos(&enemy_p); //敵座標の動的配列を取得
	GetBallPos(&ball_p);   //弾座標の動的配列を取得
	CheckAttackContact();  //攻撃の接触判定
	back->All();           //背景処理
	enemy->All();          //敵処理
	ball->All();           //弾処理
	player->All();         //プレイヤー処理
	damage->All();         //ダメージ表示処理
	ShowInfo();            //情報を表示
	AutoRecovery();        //自動回復
	ScreenDark();          //死亡時に画面を徐々に暗くする
}

void CONTROL::Finalize() {
	back = NULL;
	enemy = NULL;
	player = NULL;
	ball = NULL;
	damage = NULL;
	delete back;
	delete enemy;
	delete player;
	delete ball;
	delete damage;
}

CONTROL::~CONTROL(){
	Finalize();
}
