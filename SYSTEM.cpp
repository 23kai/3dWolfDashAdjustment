#include "SYSTEM.h"
#include"GAME.h"
SYSTEM::SYSTEM(class GAME* game) :
	GAME_OBJECT(game)
{
}

void SYSTEM::create()
{
	System = game()->container()->system();
}

void SYSTEM::init()
{
	SetDrawScreen(DX_SCREEN_BACK);
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	SetWaitVSyncFlag(FALSE);
	System.Time = GetNowHiPerformanceCount();
	System.DeltaTime = 0.000001f;
	System.FPS = 0;
	System.FPSCounter = 0;
}

float SYSTEM::delta()
{
	// ���݂̃V�X�e�����Ԃ��擾
	System.NowTime = GetNowHiPerformanceCount();

	// �O��擾�������Ԃ���̌o�ߎ��Ԃ�b�ɕϊ����ăZ�b�g
	// ( GetNowHiPerformanceCount �Ŏ擾�ł���l�̓}�C�N���b�P�ʂȂ̂� 1000000 �Ŋ��邱�Ƃŕb�P�ʂɂȂ� )
	System.DeltaTime = (System.NowTime - System.Time) / 1000000.0f;

	// ����擾�������Ԃ�ۑ�
	System.Time = System.NowTime;

	// FPS�֌W�̏���( 1�b�o�߂���ԂɎ��s���ꂽ���C�����[�v�̉񐔂� FPS �Ƃ��� )
	System.FPSCounter++;
	if (System.NowTime - System.FPSCheckTime > 1000000)
	{
		System.FPS = System.FPSCounter;
		System.FPSCounter = 0;
		System.FPSCheckTime = System.NowTime;
	}
	return System.DeltaTime;
}

void SYSTEM::rotate(float* x, float* y, const float ang, const float mx, const float my) 
{
	const float ox = *x - mx, oy = *y - my;
	*x = ox * cos(ang) + oy * sin(ang);
	*y = -ox * sin(ang) + oy * cos(ang);
	*x += mx;
	*y += my;

}

int SYSTEM::CheckKey(long Key)
{
	GetHitKeyStateAll(System.Buf);
	int k = 0;
	if (System.Buf[Key] == 1) {
		k = 1;
	}
	else {
		k = 0;
	}
	return k;
}

