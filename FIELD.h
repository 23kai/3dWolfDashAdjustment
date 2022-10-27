#pragma once
#include "OBJECTS.h"
#include"DxLib.h"
#define MAXTILE 256
class FIELD :
    public OBJECTS
{
public:
    enum MAPDATA {
        STRAIGHT_LINE,
        TURN_RIGHT,
        TURN_LEFT,
        NUM_DATA
    };
    struct DATA {
        VECTOR StartArea;//始点
        VECTOR EndArea;//終点
        int Color;//壁、床の色
        int NoKickWallColor;//蹴れない壁の色
        int LeftWallColor;//蹴れない壁の色
        int RedWallColor;//蹴れない壁の色

        VECTOR pos;//座標
        VECTOR FramePos;//フレームの座標
        MV1_REF_POLYGONLIST Poligon;//ポリゴン情報
        VECTOR MinPoligonPos;//モデルの最小頂点座標
        VECTOR MaxPoligonPos;//モデルの最大頂点座標
        VECTOR AddMinMaxPoligonPos;//頂点座標の最大値と最小値を合わせた値

        int GraphicHundle;//モデルハンドル
        int MaxHundle ;
        int CopyGraphicHandle[MAXTILE];//コピーモデルハンドル
        VECTOR CopyGraphicPos[MAXTILE];//コピーモデルの座標

        char MapTile[MAXTILE];//マップタイル
        char Map[MAXTILE];//地形
        char CopyMapTile[MAXTILE];//コピーされたマップタイル

        float radian;//回転角度
        MV1_COLL_RESULT_POLY_DIM Collision;
        VECTOR GatePos, GatePos2;//ループ場所の位置
        int GateColor;
        int p;//汎用ループ値
    };
private:
    //データ変数
    DATA Field;
public:
    FIELD(class GAME* game);
    ~FIELD();
    void create();//オブジェクト作成
    void init();//初期化
    void update();//更新
    void draw();//描画
    void collision();//衝突判定
    void loop();
    void CollisionTerminate();
};

