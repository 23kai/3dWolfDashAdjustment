#pragma once
#include "SCENE.h"
#include"DxLib.h"
//#include"GAME.h"
class TITLE :
    public SCENE
{
public:
    struct DATA {
        int Start;//�X�^�[�g�{�^��
        int Quit;//�I���{�^��
        int Option;
        VECTOR Stb;//�X�^�[�g�{�^���ʒu
        float botExpansionX;//�{�^������g��
        float botExpansionY;//�{�^������g��
        VECTOR Qub;//�I���{�^���ʒu
        VECTOR Opb;//�I�v�V�����{�^���ʒu
        //�t�H���g�֌W
        int FontHandle;//�t�H���g
        int FontColor;//�t�H���g�J���[
        //���F
        int StbWallpaperColor;//�X�^�[�g�{�^���̔��F
        int QubWallpaperColor;//����{�^���̔��F
        int OpbWallpaperColor;//�I�v�V�����{�^���̔��F
        int InitWallpaperColor;//���F�̏����F
        int TouchWallpaperColor;//�G���Ă���Ƃ��̔��F
        //�}�E�X�|�C���^�[�֌W
        int MousePointX;//X���̃}�E�X�|�C���^�[���W
        int MousePointY;//Y���̃}�E�X�|�C���^�[���W
        int MouseCrick;//�}�E�X�N���b�N
        int MouseCrickLog;//�}�E�X�N���b�N�̍ŏI���
        //���ꂼ��̔��̏��
        int StartMouseKeyCheck;//�X�^�[�g�{�^����������Ă�����
        int QuitMouseKeyCheck;//�߂�{�^����������Ă�����
        int OptionMouseKeyCheck;//�I�v�V�����{�^����������Ă�����

    };
private:
    DATA Title;
public:
    TITLE(class GAME* game);
    ~TITLE();
    void create();//�l�擾
    void init();//������
    void update();//�㏑��
    void draw();//�`��
    void nextScene();//���̃V�[��
    int quit() { return Title.Quit; }//����{�^���������ꂽ�Ƃ�
};

