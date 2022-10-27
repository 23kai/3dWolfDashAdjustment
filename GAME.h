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
#define PLAYER_JUMP_POWER			100.0f //�v���C���[�̃W�����v��
#define PLAYER_GRAVITY				3.0f		// �d��
static const float ROTATE_SPEED = DX_PI_F/2;

class GAME {
public:
	//delta���i�[����ϐ�
	float DeltaTime;
	int Height;
	int Width;
	int HalfHeight;
	int HalfWidth;
	int ColorBitDepth;
private:
	//�V�X�e����@�\������ꂽ�֐����g����悤�ɂ��邽�߂̃|�C���^�ϐ�
	class SYSTEM* System;//�Q�[��
	class COLLISION* Collision;//�Փ˔���
	class CONTAINER* Container;//�R���e�i

	//�I�u�W�F�N�g������|�C���^�ϐ�
	class CAMERA* Camera;//�J����
	class FIELD* Field;//�t�B�[���h
	class CUBE* Cube;//�l�p�`
	class LINE* Line;//����
	class OBJECTS* Objects;//�I�u�W�F�N�g�x�[�X
	class WOLF* Wolf;
	//�V�[���ʂ̃|�C���^�ϐ�
	//class SCENE* Scene;
	class TITLE* Title;//�^�C�g���V�[��
	class OPTION* Option;

public:
	
	//�V�[���ԍ�
	enum SCENE_ID {
		TITLE_ID,
		STAGE_ID,
		GAME_OVER_ID,
		OPTION_ID,
		NUM_SCENES
	};
private:
	//�V�[���A�h���X
	class SCENE* Scenes[NUM_SCENES];
	SCENE_ID CurSceneId;
	int quit=1;
public:
	//�A�h���X�Q��
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
	//�֐�
	GAME();
	~GAME();
	void run();//���s
	void ChangeScene(GAME::SCENE_ID SceneId);//�V�[���ύX
	void Quit();
};