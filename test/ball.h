#pragma once
//弾クラス

class BALL {
	double mx, my;//移動量
	double angle;//弾のアングル
	double player_x, player_y;//プレイヤーの座標

public:
	//double bx, by;//座標
	VECTOR pos;
	int radius;//弾の大きさ
	int max_radius;
	double speed;//弾のスピード
	bool endflag;//終了フラグ
	int life;//ライフ
	int max_life;
	int color;
	
	void SetBallFlag(bool flag);//フラグを設定
	bool GetBallFlag();//フラグを取得
	void SetBallPos(double x, double y, double angle);//位置を設定
	void SetBallParam(int speed, int radius, int lif, int col);//パラメータ設定
	int GetBallContact(double x, double y, double size);//弾の接触判定
	void GetBallPos(double *x, double *y);//位置を取得
	void Move();
	void Draw();
	void All();
	BALL();
};

///////////////////////// BALL_MANAGER /////////////////////////////

class BALL_MANAGER {
	BALL *ball[PSHOT_NUM];

private:
	double angle;

public:

	BALL_MANAGER();
	void SetBall(double x, double y, int width, int height, int mouse_x, int mouse_y);
	void SetBallFlag(int index, bool flag);//フラグを設定
	int GetBallNum();//弾の数を取得
	int GetBallContact(double x, double y, double size);//弾の接触判定
	void GetBallPos(std::vector<VECTOR> *bp);
	void Move();
	void Draw();
	void All();
	~BALL_MANAGER();
};
