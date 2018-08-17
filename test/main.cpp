#include "pch.h"
#include "control.h"
#include "se.h"
#include "SceneMgr.h"

char key[256];      //�L�[�擾�p�z��
int g_count;        //�J�E���g��
int MouseInput;     //�}�E�X�̃{�^���̏��
int FrameStartTime; //60FPS�Œ�p�A���ԕۑ��p�ϐ�


// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow )
{
	SetDrawScreen(DX_SCREEN_BACK);// �`���𗠉�ʂɃZ�b�g
	SetWaitVSyncFlag(FALSE);// ���������M����҂��Ȃ�	
	//	SetWaitVSyncFlag(true);
	FrameStartTime = GetNowCount();// �U�O�e�o�r�Œ�p�A���ԕۑ��p�ϐ������݂̃J�E���g�l�ɃZ�b�g
	ChangeWindowMode(TRUE);//�E�C���h�E���[�h
	//SetWindowSizeChangeEnableFlag(TRUE);
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, 32);//��ʉ𑜓x�ݒ�
	SetMouseDispFlag(TRUE);
	if( DxLib_Init() == -1 ) {return -1;}// �G���[���N�����璼���ɏI��
	CONTROL *control = CONTROL::GetInstance();

	SceneMgr sceneMgr;
	sceneMgr.Initialize();

	while(ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 && GetHitKeyStateAll(key)==0){	
		MouseInput = GetMouseInput();
		//WaitVSync(60);
		while (GetNowCount() - FrameStartTime < 1000 / 60) {}// 1/60�b���܂ő҂�
		ClsDrawScreen();// ��ʂ̃N���A
		// ���݂̃J�E���g�l��ۑ�
		FrameStartTime = GetNowCount();
		

		//control.All();
		control->FpsTimeFanction();
		if (control->GameEndCheck()) { break; }

		sceneMgr.Update();  //�X�V
		sceneMgr.Draw();    //�`��
		//WaitVSync(60);
		ScreenFlip(); //����ʂ�\��ʂɔ��f
		++g_count;//�J�E���g�����Z
	}
	DxLib_End();// �c�w���C�u�����g�p�̏I������
	return 0;// �\�t�g�̏I�� 
}