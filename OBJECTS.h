#pragma once
#include "GAME_OBJECT.h"
class OBJECTS :
    public GAME_OBJECT
{
public:
    //オブジェクト番号
    enum OBJECT_ID {
        CAMERA_ID,
        FLOOR_ID=1,
        LEFT_WALL_ID,
        RED_LEFT_WALL_ID,
        RIGHT_WALL_ID,
        RED_RIGHT_WALL_ID,
        STRAGHT_WALL_ID,
        RETREAT_WALL_ID,
        TURN_RIGHT_WALL_ID,
        TURN_LEFT_WALL_ID,
        GATE_ID,
        NUM_OBJECTS
    };
public:
    OBJECTS(class GAME* game);
    ~OBJECTS();
    void create();//オブジェクト作成
    void init();//初期化
    void proc();//実行
    void update();//新しい情報へ上書き
    void draw();//描画処理

};

