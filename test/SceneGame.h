#pragma once
#include "SceneBase.h"
#include "GameKeyConfig.h"

//ゲーム画面クラス
class SceneGame : public SceneBase {

public:
	
	SceneGame(SceneChanger* changer);
	GameKeyConfig *gkc;
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;

	void ShowKeyConfig(); //キーコンフィグ設定画面を表示
	void ShowMenu();      //メニュー画面を表示
};