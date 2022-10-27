#pragma once
#include "OBJECTS.h"
#include"DxLib.h"
class CUBE :
    public OBJECTS
{
public:
    //�l�p�`�ɕK�v�Ȓl
    struct DATA {
        VECTOR obj1;
        VECTOR obj2;
        //�F
        int CubeColorR;
        int CubeColorG;
        int CubeColorB;

    };
private:
    //�f�[�^�ϐ�
    DATA Cube;
public:
    //�֐�
    CUBE(class GAME* game);
    ~CUBE();
    void create();//�I�u�W�F�N�g�쐬
    void update();//�X�V
    void draw();//�`��
    void CreateSquare(VECTOR pos, VECTOR pos1, int color,OBJECT_ID objectId);
    void CreateCube(VECTOR start, VECTOR end, int color, OBJECT_ID objectId);//���̎l�p�`�쐬�֐�
    void CollisionOnly(VECTOR pos, VECTOR pos1, OBJECT_ID objectId);
    VECTOR target() { return Cube.obj1; }//�����_
    float posY() { return Cube.obj1.y; }
};