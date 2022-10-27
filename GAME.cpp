#include "GAME.h"
#include"DxLib.h"
#include"OBJECTS.h"
GAME::GAME() {
	//���I�m��
	System = new SYSTEM(this);
	Container = new CONTAINER;

	Collision = new COLLISION(this);
	Camera = new CAMERA(this);
	Field = new FIELD(this);
	Objects = new OBJECTS(this);
	Cube = new CUBE(this);
	Line = new LINE(this);
	Wolf = new WOLF(this);

	Scenes[TITLE_ID] = new TITLE(this);
	Scenes[STAGE_ID] = new STAGE(this);
	Scenes[GAME_OVER_ID] = new GAME_OVER(this);
	Scenes[OPTION_ID] = new OPTION(this);
	Title = new TITLE(this);
	CurSceneId = TITLE_ID;
}
GAME::~GAME() {
	//���������
	delete System;
	delete Container;
	delete Collision;
	delete Camera;
	delete Field;
	delete Objects;
	delete Cube;
	delete Line;
	delete Wolf;
	for (int i = 0; i < NUM_SCENES; i++) {
		delete Scenes[i];
	}
	delete Title;
}
void GAME::run() {
	GetScreenState(&Width, &Height, &ColorBitDepth);
	HalfHeight = Height / 2;
	HalfWidth = Width / 2;
	//��������I�u�W�F�N�g�쐬
	Container->load();
	System->init();
	System->create();
	Scenes[TITLE_ID]->create();
	Scenes[STAGE_ID]->create();
	Scenes[GAME_OVER_ID]->create();
	Scenes[OPTION_ID]->create();
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF);

	//���[�v
	while (!ProcessMessage() && CheckHitKey(KEY_INPUT_ESCAPE) == 0 && !ScreenFlip() && quit) {
		ClearDrawScreen();
		Scenes[CurSceneId]->proc();
		DeltaTime = System->delta();
	}
}

void GAME::ChangeScene(GAME::SCENE_ID SceneId)
{
	CurSceneId = SceneId;
	Scenes[CurSceneId]->init();
}

void GAME::Quit()
{
	quit = 0;
}
