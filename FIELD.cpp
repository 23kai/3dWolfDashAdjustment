#include "FIELD.h"
#include"GAME.h"
#include<math.h>
FIELD::FIELD(class GAME* game) :
	OBJECTS(game)
{
}

FIELD::~FIELD()
{
}

void FIELD::create()
{
	Field = game()->container()->field();
}

void FIELD::init()
{
	//初期化
	MV1SetupReferenceMesh(Field.GraphicHundle, 0, TRUE);
	Field.FramePos=MV1GetFramePosition(Field.GraphicHundle, 0);
	Field.pos = VSub(Field.pos, Field.FramePos);
	Field.Poligon = MV1GetReferenceMesh(Field.GraphicHundle, 0, TRUE);
	Field.MinPoligonPos = VGet(fabsf(Field.Poligon.MinPosition.x), fabsf(Field.Poligon.MinPosition.y), fabsf(Field.Poligon.MinPosition.z));
	Field.MaxPoligonPos = VGet(fabsf(Field.Poligon.MaxPosition.x), fabsf(Field.Poligon.MaxPosition.y), fabsf(Field.Poligon.MaxPosition.z));
	Field.AddMinMaxPoligonPos = VAdd(Field.MinPoligonPos, Field.MaxPoligonPos);
	strcpy_s(Field.CopyMapTile, Field.MapTile);
	loop();
}

void FIELD::update()
{

	Field.p = 0;
	collision();
}

void FIELD::draw()
{
	for (int i = 0; i < Field.p; i++) {
		if (Field.MapTile[i] != '0'&& Field.MapTile[i] != '\n'&& Field.MapTile[i] != '\0'&& Field.MapTile[i] != '4'&& Field.MapTile[i] != '5') {
			MV1DrawModel(Field.CopyGraphicHandle[i]);//モデルの描画
		}
		else if (Field.MapTile[i] == '4' || Field.MapTile[i] == '5') {
			MV1DrawModel(Field.CopyGraphicHandle[i]);//モデルの描画
			i++;
			MV1DrawModel(Field.CopyGraphicHandle[i]);//モデルの描画
		}
	}
}

void FIELD::collision()
{
	float radius = game()->wolf()->radius();
	VECTOR pos = game()->wolf()->target();
	
	//タイルの敷き詰め
	//

	for (int ZTile = 0; Field.MapTile[Field.p] != '\0'; ZTile++) {

		for (int XTile=0; Field.MapTile[Field.p] != '\n'; XTile++) {
			if (Field.MapTile[Field.p] == '1') {
				Field.CopyGraphicPos[Field.p] = VGet(Field.pos.x + (Field.AddMinMaxPoligonPos.x * XTile), Field.pos.y, Field.pos.z + (Field.AddMinMaxPoligonPos.z * ZTile));
				MV1SetPosition(Field.CopyGraphicHandle[Field.p], Field.CopyGraphicPos[Field.p]);//モデルの座標セット
				game()->cube()->CreateCube( VSub(Field.CopyGraphicPos[Field.p], Field.MinPoligonPos),VAdd(Field.CopyGraphicPos[Field.p], Field.MaxPoligonPos),GetColor(0,0,0),FLOOR_ID);
				Field.p++;
			}
			else if (Field.MapTile[Field.p] == '2') {
				VECTOR Rotate,Rotate1;
				Field.CopyGraphicPos[Field.p] = VGet(Field.AddMinMaxPoligonPos.x * XTile- (Field.FramePos.x - Field.MaxPoligonPos.x), Field.pos.y-Field.FramePos.x - (Field.FramePos.x - Field.MaxPoligonPos.x), (Field.AddMinMaxPoligonPos.z * ZTile)-Field.FramePos.z);
				Rotate = VAdd(VTransform(VAdd(Field.FramePos, Field.MaxPoligonPos), MGetRotZ(Field.radian)), VGet(Field.CopyGraphicPos[Field.p].x, Field.CopyGraphicPos[Field.p].y - Field.FramePos.x , Field.CopyGraphicPos[Field.p].z - Field.FramePos.z));
				Rotate1 = VAdd(VTransform(VSub(Field.FramePos, Field.MinPoligonPos), MGetRotZ(Field.radian)), VGet(Field.CopyGraphicPos[Field.p].x, Field.CopyGraphicPos[Field.p].y - Field.FramePos.x , Field.CopyGraphicPos[Field.p].z - Field.FramePos.z));
				MV1SetRotationXYZ(Field.CopyGraphicHandle[Field.p], VGet(0.0f, 0.0f, Field.radian));
				MV1SetPosition(Field.CopyGraphicHandle[Field.p], Field.CopyGraphicPos[Field.p]);//モデルの座標セット
				game()->cube()->CreateCube(Rotate,Rotate1,Field.LeftWallColor,LEFT_WALL_ID);
				game()->cube()->CreateCube(VGet(Rotate.x - 1, Rotate.y, Rotate.z), VGet(Rotate1.x - 1, Rotate1.y, Rotate1.z), Field.RedWallColor, RED_LEFT_WALL_ID);
				Field.p++;
			}
			else if (Field.MapTile[Field.p] == '3') {
				VECTOR Rotate, Rotate1;
				Field.CopyGraphicPos[Field.p] = VGet(Field.AddMinMaxPoligonPos.x * XTile + (Field.FramePos.x - Field.MaxPoligonPos.x), Field.pos.y - Field.FramePos.x - (Field.FramePos.x - Field.MaxPoligonPos.x), (Field.AddMinMaxPoligonPos.z * ZTile) - Field.FramePos.z);
				Rotate = VAdd(VTransform(VAdd(Field.FramePos, Field.MaxPoligonPos), MGetRotZ(Field.radian)), VGet(Field.CopyGraphicPos[Field.p].x, Field.CopyGraphicPos[Field.p].y - Field.FramePos.x, Field.CopyGraphicPos[Field.p].z - Field.FramePos.z));
				Rotate1 = VAdd(VTransform(VSub(Field.FramePos, Field.MinPoligonPos), MGetRotZ(Field.radian)), VGet(Field.CopyGraphicPos[Field.p].x, Field.CopyGraphicPos[Field.p].y - Field.FramePos.x, Field.CopyGraphicPos[Field.p].z - Field.FramePos.z));
				MV1SetRotationXYZ(Field.CopyGraphicHandle[Field.p], VGet(0.0f, 0.0f, Field.radian));
				MV1SetPosition(Field.CopyGraphicHandle[Field.p], Field.CopyGraphicPos[Field.p]);//モデルの座標セット
				game()->cube()->CreateCube(Rotate, Rotate1, GetColor(0, 0, 0),RIGHT_WALL_ID);
				game()->cube()->CreateCube(VGet(Rotate.x + 1, Rotate.y, Rotate.z), VGet(Rotate1.x + 1, Rotate1.y, Rotate1.z), Field.RedWallColor, RED_RIGHT_WALL_ID);
				Field.p++;
			}
			else if (Field.MapTile[Field.p] == '4') {
				VECTOR Rotate, Rotate1;
				Field.CopyGraphicPos[Field.p] = VGet(Field.AddMinMaxPoligonPos.x * XTile - Field.FramePos.x, Field.MaxPoligonPos.z, (Field.AddMinMaxPoligonPos.z * ZTile) + Field.MaxPoligonPos.z - Field.FramePos.z);
				MV1SetMatrix(Field.CopyGraphicHandle[Field.p], MMult(MGetScale(VGet(1, 1, 0.553f)), MMult(MGetRotX(-Field.radian), MGetTranslate(VGet(Field.CopyGraphicPos[Field.p].x, Field.pos.z+Field.MaxPoligonPos.z * 0.553f, Field.CopyGraphicPos[Field.p].z)))));
				Rotate = VAdd(VGet(Field.pos.x + Field.MaxPoligonPos.x, Field.AddMinMaxPoligonPos.x, 0), VGet(Field.AddMinMaxPoligonPos.x * XTile, 0, Field.MinPoligonPos.z + Field.FramePos.z + (Field.AddMinMaxPoligonPos.z * ZTile)));
				Rotate1 = VAdd(VGet(Field.pos.x - Field.MinPoligonPos.x, 0, 0), VGet(Field.AddMinMaxPoligonPos.x * XTile, 0, Field.MinPoligonPos.z + Field.FramePos.z + (Field.AddMinMaxPoligonPos.z * ZTile)));
				game()->cube()->CreateCube(Rotate, Rotate1, GetColor(0, 128, 0), STRAGHT_WALL_ID);
				Field.p++;

				Field.CopyGraphicPos[Field.p] = VGet(Field.pos.x + (Field.AddMinMaxPoligonPos.x * XTile), Field.pos.y, Field.pos.z + (Field.AddMinMaxPoligonPos.z * ZTile));
				MV1SetPosition(Field.CopyGraphicHandle[Field.p], Field.CopyGraphicPos[Field.p]);//モデルの座標セット
				game()->cube()->CreateCube(VSub(Field.CopyGraphicPos[Field.p], Field.MinPoligonPos), VAdd(Field.CopyGraphicPos[Field.p], Field.MaxPoligonPos), GetColor(0, 0, 0), FLOOR_ID);
				Field.p++;
			}
			else if (Field.MapTile[Field.p] == '5') {
				VECTOR Rotate, Rotate1;
				Field.CopyGraphicPos[Field.p] = VGet(Field.AddMinMaxPoligonPos.x * XTile-Field.FramePos.x,Field.MaxPoligonPos.z, (Field.AddMinMaxPoligonPos.z * ZTile) - Field.MaxPoligonPos.z + Field.FramePos.z);
				MV1SetMatrix(Field.CopyGraphicHandle[Field.p], MMult(MGetScale(VGet(1, 1, 0.553f)), MMult(MGetRotX(Field.radian), MGetTranslate(VGet(Field.CopyGraphicPos[Field.p].x, Field.MaxPoligonPos.z*0.553f, Field.CopyGraphicPos[Field.p].z)))));
				Rotate = VAdd(VGet(Field.pos.x + Field.MaxPoligonPos.x, Field.AddMinMaxPoligonPos.x, 0), VGet(Field.AddMinMaxPoligonPos.x * XTile, 0, -Field.MaxPoligonPos.z + Field.FramePos.z + (Field.AddMinMaxPoligonPos.z * ZTile)));
				Rotate1 = VAdd(VGet(Field.pos.x - Field.MinPoligonPos.x, 0, 0), VGet(Field.AddMinMaxPoligonPos.x * XTile, 0, -Field.MaxPoligonPos.z + Field.FramePos.z + (Field.AddMinMaxPoligonPos.z * ZTile)));
				game()->cube()->CreateCube(Rotate, Rotate1, GetColor(0, 128, 0), RETREAT_WALL_ID);
				Field.p++;

				Field.CopyGraphicPos[Field.p] = VGet(Field.pos.x + (Field.AddMinMaxPoligonPos.x * XTile), Field.pos.y, Field.pos.z + (Field.AddMinMaxPoligonPos.z * ZTile));
				MV1SetPosition(Field.CopyGraphicHandle[Field.p], Field.CopyGraphicPos[Field.p]);//モデルの座標セット
				game()->cube()->CreateCube(VSub(Field.CopyGraphicPos[Field.p], Field.MinPoligonPos), VAdd(Field.CopyGraphicPos[Field.p], Field.MaxPoligonPos), GetColor(0, 0, 0), FLOOR_ID);
				Field.p++;
			}
			else if (Field.MapTile[Field.p] == '0') {
				Field.p++;
			}
			else {
				break;
			}
		}
		if(Field.MapTile[Field.p] == '\n') {
			Field.p++;
		}
		else {
			Field.p++;
		}
	}

	game()->cube()->CreateCube(Field.GatePos, Field.GatePos2, GetColor(0, 0, 255), GATE_ID);

}

void FIELD::loop()
{
	for (int i = 0; i < MAXTILE; i++) {
		Field.CopyGraphicHandle[i] = MV1DuplicateModel(Field.GraphicHundle);
		Field.CopyGraphicPos[i] = VGet(0.0f, 0.0f, 0.0f);
		MV1SetRotationXYZ(Field.CopyGraphicHandle[i], VGet(0.0f, 0.0f, 0.0f));
	}
	strcpy_s(Field.MapTile, Field.CopyMapTile);
	//マップタイルのランダム化
	int thereafter = 0;//固定されたマップ最終場所
	int newline = 0;//マップタイルの改行場所
	while (Field.MapTile[thereafter] != '\0') {
		thereafter++;
	}
	while (Field.MapTile[newline] != '\n') {
		newline++;
	}
	newline++;
	if (Field.MapTile[thereafter] == '\0') {
		Field.MapTile[thereafter] = '\n';
		Field.p = thereafter;
	}
	int plus = 0;
	while (Field.p < Field.MaxHundle) {
		if (Field.p > thereafter) {
			if (Field.p % newline == newline-1) {
				Field.MapTile[Field.p] = '\n';
			}
			if (Field.MapTile[Field.p] != '\n') {
				Field.MapTile[Field.p] = '0' + GetRand(3);
				if (Field.MapTile[Field.p-1] == '2' && Field.MapTile[Field.p] == '3') {
					if (GetRand(1)) {
						Field.MapTile[Field.p-1] = '0';
					}
					else {
						Field.MapTile[Field.p] = '0';
					}
				}
			}
		}

		Field.p++;
	}
	Field.MapTile[Field.MaxHundle] = 0;
}

void FIELD::CollisionTerminate()
{
	
	for (int i = 0; i < MAXTILE; i++) {
		MV1TerminateCollInfo(Field.CopyGraphicHandle[i], 0);
		//MV1DeleteModel( int MHandle ) ;
	}
}

