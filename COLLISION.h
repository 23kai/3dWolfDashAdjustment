#pragma once
#include"OBJECTS.h"
#include"DxLib.h"

#define STAGECOLLOBJ_MAXNUM			512		// �ǉ��̃R���W�����I�u�W�F�N�g�̍ő吔

class COLLISION :
	public OBJECTS
{
public:
	struct DATA {
		//�I�u�W�F�N�g�̔ԍ�
		int ObjectNumber[STAGECOLLOBJ_MAXNUM];
		int HitObjectNumber[STAGECOLLOBJ_MAXNUM];
		//���̂̔��a
		float radius[STAGECOLLOBJ_MAXNUM];
		//�I�u�W�F�N�g�̍��W�l
		VECTOR CollisionValue0[STAGECOLLOBJ_MAXNUM];
		VECTOR CollisionValue1[STAGECOLLOBJ_MAXNUM];
		VECTOR CollisionValue2[STAGECOLLOBJ_MAXNUM];
		VECTOR HitCollisionValue0[STAGECOLLOBJ_MAXNUM];
		VECTOR HitCollisionValue1[STAGECOLLOBJ_MAXNUM];
		VECTOR HitCollisionValue2[STAGECOLLOBJ_MAXNUM];
		VECTOR CollisionExpansion;//�����蔻��g��
		float Expansion;//�����蔻����L����l
		HITRESULT_LINE HitResult;
		int j;//�ėp���[�v�l
	};
private:
	DATA Collision;
public:
	COLLISION(class GAME* game);
	~COLLISION();
	void create();
	void init();//������
	void GetCollision(VECTOR value0, VECTOR value1, VECTOR value2,OBJECT_ID ObjectNumber);//���̂��`������R�̒��_���ꂩ���Ɋi�[���邽�߂̊֐�
	void GetModelCollision(int GHandle);//���f���̓����蔻����i�[����֐�
	int collision(VECTOR pos,VECTOR MaxPoligon,VECTOR MinPoligon,MATRIX matrix,OBJECT_ID objectId);//�����蔻��l��Ԃ��֐��i�O���t�B�b�N�n���h��,�I�u�W�F�N�g�̔ԍ�,for�ɂ�鏇��)
	VECTOR HitCollision();//�����蔻��l��Ԃ��֐��i�O���t�B�b�N�n���h��,�I�u�W�F�N�g�̔ԍ�,for�ɂ�鏇��)
	int collisionStop(int i) { return Collision.ObjectNumber[i]; }//if��for���̔���ɓ���Ē��g�̃I�u�W�F�N�g�ԍ���Ԃ� �g�p��(for(int i=0;collisionStop(i)!=0;i++))�@if(CollisionStop(i)==FLOOR_ID)
	void collisionNext() { Collision.j++; }
	VECTOR CollisionValue(int i);//�O�p�`���`������3�̓_���Q�ƂŕԂ�

};
