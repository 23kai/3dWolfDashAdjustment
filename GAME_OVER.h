#pragma once
#include "SCENE.h"
#include"DxLib.h"
class GAME_OVER :
    public SCENE
{
public:
    struct DATA {
        //���ꂼ��̏��(0or1)
        int Restart;//���X�^�[�g�{�^��
        int Quit;//�I���{�^��
        int Title;//�^�C�g���{�^��
        //�X�R�A
        int Score;//�X�R�A�l
        VECTOR ScoreDraw;//�X�R�A�\���ʒu
        //�{�^���֌W
        VECTOR Stb;//���X�^�[�g�{�^���ʒu
        VECTOR Qub;//�I���{�^���ʒu
        VECTOR Tib;//�^�C�g���{�^���ʒu
        float botExpansionX;//�{�^������g��
        float botExpansionY;//�{�^������g��
        //�t�H���g��ǎ�
        int FontHandle;//�t�H���g
        int FontScale;//�t�H���g�̑傫��
        int FontThick;//�t�H���g�̑���
        int FontColor;//�t�H���g�̐F
        int StbWallpaperColor;//�X�^�[�g�{�^���̔��̐F
        int TibWallpaperColor;//�^�C�g����ʃ{�^���̔��̐F
        int QubWallpaperColor;//����{�^���̔��̐F
        int InitWallpaperColor;//�ʏ�F
        int TouchWallpaperColor;//�G��Ă��鎞�̐F
        char ScoreText[10];//�X�R�A�����\��
        char RestartText[20];//���X�^�[�g�����\��
        char QuitText[20];//���镶���\��
        char TitleText[20];//�^�C�g�������\��
        //�}�E�X�|�C���^�[�֌W
        int MousePointX;//X���̃|�C���^�[�̈ʒu
        int MousePointY;//Y���̃|�C���^�[�̈ʒu
        int MouseCrick;//�}�E�X�N���b�N���
        int MouseCrickLog;//�}�E�X�N���b�N�̍Ō�̏��
        int RestartMouseKeyCheck;//���X�^�[�g�{�^����������Ă�����
        int TitleMouseKeyCheck;//�^�C�g���{�^����������Ă�����
        int QuitMouseKeyCheck;//����{�^����������Ă�����

    };
private:
    DATA Over;
public:
    GAME_OVER(class GAME* game);
    ~GAME_OVER();
    void virtual create();//�l�擾
    void virtual init();//������
    void virtual update();//�㏑��
    void virtual draw();//�`��
    void virtual nextScene();//���̃V�[����
};

