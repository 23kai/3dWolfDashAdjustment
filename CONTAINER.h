#pragma once
#include"TITLE.h"
#include"SYSTEM.h"
#include"COLLISION.h"
#include"CAMERA.h"
#include"FIELD.h"
#include"CUBE.h"
#include"LINE.h"
#include"WOLF.h"
#include"STAGE.h"
#include"GAME_OVER.h"
#include"OPTION.h"
class CONTAINER
{
	//各データ構造体変数
	struct DATA {
		TITLE::DATA title;
		STAGE::DATA stage;
		GAME_OVER::DATA gameover;
		OPTION::DATA option;
		SYSTEM::DATA system;

		CAMERA::DATA camera;
		COLLISION::DATA collision;
		FIELD::DATA field;
		CUBE::DATA cube;
		LINE::DATA line;
		WOLF::DATA wolf;
	};
	DATA Data;
public:
	~CONTAINER();
	void load();
	void setdata();
	void loadGraphic();
	//値の取り出し関数
	const TITLE::DATA& title() { return Data.title; }
	const STAGE::DATA& stage() { return Data.stage; }
	const GAME_OVER::DATA& gameover() { return Data.gameover; }
	const OPTION::DATA& option() { return Data.option; }
	const SYSTEM::DATA& system() { return Data.system; }

	const CAMERA::DATA& camera() { return Data.camera; }
	const COLLISION::DATA& collision() { return Data.collision; }
	const FIELD::DATA& field() { return Data.field; }
	const CUBE::DATA& cube() { return Data.cube; }
	const LINE::DATA& line() { return Data.line; }
	const WOLF::DATA& wolf() { return Data.wolf; }
};

