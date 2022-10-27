#include "OPTION.h"
#include"GAME.h"
OPTION::OPTION(GAME* game):
	SCENE(game)
{
}

OPTION::~OPTION()
{
}

void OPTION::create()
{
	Option = game()->container()->option();
}

void OPTION::init()
{
	Option.SensitivityXCircle.y = Option.SensitivityXLineY;
	Option.SensitivityYCircle.y = Option.SensitivityYLineY;
	Option.Back = 0;
	Option.BabMouseKeyCheck = 0;
	Option.OnSenBotanMouseKeyCheck = 0;

	Option.Sensitivity = (Option.SensitivityLineEndX - Option.SensitivityLineStartX) / Option.SensitivitySplit / Option.Split;
	Option.SensitivityXCircle.x = round(Option.SensitivityLineStartX + (game()->system()->GetSensitivityX() / Option.SensitivityFixed+1) * Option.Sensitivity);
	Option.SensitivityYCircle.x = round(Option.SensitivityLineStartX + (game()->system()->GetSensitivityY() / Option.SensitivityFixed+1) * Option.Sensitivity);
	Option.OnSensitivityBotan = VGet(game()->HalfWidth-Option.SensiBotanExpansionX, game()->HalfHeight, 0);
	Option.OffSensitivityBotan = VGet(game()->HalfWidth, game()->HalfHeight, 0);
	if (game()->system()->GetMouseSensitivity()) {
		Option.OnSensiBotanWallPaperColor = Option.SensiBotanGreenWallPaperColor;
		Option.OffSensiBotanWallPaperColor = Option.SensiBotanRedWallPaperColor;
		strcpy_s(Option.SensitivityBotanText, Option.OnSensitivityBotanText);
	}
	else {
		Option.OffSensiBotanWallPaperColor = Option.SensiBotanGreenWallPaperColor;
		Option.OnSensiBotanWallPaperColor = Option.SensiBotanRedWallPaperColor;
		strcpy_s(Option.SensitivityBotanText, Option.OffSensitivityBotanText);
	}
}

void OPTION::update()
{

	GetMouseInputLog2(&Option.MouseCrick, &Option.MousePointX, &Option.MousePointY, &Option.MouseCrickLog, TRUE);
	GetMousePoint(&Option.MousePointX, &Option.MousePointY);
	Option.MouseCrick = GetMouseInput();
	//X�����x�ݒ�
	if (Option.MousePointX > Option.SensitivityBoxX.x && Option.MousePointY > Option.SensitivityBoxX.y &&
		Option.MousePointX < Option.SensitivityBoxX.x + Option.SebExpansionX && Option.MousePointY < Option.SensitivityBoxX.y + Option.SebExpansionY) {

		Option.SenXWallPaperColor = Option.SenTouchWallPaperColor;

		if (Option.MouseCrickLog == MOUSE_INPUT_LOG_DOWN && Option.MouseCrick == MOUSE_INPUT_LEFT) {
			if(Option.MousePointX >Option.SensitivityLineStartX && Option.MousePointX<Option.SensitivityLineEndX){
				Option.SensitivityXCircle.x = Option.MousePointX;
			}
			else if (Option.MousePointX < Option.SensitivityLineStartX) {
				Option.SensitivityXCircle.x = Option.SensitivityLineStartX;
			}
			else if (Option.MousePointX > Option.SensitivityLineEndX) {
				Option.SensitivityXCircle.x = Option.SensitivityLineEndX;
			}
			Option.SenXWallPaperColor = Option.SenPushWallPaperColor;
		}
	}
	else {
		Option.SenXWallPaperColor = Option.SenInitWallPaperColor;
	}

	//Y�����x�ݒ�
	if (Option.MousePointX > Option.SensitivityBoxY.x && Option.MousePointY > Option.SensitivityBoxY.y &&
		Option.MousePointX < Option.SensitivityBoxY.x + Option.SebExpansionX && Option.MousePointY < Option.SensitivityBoxY.y + Option.SebExpansionY) {

		Option.SenYWallPaperColor = Option.SenTouchWallPaperColor;

		if (Option.MouseCrickLog == MOUSE_INPUT_LOG_DOWN && Option.MouseCrick == MOUSE_INPUT_LEFT) {
			if (Option.MousePointX > Option.SensitivityLineStartX && Option.MousePointX < Option.SensitivityLineEndX) {
				Option.SensitivityYCircle.x = Option.MousePointX;
			}
			else if (Option.MousePointX < Option.SensitivityLineStartX) {
				Option.SensitivityYCircle.x = Option.SensitivityLineStartX;
			}
			else if (Option.MousePointX > Option.SensitivityLineEndX) {
				Option.SensitivityYCircle.x = Option.SensitivityLineEndX;
			}
			Option.SenYWallPaperColor = Option.SenPushWallPaperColor;
		}
	}
	else {
		Option.SenYWallPaperColor = Option.SenInitWallPaperColor;
	}
	//�}�E�X�ɂ��J�����ړ������邩���Ȃ���
	if (Option.MousePointX > Option.OnSensitivityBotan.x && Option.MousePointY > Option.OnSensitivityBotan.y &&
		Option.MousePointX < Option.OnSensitivityBotan.x + Option.SensiBotanExpansionX && Option.MousePointY < Option.OnSensitivityBotan.y + Option.SensiBotanExpansionY) {
		if (Option.MouseCrickLog == MOUSE_INPUT_LOG_DOWN && Option.MouseCrick == MOUSE_INPUT_LEFT) {
			Option.OnSenBotanMouseKeyCheck = 1;
		}
		if (Option.MouseCrickLog == MOUSE_INPUT_LOG_UP && Option.OnSenBotanMouseKeyCheck == 1) {
			Option.OnSensiBotanWallPaperColor = Option.SensiBotanGreenWallPaperColor;
			Option.OffSensiBotanWallPaperColor = Option.SensiBotanRedWallPaperColor;
			strcpy_s(Option.SensitivityBotanText, Option.OnSensitivityBotanText);
			Option.MouseSensitivity = 1;
			game()->system()->MouseSensitivity(Option.MouseSensitivity);
		}

	}
	else {
		Option.OnSenBotanMouseKeyCheck = 0;
	}

	if (Option.MousePointX > Option.OffSensitivityBotan.x && Option.MousePointY > Option.OffSensitivityBotan.y &&
		Option.MousePointX < Option.OffSensitivityBotan.x + Option.SensiBotanExpansionX && Option.MousePointY < Option.OffSensitivityBotan.y + Option.SensiBotanExpansionY) {
		if (Option.MouseCrickLog == MOUSE_INPUT_LOG_DOWN && Option.MouseCrick == MOUSE_INPUT_LEFT) {
			Option.OffSenBotanMouseKeyCheck = 1;
		}
		if (Option.MouseCrickLog == MOUSE_INPUT_LOG_UP && Option.OffSenBotanMouseKeyCheck == 1) {
			Option.OffSensiBotanWallPaperColor = Option.SensiBotanGreenWallPaperColor;
			Option.OnSensiBotanWallPaperColor = Option.SensiBotanRedWallPaperColor;
			strcpy_s(Option.SensitivityBotanText, Option.OffSensitivityBotanText);
			Option.MouseSensitivity = 0;
			game()->system()->MouseSensitivity(Option.MouseSensitivity);
		}

	}
	else {
		Option.OffSenBotanMouseKeyCheck = 0;
	}
	//�߂�{�^��
	if (Option.MousePointX > Option.Bab.x && Option.MousePointY > Option.Bab.y &&
		Option.MousePointX < Option.Bab.x + Option.botExpansionX && Option.MousePointY < Option.Bab.y + Option.botExpansionY) {
		if (Option.MouseCrickLog == MOUSE_INPUT_LOG_DOWN && Option.MouseCrick == MOUSE_INPUT_LEFT) {
			Option.BabMouseKeyCheck = 1;
		}
		if (Option.MouseCrickLog == MOUSE_INPUT_LOG_UP && Option.BabMouseKeyCheck == 1) {
			Option.Back = 1;
		}
		Option.BabWallPaperColor = Option.BabTouchWallPaperColor;
	}
	else {
		Option.BabWallPaperColor = Option.BabInitWallPaperColor;
		Option.BabMouseKeyCheck = 0;
	}
	//���ꂼ��̎��̊��x
	Option.SensitivityX = Option.SensitivityFixed * (Option.SensitivityXCircle.x - (Option.Sensitivity + Option.SensitivityLineStartX)) / Option.Sensitivity* Option.Calculation;
	Option.SensitivityX = round(Option.SensitivityX) / Option.Calculation;
	Option.SensitivityY = Option.SensitivityFixed * (Option.SensitivityYCircle.x - (Option.Sensitivity + Option.SensitivityLineStartX)) / Option.Sensitivity* Option.Calculation;
	Option.SensitivityY = round(Option.SensitivityY) / Option.Calculation;
	//�����ɂ��ŏ��l�ɕϊ�
	if (Option.SensitivityX < Option.SensitivityFixed) {
		Option.SensitivityX = Option.SensitivityFixed;
	}
	if (Option.SensitivityY < Option.SensitivityFixed) {
		Option.SensitivityY = Option.SensitivityFixed;
	}
	//���x��SYSTEM�ɓ���
	game()->system()->SensitivityX(Option.SensitivityX);
	game()->system()->SensitivityY(Option.SensitivityY);

}

void OPTION::draw()
{
	//X���̊��x�ݒ�֌W
	DrawBoxAA(Option.SensitivityBoxX.x, Option.SensitivityBoxX.y, Option.SensitivityBoxX.x + Option.SebExpansionX, Option.SensitivityBoxX.y + Option.SebExpansionY, Option.SenXWallPaperColor, TRUE);
	DrawStringToHandle(Option.SensitivityBoxX.x, Option.SensitivityBoxX.y - Option.FontScale, Option.SensitivityXText, Option.FontColor, Option.FontHandle);
	DrawFormatString(game()->HalfWidth, Option.SensitivityBoxX.y - Option.ValueScele, Option.FontColor, "%f", Option.SensitivityX);

	DrawLineAA(Option.SensitivityLineStartX,Option.SensitivityXLineY, Option.SensitivityLineEndX,Option.SensitivityXLineY, Option.LineColor);
	DrawCircleAA(Option.SensitivityXCircle.x, Option.SensitivityXCircle.y,Option.SensitivityCircleRadius, Option.SensitivityCircleRadius, Option.CircleColor, TRUE);
	//Y���̊��x�ݒ�֌W
	DrawBoxAA(Option.SensitivityBoxY.x, Option.SensitivityBoxY.y, Option.SensitivityBoxY.x + Option.SebExpansionX, Option.SensitivityBoxY.y + Option.SebExpansionY, Option.SenYWallPaperColor, TRUE);
	DrawStringToHandle(Option.SensitivityBoxY.x, Option.SensitivityBoxY.y - Option.FontScale, Option.SensitivityYText, Option.FontColor, Option.FontHandle);
	DrawFormatString(game()->HalfWidth, Option.SensitivityBoxY.y - Option.ValueScele, Option.FontColor, "%f", Option.SensitivityY);
	
	DrawLineAA(Option.SensitivityLineStartX,Option.SensitivityYLineY, Option.SensitivityLineEndX,Option.SensitivityYLineY, Option.LineColor);
	DrawCircleAA(Option.SensitivityYCircle.x, Option.SensitivityYCircle.y,Option.SensitivityCircleRadius, Option.SensitivityCircleRadius, Option.CircleColor, TRUE);
	//�}�E�X�ɂ��J���������ONOFF�؂�ւ��{�^��
	DrawBoxAA(Option.OnSensitivityBotan.x, Option.OnSensitivityBotan.y, Option.OnSensitivityBotan.x + Option.SensiBotanExpansionX, Option.OnSensitivityBotan.y + Option.SensiBotanExpansionY, Option.OnSensiBotanWallPaperColor, TRUE);
	DrawBoxAA(Option.OffSensitivityBotan.x, Option.OffSensitivityBotan.y, Option.OffSensitivityBotan.x + Option.SensiBotanExpansionX, Option.OffSensitivityBotan.y + Option.SensiBotanExpansionY, Option.OffSensiBotanWallPaperColor, TRUE);
	DrawStringToHandle(Option.OnSensitivityBotan.x, Option.OnSensitivityBotan.y - Option.FontScale, Option.SensitivityBotanText, Option.FontColor, Option.FontHandle);
	//�߂�{�^��
	DrawBoxAA(Option.Bab.x, Option.Bab.y, Option.Bab.x + Option.botExpansionX, Option.Bab.y + Option.botExpansionY, Option.BabWallPaperColor, TRUE);
	DrawStringToHandle(Option.Bab.x, Option.Bab.y, Option.BackBotanText, Option.FontColor, Option.FontHandle);
}

void OPTION::nextScene()
{
	if (Option.Back > 0) {
		game()->ChangeScene(GAME::TITLE_ID);
	}
}

void OPTION::ChangeScene()
{
}
