#pragma once

typedef enum {
    eScene_Title,   //タイトル画面
    eScene_Config,  //設定画面
	eScene_Game,    //ゲーム画面
	eScene_GameOver,//ゲームオーバー画面

    eScene_None,    //無し
} eScene ;

//シーンを変更するためのインターフェイスクラス
class SceneChanger {
public:
    virtual ~SceneChanger() = 0;
    virtual void ChangeScene(eScene NextScene) = 0;//指定シーンに変更する
};
