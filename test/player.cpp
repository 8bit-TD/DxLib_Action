#include "pch.h"
#include "player.h"
#include "effect_pdead.h"
#include "control.h"

PLAYER::PLAYER()
{
	//�摜�ǂݍ���
	
	if(-1==LoadDivGraph("charall.png",12,3,4,49,66,gh)){
		MSG("�G���[����");
	}

	width = 49;
	height = 66;

	//�ړ��W��
	move = 1.0f;

	//�������Əc�����̃J�E���g���B
	xcount=0, ycount=0;

	//�Y���p�ϐ�
	ix=0, iy=0, result=0;

	//�����ʒu
	x = 180;
	y = 400;
	
	//�����Ă��邩�ǂ���
	damageflag = false;
	endflag = false;
	dcount = 0;
	power = 10;
	life = PLAYER_LIFE;

	//�e������
	memset(shot, 0, sizeof(shot));

	//�e�摜�ǂݍ���
	int temp = LoadGraph("shot.png");
	int w, h;
	GetGraphSize(temp, &w, &h);

	//�t���O��S��false�ɂ��Ƃ�
	//�O���t�B�b�N�n���h���Ɖ摜�̃T�C�Y�������Ƃ�
	for (int i = 0; i<PSHOT_NUM; ++i) {
		shot[i].flag = false;
		shot[i].gh = temp;
		shot[i].width = w;
		shot[i].height = h;
	}

	//�G�t�F�N�g�N���X�̃C���X�^���X����
	effect_pdead = new EFFECT_PDEAD();

	count = 0;
}

void PLAYER::GetPosition(double *x, double *y) {
	*x = this->x;
	*y = this->y;
}

bool PLAYER::GetShotSound() {
	return s_shot;
}

void PLAYER::SetShotFlag(int index, bool flag) {
	shot[index].flag = flag;
}

bool PLAYER::GetShotPosition(int index, double *x, double *y) {
	if (shot[index].flag) {
		*x = shot[index].x;
		*y = shot[index].y;
		return true;
	}else {
		return false;
	}
}

void PLAYER::SetDamageFlag() {
	damageflag = true;
	//���C�t�����炷
	--life;
	if (life < 0) { life = 0; }
	effect_pdead->SetFlag(x, y);
}

bool PLAYER::GetDamageFlag() {
	return damageflag;
}

int PLAYER::GetLife() {
	return life;
}

void PLAYER::SetPower(int p) {
	power += p;
	if (power > 10) {
		power = 10;
	}
}

int PLAYER::GetPower() {
	return power;
}

void PLAYER::Ball() {
	if (power == 10) {
		ball.All(x, y);
	}
}

int PLAYER::NearEnemySerch() {
	CONTROL &control = CONTROL::GetInstance();
	int nearindex = -1;
	double nearresult = 0;
	double ex, ey, tx, ty;
	for (int i = 0; i < ENEMY_NUM; ++i) {
		if (!control.GetEnemyPosition(i, &ex, &ey))
			continue;
		tx = ex - x;
		ty = ey - y;
		if (nearindex == -1) {
			nearindex = i;
			nearresult = tx * tx + ty * ty;
			continue;
		}
		//��r���ď�������΂�����ŏ��Ƃ���
		if (nearresult > tx*tx + ty * ty) {
			nearindex = i;
			nearresult = tx * tx + ty * ty;
		}
	}
	return nearindex;
}

void PLAYER::BallShotSet(int index) {
	double ty;
	double trad, ex, ey;
	static int toggle = 1;
	int tindex;
	CONTROL &control = CONTROL::GetInstance();
	ty = ball.GetPosition();
	tindex = NearEnemySerch();
	//�߂�l��-1�Ȃ�G�͂������Ȃ��̂ŁA�܂������O�ɔ���
	if (tindex == -1) {
		trad = -PI / 2;
	}else {
		//��ԋ߂��G�ƒe�Ƃ̊p�x���擾
		control.GetEnemyPosition(tindex, &ex, &ey);
		trad = atan2(ey - ty + BALL_INITY, ex - x + (toggle*BALL_INITX));
	}
	shot[index].flag = true;
	shot[index].x = x + BALL_INITX * toggle;
	shot[index].y = ty + BALL_INITY;
	shot[index].rad = trad;
	shot[index].type = 1;

	if (toggle == 1) {
		toggle = -1;
	}else {
		toggle = 1;
	}
}

void PLAYER::Shot()
{

	s_shot = false;
	int num = 0;

	if (!damageflag) {
		//�L�[��������ĂĂ��A6���[�v�Ɉ�񔭎�
		if (key[KEY_INPUT_Z] == 1 && count % 6 == 0) {
			for (int i = 0; i<PSHOT_NUM; ++i) {
				if (shot[i].flag == false) {
					if (power < 3) {
						shot[i].flag = true;
						shot[i].x = x;
						shot[i].y = y;
						shot[i].rad = -PI / 2;
						shot[i].type = 0;
						break;
					}else if (power >= 3 && power < 10) {
						if (num == 0) {
							shot[i].flag = true;
							shot[i].x = x;
							shot[i].y = y;
							shot[i].rad = -1.57;
							shot[i].type = 0;
						}else if (num == 1) {
							shot[i].flag = true;
							shot[i].x = x;
							shot[i].y = y;
							shot[i].rad = -1.69;
							shot[i].type = 0;
						}else if (num == 2) {
							shot[i].flag = true;
							shot[i].x = x;
							shot[i].y = y;
							shot[i].rad = -1.45;
							shot[i].type = 0;
						}
						++num;
						if (num == 3) {
							break;
						}
					}else if (power == 10) {
						//0�̎����O������
						if (num == 0) {
							shot[i].flag = true;
							shot[i].x = x;
							shot[i].y = y;
							shot[i].rad = -1.57;
							shot[i].type = 0;
						}else if (num == 1) {
							shot[i].flag = true;
							shot[i].x = x;
							shot[i].y = y;
							shot[i].rad = -1.69;
							shot[i].type = 0;
						}else if (num == 2) {
							shot[i].flag = true;
							shot[i].x = x;
							shot[i].y = y;
							shot[i].rad = -1.45;
							shot[i].type = 0;
						}else if (num > 2) {
							BallShotSet(i);
						}
						++num;
						if (num == 5) {
							break;
						}
					}
				}
			}
			//�V���b�g�T�E���h�t���O�𗧂Ă�
			s_shot = true;
		}
	}

	//��ԋ߂��G�Ƃ̊p�x
	double trad;
	//��ԋ߂��G�̓Y����
	int index;
	double ex, ey;
	//control�N���X�̎Q�ƕϐ�
	CONTROL &control = CONTROL::GetInstance();

	//��ԋ߂��G�̓Y�����擾
	index = NearEnemySerch();

	
	//�e���ړ������鏈��
	for (int i = 0; i<PSHOT_NUM; ++i) {
		//���˂��Ă�e����
		if (shot[i].flag) {
			if (shot[i].type == 0) {
				shot[i].x += cos(shot[i].rad)*PSHOT_SPEED;
				shot[i].y += sin(shot[i].rad)*PSHOT_SPEED;
			}else if (shot[i].type == 1) {
				//�߂�l��-1�Ȃ�G�͂������Ȃ��̂ŁA�܂������O�ɔ���
				if (index == -1) {
					trad = -PI / 2;
				}else {
					//��ԋ߂��G�Ƃ̊p�x���擾
					control.GetEnemyPosition(index, &ex, &ey);
					trad = atan2(ey - shot[i].y, ex - shot[i].x);
				}

				//�{�X������ꍇ�̓{�X�Ƃ̊p�x���擾
				if (control.GetBossFlag()) {
					control.GetBossPosition(&ex, &ey);
					trad = atan2(ey - shot[i].y, ex - shot[i].x);
				}

				shot[i].rad = trad;
				shot[i].x += cos(trad)*PSHOT_SPEED;
				shot[i].y += sin(trad)*PSHOT_SPEED;
			}
			
			//��ʂ̊O�ɂ͂ݏo������t���O��߂�
			if (shot[i].y<-10 || shot[i].x < -10 || shot[i].x > 410 || shot[i].y>510) {
				shot[i].flag = false;
			}
		}
	}
}

void PLAYER::Move(){
	
	if(key[KEY_INPUT_LEFT]==1 || key[KEY_INPUT_RIGHT]==1){
		if(key[KEY_INPUT_UP]==1 || key[KEY_INPUT_DOWN]==1){
			//�ړ��W�����O�D�V�P�ɐݒ�
			move=0.71f;
		}else{
			//�΂߂���Ȃ���΂P�D�O�ɐݒ�
			move=1.0f;
		}
	}else if(key[KEY_INPUT_UP]==1 || key[KEY_INPUT_DOWN]==1){
		move=1.0f;
	}

	if (key[KEY_INPUT_LEFT] == 1) {
		x -= (int)PLAYER_SPEED * move;
	}
	if (key[KEY_INPUT_RIGHT] == 1) {
		x += (int)PLAYER_SPEED * move;
	}
	if (key[KEY_INPUT_UP] == 1) {
		y -= (int)PLAYER_SPEED * move;
	}
	if (key[KEY_INPUT_DOWN] == 1) {
		y += (int)PLAYER_SPEED * move;
	}

	//�L�����̈ړ�����
	if (x > 400 - width/2) {
		x = 400 - width/2;
	}
	else if (x < 0 + width / 2) {
		x = 0 + width / 2;
	}

	if (y > 480 - height/2) {
		y = 480 - height/2;
	}
	else if (y < 0 + height / 2) {
		y = 0 + height / 2;
	}

	//���L�[��������ĂāA����xcount���O�ȏ�Ȃ�O�ɂ��Ă���P�����B
	//����ȊO�͂P����
	if (key[KEY_INPUT_LEFT] == 1) {
		if (xcount > 0)
			xcount = 0;
		--xcount;
	}
	//�E�L�[��������ĂāA����xcount���O�ȉ��Ȃ�O�ɂ��Ă���P�����B
	//����ȊO�͂P����
	if (key[KEY_INPUT_RIGHT] == 1) {
		if (xcount < 0)
			xcount = 0;
		++xcount;
	}
	//��L�[��������ĂāA����ycount���O�ȏ�Ȃ�O�ɂ��Ă���P�����B
	//����ȊO�͂P����
	if (key[KEY_INPUT_UP] == 1) {
		if (ycount > 0)
			ycount = 0;
		--ycount;
	}
	//���L�[��������ĂāA����ycount���O�ȉ��Ȃ�O�ɂ��Ă���P�����B
	//����ȊO�͂P����
	if (key[KEY_INPUT_DOWN] == 1) {
		if (ycount < 0)
			ycount = 0;
		++ycount;
	}

	//�J�E���g������Y�������߂�B
	ix = abs(xcount) % 30 / 10;
	iy = abs(ycount) % 30 / 10;

	//x�J�E���g���v���X�Ȃ�E�����Ȃ̂�2�s�ڂ̐擪�Y���ԍ��𑫂��B
	if (xcount > 0) {
		ix += 3;
		result = ix;
	}
	else if (xcount < 0) {
		//�}�C�i�X�Ȃ獶�����Ȃ̂ŁA4�s�ڂ̐擪�Y���ԍ��𑫂��B
		ix += 9;
		result = ix;
	}

	//y�J�E���g���v���X�Ȃ牺�����Ȃ̂ŁA3�s�ڂ̐擪�Y���ԍ��𑫂��B
	if (ycount > 0) {
		iy += 6;
		result = iy;
	}
	else if (ycount < 0) {
		//�P�s�ڂ̐擪�Y���ԍ��͂O�Ȃ̂ŉ�������K�v�Ȃ��B(������₷�����邽�߂ɏ����Ƃ��܂���)
		iy += 0;
		result = iy;
	}

	//�΂߈ړ��̏ꍇ�͉����D��
	if (move == 0.71f)
	result = ix;

	//������ĂȂ���΃J�E���g���[���ɂ���B
	if (key[KEY_INPUT_LEFT] != 1 && key[KEY_INPUT_RIGHT] != 1) {
		xcount = 0;
	}
	if (key[KEY_INPUT_UP] != 1 && key[KEY_INPUT_DOWN] != 1) {
		ycount = 0;
	}

}

void PLAYER::Draw()
{
	//�e�`��
	for (int i = 0; i<PSHOT_NUM; ++i) {
		if (shot[i].flag) {
			DrawRotaGraph(shot[i].x , shot[i].y , 1.0, shot[i].rad+(90*PI/180), shot[i].gh, TRUE);
		}
	}
	//�����Ă�Ε`��
	if (damageflag) {
		if (dcount > 20) {
			if (dcount % 2 == 0) {
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 140);
				DrawGraph(PLAYER_INITX - width / 2, PLAYER_INITY - height / 2 + 60 - (dcount - 20), gh[1], TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}else {
				DrawGraph(PLAYER_INITX - width / 2, PLAYER_INITY - height / 2 + 60 - (dcount - 20), gh[1], TRUE);
			}
		}
		++dcount;
		if (dcount == 80) {
			damageflag = false;
			dcount = 0;
			//���W�������l�ɖ߂�
			x = PLAYER_INITX;
			y = PLAYER_INITY;
			//������̉摜�ɂ���
			result = 1;
		}
	}else {
		//�ʏ�`��
		DrawGraph(x - width / 2, y - height / 2, gh[result], TRUE);
		//DrawCircle(x, y,20,255,1);
	}
}

void PLAYER::All()
{
	if (!damageflag) {
		Move();
	}
	Shot();
	effect_pdead->All();
	Ball();
	Draw();
	
	++count;
}

