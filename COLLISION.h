#pragma once
#include"OBJECTS.h"
#include"DxLib.h"

#define STAGECOLLOBJ_MAXNUM			512		// 追加のコリジョンオブジェクトの最大数

class COLLISION :
	public OBJECTS
{
public:
	struct DATA {
		//オブジェクトの番号
		int ObjectNumber[STAGECOLLOBJ_MAXNUM];
		int HitObjectNumber[STAGECOLLOBJ_MAXNUM];
		//球体の半径
		float radius[STAGECOLLOBJ_MAXNUM];
		//オブジェクトの座標値
		VECTOR CollisionValue0[STAGECOLLOBJ_MAXNUM];
		VECTOR CollisionValue1[STAGECOLLOBJ_MAXNUM];
		VECTOR CollisionValue2[STAGECOLLOBJ_MAXNUM];
		VECTOR HitCollisionValue0[STAGECOLLOBJ_MAXNUM];
		VECTOR HitCollisionValue1[STAGECOLLOBJ_MAXNUM];
		VECTOR HitCollisionValue2[STAGECOLLOBJ_MAXNUM];
		VECTOR CollisionExpansion;//当たり判定拡張
		float Expansion;//当たり判定を広げる値
		HITRESULT_LINE HitResult;
		int j;//汎用ループ値
	};
private:
	DATA Collision;
public:
	COLLISION(class GAME* game);
	~COLLISION();
	void create();
	void init();//初期化
	void GetCollision(VECTOR value0, VECTOR value1, VECTOR value2,OBJECT_ID ObjectNumber);//物体を形成する３つの頂点を一か所に格納するための関数
	void GetModelCollision(int GHandle);//モデルの当たり判定を格納する関数
	int collision(VECTOR pos,VECTOR MaxPoligon,VECTOR MinPoligon,MATRIX matrix,OBJECT_ID objectId);//当たり判定値を返す関数（グラフィックハンドル,オブジェクトの番号,forによる順番)
	VECTOR HitCollision();//当たり判定値を返す関数（グラフィックハンドル,オブジェクトの番号,forによる順番)
	int collisionStop(int i) { return Collision.ObjectNumber[i]; }//ifやfor文の判定に入れて中身のオブジェクト番号を返す 使用例(for(int i=0;collisionStop(i)!=0;i++))　if(CollisionStop(i)==FLOOR_ID)
	void collisionNext() { Collision.j++; }
	VECTOR CollisionValue(int i);//三角形を形成する3つの点を参照で返す

};
