#include "STAGE.h"
#include"GAME.h"
STAGE::STAGE(class GAME* game):
	SCENE(game)
{
}

STAGE::~STAGE()
{
}

void STAGE::create()
{
	Stage = game()->container()->stage();
}

void STAGE::init()
{
	Stage.Change = 0;
	game()->objects()->create();
	game()->objects()->init();
	Stage.InitMousePointX = game()->HalfWidth;
	Stage.InitMousePointY = game()->HalfHeight;
	SetMousePoint(Stage.InitMousePointX, Stage.InitMousePointY);
}

void STAGE::update()
{
	game()->collision()->init();
	game()->objects()->proc();
	if (game()->system()->GetMouseSensitivity()) {
		SetMousePoint(Stage.InitMousePointX, Stage.InitMousePointY);
	}
	if (game()->wolf()->state() == 1) {
		ChangeScene();
	}
}

void STAGE::draw()
{
}

void STAGE::nextScene()
{
	if (Stage.Change == 1) {
		game()->field()->CollisionTerminate();
		game()->ChangeScene(GAME::GAME_OVER_ID);
	}
}

void STAGE::ChangeScene()
{
	Stage.Change = 1;
}
