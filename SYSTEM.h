#pragma once
#include"GAME_OBJECT.h"
#include"DxLib.h"
#include<math.h>

//フレームレート計算や回転行列といった機能の集まり
class SYSTEM:
	public GAME_OBJECT
{
public:
	struct DATA {
		//フレームレート計算使用変数
		LONGLONG NowTime;//現在時刻
		LONGLONG Time;//NowTimeの別保存場所
		//FPS計測関係
		float DeltaTime;//この値を移動値に掛ける
		int FPS;
		int FPSCounter;
		LONGLONG FPSCheckTime;

		char Buf[256];//キーの押下状態

		float SensitivityX;//X軸感度
		float SensitivityY;//Y軸感度
		int MouseSensitivity;//マウスカメラ操作

		int K;
	};
private:
	DATA System;
public:
	SYSTEM(class GAME* game);
	void create();
	void init();//初期化
	float delta();//delta計算結果関数
	void rotate(float* x, float* y, const float ang, const float mx, const float my);//回転行列
	int CheckKey(long Key);//各キーの押されている状態確認(返り値はキー割り当て値）
	float GetSensitivityX() { return System.SensitivityX; }//X軸感度取り出し
	float GetSensitivityY() { return System.SensitivityY; }//Y軸感度取り出し
	bool GetMouseSensitivity() { return System.MouseSensitivity; }//マウスカメラ操作状態取り出し
	void SensitivityX(float sensi) { System.SensitivityX = sensi; }//X軸感度入力
	void SensitivityY(float sensi) { System.SensitivityY = sensi; }//Y軸感度入力
	void MouseSensitivity(int MouseSensi) { System.MouseSensitivity = MouseSensi; }//マウスカメラ操作状態入力
};
