#pragma once
#include "OBJECTS.h"
#include"DxLib.h"

#define PLAYER_ANGLE_SPEED			0.2f		// �p�x�ω����x
class WOLF :
    public OBJECTS
{
public:
    //ON��OFF��
    enum ONOFF_ID {
        OFF_ID,
        ON_ID
    };
    //�I�I�J�~���f���̃A�j���[�V�����ԍ�
    enum ANIMATION_ID {
        CROUCHING_WALK_ID = 1,//���Ⴊ�ݕ���
        STAND_BY_ID,//�ҋ@���[�V����
        RUN_ID,//����
        SIT_ID,//����
        WALKING_ID//����
    };
    //�v���C���[�̏�Ԕԍ�
    enum STATE_ID {
        HIT_FLOOR_ID=1,
        HIT_LEFTWALL_ID,
        HIT_RED_LEFTWALL_ID,
        HIT_RIGHTWALL_ID,
        HIT_RED_RIGHTWALL_ID,
        HIT_STRAGHTWALL_ID,
        HIT_GATE_ID,
        NUM_HITSTATE
    };
    //�I�I�J�~���f���̃n���h����A�j���[�V�������ԁA���W�̕ϐ�
    struct DATA {
        VECTOR Pos;//���W
        VECTOR MinPoligonPos;//�Œ���W
        VECTOR MaxPoligonPos;//�ō����W
        VECTOR ModelScale;//���f���̑傫��
        MATRIX matrix;
        float UnderLowwer;//Y���W�̍Œ�l
        VECTOR InitPos;//�ʒu������
        int GraphicHundle;//���f���ԍ�
        VECTOR ModelCenterFrame;
        int AnimHundle;//�A�j���[�V�����ԍ�
        int AttachAnim;//�A�^�b�`����A�j���[�V����
        int TotalTime;//�A�j���[�V�����̑�����
        float PlayTime;//�A�j���[�V�����̌�����
        float AnimTimeSpeed;//�A�j���[�V�����̓������x
        VECTOR TargetMoveDirection;//�L�����N�^�[�������ׂ�����

        VECTOR UpMoveVec;//�J�������猩�ď�Ɉړ�����l
        VECTOR LeftMoveVec;//�J�������猩�č��Ɉړ�����l
        VECTOR MoveVec;//�ړ������l
        float Angle;// ���f���������Ă�������̊p�x
        int AngleState;//��]�����̏�������
        float RadianZ;//Z���̉�]
        MATRIX Radian;//��]
        VECTOR RadianTranslation;

        float MovingSpeed;//�ړ����x
        float WalkSpeed;//�������x
        float DashSpeed;//�_�b�V���X�s�[�h
        int MovingCheck;//�ړ����邩���Ȃ���
        float DownSpeed;//�����������ۂ̃X�s�[�h��������l
        float MaxWalkSpeed;//�ړ����x�̍ő�l
        float MaxDashSpeed;//�_�b�V���̍ő呬�x

        int AirCheck;//�󒆊m�F�l
        float JumpPower;//�W�����v��
        float Gravity;//�d��
        float GravityPlusSpeed;//�d�͉����x
        float GravityUpperLimit;//�d�͑��x�̏���l
        int JumpStock;//�W�����v��
        int JumpFloorStock;//�n�ʂɂ����Ƃ��̃W�����v��
        int JumpWallStock;//�ǂɒ���t�������̃W�����v��
        float JumpCoolTime;//�W�����v�̌��Ďg�p����
        float JumpCoolDown;//�W�����v�̍Ďg�p����

        int State;//�v���C���[�̏��
        int StateConditions[NUM_HITSTATE];//�v���C���[�̏d�Ȃ�Ȃ������̎�
        int HitState[NUM_HITSTATE];//�v���C���[�̏�Ԃ𕡐����肳����
        VECTOR HitVector;
        float StateTime;//��Ԃ̕ێ�����
        MV1_REF_POLYGONLIST Poligon;//�|���S�����
        
        VECTOR CollisionSphere;//�����蔻��͈͎w��p���̍��W
        float radius;//�����蔻��͈͎w��p���̂̔��a

        float Score;//�i�񂾋����ɉ������X�R�A
        float BonusScore;//�{�[�i�X�X�R�A���Z
        float ScoreVz;//�v���C���[�̈ʒu
        float MscoreZ;//�v���C���[�����ݐi�񂾍ō��ʒu
    };
private:
    DATA Wolf;
public:
    WOLF(class GAME* game);
    ~WOLF();
    void create();//�I�u�W�F�N�g�쐬�i�l�擾)
    void init();//������
    void update();//�X�V
    void draw();//�`��
    void move();//�ړ�
    void angleProcess();
    void animProcess();
    void attachAnim(enum ANIMATION_ID animId);
    void modelInit();
    void collision();
    float radius() { return Wolf.radius; }
    VECTOR CollisionCircle() { return Wolf.CollisionSphere; }
    VECTOR target() { return Wolf.Pos; }
    int state() { return Wolf.State; }
    int score() { return (int)Wolf.Score; }
};

