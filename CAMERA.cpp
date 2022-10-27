#include "CAMERA.h"
#include"GAME.h"
#include<math.h>
CAMERA::CAMERA(class GAME* game):
	OBJECTS(game)
{
}

CAMERA::~CAMERA()
{
}

void CAMERA::create()
{
	Camera = game()->container()->camera();
}
void CAMERA::init() {
	Camera.Vtarget = game()->wolf()->target();
	Camera.Pos = VGet(Camera.Vtarget.x, Camera.Vtarget.y, Camera.Vtarget.z - Camera.radius);
	Camera.Pos = VSub(Camera.Pos, Camera.Vtarget);
	Camera.Pos = VTransformSR(Camera.Pos, MGetRotX(Camera.InitRadian));
	Camera.Pos = VAdd(Camera.Pos, Camera.Vtarget);
}
void CAMERA::proc()
{
	update();
	draw();
}

void CAMERA::update()
{
	Camera.Target=game()->wolf()->target();

	Camera.Pos=VAdd(Camera.Pos, VSub(Camera.Target, Camera.Vtarget));
	MATRIX RotateX = MGetIdent();
	MATRIX RotateY = MGetIdent();
	float radian = 0.0f;
	GetMousePoint(&Camera.MousePointX,&Camera.MousePointY);
	
	//É}ÉEÉXëÄçÏî≈ÉJÉÅÉâà⁄ìÆ
	//âEâÒì]
	if (Camera.MousePointX > game()->HalfWidth && game()->system()->GetMouseSensitivity()) {
		Camera.Pos = VSub(Camera.Pos, Camera.Target);
		RotateY = MGetRotY((game()->HalfWidth - Camera.MousePointX) * Camera.Radian * game()->system()->GetSensitivityX());

		Camera.Pos = VTransformSR(Camera.Pos, RotateY);
		Camera.Pos = VAdd(Camera.Pos, Camera.Target);
	}
	//ç∂âÒì]
	if (Camera.MousePointX < game()->HalfWidth && game()->system()->GetMouseSensitivity()) {
		Camera.Pos = VSub(Camera.Pos, Camera.Target);
		RotateY = MGetRotY((game()->HalfWidth - Camera.MousePointX) * Camera.Radian * game()->system()->GetSensitivityX());

		Camera.Pos = VTransformSR(Camera.Pos, RotateY);
		Camera.Pos = VAdd(Camera.Pos, Camera.Target);
	}
	//â∫âÒì]
	if (Camera.MousePointY < game()->HalfHeight && game()->system()->GetMouseSensitivity()) {
		Camera.Pos = VSub(Camera.Pos, Camera.Target);

		radian = atan2(-Camera.Pos.x, -Camera.Pos.z);
		RotateY = MGetRotY(-radian);
		if (fabsf(Camera.Pos.x) > 1.0f || fabsf(Camera.Pos.z) > 1.0f || Camera.Pos.y < 0.0f) {
			RotateX = MGetRotX((game()->HalfHeight - Camera.MousePointY) * Camera.Radian * game()->system()->GetSensitivityY());
		}

		Camera.Pos = VTransformSR(Camera.Pos, RotateY);
		RotateY = MGetRotY(radian);
		Camera.Pos = VTransformSR(Camera.Pos, RotateX);
		Camera.Pos = VTransformSR(Camera.Pos, RotateY);
		Camera.Pos = VAdd(Camera.Pos, Camera.Target);
	}
	//è„âÒì]
	if (Camera.MousePointY > game()->HalfHeight && game()->system()->GetMouseSensitivity()) {
		Camera.Pos = VSub(Camera.Pos, Camera.Target);

		radian = atan2(-Camera.Pos.x, -Camera.Pos.z);
		RotateY = MGetRotY(-radian);
		if (fabsf(Camera.Pos.x) > 1.0f || fabsf(Camera.Pos.z) > 1.0f || Camera.Pos.y > 0.0f) {
			RotateX = MGetRotX((game()->HalfHeight - Camera.MousePointY) * Camera.Radian * game()->system()->GetSensitivityY());
		}

		Camera.Pos = VTransformSR(Camera.Pos, RotateY);
		RotateY = MGetRotY(radian);
		Camera.Pos = VTransformSR(Camera.Pos, RotateX);
		Camera.Pos = VTransformSR(Camera.Pos, RotateY);
		Camera.Pos = VAdd(Camera.Pos, Camera.Target);
	}

	//ÉJÉÅÉâà⁄ìÆ(âÒì])
	//ç∂âÒì]
	if (CheckHitKey(KEY_INPUT_LEFT) > 0) {
		Camera.Pos = VSub(Camera.Pos, Camera.Target);
		RotateY = MGetRotY(ROTATE_SPEED * game()->DeltaTime);

		Camera.Pos = VTransformSR(Camera.Pos, RotateY);
		Camera.Pos = VAdd(Camera.Pos, Camera.Target);
	}
	//âEâÒì]
	if (CheckHitKey(KEY_INPUT_RIGHT) > 0) {
		Camera.Pos = VSub(Camera.Pos, Camera.Target);
		RotateY = MGetRotY(-ROTATE_SPEED * game()->DeltaTime);

		Camera.Pos = VTransformSR(Camera.Pos, RotateY);
		Camera.Pos = VAdd(Camera.Pos, Camera.Target);
	}
	//è„âÒì]
	if (CheckHitKey(KEY_INPUT_UP) > 0) {
		Camera.Pos = VSub(Camera.Pos,Camera.Target);

		radian = atan2(-Camera.Pos.x,-Camera.Pos.z);
		RotateY = MGetRotY(-radian);
		if (fabsf(Camera.Pos.x) > 1.0f || fabsf(Camera.Pos.z) > 1.0f||Camera.Pos.y<0.0f) {
			RotateX = MGetRotX(ROTATE_SPEED * game()->DeltaTime);
		}

		Camera.Pos = VTransformSR(Camera.Pos, RotateY);
		RotateY = MGetRotY(radian);
		Camera.Pos = VTransformSR(Camera.Pos, RotateX);
		Camera.Pos = VTransformSR(Camera.Pos, RotateY);
		Camera.Pos = VAdd(Camera.Pos, Camera.Target);
	}
	//â∫âÒì]
	if (CheckHitKey(KEY_INPUT_DOWN) > 0) {
		Camera.Pos = VSub(Camera.Pos, Camera.Target);

		radian = atan2(-Camera.Pos.x, -Camera.Pos.z);
		RotateY = MGetRotY(-radian);
		if (fabsf(Camera.Pos.x) > 1.0f || fabsf(Camera.Pos.z) > 1.0f || Camera.Pos.y > 0.0f) {
			RotateX = MGetRotX(-ROTATE_SPEED * game()->DeltaTime);
		}

		Camera.Pos = VTransformSR(Camera.Pos, RotateY);
		RotateY = MGetRotY(radian);
		Camera.Pos = VTransformSR(Camera.Pos, RotateX);
		Camera.Pos = VTransformSR(Camera.Pos, RotateY);
		Camera.Pos = VAdd(Camera.Pos, Camera.Target);
	}

	DrawFormatString(0, 300, GetColor(255, 255, 255), "radian=%f", radian);
	Camera.Vtarget = Camera.Target;
}

void CAMERA::draw()
{
	
	SetCameraNearFar(Camera.MinDrawingRange, Camera.MaxDrawingRange);
	SetCameraPositionAndTarget_UpVecY(Camera.Pos, VGet(Camera.Target.x,Camera.Target.y,Camera.Target.z));

}

void CAMERA::charaCamera(VECTOR vpos)
{
	Camera.Pos = VAdd(Camera.Pos, vpos);
}
