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
	//�l�擾
	game()->camera()->create();
	game()->collision()->create();
	game()->cube()->create();
	game()->line()->create();
	game()->field()->create();
	game()->wolf()->create();
}

void OBJECTS::init()
{
	//������
	game()->field()->init();
	game()->camera()->init();
}

void OBJECTS::proc()
{
	
	//�僋�[�v
	update();
	draw();
}

void OBJECTS::update()
{
	//���̏㏑��
	game()->camera()->proc();
	game()->field()->update();
	game()->wolf()->update();
}

void OBJECTS::draw()
{
	//�`��
	game()->field()->draw();
	game()->wolf()->draw();
}
