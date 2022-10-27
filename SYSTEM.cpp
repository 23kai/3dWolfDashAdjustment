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
	// 現在のシステム時間を取得
	System.NowTime = GetNowHiPerformanceCount();

	// 前回取得した時間からの経過時間を秒に変換してセット
	// ( GetNowHiPerformanceCount で取得できる値はマイクロ秒単位なので 1000000 で割ることで秒単位になる )
	System.DeltaTime = (System.NowTime - System.Time) / 1000000.0f;

	// 今回取得した時間を保存
	System.Time = System.NowTime;

	// FPS関係の処理( 1秒経過する間に実行されたメインループの回数を FPS とする )
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

