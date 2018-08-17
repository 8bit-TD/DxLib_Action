#pragma once
#include <windows.h>

//��ʉ𑜓x
#define GAME_WIDTH 1920
#define GAME_HEIGHT 1080

//�v���C���[�ݒ�
#define BASE_SPEED 0.5
#define GRAVITY 0.2
#define BASE_JUMP 0.1
#define PSHOT_NUM 200  //�e�̐�
#define DAMAGE_NUM 200 //�_���[�W�̐�

//�u���b�N�̐ݒ�
#define BLOCK_SIZE 32
#define BLOCK_W_NUM (GAME_WIDTH / BLOCK_SIZE)
#define BLOCK_H_NUM (GAME_HEIGHT / BLOCK_SIZE)
#define BLOCK_NUM (BLOCK_W_NUM * BLOCK_H_NUM)

//���b�Z�[�W�{�b�N�X
#define MSG(m) {\
	MessageBox(NULL,m,"���b�Z�[�W",MB_OK);}

#define PI 3.1415

//extern�錾����key�z��ɂǂ�����ł��A�N�Z�X�ł���悤�ɂ���
extern char key[256];

//extern�錾���ăJ�E���g���ɂǂ�����ł��A�N�Z�X�ł���悤�ɂ���
extern int g_count;
//extern�錾���ă}�E�X�̃{�^���̏�Ԃ��ǂ��ނł��A�N�Z�X�ł��鐢�ɂ���
extern int MouseInput;


