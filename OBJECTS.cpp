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
	//’læ“¾
	game()->camera()->create();
	game()->collision()->create();
	game()->cube()->create();
	game()->line()->create();
	game()->field()->create();
	game()->wolf()->create();
}

void OBJECTS::init()
{
	//‰Šú‰»
	game()->field()->init();
	game()->camera()->init();
}

void OBJECTS::proc()
{
	
	//åƒ‹[ƒv
	update();
	draw();
}

void OBJECTS::update()
{
	//î•ñ‚Ìã‘‚«
	game()->camera()->proc();
	game()->field()->update();
	game()->wolf()->update();
}

void OBJECTS::draw()
{
	//•`‰æ
	game()->field()->draw();
	game()->wolf()->draw();
}
