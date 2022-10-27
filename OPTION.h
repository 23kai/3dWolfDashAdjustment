#pragma once
#include "SCENE.h"
#include"DxLib.h"
#include<cmath>
class OPTION :
    public SCENE
{
public:
    struct DATA {
        //それぞれの状態(0or1)
        int Change;//シーン切り替え
        int Back;//戻るボタンの動作(0or1)
        int MouseSensitivity;//マウス操作ONOFF(0or1)
        int BabMouseKeyCheck;//戻るボタンが押されている状態(0or1)
        int OnSenBotanMouseKeyCheck;//マウスによるカメラ操作をONにするボタンが押されている状態(0or1)
        int OffSenBotanMouseKeyCheck;//マウスによるカメラ操作をOffにするボタンが押されている状態(0or1)

        //感度設定関係
        VECTOR SensitivityBoxX;//X軸感度設定の箱
        VECTOR SensitivityBoxY;//Y軸感度設定の箱
        float SebExpansionX;//ボタン判定拡張
        float SebExpansionY;//ボタン判定拡張
        float SensitivityLineStartX;//感度設定の線の始点
        float SensitivityLineEndX;//感度設定の線の終点
        float SensitivityXLineY;//X軸感度設定の線のY座標
        float SensitivityYLineY;//Y軸感度設定の線のY座標
        char SensitivityXText[40];//カメラ感度の値表示する
        char SensitivityYText[40];//カメラ感度の値表示する

        //感度設定の際の円
        VECTOR SensitivityXCircle;//X軸感度設定の点
        VECTOR SensitivityYCircle;//Y軸感度設定の点
        float SensitivityCircleRadius;//円の大きさ

        //感度設定に使われている箱や円、線の色
        int SenXWallPaperColor;//X軸感度設定の箱の色
        int SenYWallPaperColor;//Y軸感度設定の箱の色
        int SenInitWallPaperColor;//感度設定の箱の初期色
        int SenTouchWallPaperColor;//感度設定の箱に触っている時の色
        int SenPushWallPaperColor;//感度設定の箱を押している時の色
        int CircleColor;//感度設定の点の色
        int LineColor;//感度設定の線の色

        //戻るボタン関係
        VECTOR Bab;//戻るボタンの位置
        float botExpansionX;//ボタン判定拡張
        float botExpansionY;//ボタン判定拡張
        char BackBotanText[10];//マウスによるカメラ操作の設定の状況を表示する

        //戻るボタンの箱の色
        int BabWallPaperColor;//戻るボタンの箱の色
        int BabInitWallPaperColor;//戻るボタンの初期の色
        int BabTouchWallPaperColor;//戻るボタンを触っている時の色

        //マウスによるカメラ操作をするしないのボタン関係
        VECTOR OnSensitivityBotan;//感度をONにするボタン
        VECTOR OffSensitivityBotan;//感度をOFFにするボタン
        float SensiBotanExpansionX;//ボタン判定拡張
        float SensiBotanExpansionY;//ボタン判定拡張
        char SensitivityBotanText[40];//マウスによるカメラ操作の設定の状況を表示する
        char OnSensitivityBotanText[30];//マウスによるカメラ操作の設定の状況を表示する
        char OffSensitivityBotanText[30];//マウスによるカメラ操作の設定の状況を表示する

        //マウスによるカメラ操作をするしないのボタンの箱の色
        int OnSensiBotanWallPaperColor;//戻るボタンの箱の色
        int OffSensiBotanWallPaperColor;//戻るボタンの箱の色
        int SensiBotanRedWallPaperColor;//戻るボタンの初期の色
        int SensiBotanGreenWallPaperColor;//戻るボタンを触っている時の色

        //感度設定に必要な値や計算値
        float SensitivityX;//X軸感度
        float SensitivityY;//Y軸感度
        float Sensitivity;//感度設定の0.1ごとの分割を長さで表した数字
        float SensitivityFixed;//感度の最小値
        int SensitivitySplit;//感度設定の分割(最大12とした分割量)
        int Split;//分割(小数点の計算に必要な10分割)
        double Calculation;//感度設定の計算

        //フォント関係
        int FontHandle;//文字のフォントを記憶する
        int FontColor;//文字のフォントの色
        int FontScale;//フォントの大きさ
        int FontThick;//フォントの太さ
        int ValueScele;//値表示の際座標をずらしてちょうど良い位置に置くための値

        //マウスポインター関係
        int MousePointX;//マウスポインターの現X座標
        int MousePointY;//マウスポインターの現Y座標
        int MouseCrick;//マウスクリック
        int MouseCrickLog;//マウスクリックの現状況
        int MouseKeyCheck;
        //int SebMouseKeyCheck;
    };
private:
    DATA Option;
public:
    OPTION(class GAME* game);
    ~OPTION();
    void create();
    void init();
    void update();
    void draw();
    void nextScene();
    void ChangeScene();
};

