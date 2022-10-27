#pragma once
#include"OBJECTS.h"
#include"DxLib.h"
#include<math.h>
class CAMERA :
    public OBJECTS
{
public:
    struct  DATA {
        VECTOR Pos;//位置
        VECTOR Target;//カメラが見ている座標
        VECTOR Vtarget;//注視点が動いた量
        float radius;//半径
        float Radian;//回転量
        float InitRadian;//回転量初期値
        MATRIX Matrix;
        int TargetNumber;
        float MaxDrawingRange;
        float MinDrawingRange;
        int MousePointX;
        int MousePointY;
    };
private:
    DATA Camera;
    
public:
    CAMERA(class GAME* game);
    ~CAMERA();
    void create();//オブジェクト作成
    void init();//初期化
    void proc();//実行順
    void update();//更新
    void draw();//描画or設置
    void charaCamera(VECTOR vpos);
    VECTOR target() { return Camera.Target; }
    VECTOR pos() { return Camera.Pos; }
};

