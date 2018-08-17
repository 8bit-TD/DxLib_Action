#pragma once
#include <windows.h>

//画面解像度
#define GAME_WIDTH 1920
#define GAME_HEIGHT 1080

//プレイヤー設定
#define BASE_SPEED 0.5
#define GRAVITY 0.2
#define BASE_JUMP 0.1
#define PSHOT_NUM 200  //弾の数
#define DAMAGE_NUM 200 //ダメージの数

//ブロックの設定
#define BLOCK_SIZE 32
#define BLOCK_W_NUM (GAME_WIDTH / BLOCK_SIZE)
#define BLOCK_H_NUM (GAME_HEIGHT / BLOCK_SIZE)
#define BLOCK_NUM (BLOCK_W_NUM * BLOCK_H_NUM)

//メッセージボックス
#define MSG(m) {\
	MessageBox(NULL,m,"メッセージ",MB_OK);}

#define PI 3.1415

//extern宣言してkey配列にどこからでもアクセスできるようにする
extern char key[256];

//extern宣言してカウント数にどこからでもアクセスできるようにする
extern int g_count;
//extern宣言してマウスのボタンの状態をどこ彼でもアクセスできる世にする
extern int MouseInput;


