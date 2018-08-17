#pragma once
//すべてのキャラクターの基底クラス
class CHARA {
private:
	
public:
	int gh;                //グラフィックハンドル格納用配列
	VECTOR pos;            //位置
	int width, height;     //画像幅
	int ch_size;           //キャラクターすり抜け用のサイズ
	int aim;               //向いている方向
	double speed;          //スピード
	double jump;           //ジャンプ力
	int maxhp;             //MaxHP
	double hp;             //HP
	int maxmp;             //MaxMp
	double mp;             //MP
	bool death_flag;       //死亡フラグ
	double move_x, move_y; //移動先座標
	double fall_sp;        //落下速度
	bool side_contact;     //左右のブロックに接触したフラグ
	int mouse_x;           //マウスの座標x
	int mouse_y;           //マウスの座標y
	int hp_gauge;          //hpゲージ用
	int mp_gauge;          //mpゲージ用
	bool damage_flag;      //ダメージを受けた時のフラグ

	void CheckMove();                  //移動できるか判定
	void CheckAim();                   //マウス座標をチェック
	bool GetDeathFlag();               //死亡フラグを取得
	void GetPos(double *x, double *y); //位置を取得
	double GetMaxHP();                 //MAXHPを取得
	double GetMaxMP();                 //MAXMPを取得
	int GetMP();                       //MPを取得
	void SetDamage(int damage);        //ダメージを設定
	void SetRecoveryHP(int val);       //HPを回復
	void SetRecoveryMP(int val);       //MPを回復
	void SetUseMP(int val);            //MPを使用
	void AutoRecovery();               //自動回復
	bool CheckContact(VECTOR pos, double size); //接触判定
	virtual void Move();
	virtual void Draw();
	virtual void All();
	CHARA(
		std::string file, //画像
		int x,            //x座標
		int y,            //y座標 
		int w,            //w解像度
		int h,            //h解像度
		int s,            //キャラクターすり抜け用のサイズ
		int a,            //向いている方向 
		double sp,        //スピード
		double jp,        //ジャンプ
		int mhp,          //maxhp
		int mmp           //maxmp
	);
	virtual ~CHARA();
};
