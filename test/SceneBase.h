#pragma once

#include "Task.h"
#include "SceneChanger.h"

//シーンの基底クラス。
class SceneBase : public Task {

protected:
    //int mImageHandle;                //画像ハンドル格納用変数
    SceneChanger* mSceneChanger;    //クラス所有元にシーン切り替えを伝えるインターフェイス

public :
    SceneBase(SceneChanger* changer);
    virtual ~SceneBase(){}
    virtual void Initialize() override {}    //初期化処理をオーバーライド。
    virtual void Finalize() override ;        //終了処理をオーバーライド。
    virtual void Update() override {}        //更新処理をオーバーライド。
    virtual void Draw() override ;            //描画処理をオーバーライド。

};
