#pragma once
#include"SYSTEM.h"
#include"COLLISION.h"
#include"CONTAINER.h"

#include"CAMERA.h"
#include"FIELD.h"
#include"CUBE.h"
#include"LINE.h"
#include"WOLF.h"

#include"SCENE.h"
#include"TITLE.h"
#include"STAGE.h"
#include"OPTION.h"
#define PLAYER_JUMP_POWER			100.0f //プレイヤーのジャンプ力
#define PLAYER_GRAVITY				3.0f		// 重力
static const float ROTATE_SPEED = DX_PI_F/2;

class GAME {
public:
	//deltaを格納する変数
	float DeltaTime;
	int Height;
	int Width;
	int HalfHeight;
	int HalfWidth;
	int ColorBitDepth;
private:
	//システムや機能等を入れた関数を使えるようにするためのポインタ変数
	class SYSTEM* System;//ゲーム
	class COLLISION* Collision;//衝突判定
	class CONTAINER* Container;//コンテナ

	//オブジェクトを入れるポインタ変数
	class CAMERA* Camera;//カメラ
	class FIELD* Field;//フィールド
	class CUBE* Cube;//四角形
	class LINE* Line;//線分
	class OBJECTS* Objects;//オブジェクトベース
	class WOLF* Wolf;
	//シーン別のポインタ変数
	//class SCENE* Scene;
	class TITLE* Title;//タイトルシーン
	class OPTION* Option;

public:
	
	//シーン番号
	enum SCENE_ID {
		TITLE_ID,
		STAGE_ID,
		GAME_OVER_ID,
		OPTION_ID,
		NUM_SCENES
	};
private:
	//シーンアドレス
	class SCENE* Scenes[NUM_SCENES];
	SCENE_ID CurSceneId;
	int quit=1;
public:
	//アドレス参照
	class SYSTEM* system() { return System; }
	class COLLISION* collision() { return Collision; }
	class CONTAINER* container() { return Container; }

	class CAMERA* camera() { return Camera; }
	class FIELD* field() { return Field; }
	class CUBE* cube() { return Cube; }
	class LINE* line() { return Line; }
	class OBJECTS* objects() { return Objects; }
	class WOLF* wolf() { return Wolf; }

	class TITLE* title() { return Title; }
	class OPTION* option() { return Option; }
public:
	//関数
	GAME();
	~GAME();
	void run();//実行
	void ChangeScene(GAME::SCENE_ID SceneId);//シーン変更
	void Quit();
};