#pragma once
#include"GAME_OBJECT.h"
#include"DxLib.h"
#include<math.h>

//�t���[�����[�g�v�Z���]�s��Ƃ������@�\�̏W�܂�
class SYSTEM:
	public GAME_OBJECT
{
public:
	struct DATA {
		//�t���[�����[�g�v�Z�g�p�ϐ�
		LONGLONG NowTime;//���ݎ���
		LONGLONG Time;//NowTime�̕ʕۑ��ꏊ
		//FPS�v���֌W
		float DeltaTime;//���̒l���ړ��l�Ɋ|����
		int FPS;
		int FPSCounter;
		LONGLONG FPSCheckTime;

		char Buf[256];//�L�[�̉������

		float SensitivityX;//X�����x
		float SensitivityY;//Y�����x
		int MouseSensitivity;//�}�E�X�J��������

		int K;
	};
private:
	DATA System;
public:
	SYSTEM(class GAME* game);
	void create();
	void init();//������
	float delta();//delta�v�Z���ʊ֐�
	void rotate(float* x, float* y, const float ang, const float mx, const float my);//��]�s��
	int CheckKey(long Key);//�e�L�[�̉�����Ă����Ԋm�F(�Ԃ�l�̓L�[���蓖�Ēl�j
	float GetSensitivityX() { return System.SensitivityX; }//X�����x���o��
	float GetSensitivityY() { return System.SensitivityY; }//Y�����x���o��
	bool GetMouseSensitivity() { return System.MouseSensitivity; }//�}�E�X�J���������Ԏ��o��
	void SensitivityX(float sensi) { System.SensitivityX = sensi; }//X�����x����
	void SensitivityY(float sensi) { System.SensitivityY = sensi; }//Y�����x����
	void MouseSensitivity(int MouseSensi) { System.MouseSensitivity = MouseSensi; }//�}�E�X�J���������ԓ���
};
