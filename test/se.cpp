#include "pch.h"
#include "se.h"

SE::SE() {
	volume = 30;
	se_shot = LoadSoundMem("sound/ch/shot.mp3");//ショット音
	se_death = LoadSoundMem("sound/ch/enemy_death.mp3");//敵死亡時の音
	se_damage = LoadSoundMem("sound/ch/damage.mp3");//ダメージを受けた時の音
	se_block = LoadSoundMem("sound/ch/block.mp3");//弾がブロックに当たった時の音
	se_click = LoadSoundMem("sound/system/click.mp3");//クリック音
}

void SE::SE_Shot() {//ショット音
	PlaySoundMem(se_shot, DX_PLAYTYPE_BACK);
	ChangeVolumeSoundMem(255 * volume / 100, se_shot);
}

void SE::SE_Death() {//敵死亡時の音
	PlaySoundMem(se_death, DX_PLAYTYPE_BACK);
	ChangeVolumeSoundMem(255 * volume / 100, se_death);
}

void SE::SE_Damage() {//ダメージを受けた時の音
	PlaySoundMem(se_damage, DX_PLAYTYPE_BACK);
	ChangeVolumeSoundMem(255 * volume / 100, se_damage);
}

void SE::SE_Block() {//弾がブロックに当たった時の音
	PlaySoundMem(se_block, DX_PLAYTYPE_BACK);
	ChangeVolumeSoundMem(255 * volume / 100, se_block);
}

void SE::SE_Click() {//クリック音
	PlaySoundMem(se_click, DX_PLAYTYPE_BACK);
	ChangeVolumeSoundMem(255 * volume / 100, se_click);
}
