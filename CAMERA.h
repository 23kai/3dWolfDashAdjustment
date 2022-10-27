#pragma once
#include"OBJECTS.h"
#include"DxLib.h"
#include<math.h>
class CAMERA :
    public OBJECTS
{
public:
    struct  DATA {
        VECTOR Pos;//�ʒu
        VECTOR Target;//�J���������Ă�����W
        VECTOR Vtarget;//�����_����������
        float radius;//���a
        float Radian;//��]��
        float InitRadian;//��]�ʏ����l
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
    void create();//�I�u�W�F�N�g�쐬
    void init();//������
    void proc();//���s��
    void update();//�X�V
    void draw();//�`��or�ݒu
    void charaCamera(VECTOR vpos);
    VECTOR target() { return Camera.Target; }
    VECTOR pos() { return Camera.Pos; }
};

