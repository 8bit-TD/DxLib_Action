#pragma once

class SE {
public:
	int se_shot;//�V���b�g��
	int se_death;//�G���S���̉�
	int se_damage;//�_���[�W���󂯂����̉�
	int se_block; //�e���u���b�N�ɓ����������̉�
	int se_click; //�N���b�N��
	int volume;

	SE();
	void SE_Shot();//�V���b�g��
	void SE_Death();//�G���S���̉�
	void SE_Damage();//�_���[�W���󂯂����̉�
	void SE_Block();//�e���u���b�N�ɓ����������̉�
	void SE_Click();//�N���b�N��
	static SE* GetInstance() {//�V���O���g��
		static SE se;
		return &se;
	}
};