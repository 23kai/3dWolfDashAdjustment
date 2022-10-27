#include "GAME_OVER.h"
#include"GAME.h"
GAME_OVER::GAME_OVER(class GAME* game):
	SCENE(game)
{
}

GAME_OVER::~GAME_OVER()
{
}

void GAME_OVER::create()
{
	Over = game()->container()->gameover();
	init();
}

void GAME_OVER::init()
{
	Over.Restart = 0;
	Over.Title = 0;
	Over.Quit = 0;
	
	Over.RestartMouseKeyCheck = 0;
	Over.TitleMouseKeyCheck = 0;
	Over.QuitMouseKeyCheck = 0;
}

void GAME_OVER::update()
{
	Over.Score = game()->wolf()->score();

	GetMouseInputLog2(&Over.MouseCrick, &Over.MousePointX, &Over.MousePointY, &Over.MouseCrickLog, TRUE);
	GetMousePoint(&Over.MousePointX, &Over.MousePointY);
	Over.MouseCrick = GetMouseInput();
	//リスタートボタン
	if (Over.MousePointX > Over.Stb.x && Over.MousePointY > Over.Stb.y &&
		Over.MousePointX < Over.Stb.x + Over.botExpansionX && Over.MousePointY < Over.Stb.y + Over.botExpansionY ) {
		if (Over.MouseCrickLog == MOUSE_INPUT_LOG_DOWN && Over.MouseCrick == MOUSE_INPUT_LEFT) {
			Over.RestartMouseKeyCheck = 1;
		}
		if (Over.MouseCrickLog == MOUSE_INPUT_LOG_UP && Over.RestartMouseKeyCheck == 1) {
			Over.Restart = 1;
		}
		Over.StbWallpaperColor = Over.TouchWallpaperColor;
	}
	else {
		Over.StbWallpaperColor = Over.InitWallpaperColor;
		Over.RestartMouseKeyCheck = 0;
	}

	//タイトル画面に戻るボタン
	if (Over.MousePointX > Over.Tib.x && Over.MousePointY > Over.Tib.y &&
		Over.MousePointX < Over.Tib.x + Over.botExpansionX && Over.MousePointY < Over.Tib.y + Over.botExpansionY ) {
		if (Over.MouseCrickLog == MOUSE_INPUT_LOG_DOWN && Over.MouseCrick == MOUSE_INPUT_LEFT) {
			Over.TitleMouseKeyCheck = 1;
		}
		if (Over.MouseCrickLog == MOUSE_INPUT_LOG_UP && Over.TitleMouseKeyCheck == 1) {
			Over.Title = 1;
		}
		Over.TibWallpaperColor = Over.TouchWallpaperColor;
	}
	else {
		Over.TibWallpaperColor = Over.InitWallpaperColor;
		Over.TitleMouseKeyCheck = 0;
	}

	//終了ボタン
	if (Over.MousePointX > Over.Qub.x && Over.MousePointY > Over.Qub.y &&
		Over.MousePointX < Over.Qub.x + Over.botExpansionX && Over.MousePointY < Over.Qub.y + Over.botExpansionY ) {
		if (Over.MouseCrickLog == MOUSE_INPUT_LOG_DOWN && Over.MouseCrick == MOUSE_INPUT_LEFT) {
			Over.QuitMouseKeyCheck = 1;
		}
		if (Over.MouseCrickLog == MOUSE_INPUT_LOG_UP && Over.QuitMouseKeyCheck == 1) {
			Over.Quit = 1;
		}
		Over.QubWallpaperColor = Over.TouchWallpaperColor;
	}
	else {
		Over.QubWallpaperColor = Over.InitWallpaperColor;
		Over.QuitMouseKeyCheck = 0;
	}
}

void GAME_OVER::draw()
{
	DrawFormatStringToHandle(Over.ScoreDraw.x, Over.ScoreDraw.y, Over.FontColor, Over.FontHandle,"%s %d",Over.ScoreText,Over.Score);

	DrawBoxAA(Over.Stb.x, Over.Stb.y, Over.Stb.x + Over.botExpansionX, Over.Stb.y + Over.botExpansionY, Over.StbWallpaperColor, TRUE);
	DrawStringToHandle(Over.Stb.x, Over.Stb.y, Over.RestartText, Over.FontColor, Over.FontHandle);

	DrawBoxAA(Over.Tib.x, Over.Tib.y, Over.Tib.x + Over.botExpansionX, Over.Tib.y + Over.botExpansionY, Over.TibWallpaperColor, TRUE);
	DrawStringToHandle(Over.Tib.x, Over.Tib.y, Over.TitleText, Over.FontColor, Over.FontHandle);

	DrawBoxAA(Over.Qub.x, Over.Qub.y, Over.Qub.x + Over.botExpansionX, Over.Qub.y + Over.botExpansionY, Over.QubWallpaperColor, TRUE);
	DrawStringToHandle(Over.Qub.x, Over.Qub.y, Over.QuitText, Over.FontColor, Over.FontHandle);
}

void GAME_OVER::nextScene()
{
	if (Over.Restart > 0) {
		game()->ChangeScene(GAME::STAGE_ID);
	}
	if (Over.Title > 0) {
		game()->ChangeScene(GAME::TITLE_ID);
	}
	if (Over.Quit > 0) {
		game()->Quit();
	}
}
