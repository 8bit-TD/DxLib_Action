#include "pch.h"
#include "control.h"

CONTROL::CONTROL(){

}

void CONTROL::Create() {
	gameover_flag = false; //�Q�[���I�[�o�[�t���O
	death_count = 0;       //�v���C���[�����񂾌�̃J�E���g
	game_mode = GAME;//�Q�[�����[�h�ݒ�
	back = new BACK;
	//enemy_num = GetRand(190)+10;//�G�̐�
	enemy_num = 100;
	enemy = new ENEMY_MANAGER(enemy_num, GetBlankBlock());//�G�쐬(�G�̐�, �󂢂Ă���u���b�N�̔z��)
	std::string ch_file = "images/ch/ch_01.png";
	int px = (GAME_WIDTH / 2); int py = (GAME_HEIGHT - BLOCK_SIZE * 3);
	player = new PLAYER(
		ch_file,//�摜
		px,//x���W
		py,//y���W 
		32,//w�𑜓x
		32,//h�𑜓x
		16,//�L�����N�^�[���蔲���p�̃T�C�Y
		1, //�����Ă������
		2, //�X�s�[�h
		8, //�W�����v
		500,//maxhp
		500//maxmp
	);
	ball = new BALL_MANAGER;
	damage = new DAMAGE_MANAGER;
}

void CONTROL::GetEnemyPos(std::vector<VECTOR> *ep) {//�G���W�̓��I�z����擾
	enemy->GetEnemyPos(ep);
}

void CONTROL::GetBallPos(std::vector<VECTOR> *bp) {//�e�̈ʒu���擾
	ball->GetBallPos(bp);
}

void CONTROL::SetPlayerBall(double x, double y, int width, int height, int mouse_x, int mouse_y) {//�v���C���[�̒e�p�����[�^�ݒ�
	ball->SetBall(x, y, width, height, mouse_x, mouse_y);
}

int CONTROL::GetBlockFlag(double x, double y) {//�u���b�N�����邩�ǂ����̔���
	return back->GetBlockFlag(x, y);
}

int CONTROL::CheckMove(double x, double y, double *move_x, double *move_y, int size, int offset, bool adjust) {//�ړ��ł��邩����
	return back->GetBlockContact(x, y, move_x, move_y, size, offset, adjust);
}

void CONTROL::GetMousePos(int *x, int *y) {//�}�E�X���W���擾
	GetMousePoint(x, y);
}

void CONTROL::GetPlayerPos(double *x, double *y) {//�v���C���[���W���擾
	player->GetPlayerPos(x, y);
}

void CONTROL::SetEnemyDamage(int index, int damage) {//�G�Ƀ_���[�W��ݒ�
	enemy->SetDamage(index, damage);
}

bool CONTROL::GameEndCheck() {//�Q�[���̏I������
	if (key[KEY_INPUT_F4] == 1) {
		return true;//ESC�L�[����������Q�[���I��
	}
	return false;
}

std::vector<double> CONTROL::GetBlankBlock() { return back->GetBlankBlock(); }//�󂢂Ă���u���b�N��Ԃ�

void CONTROL::FpsTimeFanction() {// �t���[�����[�g���Z�o
	SetFontSize(13);
	if (FpsTime_i == 0)
		FpsTime[0] = GetNowCount();               //1���ڂ̎��Ԏ擾
	if (FpsTime_i == 49) {
		FpsTime[1] = GetNowCount();               //50���ڂ̎��Ԏ擾
		Fps = 1000.0f / ((FpsTime[1] - FpsTime[0]) / 50.0f);//���肵���l����fps���v�Z
		FpsTime_i = 0;//�J�E���g��������
	} else
		FpsTime_i++;//���݉����ڂ��J�E���g
	if (Fps != 0)
		DrawFormatString(GAME_WIDTH - 70, GAME_HEIGHT - 20, GetColor(255,255,255), "FPS %.1f", Fps); //fps��\��
	return;
}

void CONTROL::GetPlayerHP(int *Hp, int *Maxhp) {//�v���C���[��hp���擾
	player->GetPlayerHP(Hp, Maxhp);
}

int CONTROL::GetEnemyNum() {//�G�̐����擾
	return enemy->GetEnemyNum();
}

int CONTROL::GetBallNum() {//�e�̐����擾
	return ball->GetBallNum();
}

void CONTROL::ShowDamage(VECTOR p, int d, int col) {
	damage->SetDamage(p, d, col);
}

void CONTROL::CheckAttackContact() {//�U���̐ڐG����
	for (int e = 0; e < enemy_num; ++e) {//�G�̃v���C���[�̒e�̐ڐG����
		if (enemy->GetDeathFlag(e)) { continue; }
		for (int b = 0; b < GetBallNum(); ++b) {
			if ((enemy_p[e].x < ball_p[b].x) && (enemy_p[e].x + BLOCK_SIZE > ball_p[b].x) && (enemy_p[e].y < ball_p[b].y) && (enemy_p[e].y + BLOCK_SIZE > ball_p[b].y)) {
				int dam = GetRand(50)+1;
				VECTOR pos;
				pos.x = enemy_p[e].x + BLOCK_SIZE / 2;
				pos.y = enemy_p[e].y - 20;
				SetEnemyDamage(e, dam); //�G�Ƀ_���[�W��ݒ�
				ball->SetBallFlag(b, true); //�e�̃t���O��ݒ�
				player->SetUseMP(1);        //MP����
				ShowDamage(pos, dam, GetColor(255,255,255)); //�_���[�W��\��
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

void CONTROL::AutoRecovery() {//�����񕜏���
	if (g_count % 60 == 0) {
		player->AutoRecovery();//�v���C���[�̎�����
		enemy->AutoRecovery();//�G�̎�����
	}
}

bool CONTROL::GetGameOverFlag() {//�Q�[���I�[�o�[�t���O���擾
	return gameover_flag;
}

void CONTROL::ScreenDark() {//���S���ɉ�ʂ����X�ɈÂ�����
	if (player_hp == 0) {++death_count;	}
	if (death_count > 300) {gameover_flag = true;}
}

CONTROL::eGame CONTROL::GetGameMode() {//�Q�[�����[�h���擾
	return game_mode;
}

void CONTROL::SetGameMode(CONTROL::eGame eg) {//�Q�[�����[�h��ݒ�
	game_mode = eg;
}

void CONTROL::ShowInfo() {//����\��
	int mouse_x, mouse_y;      GetMousePos(&mouse_x, &mouse_y);
	double player_x, player_y; GetPlayerPos(&player_x, &player_y);
	int maxhp;             GetPlayerHP(&player_hp, &maxhp);
	
	SetFontSize(13);
	DrawFormatString(10, GAME_HEIGHT - 20, GetColor(255, 255, 255), "�}�E�X�ʒu: %d,%d", mouse_x, mouse_y);
	DrawFormatString(180, GAME_HEIGHT - 20, GetColor(255, 255, 255), "�v���C���[�ʒu: %d,%d", (int)player_x, (int)player_y);
	DrawFormatString(380, GAME_HEIGHT - 20, GetColor(255, 255, 255), "HP: %d/%d", player_hp, maxhp);
	DrawFormatString(480, GAME_HEIGHT - 20, GetColor(255, 255, 255), "�e: %d/%d", GetBallNum(), (int)PSHOT_NUM);
	DrawFormatString(580, GAME_HEIGHT - 20, GetColor(255, 255, 255), "�G: %d/%d", GetEnemyNum(), enemy_num);
	DrawFormatString(700, GAME_HEIGHT - 20, GetColor(255, 255, 255), "���[�h: %d", game_mode);
	DrawFormatString(1600, GAME_HEIGHT - 20, GetColor(255, 255, 255), "�t���[��: %d", g_count);
	SetDrawBlendMode(DX_BLENDMODE_MULA, death_count);
	DrawBox(0, 0, GAME_WIDTH, GAME_HEIGHT, GetColor(0, 0, 0), 1);//���S���̉�ʈÓ]
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

void CONTROL::All(){
	GetEnemyPos(&enemy_p); //�G���W�̓��I�z����擾
	GetBallPos(&ball_p);   //�e���W�̓��I�z����擾
	CheckAttackContact();  //�U���̐ڐG����
	back->All();           //�w�i����
	enemy->All();          //�G����
	ball->All();           //�e����
	player->All();         //�v���C���[����
	damage->All();         //�_���[�W�\������
	ShowInfo();            //����\��
	AutoRecovery();        //������
	ScreenDark();          //���S���ɉ�ʂ����X�ɈÂ�����
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
