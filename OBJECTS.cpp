#include "OBJECTS.h"
#include"GAME.h"
OBJECTS::OBJECTS(class GAME* game) :
	GAME_OBJECT(game)
{
}

OBJECTS::~OBJECTS()
{
}

void OBJECTS::create()
{
	//値取得
	game()->camera()->create();
	game()->collision()->create();
	game()->cube()->create();
	game()->line()->create();
	game()->field()->create();
	game()->wolf()->create();
}

void OBJECTS::init()
{
	//初期化
	game()->field()->init();
	game()->camera()->init();
}

void OBJECTS::proc()
{
	
	//主ループ
	update();
	draw();
}

void OBJECTS::update()
{
	//情報の上書き
	game()->camera()->proc();
	game()->field()->update();
	game()->wolf()->update();
}

void OBJECTS::draw()
{
	//描画
	game()->field()->draw();
	game()->wolf()->draw();
}
