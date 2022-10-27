#include "COLLISION.h"
#include"GAME.h"
COLLISION::COLLISION(class GAME* game) :
	OBJECTS(game)
{
}

COLLISION::~COLLISION()
{
	for (int i = 0; i < STAGECOLLOBJ_MAXNUM; i++) {

	}
}

void COLLISION::create()
{
	Collision = game()->container()->collision();
}

void COLLISION::init()
{
	Collision.j = 0;
	for (int i = 0; i < STAGECOLLOBJ_MAXNUM; i++) {
		Collision.ObjectNumber[i] = 0;
		Collision.HitObjectNumber[i] = 0;
		Collision.CollisionValue0[i] = VGet(0, 0, 0);
		Collision.CollisionValue1[i] = VGet(0, 0, 0);
		Collision.CollisionValue2[i] = VGet(0, 0, 0);
		Collision.HitCollisionValue0[i] = VGet(0, 0, 0);
		Collision.HitCollisionValue1[i] = VGet(0, 0, 0);
		Collision.HitCollisionValue2[i] = VGet(0, 0, 0);
		Collision.radius[i] = 0;
	}
}

void COLLISION::GetCollision(VECTOR value0, VECTOR value1, VECTOR value2,OBJECT_ID objectNumber)
{
	//配列分だけ繰り返し、空き場所があればそこに値を入れ関数を抜ける
	for (int i = 0; i < STAGECOLLOBJ_MAXNUM; i++) {
		if (Collision.ObjectNumber[i] <= 0) {
			/*
			VECTOR SaveValue;
			if (objectNumber == FLOOR_ID) {
				for (; value0.x != value1.x || value0.z != value2.z ;) {
					if (value0.z == value1.z && value0.x == value2.x) {
						break;
					}
					SaveValue = value0;
					value0 = value1;
					value1 = value2;
					value2 = SaveValue;
				}
				if (value0.z != value2.z && value0.x != value1.x) {
					SaveValue = value1;
					value1 = value2;
					value2 = SaveValue;
				}
			}
			*/
			Collision.CollisionValue0[i] = value0;
			Collision.CollisionValue1[i] = value1;
			Collision.CollisionValue2[i] = value2;
			//壁か床か
			Collision.ObjectNumber[i] = objectNumber;
			
			break;
		}
	}
}

void COLLISION::GetModelCollision(int GHandle)
{
	MV1SetupCollInfo(GHandle, -1, 8, 8, 8);
}

int COLLISION::collision(VECTOR pos, VECTOR MaxPoligon, VECTOR MinPoligon,MATRIX matrix, OBJECT_ID objectId)
{
	//当たり判定
	int discrimination = 0;
	//モデルの最大座標と最小座標を利用したZ軸方向の２点座標
	VECTOR MaxPoligonPosZ = VAdd(pos, VGet(MaxPoligon.x * matrix.m[0][0], MaxPoligon.y * matrix.m[1][1], MaxPoligon.z * matrix.m[2][2]));
	VECTOR MinPoligonPosZ = VAdd(pos, VGet(MinPoligon.x * matrix.m[0][0], MinPoligon.y * matrix.m[1][1], MinPoligon.z * matrix.m[2][2]));
	//モデルの最大座標と最小座標を利用したX軸方向の２点座標
	VECTOR MaxPoligonPosX = VAdd(pos, VGet(MaxPoligon.z * matrix.m[0][2], MaxPoligon.y * matrix.m[1][1], MaxPoligon.x * matrix.m[2][0]));
	VECTOR MinPoligonPosX = VAdd(pos, VGet(MinPoligon.z * matrix.m[0][2], MinPoligon.y * matrix.m[1][1], MinPoligon.x * matrix.m[2][0]));

	//DrawTriangle3D(VGet(MinPoligonPosZ.x, MinPoligonPosZ.y, MaxPoligonPosZ.z), MinPoligonPosZ, VGet(MaxPoligonPosZ.x, MinPoligonPosZ.y, MinPoligonPosZ.z), GetColor(0, 0, 0), TRUE);
	//DrawTriangle3D(VGet(MaxPoligonPosZ.x, MaxPoligonPosZ.y, MinPoligonPosZ.z), MaxPoligonPosZ, VGet(MinPoligonPosZ.x, MaxPoligonPosZ.y, MinPoligonPosZ.z), GetColor(255, 255, 255), TRUE);
	//
	//DrawTriangle3D(VGet(MinPoligonPosX.x, MinPoligonPosX.y, MaxPoligonPosX.z), MinPoligonPosX, VGet(MaxPoligonPosX.x, MinPoligonPosX.y, MinPoligonPosX.z), GetColor(0, 0, 0), TRUE);
	//DrawTriangle3D(VGet(MaxPoligonPosX.x, MaxPoligonPosX.y, MinPoligonPosX.z), MaxPoligonPosX, VGet(MinPoligonPosX.x, MaxPoligonPosX.y, MinPoligonPosX.z), GetColor(255, 255, 255), TRUE);
	//
	//DrawTriangle3D(VGet(MinPoligonPosX.x, MaxPoligonPosX.y, MaxPoligonPosX.z), MinPoligonPosX, VGet(MinPoligonPosX.x, MinPoligonPosX.y, MaxPoligonPosX.z), GetColor(0, 0, 0), TRUE);
	//DrawTriangle3D(VGet(MaxPoligonPosX.x, MaxPoligonPosX.y, MinPoligonPosX.z), MaxPoligonPosX, VGet(MaxPoligonPosX.x, MinPoligonPosX.y, MinPoligonPosX.z), GetColor(255, 255, 255), TRUE);
	//
	//DrawTriangle3D(VGet(MinPoligonPosZ.x, MaxPoligonPosZ.y, MaxPoligonPosZ.z), MinPoligonPosZ, VGet(MinPoligonPosZ.x, MinPoligonPosZ.y, MaxPoligonPosZ.z), GetColor(0, 0, 0), TRUE);
	//DrawTriangle3D(VGet(MaxPoligonPosZ.x, MaxPoligonPosZ.y, MinPoligonPosZ.z), MaxPoligonPosZ, VGet(MaxPoligonPosZ.x, MinPoligonPosZ.y, MinPoligonPosZ.z), GetColor(255, 255, 255), TRUE);
	
	if (objectId == STRAGHT_WALL_ID) {
		Collision.HitResult = HitCheck_Line_Triangle(VGet(MinPoligonPosZ.x, MinPoligonPosZ.y, MaxPoligonPosZ.z), MinPoligonPosZ, Collision.CollisionValue0[Collision.j], Collision.CollisionValue1[Collision.j], Collision.CollisionValue2[Collision.j]);
		DrawFormatString(0, 100, GetColor(255, 255, 255), "Hit=%d", Collision.HitResult.HitFlag);
		if (Collision.HitResult.HitFlag > 0) {
			discrimination = STRAGHT_WALL_ID;
			return discrimination;
		}
		Collision.HitResult = HitCheck_Line_Triangle(VGet(MaxPoligonPosZ.x, MinPoligonPosZ.y, MaxPoligonPosZ.z), VGet(MaxPoligonPosZ.x, MinPoligonPosZ.y, MinPoligonPosZ.z), Collision.CollisionValue0[Collision.j], Collision.CollisionValue1[Collision.j], Collision.CollisionValue2[Collision.j]);
		DrawFormatString(0, 100, GetColor(255, 255, 255), "Hit=%d", Collision.HitResult.HitFlag);
		if (Collision.HitResult.HitFlag > 0) {
			discrimination = STRAGHT_WALL_ID;
			return discrimination;
		}
		Collision.HitResult = HitCheck_Line_Triangle(MaxPoligonPosZ, VGet(MaxPoligonPosZ.x, MaxPoligonPosZ.y, MinPoligonPosZ.z), Collision.CollisionValue0[Collision.j], Collision.CollisionValue1[Collision.j], Collision.CollisionValue2[Collision.j]);
		DrawFormatString(0, 100, GetColor(255, 255, 255), "Hit=%d", Collision.HitResult.HitFlag);
		if (Collision.HitResult.HitFlag > 0) {
			discrimination = STRAGHT_WALL_ID;
			return discrimination;
		}
		Collision.HitResult = HitCheck_Line_Triangle(VGet(MinPoligonPosZ.x, MaxPoligonPosZ.y, MaxPoligonPosZ.z), VGet(MinPoligonPosZ.x, MaxPoligonPosZ.y, MinPoligonPosZ.z), Collision.CollisionValue0[Collision.j], Collision.CollisionValue1[Collision.j], Collision.CollisionValue2[Collision.j]);
		DrawFormatString(0, 100, GetColor(255, 255, 255), "Hit=%d", Collision.HitResult.HitFlag);
		if (Collision.HitResult.HitFlag > 0) {
			discrimination = STRAGHT_WALL_ID;
			return discrimination;
		}
	}

	//地面当たり判定
	if (objectId == FLOOR_ID) {
		Collision.HitResult = HitCheck_Line_Triangle(VGet(MinPoligonPosZ.x, MinPoligonPosZ.y, MaxPoligonPosZ.z), VGet(MaxPoligonPosZ.x, MaxPoligonPosZ.y, MinPoligonPosZ.z), Collision.CollisionValue0[Collision.j], Collision.CollisionValue1[Collision.j], Collision.CollisionValue2[Collision.j]);
		DrawFormatString(0,100,GetColor(255,255,255),"Hit=%d",Collision.HitResult.HitFlag);
		if (Collision.HitResult.HitFlag > 0) {
			discrimination = FLOOR_ID;
			return discrimination;
		}

		Collision.HitResult = HitCheck_Line_Triangle(VGet(MaxPoligonPosZ.x, MinPoligonPosZ.y, MinPoligonPosZ.z), VGet(MinPoligonPosZ.x, MaxPoligonPosZ.y, MinPoligonPosZ.z), Collision.CollisionValue0[Collision.j], Collision.CollisionValue1[Collision.j], Collision.CollisionValue2[Collision.j]);
		DrawFormatString(0, 100, GetColor(255, 255, 255), "Hit=%d", Collision.HitResult.HitFlag);
		if (Collision.HitResult.HitFlag > 0) {
			discrimination = FLOOR_ID;
			return discrimination;
		}

		Collision.HitResult = HitCheck_Line_Triangle(VGet(MinPoligonPosX.x, MinPoligonPosX.y, MaxPoligonPosX.z), VGet(MaxPoligonPosX.x, MaxPoligonPosX.y, MinPoligonPosX.z), Collision.CollisionValue0[Collision.j], Collision.CollisionValue1[Collision.j], Collision.CollisionValue2[Collision.j]);
		DrawFormatString(0, 100, GetColor(255, 255, 255), "Hit=%d", Collision.HitResult.HitFlag);
		if (Collision.HitResult.HitFlag > 0) {
			discrimination = FLOOR_ID;
			return discrimination;
		}

		Collision.HitResult = HitCheck_Line_Triangle(VGet(MaxPoligonPosX.x, MinPoligonPosX.y, MinPoligonPosX.z), VGet(MinPoligonPosX.x, MaxPoligonPosX.y, MinPoligonPosX.z), Collision.CollisionValue0[Collision.j], Collision.CollisionValue1[Collision.j], Collision.CollisionValue2[Collision.j]);
		DrawFormatString(0, 100, GetColor(255, 255, 255), "Hit=%d", Collision.HitResult.HitFlag);
		if (Collision.HitResult.HitFlag > 0) {
			discrimination = FLOOR_ID;
			return discrimination;
		}
	}

	//左壁当たり判定
	if (objectId == LEFT_WALL_ID) {
		Collision.HitResult = HitCheck_Line_Triangle(VGet(MaxPoligonPosX.x, MinPoligonPosX.y, MinPoligonPosX.z), VGet(MinPoligonPosX.x, MinPoligonPosX.y, MinPoligonPosX.z), Collision.CollisionValue0[Collision.j], Collision.CollisionValue1[Collision.j], Collision.CollisionValue2[Collision.j]);
		DrawFormatString(0, 120, GetColor(255, 255, 255), "Hit=%d", Collision.HitResult.HitFlag);
		if (Collision.HitResult.HitFlag > 0) {
			discrimination = LEFT_WALL_ID;
			return discrimination;
		}
		Collision.HitResult = HitCheck_Line_Triangle(VGet(MinPoligonPosX.x, MaxPoligonPosX.y, MinPoligonPosX.z), VGet(MaxPoligonPosX.x, MaxPoligonPosX.y, MinPoligonPosX.z), Collision.CollisionValue0[Collision.j], Collision.CollisionValue1[Collision.j], Collision.CollisionValue2[Collision.j]);
		DrawFormatString(0, 120, GetColor(255, 255, 255), "Hit=%d", Collision.HitResult.HitFlag);
		if (Collision.HitResult.HitFlag > 0) {
			discrimination = LEFT_WALL_ID;
			return discrimination;
		}
		Collision.HitResult = HitCheck_Line_Triangle(VGet(MaxPoligonPosX.x, MinPoligonPosX.y, MaxPoligonPosX.z), VGet(MinPoligonPosX.x, MinPoligonPosX.y, MaxPoligonPosX.z), Collision.CollisionValue0[Collision.j], Collision.CollisionValue1[Collision.j], Collision.CollisionValue2[Collision.j]);
		DrawFormatString(0, 100, GetColor(255, 255, 255), "Hit=%d", Collision.HitResult.HitFlag);
		if (Collision.HitResult.HitFlag > 0) {
			discrimination = LEFT_WALL_ID;
			return discrimination;
		}
		Collision.HitResult = HitCheck_Line_Triangle(VGet(MinPoligonPosX.x, MaxPoligonPosX.y, MaxPoligonPosX.z), VGet(MaxPoligonPosX.x, MaxPoligonPosX.y, MaxPoligonPosX.z), Collision.CollisionValue0[Collision.j], Collision.CollisionValue1[Collision.j], Collision.CollisionValue2[Collision.j]);
		DrawFormatString(0, 100, GetColor(255, 255, 255), "Hit=%d", Collision.HitResult.HitFlag);
		if (Collision.HitResult.HitFlag > 0) {
			discrimination = LEFT_WALL_ID;
			return discrimination;
		}

		Collision.HitResult = HitCheck_Line_Triangle(VGet(MaxPoligonPosZ.x, MinPoligonPosZ.y, MinPoligonPosZ.z), VGet(MinPoligonPosZ.x, MinPoligonPosZ.y, MinPoligonPosZ.z), Collision.CollisionValue0[Collision.j], Collision.CollisionValue1[Collision.j], Collision.CollisionValue2[Collision.j]);
		DrawFormatString(0, 120, GetColor(255, 255, 255), "Hit=%d", Collision.HitResult.HitFlag);
		if (Collision.HitResult.HitFlag > 0) {
			discrimination = LEFT_WALL_ID;
			return discrimination;
		}
		Collision.HitResult = HitCheck_Line_Triangle(VGet(MinPoligonPosZ.x, MaxPoligonPosZ.y, MinPoligonPosZ.z), VGet(MaxPoligonPosZ.x, MaxPoligonPosZ.y, MinPoligonPosZ.z), Collision.CollisionValue0[Collision.j], Collision.CollisionValue1[Collision.j], Collision.CollisionValue2[Collision.j]);
		DrawFormatString(0, 120, GetColor(255, 255, 255), "Hit=%d", Collision.HitResult.HitFlag);
		if (Collision.HitResult.HitFlag > 0) {
			discrimination = LEFT_WALL_ID;
			return discrimination;
		}
		Collision.HitResult = HitCheck_Line_Triangle(VGet(MaxPoligonPosZ.x, MinPoligonPosZ.y, MaxPoligonPosZ.z), VGet(MinPoligonPosZ.x, MinPoligonPosZ.y, MaxPoligonPosZ.z), Collision.CollisionValue0[Collision.j], Collision.CollisionValue1[Collision.j], Collision.CollisionValue2[Collision.j]);
		DrawFormatString(0, 100, GetColor(255, 255, 255), "Hit=%d", Collision.HitResult.HitFlag);
		if (Collision.HitResult.HitFlag > 0) {
			discrimination = LEFT_WALL_ID;
			return discrimination;
		}
		Collision.HitResult = HitCheck_Line_Triangle(VGet(MinPoligonPosZ.x, MaxPoligonPosZ.y, MaxPoligonPosZ.z), VGet(MaxPoligonPosZ.x, MaxPoligonPosZ.y, MaxPoligonPosZ.z), Collision.CollisionValue0[Collision.j], Collision.CollisionValue1[Collision.j], Collision.CollisionValue2[Collision.j]);
		DrawFormatString(0, 100, GetColor(255, 255, 255), "Hit=%d", Collision.HitResult.HitFlag);
		if (Collision.HitResult.HitFlag > 0) {
			discrimination = LEFT_WALL_ID;
			return discrimination;
		}
	}

	//左壁裏判定
	if (objectId == RED_LEFT_WALL_ID) {
		Collision.HitResult = HitCheck_Line_Triangle(VGet(MaxPoligonPosX.x, MinPoligonPosX.y, MinPoligonPosX.z), VGet(MinPoligonPosX.x, MinPoligonPosX.y, MinPoligonPosX.z), Collision.CollisionValue0[Collision.j], Collision.CollisionValue1[Collision.j], Collision.CollisionValue2[Collision.j]);
		DrawFormatString(0, 120, GetColor(255, 255, 255), "Hit=%d", Collision.HitResult.HitFlag);
		if (Collision.HitResult.HitFlag > 0) {
			discrimination = RED_LEFT_WALL_ID;
			return discrimination;
		}
		Collision.HitResult = HitCheck_Line_Triangle(VGet(MinPoligonPosX.x, MaxPoligonPosX.y, MinPoligonPosX.z), VGet(MaxPoligonPosX.x, MaxPoligonPosX.y, MinPoligonPosX.z), Collision.CollisionValue0[Collision.j], Collision.CollisionValue1[Collision.j], Collision.CollisionValue2[Collision.j]);
		DrawFormatString(0, 120, GetColor(255, 255, 255), "Hit=%d", Collision.HitResult.HitFlag);
		if (Collision.HitResult.HitFlag > 0) {
			discrimination = RED_LEFT_WALL_ID;
			return discrimination;
		}
		Collision.HitResult = HitCheck_Line_Triangle(VGet(MaxPoligonPosX.x, MinPoligonPosX.y, MaxPoligonPosX.z), VGet(MinPoligonPosX.x, MinPoligonPosX.y, MaxPoligonPosX.z), Collision.CollisionValue0[Collision.j], Collision.CollisionValue1[Collision.j], Collision.CollisionValue2[Collision.j]);
		DrawFormatString(0, 100, GetColor(255, 255, 255), "Hit=%d", Collision.HitResult.HitFlag);
		if (Collision.HitResult.HitFlag > 0) {
			discrimination = RED_LEFT_WALL_ID;
			return discrimination;
		}
		Collision.HitResult = HitCheck_Line_Triangle(VGet(MinPoligonPosX.x, MaxPoligonPosX.y, MaxPoligonPosX.z), VGet(MaxPoligonPosX.x, MaxPoligonPosX.y, MaxPoligonPosX.z), Collision.CollisionValue0[Collision.j], Collision.CollisionValue1[Collision.j], Collision.CollisionValue2[Collision.j]);
		DrawFormatString(0, 100, GetColor(255, 255, 255), "Hit=%d", Collision.HitResult.HitFlag);
		if (Collision.HitResult.HitFlag > 0) {
			discrimination = RED_LEFT_WALL_ID;
			return discrimination;
		}
		
	}

	//右壁判定
	if (objectId == RIGHT_WALL_ID) {
		Collision.HitResult = HitCheck_Line_Triangle(VGet(MaxPoligonPosX.x, MinPoligonPosX.y, MinPoligonPosX.z), VGet(MinPoligonPosX.x, MinPoligonPosX.y, MinPoligonPosX.z), Collision.CollisionValue0[Collision.j], Collision.CollisionValue1[Collision.j], Collision.CollisionValue2[Collision.j]);
		DrawFormatString(0, 120, GetColor(255, 255, 255), "Hit=%d", Collision.HitResult.HitFlag);
		if (Collision.HitResult.HitFlag > 0) {
			discrimination = RIGHT_WALL_ID;
			return discrimination;
		}
		Collision.HitResult = HitCheck_Line_Triangle(VGet(MinPoligonPosX.x, MaxPoligonPosX.y, MinPoligonPosX.z), VGet(MaxPoligonPosX.x, MaxPoligonPosX.y, MinPoligonPosX.z), Collision.CollisionValue0[Collision.j], Collision.CollisionValue1[Collision.j], Collision.CollisionValue2[Collision.j]);
		DrawFormatString(0, 120, GetColor(255, 255, 255), "Hit=%d", Collision.HitResult.HitFlag);
		if (Collision.HitResult.HitFlag > 0) {
			discrimination = RIGHT_WALL_ID;
			return discrimination;
		}
		Collision.HitResult = HitCheck_Line_Triangle(VGet(MaxPoligonPosX.x, MinPoligonPosX.y, MaxPoligonPosX.z), VGet(MinPoligonPosX.x, MinPoligonPosX.y, MaxPoligonPosX.z), Collision.CollisionValue0[Collision.j], Collision.CollisionValue1[Collision.j], Collision.CollisionValue2[Collision.j]);
		DrawFormatString(0, 100, GetColor(255, 255, 255), "Hit=%d", Collision.HitResult.HitFlag);
		if (Collision.HitResult.HitFlag > 0) {
			discrimination = RIGHT_WALL_ID;
			return discrimination;
		}
		Collision.HitResult = HitCheck_Line_Triangle(VGet(MinPoligonPosX.x, MaxPoligonPosX.y, MaxPoligonPosX.z), VGet(MaxPoligonPosX.x, MaxPoligonPosX.y, MaxPoligonPosX.z), Collision.CollisionValue0[Collision.j], Collision.CollisionValue1[Collision.j], Collision.CollisionValue2[Collision.j]);
		DrawFormatString(0, 100, GetColor(255, 255, 255), "Hit=%d", Collision.HitResult.HitFlag);
		if (Collision.HitResult.HitFlag > 0) {
			discrimination = RIGHT_WALL_ID;
			return discrimination;
		}

		Collision.HitResult = HitCheck_Line_Triangle(VGet(MaxPoligonPosZ.x, MinPoligonPosZ.y, MinPoligonPosZ.z), VGet(MinPoligonPosZ.x, MinPoligonPosZ.y, MinPoligonPosZ.z), Collision.CollisionValue0[Collision.j], Collision.CollisionValue1[Collision.j], Collision.CollisionValue2[Collision.j]);
		DrawFormatString(0, 120, GetColor(255, 255, 255), "Hit=%d", Collision.HitResult.HitFlag);
		if (Collision.HitResult.HitFlag > 0) {
			discrimination = RIGHT_WALL_ID;
			return discrimination;
		}
		Collision.HitResult = HitCheck_Line_Triangle(VGet(MinPoligonPosZ.x, MaxPoligonPosZ.y, MinPoligonPosZ.z), VGet(MaxPoligonPosZ.x, MaxPoligonPosZ.y, MinPoligonPosZ.z), Collision.CollisionValue0[Collision.j], Collision.CollisionValue1[Collision.j], Collision.CollisionValue2[Collision.j]);
		DrawFormatString(0, 120, GetColor(255, 255, 255), "Hit=%d", Collision.HitResult.HitFlag);
		if (Collision.HitResult.HitFlag > 0) {
			discrimination = RIGHT_WALL_ID;
			return discrimination;
		}
		Collision.HitResult = HitCheck_Line_Triangle(VGet(MaxPoligonPosZ.x, MinPoligonPosZ.y, MaxPoligonPosZ.z), VGet(MinPoligonPosZ.x, MinPoligonPosZ.y, MaxPoligonPosZ.z), Collision.CollisionValue0[Collision.j], Collision.CollisionValue1[Collision.j], Collision.CollisionValue2[Collision.j]);
		DrawFormatString(0, 100, GetColor(255, 255, 255), "Hit=%d", Collision.HitResult.HitFlag);
		if (Collision.HitResult.HitFlag > 0) {
			discrimination = RIGHT_WALL_ID;
			return discrimination;
		}
		Collision.HitResult = HitCheck_Line_Triangle(VGet(MinPoligonPosZ.x, MaxPoligonPosZ.y, MaxPoligonPosZ.z), VGet(MaxPoligonPosZ.x, MaxPoligonPosZ.y, MaxPoligonPosZ.z), Collision.CollisionValue0[Collision.j], Collision.CollisionValue1[Collision.j], Collision.CollisionValue2[Collision.j]);
		DrawFormatString(0, 100, GetColor(255, 255, 255), "Hit=%d", Collision.HitResult.HitFlag);
		if (Collision.HitResult.HitFlag > 0) {
			discrimination = RIGHT_WALL_ID;
			return discrimination;
		}
	}

	//右壁裏判定
	if (objectId == RED_RIGHT_WALL_ID) {
		Collision.HitResult = HitCheck_Line_Triangle(VGet(MaxPoligonPosX.x, MinPoligonPosX.y, MinPoligonPosX.z), VGet(MinPoligonPosX.x, MinPoligonPosX.y, MinPoligonPosX.z), Collision.CollisionValue0[Collision.j], Collision.CollisionValue1[Collision.j], Collision.CollisionValue2[Collision.j]);
		DrawFormatString(0, 120, GetColor(255, 255, 255), "Hit=%d", Collision.HitResult.HitFlag);
		if (Collision.HitResult.HitFlag > 0) {
			discrimination = RED_RIGHT_WALL_ID;
			return discrimination;
		}
		Collision.HitResult = HitCheck_Line_Triangle(VGet(MinPoligonPosX.x, MaxPoligonPosX.y, MinPoligonPosX.z), VGet(MaxPoligonPosX.x, MaxPoligonPosX.y, MinPoligonPosX.z), Collision.CollisionValue0[Collision.j], Collision.CollisionValue1[Collision.j], Collision.CollisionValue2[Collision.j]);
		DrawFormatString(0, 120, GetColor(255, 255, 255), "Hit=%d", Collision.HitResult.HitFlag);
		if (Collision.HitResult.HitFlag > 0) {
			discrimination = RED_RIGHT_WALL_ID;
			return discrimination;
		}
		Collision.HitResult = HitCheck_Line_Triangle(VGet(MaxPoligonPosX.x, MinPoligonPosX.y, MaxPoligonPosX.z), VGet(MinPoligonPosX.x, MinPoligonPosX.y, MaxPoligonPosX.z), Collision.CollisionValue0[Collision.j], Collision.CollisionValue1[Collision.j], Collision.CollisionValue2[Collision.j]);
		DrawFormatString(0, 100, GetColor(255, 255, 255), "Hit=%d", Collision.HitResult.HitFlag);
		if (Collision.HitResult.HitFlag > 0) {
			discrimination = RED_RIGHT_WALL_ID;
			return discrimination;
		}
		Collision.HitResult = HitCheck_Line_Triangle(VGet(MinPoligonPosX.x, MaxPoligonPosX.y, MaxPoligonPosX.z), VGet(MaxPoligonPosX.x, MaxPoligonPosX.y, MaxPoligonPosX.z), Collision.CollisionValue0[Collision.j], Collision.CollisionValue1[Collision.j], Collision.CollisionValue2[Collision.j]);
		DrawFormatString(0, 100, GetColor(255, 255, 255), "Hit=%d", Collision.HitResult.HitFlag);
		if (Collision.HitResult.HitFlag > 0) {
			discrimination = RED_RIGHT_WALL_ID;
			return discrimination;
		}
	}
	//一周するためのゲートの当たり判定
	if (objectId == GATE_ID) {
		Collision.CollisionExpansion = VGet(Collision.CollisionValue0[Collision.j].x , Collision.CollisionValue0[Collision.j].y, Collision.CollisionValue0[Collision.j].z+10);
		if (MaxPoligonPosZ.x >= Collision.CollisionValue0[Collision.j].x && MinPoligonPosZ.x < Collision.CollisionValue2[Collision.j].x) {
			if (MaxPoligonPosZ.y > Collision.CollisionValue0[Collision.j].y && MinPoligonPosZ.y < Collision.CollisionValue2[Collision.j].y) {
				if (MaxPoligonPosZ.z > Collision.CollisionValue0[Collision.j].z && MaxPoligonPosZ.z < Collision.CollisionExpansion.z) {
					discrimination = GATE_ID;
				}
				else if (MinPoligonPosZ.z>Collision.CollisionValue0[Collision.j].z && MinPoligonPosZ.z<Collision.CollisionExpansion.z) {
					discrimination = GATE_ID;
				}
			}
		}
	}
	
	return discrimination;
}

VECTOR COLLISION::HitCollision()
{
	return Collision.HitResult.Position;
}

VECTOR COLLISION::CollisionValue(int i)
{
	//形を形成する３点を返す
	switch (i) {
	case 1:return Collision.CollisionValue1[Collision.j-1];

	case 2:return Collision.CollisionValue2[Collision.j-1];

	default:break;
	}
	return Collision.CollisionValue0[Collision.j-1];
}
