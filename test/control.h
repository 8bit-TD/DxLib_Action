#include "player.h"
#include "enemy.h"
#include "back.h"
#include "damage.h"

class CONTROL {
private:
	BACK * back;                     //�w�i�N���X
	PLAYER *player;                  //�v���C���[�N���X
	ENEMY_MANAGER *enemy;            //�G�N���X
	BALL_MANAGER *ball;              //�e�N���X
	DAMAGE_MANAGER *damage;          //�_���[�W�N���X
	std::vector<double> blank_block; //�󂢂Ă���u���b�N���I�z��
	std::vector<VECTOR> enemy_p;     //�G�̈ʒu
	std::vector<VECTOR> ball_p;      //�e�̈ʒu
	int enemy_num;                   //�G�̐�
	double Fps = 0;                  //�t���[�����[�g�\���p
	int FpsTime[2] = { 0, };         //�t���[�����[�g�\���p
	int FpsTime_i = 0;               //�t���[�����[�g�\���p
	int player_hp;                   //�v���C���[��HP
	bool gameover_flag;              //�Q�[���I�[�o�[�t���O
	int death_count;                 //�v���C���[�����񂾌�̃J�E���g

	CONTROL();                                 //�R���X�g���N�^
	~CONTROL();                                //�f�X�g���N�^
	std::vector<double> GetBlankBlock();       //�󂢂Ă���u���b�N��Ԃ�
	void ShowInfo();                           //�����擾���ĕ\��
	void GetPlayerHP(int *hp, int *maxhp);     //�v���C���[��hp���擾
	int GetBallNum();                          //�e�̐����擾
	int GetEnemyNum();                         //�G�̐����擾
	void GetEnemyPos(std::vector<VECTOR> *ep); //�G���W���擾
	void GetBallPos(std::vector<VECTOR> *bp);  //�e���W���擾
	void CheckAttackContact();                 //�U���̐ڐG����
	void AutoRecovery();                       //�����񕜏���
	void ScreenDark();                         //���S���ɉ�ʂ����X�ɈÂ�����

public:
	typedef enum eGame{ //�Q�[�����[�h
		GAME,      //�Q�[�����
		MENU,      //���j���[���
		KEYCONFIG, //�L�[�ݒ���
	}eGame;
	eGame game_mode;    //�Q�[�����[�h

	void Create();
	void FpsTimeFanction();                     //�t���[�����[�g���Z�o
	int GetBlockFlag(double x, double y);       //�u���b�N�����邩�ǂ����̔���
	void GetMousePos(int *x, int *y);           //�}�E�X���W���擾
	void GetPlayerPos(double *x, double *y);    //�v���C���[���W���擾
	void SetEnemyDamage(int index, int damage); //�G�Ƀ_���[�W��ݒ�
	void ShowDamage(VECTOR p, int d, int col);  //�_���[�W��\��
	bool GetGameOverFlag();                     //�Q�[���I�[�o�[�t���O���擾
	eGame GetGameMode();                        //�Q�[�����[�h���擾
	void SetGameMode(eGame eg);                 //�Q�[�����[�h��ݒ�
    //�v���C���[�̒e�p�����[�^�ݒ�
	void SetPlayerBall(double x, double y, int width, int height, int mouse_x, int mouse_y);
	void All();
	void Finalize();
	bool GameEndCheck();//�Q�[���̏I������
	int CheckMove(      //�ړ��ł��邩�̔���
		double x,       //�ʒux
		double y,       //�ʒuy
		double *move_x, //�ړ��lx
		double *move_y, //�ړ��ly
		int size,       //�T�C�Y
		int offset,     //�I�t�Z�b�g
		bool adjust     //�ړ��l�̒���
	);
	static CONTROL* GetInstance(void) {//�V���O���g��
		static CONTROL control;
		return &control;
	}
};
