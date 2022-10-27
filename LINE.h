#pragma once
#include "OBJECTS.h"
#include"Dxlib.h"
class LINE :
    public OBJECTS
{
public:
    struct DATA {
        VECTOR PosStart;
        VECTOR PosEnd;
        int ColorR;
        int ColorG;
        int ColorB;
        int Color;
    };
private:
    DATA Line;
public:
    LINE(class GAME* game);
    ~LINE();
    void create();
    void init();
    void CreateSquareLine(VECTOR startPos, VECTOR EndPos);
};

