#include "pch.h"
#include "se.h"

SE::SE() {
	volume = 30;
	se_shot = LoadSoundMem("sound/ch/shot.mp3");//�V���b�g��
	se_death = LoadSoundMem("sound/ch/enemy_death.mp3");//�G���S���̉�
	se_damage = LoadSoundMem("sound/ch/damage.mp3");//�_���[�W���󂯂����̉�
	se_block = LoadSoundMem("sound/ch/block.mp3");//�e���u���b�N�ɓ����������̉�
	se_click = LoadSoundMem("sound/system/click.mp3");//�N���b�N��
}

void SE::SE_Shot() {//�V���b�g��
	PlaySoundMem(se_shot, DX_PLAYTYPE_BACK);
	ChangeVolumeSoundMem(255 * volume / 100, se_shot);
}

void SE::SE_Death() {//�G���S���̉�
	PlaySoundMem(se_death, DX_PLAYTYPE_BACK);
	ChangeVolumeSoundMem(255 * volume / 100, se_death);
}

void SE::SE_Damage() {//�_���[�W���󂯂����̉�
	PlaySoundMem(se_damage, DX_PLAYTYPE_BACK);
	ChangeVolumeSoundMem(255 * volume / 100, se_damage);
}

void SE::SE_Block() {//�e���u���b�N�ɓ����������̉�
	PlaySoundMem(se_block, DX_PLAYTYPE_BACK);
	ChangeVolumeSoundMem(255 * volume / 100, se_block);
}

void SE::SE_Click() {//�N���b�N��
	PlaySoundMem(se_click, DX_PLAYTYPE_BACK);
	ChangeVolumeSoundMem(255 * volume / 100, se_click);
}
