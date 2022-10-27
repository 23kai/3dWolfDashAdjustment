#include "LINE.h"
#include"GAME.h"
LINE::LINE(class GAME* game):
	OBJECTS(game)
{
}

LINE::~LINE()
{
}

void LINE::create()
{
	Line = game()->container()->line();
	init();
}

void LINE::init()
{
	Line.Color = GetColor(Line.ColorR, Line.ColorG, Line.ColorB);
}

void LINE::CreateSquareLine(VECTOR startPos, VECTOR endPos)
{
	VECTOR StartUp, EndDown;

	StartUp.x = startPos.x;
	StartUp.y = endPos.y;
	StartUp.z = startPos.z;

	EndDown.x = endPos.x;
	EndDown.y = startPos.y;
	EndDown.z = endPos.z;

	DrawLine3D(startPos, StartUp, Line.Color);
	DrawLine3D(startPos, EndDown, Line.Color);
	DrawLine3D(endPos, StartUp, Line.Color);
	DrawLine3D(endPos, EndDown, Line.Color);
}
