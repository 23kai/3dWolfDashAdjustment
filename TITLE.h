#pragma once
#include "SCENE.h"
#include"DxLib.h"
//#include"GAME.h"
class TITLE :
    public SCENE
{
public:
    struct DATA {
        int Start;//スタートボタン
        int Quit;//終了ボタン
        int Option;
        VECTOR Stb;//スタートボタン位置
        float botExpansionX;//ボタン判定拡張
        float botExpansionY;//ボタン判定拡張
        VECTOR Qub;//終了ボタン位置
        VECTOR Opb;//オプションボタン位置
        //フォント関係
        int FontHandle;//フォント
        int FontColor;//フォントカラー
        //箱色
        int StbWallpaperColor;//スタートボタンの箱色
        int QubWallpaperColor;//閉じるボタンの箱色
        int OpbWallpaperColor;//オプションボタンの箱色
        int InitWallpaperColor;//箱色の初期色
        int TouchWallpaperColor;//触っているときの箱色
        //マウスポインター関係
        int MousePointX;//X軸のマウスポインター座標
        int MousePointY;//Y軸のマウスポインター座標
        int MouseCrick;//マウスクリック
        int MouseCrickLog;//マウスクリックの最終状態
        //それぞれの箱の状態
        int StartMouseKeyCheck;//スタートボタンが押されている状態
        int QuitMouseKeyCheck;//戻るボタンが押されている状態
        int OptionMouseKeyCheck;//オプションボタンが押されている状態

    };
private:
    DATA Title;
public:
    TITLE(class GAME* game);
    ~TITLE();
    void create();//値取得
    void init();//初期化
    void update();//上書き
    void draw();//描画
    void nextScene();//次のシーン
    int quit() { return Title.Quit; }//閉じるボタンが押されたとき
};

