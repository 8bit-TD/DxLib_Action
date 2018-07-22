#include "player.h"
#include "back.h"
#include "enemy.h"
#include "EFFECT_EDEAD.h"
#include "graze.h"
#include "score.h"
#include "item.h"
#include "boss.h"

class CONTROL {

	//�v���C���[�N���X
	PLAYER *player;

	//�w�i�N���X
	BACK *back;

	//�G�N���X
	ENEMY *enemy[ENEMY_NUM];

	BOSS *boss;

	//�G���ŃG�t�F�N�g�N���X
	EFFECT_EDEAD *effect_edead[EFFECT_EDEADNUM];

	//�O���C�Y�N���X
	GRAZE *graze[GRAZE_NUM];

	//�X�R�A�N���X
	SCORE *score;

	//�A�C�e���N���X
	ITEM *item[ITEM_NUM];

	//�T�E���h�n���h��
	int s_eshot;
	int s_pshot;
	int s_edead;
	int s_graze;
	int s_item;

	//�T�E���h��炷���ǂ����̃t���O
	bool eshot_flag;
	bool pshot_flag;
	bool graze_flag;
	bool item_flag;

	//�G���ŉ��t���O�Z�b�g
	bool edead_flag;
	//�v���C���[���ŉ��t���O���Z�b�g
	bool pdead_flag;

private:
	CONTROL();
	~CONTROL();
	void SoundAll();
	void CollisionAll();
	void BossCollisionAll();
	bool CircleCollision(double c1, double c2, double cx1, double cx2, double cy1, double cy2);
	void EnemyDeadEffect(double x, double y);
public:
	void All();
	void GetPlayerPosition(double *x, double *y);
	bool GetEnemyPosition(int index, double *x, double *y);
	
	static CONTROL& GetInstance() {
		static CONTROL control;
		return control;
	}
};
