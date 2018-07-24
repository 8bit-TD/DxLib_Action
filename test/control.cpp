#include "pch.h"
#include "control.h"

CONTROL::CONTROL()
{
	player = new PLAYER;

	back = new BACK;

	//�G�t�F�N�g�N���X�̃C���X�^���X����
	for (int i = 0; i < EFFECT_EDEADNUM; ++i) {
		effect_edead[i] = new EFFECT_EDEAD;
	}

	//�O���C�Y�̃C���X�^���X����
	for (int i = 0; i < GRAZE_NUM; ++i) {
		graze[i] = new GRAZE;
	}

	score = new SCORE;
	//�A�C�e���N���X�̃C���X�^���X����
	for (int i = 0; i < ITEM_NUM; ++i) {
		item[i] = new ITEM;
	}
	

	FILE *fp;
	ENEMYDATA data[ENEMY_NUM];
	char buf[100];
	int c;
	int col = 1;
	int row = 0;

	memset(buf, 0, sizeof(buf));
	fp = fopen("enemydata.csv", "r");

	//�w�b�_�ǂݔ�΂�
	while (fgetc(fp) != '\n');

	while (1) {

		while (1) {

			c = fgetc(fp);

			//�����Ȃ烋�[�v�𔲂���B
			if (c == EOF)
				goto out;

			//�J���}�����s�łȂ���΁A�����Ƃ��ĂȂ���
			if (c != ',' && c != '\n')
				strcat(buf, (const char*)&c);
			//�J���}�����s�Ȃ烋�[�v������B
			else
				break;
		}
		//�����ɗ����Ƃ������Ƃ́A1�Z�����̕����񂪏o���オ�����Ƃ�������
		switch (col) {
			//1��ڂ͓G��ނ�\���Batoi�֐��Ő��l�Ƃ��đ���B
		case 1:	data[row].type = atoi(buf); break;
			//2��ڂ͒e��ށB�ȍ~�ȗ��B
		case 2: data[row].stype = atoi(buf); break;
		case 3: data[row].m_pattern = atoi(buf); break;
		case 4: data[row].s_pattern = atoi(buf); break;
		case 5: data[row].in_time = atoi(buf); break;
		case 6: data[row].stop_time = atoi(buf); break;
		case 7: data[row].shot_time = atoi(buf); break;
		case 8: data[row].out_time = atoi(buf); break;
		case 9: data[row].x = atoi(buf); break;
		case 10: data[row].y = atoi(buf); break;
		case 11: data[row].speed = atoi(buf); break;
		case 12: data[row].hp = atoi(buf); break;
		case 13: data[row].item = atoi(buf); break;
		}
		//�o�b�t�@��������
		memset(buf, 0, sizeof(buf));
		//�񐔂𑫂�
		++col;

		//�����ǂݍ��񂾕��������s��������񐔂����������čs���𑝂₷
		if (c == '\n') {
			col = 1;
			++row;
		}
	}
out:

	//�G�N���X����
	for (int i = 0; i<ENEMY_NUM; ++i) {
		/*
		enemy[i] = new ENEMY(data[i].type, data[i].stype, data[i].m_pattern, data[i].s_pattern, data[i].in_time, data[i].stop_time, data[i].shot_time,
			data[i].out_time, data[i].x, data[i].y, data[i].speed, data[i].hp, data[i].item);
		*/
	}

	boss = new BOSS();
	
	//�T�E���h�t�@�C���ǂݍ���
	s_eshot = LoadSoundMem("enemyshot.mp3");
	s_pshot = LoadSoundMem("playershot.mp3");
	s_edead = LoadSoundMem("enemydead.mp3");
	s_graze = LoadSoundMem("graze.mp3");
	s_item = LoadSoundMem("item.mp3");

	eshot_flag = false;
	pshot_flag = false;
	edead_flag = false;
	pdead_flag = false;
	graze_flag = false;
	item_flag = false;

}

void CONTROL::EnemyDeadEffect(double x, double y) {
	//�G�t�F�N�g�Z�b�g
	for (int z = 0; EFFECT_EDEADNUM; ++z) {
		if (!effect_edead[z]->GetFlag()) {
			effect_edead[z]->SetFlag(x, y);
			break;
		}
	}
}

void CONTROL::GetPlayerPosition(double *x, double *y) {
	double tempx, tempy;
	player->GetPosition(&tempx, &tempy);
	*x = tempx;
	*y = tempy;
}

bool CONTROL::GetBossFlag() {
	return boss->GetFlag();
}

void CONTROL::GetBossPosition(double *x, double *y) {
	double tempx, tempy;
	boss->GetPosition(&tempx, &tempy);
	*x = tempx;
	*y = tempy;
}

bool CONTROL::GetEnemyPosition(int index, double *x, double *y) {
	double tempx, tempy;
	if (enemy[index] == NULL || enemy[index]->GetDeadFlag())
		return false;

	//�w�肵���Y���̓G�̍��W���擾
	enemy[index]->GetPosition(&tempx, &tempy);
	//���
	*x = tempx;
	*y = tempy;
	return true;
}

bool CONTROL::CircleCollision(double c1, double c2, double cx1, double cx2, double cy1, double cy2) {
	double hlength = c1 + c2;
	double xlength = cx1 - cx2;
	double ylength = cy1 - cy2;
	if (hlength * hlength >= xlength * xlength + ylength * ylength) {
		return true;
	}else {
		return false;
	}
}

void CONTROL::CollisionAll() {
	double px, py, ex, ey;

	bool tempflag =  false;
	bool gtempflag = false;

	//����L�����̒e�ƓG�̓����蔻��
	for (int i = 0; i < PSHOT_NUM; ++i) {
		if (player->GetShotPosition(i, &px, &py)) {
			for (int s = 0; s < ENEMY_NUM; ++s) {
				//�G�N���X�̃|�C���^��NULL����Ȃ��A����deadflag��false(����łȂ����A�҂��ĂȂ�)
				if (enemy[s] != NULL && !enemy[s]->GetDeadFlag()) {
					enemy[s]->GetPosition(&ex, &ey);
					//�����蔻��
					if (CircleCollision(PSHOT_COLLISION, ENEMY1_COLLISION, px, ex, py, ey)) {
						//�������Ă���΁Adeadflag�𗧂Ă�
						enemy[s]->SetDeadFlag();
						//���������e�̃t���O��߂�
						player->SetShotFlag(i, false);
						//�G���ŉ��t���O�Z�b�g
						edead_flag = true;
						//�G���ŃG�t�F�N�g�Z�b�g
						EnemyDeadEffect(ex, ey);
						//���_��������
						score->SetScore(CURRENT_SCORE, 100);
						//�A�C�e���o��
						for (int z = 0; z < ITEM_NUM; ++z) {
							if (!item[z]->GetFlag()) {
								item[z]->SetFlag(ex, ey, enemy[s]->GetItem());
								break;
							}
						}
					}
				}
			}
		}
	}

	//�G�̒e�Ƒ���L�����Ƃ̓����蔻��
	//�v���C���[�������Ă����
	if (!player->GetDamageFlag()) {
		player->GetPosition(&px, &py);
		for (int i = 0; i < ENEMY_NUM; ++i) {
			if (enemy[i] != NULL) {
				for (int s = 0; s < ENEMY_SNUM; ++s) {
					//�e�t���O�������Ă����true��Ԃ�
					if (enemy[i]->GetShotPosition(s, &ex, &ey)) {
						//�e�ɂ���ē����蔻�肪�Ⴄ�̂�wsitch���ŕ���
						switch (enemy[i]->GetShotType()) {
							case 0:
								//�O���C�Y����
								if (CircleCollision(GRAZE_COLLISION, ESHOT0_COLLISION, px, ex, py, ey)) {
									gtempflag = true;
								}
								//�������Ă��
								if (CircleCollision(PLAYER_COLLISION, ESHOT0_COLLISION, px, ex, py, ey)) {
									tempflag = true;
								}
								break;
							case 1:
								if (CircleCollision(GRAZE_COLLISION, ESHOT1_COLLISION, px, ex, py, ey)) {
									gtempflag = true;
								}
								if (CircleCollision(PLAYER_COLLISION, ESHOT1_COLLISION, px, ex, py, ey)) {
									tempflag = true;
								}
								break;
							case 2:
								if (CircleCollision(GRAZE_COLLISION, ESHOT2_COLLISION, px, ex, py, ey)) {
									gtempflag = true;
								}
								if (CircleCollision(PLAYER_COLLISION, ESHOT2_COLLISION, px, ex, py, ey)) {
									tempflag = true;
								}
								break;
						}
						//�O���C�Y�����蔻�肪true�Ȃ�
						if (gtempflag) {
							//�܂�
							if (!enemy[i]->GetGrazeFlag(s)) {
								enemy[i]->SetGrazeFlag(s);
								//�O���C�Y�̃C���X�^���X����
								for (int z = 0; z < GRAZE_NUM; ++z) {
									if (!graze[z]->GetFlag()) {
										graze[z]->SetFlag(px, py);
										break;
									}
								}
								//�O���C�Y�̓��_��������
								score->SetScore(GRAZE_SCORE, 1);
								score->SetScore(CURRENT_SCORE, 20);
								//�O���C�Y���Z�b�g
								graze_flag = true;
							}
							gtempflag = false;
						}
						if (tempflag) {
							//����L������damageflag�𗧂Ă�
							player->SetDamageFlag();
							//�e������
							enemy[i]->SetShotFlag(s, false);
							//�v���C���[���ŉ��t���O�𗧂Ă�
							pdead_flag = true;
							//�ꎞ�t���O��߂�
							tempflag = false;
						}
					}
				}
			}
		}
		
		double ix, iy;
		//�A�C�e���ƃv���C���[�̓����蔻��
		for (int i = 0; i < ITEM_NUM; ++i) {
			if (item[i]->GetFlag()) {
				item[i]->GetPosition(&ix, &iy);
				if (CircleCollision(PLAYER_COLLISION, ITEM_COLLISION, px, ix, py, iy)) {
					switch (item[i]->GetType()) {
						case 0:
							score->SetScore(CURRENT_SCORE, 300);
							break;
						case 1:
							player->SetPower(1);
							score->SetScore(POWER_SCORE, player->GetPower());
							//�p���[�𑝂₷
							break;
					}
					item[i]->Delete();
					//�A�C�e���擾�����Z�b�g
					item_flag = true;
				}
			}
		}

	}
	//���C�t�͖���擾
	score->SetScore(LIFE_SCORE, player->GetLife());
}

void CONTROL::BossCollisionAll() {
	double px, py, bx, by, ix, iy;
	int bhp;
	//�o���A�C�e����
	int itemnum = 0;
	//�O���C�Y�ƃq�b�g�������̃t���O
	bool hflag = false, gflag = false;
	//�{�X�̒e�̎��
	int type;

	//�܂����G�t���O�������ĂȂ������`�F�b�N
	if (!boss->GetNodamageFlag()) {
		//�v���C���[�̃V���b�g�ƃ{�X�̓����蔻��
		for (int i = 0; i < PSHOT_NUM; ++i) {
			if (player->GetShotPosition(i, &px, &py)) {
				boss->GetPosition(&bx, &by);
				//�����蔻��
				if (CircleCollision(PSHOT_COLLISION, BOSS_COLLISION, px, bx, py, by)) {
					//�������Ă����hp�����炷
					bhp = boss->HpSet(1);
					//���������e�̃t���O��߂�
					player->SetShotFlag(i, false);
					//�{�X�̃_���[�W
					boss->SetDamageFlag();
					//���_��������
					score->SetScore(CURRENT_SCORE, 10);

					char buf[100];
					sprintf(buf, "%d", bhp);
					SetMainWindowText(buf);

					//�{�X�̑O��HP��2/3�ȏ�ŁA��HP��2/3�ȉ��Ȃ�
					if (BOSS_HP * 2 / 3 >= bhp && boss->GetPrevHp() > BOSS_HP * 2 / 3) {
						//�_���[�W�G�t�F�N�g���o��
						EnemyDeadEffect(bx, by);
						//�_���[�W����炷
						edead_flag = true;
						//����ɓ��_��������
						score->SetScore(CURRENT_SCORE, 1000);
						//�A�C�e�����o��
						for (int z = 0; z < ITEM_NUM; ++z) {
							if (!item[z]->GetFlag()) {
								//�A�C�e���̏������W���΂炯������
								ix = (rand() % 100 - 51) + bx;
								iy = (rand() % 100 - 51) + by;
								item[z]->SetFlag(ix, iy, rand() % 2);
								++itemnum;
								//5�o�����烋�[�v�𔲂���
								if (itemnum == 5) {
									break;
								}
							}
							boss->SetDamageSetting();
						}
						
					} else if (BOSS_HP / 3 >= bhp && boss->GetPrevHp() > BOSS_HP / 3) {
						//�_���[�W�G�t�F�N�g���o��
						EnemyDeadEffect(bx, by);
						//�_���[�W����炷
						edead_flag = true;
						//����ɓ��_��������
						score->SetScore(CURRENT_SCORE, 1000);
						//�A�C�e�����o���B
						for (int z = 0; z < ITEM_NUM; ++z) {
							if (!item[z]->GetFlag()) {
								//�A�C�e���̏������W���΂炯������
								ix = (rand() % 100 - 51) + bx;
								iy = (rand() % 100 - 51) + by;
								item[z]->SetFlag(ix, iy, rand() % 2);
								++itemnum;
								//5�o�����烋�[�v�𔲂���
								if (itemnum == 5) {
									break;
								}
							}
						}
						boss->SetDamageSetting();
					} else if (bhp <= 0) {
						//�t���O��߂�
						boss->SetFlag(false);
						//���ŃG�t�F�N�g���o��
						EnemyDeadEffect(bx, by);
						//���ŉ���炷
						edead_flag = true;
						//����ɓ��_��������
						score->SetScore(CURRENT_SCORE, 10000);
						//�A�C�e�����o��
						for (int z = 0; z < ITEM_NUM; ++z) {
							if (!item[z]->GetFlag()) {
								ix = (rand() % 100 - 51) + bx;
								iy = (rand() % 100 - 51) + by;
								item[z]->SetFlag(ix, iy, rand() % 2);
								++itemnum;
								//10�o�����烋�[�v�𔲂���
								if (itemnum == 10) {
									break;
								}
							}
						}
					}

					//�����{�X��HP��0�ȉ��Ȃ�
					if (bhp <= 0) {
						//�t���O��߂�
						boss->SetFlag(false);
						//���ŃG�t�F�N�g���o��
						EnemyDeadEffect(bx, by);
						//���ŉ���炷
						edead_flag = true;
						//����ɓ��_��������
						score->SetScore(CURRENT_SCORE, 10000);
						//�A�C�e�����o��
						for (int z = 0; z < ITEM_NUM; ++z) {
							if (!item[z]->GetFlag()) {
								//�A�C�e���̏������W���΂炯������
								ix = (rand() % 100 - 51) + bx;
								iy = (rand() % 100 - 51) + by;
								item[z]->SetFlag(ix, iy, rand() % 2);
								++itemnum;
								//10�o���烋�[�v�𔲂���
								if (itemnum == 10) {
									break;
								}
							}
						}
					}
				}
			}
		}
	}

	//�{�X�̃V���b�g�ƃv���C���[�̓����蔻��
	if (!player->GetDamageFlag()) {
		player->GetPosition(&px, &py);
		for (int i = 0; i < BOSS_SHOTNUM; ++i) {
			if (boss->GetShotPosition(i, &bx, &by, &type)) {
				switch (type) {
					case 0:
						if (CircleCollision(GRAZE_COLLISION, ESHOT0_COLLISION, px, bx, py, by)) {
							gflag = true;
						}
						if (CircleCollision(PLAYER_COLLISION, ESHOT0_COLLISION, px, bx, py, by)) {
							hflag = true;
						}
						break;
					case 1:
						if (CircleCollision(GRAZE_COLLISION, ESHOT1_COLLISION, px, bx, py, by)) {
							gflag = true;
						}
						if (CircleCollision(PLAYER_COLLISION, ESHOT1_COLLISION, px, bx, py, by)) {
							hflag = true;
						}
						break;
					case 2:
						if (CircleCollision(GRAZE_COLLISION, ESHOT2_COLLISION, px, bx, py, by)) {
							gflag = true;
						}
						if (CircleCollision(PLAYER_COLLISION, ESHOT2_COLLISION, px, bx, py, by)) {
							hflag = true;
						}
						break;
				}
				//�O���C�Y�t���O�������Ă���
				if (gflag) {
					//�Y���̒e�����łɃO���C�Y���Ă��邩�`�F�b�N
					if (!boss->GetGrazeFlag(i)) {
						boss->SetGrazeFlag(i);
						//�܂��g���ĂȂ��O���C�Y�G�t�F�N�g��T��
						for (int z = 0; z < GRAZE_NUM; ++z) {
							if (!graze[z]->GetFlag()) {
								graze[z]->SetFlag(px, py);
								break;
							}
						}
						//�O���C�Y�̓��_��������
						score->SetScore(GRAZE_SCORE, 1);
						score->SetScore(CURRENT_SCORE, 20);
						//�O���C�Y���Z�b�g
						graze_flag = true;
					}
					//���̒e�̃O���C�Y���`�F�b�N���邽�߂̃t���O��߂��B
					gflag = false;
				}
				if (hflag) {
					//����L������damageflag�𗧂Ă�
					player->SetDamageFlag();
					//�e������
					boss->SetShotFlag(i, false);
					//�v���C���[���ŉ��t���O�𗧂Ă�
					pdead_flag = true;
					//�ꎞ�t���O��߂�
					hflag = false;
					//�P�ł�����������v���C���[�͏��ł���̂ŁA
					//���̒e���`�F�b�N����K�v�Ȃ��̂Ń��[�v�𔲂���B
					break;
				}
			}
		}
	}
	//�A�C�e���ƃv���C���[�̓����蔻��
	for (int i = 0; i < ITEM_NUM; ++i) {
		if (item[i]->GetFlag()) {
			item[i]->GetPosition(&ix, &iy);
			if (CircleCollision(PLAYER_COLLISION, ITEM_COLLISION, px, ix, py, iy)) {
				switch (item[i]->GetType()) {
					case 0:
						score->SetScore(CURRENT_SCORE, 300);
						break;
					case 1:
						player->SetPower(1);
						score->SetScore(POWER_SCORE, player->GetPower());
						//�p���[�𑝂₷
						break;
				}
				item[i]->Delete();
				//�A�C�e���擾�����Z�b�g
				item_flag = true;
			}
		}
	}
	//���C�t�͖���擾
	score->SetScore(LIFE_SCORE, player->GetLife());
}

void CONTROL::All()
{
	//�T�E���h�t���O��������
	eshot_flag = pshot_flag = edead_flag = pdead_flag = graze_flag = item_flag = false;
		
	//�`��̈���w��
	SetDrawArea(MARGIN, MARGIN, MARGIN + 380, MARGIN + 460);
	
	back->All();

	//�v���C���[�N���X��All�֐����s
	player->All();
	
	//�v���C���[�V���b�g�T�E���h�t���O���`�F�b�N
	if (player->GetShotSound()) {
		pshot_flag = true;
	}

	for (int i = 0; i < ENEMY_NUM; ++i) {
		if (enemy[i] != NULL) {
			//�G�V���b�g�T�E���h�t���O�`�F�b�N
			if (enemy[i]->GetShotSound()) {
				eshot_flag = true;
			}
			if (enemy[i]->All()) {
				delete enemy[i];
				enemy[i] = NULL;
			}
		}
	}


	boss->All();
	//�G�V���b�g�T�E���h�t���O�`�F�b�N
	if (boss->GetShotSound()) {
		eshot_flag = true;
	}

	//�����蔻��
	CollisionAll();
	BossCollisionAll();

	//�O���C�Y�`��
	for (int i = 0; i < GRAZE_NUM; ++i) {
		graze[i]->All();
	}

	//�G���ŃG�t�F�N�g
	for (int i = 0; i < EFFECT_EDEADNUM; ++i) {
		if (effect_edead[i]->GetFlag()) {
			effect_edead[i]->All();
		}
	}

	//�A�C�e��
	for (int i = 0; i < ITEM_NUM; ++i) {
		if (item[i]->GetFlag()) {
			item[i]->All();
		}
	}

	//�`��̈���w��
	SetDrawArea(0, 0, 640, 480);

	//�X�R�A
	score->All();

	SoundAll();
	++g_count;
}

void CONTROL::SoundAll() {
	if (pshot_flag) {
		PlaySoundMem(s_pshot, DX_PLAYTYPE_BACK);
	}
	if (eshot_flag) {
		PlaySoundMem(s_eshot, DX_PLAYTYPE_BACK);
	}
	if (edead_flag) {
		PlaySoundMem(s_edead, DX_PLAYTYPE_BACK);
	}
	if (pdead_flag) {
		PlaySoundMem(s_edead, DX_PLAYTYPE_BACK);
	}
	if (graze_flag) {
		PlaySoundMem(s_graze, DX_PLAYTYPE_BACK);
	}
	if (item_flag) {
		PlaySoundMem(s_item, DX_PLAYTYPE_BACK);
	}
}

CONTROL::~CONTROL()
{
	delete player;
	delete back;
	for (int i = 0; i < ENEMY_NUM; ++i) {
		if (enemy[i] != NULL) {
			delete enemy[i];
		}
	}
	delete boss;
}