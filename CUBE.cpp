#include "CUBE.h"
#include"GAME.h"
CUBE::CUBE(class GAME* game):
	OBJECTS(game)
{
}

CUBE::~CUBE()
{
}

void CUBE::create()
{
	Cube = game()->container()->cube();
}

void CUBE::update()
{
	
}

void CUBE::draw()
{

}

void CUBE::CreateSquare(VECTOR pos, VECTOR pos1, int color,OBJECT_ID objectId)
{
	VECTOR pos2, pos3;
	pos2.x = pos.x;
	pos2.y = pos1.y;
	pos2.z = pos.z;
	
	pos3.x = pos1.x;
	pos3.y = pos.y;
	pos3.z = pos1.z;

	DrawTriangle3D(pos, pos2, pos1, color, TRUE);
	DrawTriangle3D(pos, pos3, pos1, color, TRUE);
	game()->line()->CreateSquareLine(pos, pos1);

	game()->collision()->GetCollision(pos, pos2, pos1,objectId);
	game()->collision()->GetCollision(pos, pos3, pos1,objectId);
}

void CUBE::CreateCube(VECTOR start, VECTOR end,int color,OBJECT_ID objectId)
{
	
	//左面
	DrawTriangle3D(start, VGet(start.x,end.y,start.z), VGet(start.x,end.y,end.z), color, TRUE);
	DrawTriangle3D(start, VGet(start.x,start.y,end.z), VGet(start.x,end.y,end.z), color, TRUE);
	game()->line()->CreateSquareLine(start, VGet(start.x,end.y,end.z));

	//右面
	DrawTriangle3D(end, VGet(end.x,start.y,end.z), VGet(end.x,start.y,start.z), color, TRUE);
	DrawTriangle3D(end, VGet(end.x,end.y,start.z), VGet(end.x,start.y,start.z), color, TRUE);
	game()->line()->CreateSquareLine(end, VGet(end.x,start.y,start.z));

	//手前面
	DrawTriangle3D(start, VGet(start.x,end.y,start.z), VGet(end.x,end.y,start.z), color, TRUE);
	DrawTriangle3D(start, VGet(end.x,start.y,start.z), VGet(end.x,end.y,start.z), color, TRUE);
	game()->line()->CreateSquareLine(start, VGet(end.x,end.y,start.z));

	//奥面
	DrawTriangle3D(end, VGet(start.x,end.y,end.z), VGet(start.x,start.y,end.z), color, TRUE);
	DrawTriangle3D(end, VGet(end.x,start.y,end.z), VGet(start.x,start.y,end.z), color, TRUE);
	game()->line()->CreateSquareLine(end, VGet(start.x,start.y,end.z));

	//表面
	//DrawTriangle3D(VGet(start.x,end.y,start.z), VGet(end.x,end.y,start.z), end, color, TRUE);
	//DrawTriangle3D(VGet(start.x,end.y,start.z), VGet(start.x,end.y,end.z), end, color, TRUE);

	//裏面
	DrawTriangle3D(start, VGet(end.x,start.y,start.z), end, color, TRUE);
	DrawTriangle3D(start, VGet(start.x,start.y,end.z), end, color, TRUE);

	CollisionOnly(start, end, objectId);
}

void CUBE::CollisionOnly(VECTOR pos, VECTOR pos1,OBJECT_ID objectId)
{
	/*
	//左面当たり判定
	game()->collision()->GetCollision(pos, VGet(pos.x,pos1.y,pos.z), VGet(pos.x,pos1.y,pos1.z));
	game()->collision()->GetCollision(pos, VGet(pos.x,pos.y,pos1.z), VGet(pos.x,pos1.y,pos1.z));
	//右面当たり判定
	game()->collision()->GetCollision(pos1, VGet(pos1.x,pos.y,pos1.z), VGet(pos1.x,pos.y,pos.z));
	game()->collision()->GetCollision(pos1, VGet(pos1.x,pos1.y,pos.z), VGet(pos1.x,pos.y,pos.z));
	//手前面当たり判定
	game()->collision()->GetCollision(pos, VGet(pos.x,pos1.y,pos.z), VGet(pos1.x,pos1.y,pos.z));
	game()->collision()->GetCollision(pos, VGet(pos1.x,pos.y,pos.z), VGet(pos1.x,pos1.y,pos.z));
	//奥面当たり判定
	game()->collision()->GetCollision(pos1, VGet(pos.x,pos1.y,pos1.z), VGet(pos.x,pos.y,pos1.z));
	game()->collision()->GetCollision(pos1, VGet(pos1.x,pos.y,pos1.z), VGet(pos.x,pos.y,pos1.z));
	//表面当たり判定
	game()->collision()->GetCollision(VGet(pos.x,pos1.y,pos.z), VGet(pos1.x,pos1.y,pos.z), pos1);
	game()->collision()->GetCollision(VGet(pos.x,pos1.y,pos.z), VGet(pos.x,pos1.y,pos1.z), pos1);
	*/

	//裏面当たり判定
	game()->collision()->GetCollision(pos, VGet(pos1.x,pos1.y,pos.z), pos1, objectId);
	game()->collision()->GetCollision(pos, VGet(pos.x,pos.y,pos1.z), pos1, objectId);
}
