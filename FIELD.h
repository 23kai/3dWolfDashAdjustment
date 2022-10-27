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
        VECTOR StartArea;//�n�_
        VECTOR EndArea;//�I�_
        int Color;//�ǁA���̐F
        int NoKickWallColor;//�R��Ȃ��ǂ̐F
        int LeftWallColor;//�R��Ȃ��ǂ̐F
        int RedWallColor;//�R��Ȃ��ǂ̐F

        VECTOR pos;//���W
        VECTOR FramePos;//�t���[���̍��W
        MV1_REF_POLYGONLIST Poligon;//�|���S�����
        VECTOR MinPoligonPos;//���f���̍ŏ����_���W
        VECTOR MaxPoligonPos;//���f���̍ő咸�_���W
        VECTOR AddMinMaxPoligonPos;//���_���W�̍ő�l�ƍŏ��l�����킹���l

        int GraphicHundle;//���f���n���h��
        int MaxHundle ;
        int CopyGraphicHandle[MAXTILE];//�R�s�[���f���n���h��
        VECTOR CopyGraphicPos[MAXTILE];//�R�s�[���f���̍��W

        char MapTile[MAXTILE];//�}�b�v�^�C��
        char Map[MAXTILE];//�n�`
        char CopyMapTile[MAXTILE];//�R�s�[���ꂽ�}�b�v�^�C��

        float radian;//��]�p�x
        MV1_COLL_RESULT_POLY_DIM Collision;
        VECTOR GatePos, GatePos2;//���[�v�ꏊ�̈ʒu
        int GateColor;
        int p;//�ėp���[�v�l
    };
private:
    //�f�[�^�ϐ�
    DATA Field;
public:
    FIELD(class GAME* game);
    ~FIELD();
    void create();//�I�u�W�F�N�g�쐬
    void init();//������
    void update();//�X�V
    void draw();//�`��
    void collision();//�Փ˔���
    void loop();
    void CollisionTerminate();
};

