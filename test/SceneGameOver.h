#pragma once
#include "SceneBase.h"

//�Q�[���I�[�o�[���
class SceneGameOver : public SceneBase {
public:
	SceneGameOver(SceneChanger* changer);
	void Initialize() override;
	void Update() override;
	void Draw() override;
};