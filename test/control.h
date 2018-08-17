#include "player.h"
#include "enemy.h"
#include "back.h"
#include "damage.h"

class CONTROL {
private:
	BACK * back;                     //背景クラス
	PLAYER *player;                  //プレイヤークラス
	ENEMY_MANAGER *enemy;            //敵クラス
	BALL_MANAGER *ball;              //弾クラス
	DAMAGE_MANAGER *damage;          //ダメージクラス
	std::vector<double> blank_block; //空いているブロック動的配列
	std::vector<VECTOR> enemy_p;     //敵の位置
	std::vector<VECTOR> ball_p;      //弾の位置
	int enemy_num;                   //敵の数
	double Fps = 0;                  //フレームレート表示用
	int FpsTime[2] = { 0, };         //フレームレート表示用
	int FpsTime_i = 0;               //フレームレート表示用
	int player_hp;                   //プレイヤーのHP
	bool gameover_flag;              //ゲームオーバーフラグ
	int death_count;                 //プレイヤーが死んだ後のカウント

	CONTROL();                                 //コンストラクタ
	~CONTROL();                                //デストラクタ
	std::vector<double> GetBlankBlock();       //空いているブロックを返す
	void ShowInfo();                           //情報を取得して表示
	void GetPlayerHP(int *hp, int *maxhp);     //プレイヤーのhpを取得
	int GetBallNum();                          //弾の数を取得
	int GetEnemyNum();                         //敵の数を取得
	void GetEnemyPos(std::vector<VECTOR> *ep); //敵座標を取得
	void GetBallPos(std::vector<VECTOR> *bp);  //弾座標を取得
	void CheckAttackContact();                 //攻撃の接触判定
	void AutoRecovery();                       //自動回復処理
	void ScreenDark();                         //死亡時に画面を徐々に暗くする

public:
	typedef enum eGame{ //ゲームモード
		GAME,      //ゲーム画面
		MENU,      //メニュー画面
		KEYCONFIG, //キー設定画面
	}eGame;
	eGame game_mode;    //ゲームモード

	void Create();
	void FpsTimeFanction();                     //フレームレートを算出
	int GetBlockFlag(double x, double y);       //ブロックがあるかどうかの判定
	void GetMousePos(int *x, int *y);           //マウス座標を取得
	void GetPlayerPos(double *x, double *y);    //プレイヤー座標を取得
	void SetEnemyDamage(int index, int damage); //敵にダメージを設定
	void ShowDamage(VECTOR p, int d, int col);  //ダメージを表示
	bool GetGameOverFlag();                     //ゲームオーバーフラグを取得
	eGame GetGameMode();                        //ゲームモードを取得
	void SetGameMode(eGame eg);                 //ゲームモードを設定
    //プレイヤーの弾パラメータ設定
	void SetPlayerBall(double x, double y, int width, int height, int mouse_x, int mouse_y);
	void All();
	void Finalize();
	bool GameEndCheck();//ゲームの終了判定
	int CheckMove(      //移動できるかの判定
		double x,       //位置x
		double y,       //位置y
		double *move_x, //移動値x
		double *move_y, //移動値y
		int size,       //サイズ
		int offset,     //オフセット
		bool adjust     //移動値の調整
	);
	static CONTROL* GetInstance(void) {//シングルトン
		static CONTROL control;
		return &control;
	}
};
