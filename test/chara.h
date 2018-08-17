#pragma once
//���ׂẴL�����N�^�[�̊��N���X
class CHARA {
private:
	
public:
	int gh;                //�O���t�B�b�N�n���h���i�[�p�z��
	VECTOR pos;            //�ʒu
	int width, height;     //�摜��
	int ch_size;           //�L�����N�^�[���蔲���p�̃T�C�Y
	int aim;               //�����Ă������
	double speed;          //�X�s�[�h
	double jump;           //�W�����v��
	int maxhp;             //MaxHP
	double hp;             //HP
	int maxmp;             //MaxMp
	double mp;             //MP
	bool death_flag;       //���S�t���O
	double move_x, move_y; //�ړ�����W
	double fall_sp;        //�������x
	bool side_contact;     //���E�̃u���b�N�ɐڐG�����t���O
	int mouse_x;           //�}�E�X�̍��Wx
	int mouse_y;           //�}�E�X�̍��Wy
	int hp_gauge;          //hp�Q�[�W�p
	int mp_gauge;          //mp�Q�[�W�p
	bool damage_flag;      //�_���[�W���󂯂����̃t���O

	void CheckMove();                  //�ړ��ł��邩����
	void CheckAim();                   //�}�E�X���W���`�F�b�N
	bool GetDeathFlag();               //���S�t���O���擾
	void GetPos(double *x, double *y); //�ʒu���擾
	double GetMaxHP();                 //MAXHP���擾
	double GetMaxMP();                 //MAXMP���擾
	int GetMP();                       //MP���擾
	void SetDamage(int damage);        //�_���[�W��ݒ�
	void SetRecoveryHP(int val);       //HP����
	void SetRecoveryMP(int val);       //MP����
	void SetUseMP(int val);            //MP���g�p
	void AutoRecovery();               //������
	bool CheckContact(VECTOR pos, double size); //�ڐG����
	virtual void Move();
	virtual void Draw();
	virtual void All();
	CHARA(
		std::string file, //�摜
		int x,            //x���W
		int y,            //y���W 
		int w,            //w�𑜓x
		int h,            //h�𑜓x
		int s,            //�L�����N�^�[���蔲���p�̃T�C�Y
		int a,            //�����Ă������ 
		double sp,        //�X�s�[�h
		double jp,        //�W�����v
		int mhp,          //maxhp
		int mmp           //maxmp
	);
	virtual ~CHARA();
};
