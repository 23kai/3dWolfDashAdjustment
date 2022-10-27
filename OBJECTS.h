#pragma once
#include "GAME_OBJECT.h"
class OBJECTS :
    public GAME_OBJECT
{
public:
    //�I�u�W�F�N�g�ԍ�
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
    void create();//�I�u�W�F�N�g�쐬
    void init();//������
    void proc();//���s
    void update();//�V�������֏㏑��
    void draw();//�`�揈��

};

