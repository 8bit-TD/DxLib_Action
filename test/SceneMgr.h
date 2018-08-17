#pragma once

#include "SceneChanger.h"
#include "SceneBase.h"
#include "System.h"

class SceneMgr : public SceneChanger, Task {

private:
    SceneBase * mScene    ;    //シーン管理変数
    eScene mNextScene;    //次のシーン管理変数
	System *system;

public:
    SceneMgr();
    void Initialize() override;//初期化
    void Finalize() override;//終了処理
    void Update() override;//更新
    void Draw() override;//描画

    // 引数 nextScene にシーンを変更する
    void ChangeScene(eScene NextScene) override;

};