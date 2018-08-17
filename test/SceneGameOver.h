#pragma once
#include "SceneBase.h"

//ゲームオーバー画面
class SceneGameOver : public SceneBase {
public:
	SceneGameOver(SceneChanger* changer);
	void Initialize() override;
	void Update() override;
	void Draw() override;
};