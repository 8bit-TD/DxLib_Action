#include "damage.h"

DAMAGE::DAMAGE() {
	pos.x = pos.y = pos.z = bound = my = damage = rise_value = color = 0;
	endflag = true;
}

bool DAMAGE::GetDamageFlag() {//ƒtƒ‰ƒO‚ðŽæ“¾
	return endflag;
}

void DAMAGE::SetDamage(bool flag, VECTOR p, int d, int col) {
	color = col;
	endflag = flag; 
	my = rise_value;
	//rise_value = -GetRand(2)/1.0 - 1.0;
	rise_value = -(GetRand(2) + 0.5);
	bound = 0;
	pos.x = (p.x+(GetRand(0)-0)); pos.y = p.y; start_y = p.y + 40;
	damage = d;
}

void DAMAGE::Move() {
	if (!endflag) {
		my += GRAVITY/2;
		pos.y += my;
		if (pos.y > start_y) {
			bound++;
			my += (rise_value / bound);
		}
		if (bound > 5) { endflag = true; }
	}
}

void DAMAGE::Draw() {
	if (!endflag) {
		SetFontSize(10);
		//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255 - (50*bound));
		//SetFontThickness(1);
		//ChangeFont("‚l‚r –¾’©");
		DrawString(pos.x, pos.y, std::to_string(damage).c_str(), color);
		//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		//SetFontThickness(6);
	}
}

void DAMAGE::All() {
	Move();
	Draw();
}

///////////////////////// DAMAGE_MANAGER /////////////////////////////

DAMAGE_MANAGER::DAMAGE_MANAGER() {
	for (int i = 0; i < DAMAGE_NUM; ++i) {
		damage[i] = new DAMAGE;
	}
}

void DAMAGE_MANAGER::SetDamage(VECTOR p, int d, int col) {
	for (int i = 0; i < DAMAGE_NUM; ++i) {
		if (damage[i]->GetDamageFlag()) {
			damage[i]->SetDamage(false, p, d, col);
			break;
		}
	}
	++count;
}

void DAMAGE_MANAGER::Move() {
	for (int i = 0; i < DAMAGE_NUM; ++i) {
		damage[i]->Move();
	}
}

void DAMAGE_MANAGER::Draw() {
	for (int i = 0; i < DAMAGE_NUM; ++i) {
		damage[i]->Draw();
	}
}

void DAMAGE_MANAGER::All() {
	Move();
	Draw();
}

DAMAGE_MANAGER::~DAMAGE_MANAGER() {
	for (int i = 0; i < DAMAGE_NUM; ++i) {
		damage[i] = NULL;
		delete damage[i];
	}
}