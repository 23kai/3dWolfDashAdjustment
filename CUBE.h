#pragma once
#include "OBJECTS.h"
#include"DxLib.h"
class CUBE :
    public OBJECTS
{
public:
    //四角形に必要な値
    struct DATA {
        VECTOR obj1;
        VECTOR obj2;
        //色
        int CubeColorR;
        int CubeColorG;
        int CubeColorB;

    };
private:
    //データ変数
    DATA Cube;
public:
    //関数
    CUBE(class GAME* game);
    ~CUBE();
    void create();//オブジェクト作成
    void update();//更新
    void draw();//描画
    void CreateSquare(VECTOR pos, VECTOR pos1, int color,OBJECT_ID objectId);
    void CreateCube(VECTOR start, VECTOR end, int color, OBJECT_ID objectId);//立体四角形作成関数
    void CollisionOnly(VECTOR pos, VECTOR pos1, OBJECT_ID objectId);
    VECTOR target() { return Cube.obj1; }//注視点
    float posY() { return Cube.obj1.y; }
};