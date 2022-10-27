#pragma once
#include "SCENE.h"
#include"DxLib.h"
#include<cmath>
class OPTION :
    public SCENE
{
public:
    struct DATA {
        //���ꂼ��̏��(0or1)
        int Change;//�V�[���؂�ւ�
        int Back;//�߂�{�^���̓���(0or1)
        int MouseSensitivity;//�}�E�X����ONOFF(0or1)
        int BabMouseKeyCheck;//�߂�{�^����������Ă�����(0or1)
        int OnSenBotanMouseKeyCheck;//�}�E�X�ɂ��J���������ON�ɂ���{�^����������Ă�����(0or1)
        int OffSenBotanMouseKeyCheck;//�}�E�X�ɂ��J���������Off�ɂ���{�^����������Ă�����(0or1)

        //���x�ݒ�֌W
        VECTOR SensitivityBoxX;//X�����x�ݒ�̔�
        VECTOR SensitivityBoxY;//Y�����x�ݒ�̔�
        float SebExpansionX;//�{�^������g��
        float SebExpansionY;//�{�^������g��
        float SensitivityLineStartX;//���x�ݒ�̐��̎n�_
        float SensitivityLineEndX;//���x�ݒ�̐��̏I�_
        float SensitivityXLineY;//X�����x�ݒ�̐���Y���W
        float SensitivityYLineY;//Y�����x�ݒ�̐���Y���W
        char SensitivityXText[40];//�J�������x�̒l�\������
        char SensitivityYText[40];//�J�������x�̒l�\������

        //���x�ݒ�̍ۂ̉~
        VECTOR SensitivityXCircle;//X�����x�ݒ�̓_
        VECTOR SensitivityYCircle;//Y�����x�ݒ�̓_
        float SensitivityCircleRadius;//�~�̑傫��

        //���x�ݒ�Ɏg���Ă��锠��~�A���̐F
        int SenXWallPaperColor;//X�����x�ݒ�̔��̐F
        int SenYWallPaperColor;//Y�����x�ݒ�̔��̐F
        int SenInitWallPaperColor;//���x�ݒ�̔��̏����F
        int SenTouchWallPaperColor;//���x�ݒ�̔��ɐG���Ă��鎞�̐F
        int SenPushWallPaperColor;//���x�ݒ�̔��������Ă��鎞�̐F
        int CircleColor;//���x�ݒ�̓_�̐F
        int LineColor;//���x�ݒ�̐��̐F

        //�߂�{�^���֌W
        VECTOR Bab;//�߂�{�^���̈ʒu
        float botExpansionX;//�{�^������g��
        float botExpansionY;//�{�^������g��
        char BackBotanText[10];//�}�E�X�ɂ��J��������̐ݒ�̏󋵂�\������

        //�߂�{�^���̔��̐F
        int BabWallPaperColor;//�߂�{�^���̔��̐F
        int BabInitWallPaperColor;//�߂�{�^���̏����̐F
        int BabTouchWallPaperColor;//�߂�{�^����G���Ă��鎞�̐F

        //�}�E�X�ɂ��J������������邵�Ȃ��̃{�^���֌W
        VECTOR OnSensitivityBotan;//���x��ON�ɂ���{�^��
        VECTOR OffSensitivityBotan;//���x��OFF�ɂ���{�^��
        float SensiBotanExpansionX;//�{�^������g��
        float SensiBotanExpansionY;//�{�^������g��
        char SensitivityBotanText[40];//�}�E�X�ɂ��J��������̐ݒ�̏󋵂�\������
        char OnSensitivityBotanText[30];//�}�E�X�ɂ��J��������̐ݒ�̏󋵂�\������
        char OffSensitivityBotanText[30];//�}�E�X�ɂ��J��������̐ݒ�̏󋵂�\������

        //�}�E�X�ɂ��J������������邵�Ȃ��̃{�^���̔��̐F
        int OnSensiBotanWallPaperColor;//�߂�{�^���̔��̐F
        int OffSensiBotanWallPaperColor;//�߂�{�^���̔��̐F
        int SensiBotanRedWallPaperColor;//�߂�{�^���̏����̐F
        int SensiBotanGreenWallPaperColor;//�߂�{�^����G���Ă��鎞�̐F

        //���x�ݒ�ɕK�v�Ȓl��v�Z�l
        float SensitivityX;//X�����x
        float SensitivityY;//Y�����x
        float Sensitivity;//���x�ݒ��0.1���Ƃ̕����𒷂��ŕ\��������
        float SensitivityFixed;//���x�̍ŏ��l
        int SensitivitySplit;//���x�ݒ�̕���(�ő�12�Ƃ���������)
        int Split;//����(�����_�̌v�Z�ɕK�v��10����)
        double Calculation;//���x�ݒ�̌v�Z

        //�t�H���g�֌W
        int FontHandle;//�����̃t�H���g���L������
        int FontColor;//�����̃t�H���g�̐F
        int FontScale;//�t�H���g�̑傫��
        int FontThick;//�t�H���g�̑���
        int ValueScele;//�l�\���̍ۍ��W�����炵�Ă��傤�Ǘǂ��ʒu�ɒu�����߂̒l

        //�}�E�X�|�C���^�[�֌W
        int MousePointX;//�}�E�X�|�C���^�[�̌�X���W
        int MousePointY;//�}�E�X�|�C���^�[�̌�Y���W
        int MouseCrick;//�}�E�X�N���b�N
        int MouseCrickLog;//�}�E�X�N���b�N�̌���
        int MouseKeyCheck;
        //int SebMouseKeyCheck;
    };
private:
    DATA Option;
public:
    OPTION(class GAME* game);
    ~OPTION();
    void create();
    void init();
    void update();
    void draw();
    void nextScene();
    void ChangeScene();
};

