#pragma once

class SE {
public:
	int se_shot;//ショット音
	int se_death;//敵死亡時の音
	int se_damage;//ダメージを受けた時の音
	int se_block; //弾がブロックに当たった時の音
	int se_click; //クリック音
	int volume;

	SE();
	void SE_Shot();//ショット音
	void SE_Death();//敵死亡時の音
	void SE_Damage();//ダメージを受けた時の音
	void SE_Block();//弾がブロックに当たった時の音
	void SE_Click();//クリック音
	static SE* GetInstance() {//シングルトン
		static SE se;
		return &se;
	}
};