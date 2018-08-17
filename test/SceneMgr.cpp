#include "DxLib.h"
#include "SceneConfigKey.h"
#include "SceneTitle.h"
#include "SceneGame.h"
#include "SceneMgr.h"
#include "SceneGameOver.h"
//#include "System.h"

SceneMgr::SceneMgr() :  mNextScene(eScene_None) //次のシーン管理変数
{
    mScene = (SceneBase*) new SceneTitle(this);
	//system = new System;
}

//初期化
void SceneMgr::Initialize(){
    mScene->Initialize();
}

//終了処理
void SceneMgr::Finalize(){
    mScene->Finalize();
}

//更新
void SceneMgr::Update(){
    if(mNextScene != eScene_None){    //次のシーンがセットされていたら
        mScene->Finalize();//現在のシーンの終了処理を実行
        delete mScene;
        switch(mNextScene){       //シーンによって処理を分岐
        case eScene_Title:        //次の画面がメニューなら
            mScene = (SceneBase*) new SceneTitle(this);   //タイトル画面のインスタンスを生成する
            break;//以下略
        case eScene_Config:
            mScene = (SceneBase*) new SceneConfigKey(this);
            break;
		case eScene_Game:
			mScene = (SceneBase*) new SceneGame(this);
			break;
		case eScene_GameOver:
			mScene = (SceneBase*) new SceneGameOver(this);
			break;
        }
        mNextScene = eScene_None;    //次のシーン情報をクリア
        mScene->Initialize();    //シーンを初期化
    }

    mScene->Update(); //シーンの更新
	//system->Update();
}

//描画
void SceneMgr::Draw(){
    mScene->Draw(); //シーンの描画
	//system->Draw();
}

// 引数 nextScene にシーンを変更する
void SceneMgr::ChangeScene(eScene NextScene){
    mNextScene = NextScene;    //次のシーンをセットする
}
