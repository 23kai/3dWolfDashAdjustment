#pragma once
#include "GAME_OBJECT.h"
//#include"DxLib.h"
class SCENE :
    public GAME_OBJECT
{
public:
    SCENE(class GAME* game);
    ~SCENE();
    void virtual create();
    void virtual init();
    void virtual proc();
    void virtual update();
    void virtual draw();
    void virtual nextScene();
};