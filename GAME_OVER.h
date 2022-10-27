#pragma once
#include "SCENE.h"
#include"DxLib.h"
class GAME_OVER :
    public SCENE
{
public:
    struct DATA {
        //それぞれの状態(0or1)
        int Restart;//リスタートボタン
        int Quit;//終了ボタン
        int Title;//タイトルボタン
        //スコア
        int Score;//スコア値
        VECTOR ScoreDraw;//スコア表示位置
        //ボタン関係
        VECTOR Stb;//リスタートボタン位置
        VECTOR Qub;//終了ボタン位置
        VECTOR Tib;//タイトルボタン位置
        float botExpansionX;//ボタン判定拡張
        float botExpansionY;//ボタン判定拡張
        //フォントや壁紙
        int FontHandle;//フォント
        int FontScale;//フォントの大きさ
        int FontThick;//フォントの太さ
        int FontColor;//フォントの色
        int StbWallpaperColor;//スタートボタンの箱の色
        int TibWallpaperColor;//タイトル画面ボタンの箱の色
        int QubWallpaperColor;//閉じるボタンの箱の色
        int InitWallpaperColor;//通常色
        int TouchWallpaperColor;//触れている時の色
        char ScoreText[10];//スコア文字表示
        char RestartText[20];//リスタート文字表示
        char QuitText[20];//閉じる文字表示
        char TitleText[20];//タイトル文字表示
        //マウスポインター関係
        int MousePointX;//X軸のポインターの位置
        int MousePointY;//Y軸のポインターの位置
        int MouseCrick;//マウスクリック状態
        int MouseCrickLog;//マウスクリックの最後の状態
        int RestartMouseKeyCheck;//リスタートボタンが押されている状態
        int TitleMouseKeyCheck;//タイトルボタンが押されている状態
        int QuitMouseKeyCheck;//閉じるボタンが押されている状態

    };
private:
    DATA Over;
public:
    GAME_OVER(class GAME* game);
    ~GAME_OVER();
    void virtual create();//値取得
    void virtual init();//初期化
    void virtual update();//上書き
    void virtual draw();//描画
    void virtual nextScene();//次のシーンへ
};

