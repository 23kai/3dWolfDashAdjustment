#include "TITLE.h"
#include"GAME.h"
TITLE::TITLE(class GAME* game):
	SCENE(game)
{
}

TITLE::~TITLE()
{
}

void TITLE::create()
{
	Title = game()->container()->title();
	init();
}

void TITLE::init()
{
	Title.FontHandle=CreateFontToHandle(NULL, 80, 3, DX_FONTTYPE_NORMAL);
	Title.Start = 0;
	Title.Option = 0;
	Title.Quit= 0;

	Title.StartMouseKeyCheck = 0;
	Title.OptionMouseKeyCheck = 0;
	Title.QuitMouseKeyCheck = 0;
}

void TITLE::update()
{
	GetMouseInputLog2(&Title.MouseCrick, &Title.MousePointX, &Title.MousePointY, &Title.MouseCrickLog, TRUE);
	GetMousePoint(&Title.MousePointX, &Title.MousePointY);
	Title.MouseCrick = GetMouseInput();

	//スタートボタン
	if (Title.MousePointX > Title.Stb.x && Title.MousePointY > Title.Stb.y &&
		Title.MousePointX < Title.Stb.x + Title.botExpansionX && Title.MousePointY < Title.Stb.y + Title.botExpansionY) {
		if (Title.MouseCrickLog == MOUSE_INPUT_LOG_DOWN && Title.MouseCrick == MOUSE_INPUT_LEFT) {
			Title.StartMouseKeyCheck = 1;
		}
		if (Title.MouseCrickLog == MOUSE_INPUT_LOG_UP && Title.StartMouseKeyCheck == 1) {
			Title.Start = 1;
		}
		Title.StbWallpaperColor = Title.TouchWallpaperColor;
	}
	else {
		Title.StbWallpaperColor = Title.InitWallpaperColor;
		Title.StartMouseKeyCheck = 0;
	}

	//オプションボタン
	if (Title.MousePointX > Title.Opb.x && Title.MousePointY > Title.Opb.y &&
		Title.MousePointX < Title.Opb.x + Title.botExpansionX && Title.MousePointY < Title.Opb.y + Title.botExpansionY) {
		if (Title.MouseCrickLog == MOUSE_INPUT_LOG_DOWN && Title.MouseCrick == MOUSE_INPUT_LEFT) {
			Title.OptionMouseKeyCheck = 1;
		}
		if (Title.MouseCrickLog == MOUSE_INPUT_LOG_UP && Title.OptionMouseKeyCheck == 1) {
			Title.Option = 1;
		}
		Title.OpbWallpaperColor = Title.TouchWallpaperColor;
	}
	else {
		Title.OpbWallpaperColor = Title.InitWallpaperColor;
		Title.OptionMouseKeyCheck = 0;
	}

	//終了ボタン
	if (Title.MousePointX > Title.Qub.x && Title.MousePointY > Title.Qub.y &&
		Title.MousePointX < Title.Qub.x + Title.botExpansionX && Title.MousePointY < Title.Qub.y + Title.botExpansionY) {
		if (Title.MouseCrickLog == MOUSE_INPUT_LOG_DOWN && Title.MouseCrick == MOUSE_INPUT_LEFT) {
			Title.QuitMouseKeyCheck = 1;
		}
		if (Title.MouseCrickLog == MOUSE_INPUT_LOG_UP && Title.QuitMouseKeyCheck == 1) {
			Title.Quit = 1;
		}
		Title.QubWallpaperColor = Title.TouchWallpaperColor;
	}
	else {
		Title.QubWallpaperColor = Title.InitWallpaperColor;
		Title.QuitMouseKeyCheck = 0;
	}
}

void TITLE::draw()
{
	DrawBoxAA(Title.Stb.x, Title.Stb.y, Title.Stb.x+Title.botExpansionX, Title.Stb.y+Title.botExpansionY,Title.StbWallpaperColor, TRUE);
	DrawStringToHandle(Title.Stb.x, Title.Stb.y,"start", Title.FontColor, Title.FontHandle);

	DrawBoxAA(Title.Opb.x, Title.Opb.y, Title.Opb.x + Title.botExpansionX, Title.Opb.y + Title.botExpansionY, Title.OpbWallpaperColor, TRUE);
	DrawStringToHandle(Title.Opb.x, Title.Opb.y, "option", Title.FontColor, Title.FontHandle);

	DrawBoxAA(Title.Qub.x, Title.Qub.y, Title.Qub.x+Title.botExpansionX, Title.Qub.y+Title.botExpansionY, Title.QubWallpaperColor, TRUE);
	DrawStringToHandle(Title.Qub.x, Title.Qub.y,"quit", Title.FontColor, Title.FontHandle);
	
}

void TITLE::nextScene()
{
	if (Title.Start > 0) {
		game()->ChangeScene(GAME::STAGE_ID);
	}
	if (Title.Option > 0) {
		game()->ChangeScene(GAME::OPTION_ID);
	}
	if (Title.Quit > 0) {
		game()->Quit();
	}
}
