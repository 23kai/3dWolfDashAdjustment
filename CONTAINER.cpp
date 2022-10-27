#include "CONTAINER.h"
#include<string.h>
CONTAINER::~CONTAINER() {

}
void CONTAINER::load() {
	loadGraphic();
	setdata();
}
void CONTAINER::setdata() {
	//タイトルシーン
	Data.title.Start = 0;
	Data.title.Quit = 0;
	//ボタン座標
	Data.title.Stb = VGet(100.0f, 200.0f, 0.0f);
	Data.title.Opb = VGet(100.0f, 400.0f, 0.0f);
	Data.title.Qub = VGet(100.0f, 600.0f, 0.0f);
	Data.title.botExpansionX = 400.0f;
	Data.title.botExpansionY = 100.0f;

	Data.title.FontColor = GetColor(255, 255, 255);
	Data.title.StbWallpaperColor = GetColor(255, 255, 255);
	Data.title.OpbWallpaperColor = GetColor(255, 255, 255);
	Data.title.QubWallpaperColor = GetColor(255, 255, 255);
	Data.title.InitWallpaperColor = GetColor(0, 128, 128);
	Data.title.TouchWallpaperColor = GetColor(0, 128, 255);

	//マウスの現在地の初期化(バグを避けるため）
	Data.title.MousePointX = 0;
	Data.title.MousePointY = 0;
	
	//ステージシーン
	//シーン変更(TRUE or FALSE)
	Data.stage.Change = 0;
	//ゲームオーバーシーン
	Data.gameover.Restart = 0;
	Data.gameover.Quit = 0;
	Data.gameover.Title = 0;
	Data.gameover.Score = 0;

	Data.gameover.ScoreDraw = VGet(100.0f, 0.0f, 0.0f);
	Data.gameover.Stb = VGet(100.0f, 200.0f, 0.0f);
	Data.gameover.Tib = VGet(100.0f, 400.0f, 0.0f);
	Data.gameover.Qub = VGet(100.0f, 600.0f, 0.0f);
	Data.gameover.botExpansionX = 400.0f;
	Data.gameover.botExpansionY = 100.0f;

	Data.gameover.FontColor = GetColor(255, 255, 255);
	Data.gameover.FontScale = 50;
	Data.gameover.FontThick = 3;
	Data.gameover.FontHandle = CreateFontToHandle(NULL, Data.gameover.FontScale, Data.gameover.FontThick, DX_FONTTYPE_NORMAL);
	Data.gameover.StbWallpaperColor = GetColor(255, 255, 255);
	Data.gameover.TibWallpaperColor = GetColor(255, 255, 255);
	Data.gameover.QubWallpaperColor = GetColor(255, 255, 255);
	Data.gameover.InitWallpaperColor = GetColor(0, 128, 128);
	Data.gameover.TouchWallpaperColor = GetColor(0, 128, 255);

	//オプションシーン
	Data.option.Back = 0;
	Data.option.Bab = VGet(50.0f, 600.0f, 0.0f);
	Data.option.botExpansionX = 100.0f;
	Data.option.botExpansionY = 50.0f;
	Data.option.BabInitWallPaperColor = GetColor(0, 128, 128);
	Data.option.BabTouchWallPaperColor = GetColor(0, 128, 255);

	Data.option.SensitivityBoxX = VGet(100.0f, 50.0f, 0.0f);
	Data.option.SensitivityBoxY = VGet(100.0f, 100.0f, 0.0f);
	Data.option.SebExpansionX = 1000.0f;
	Data.option.SebExpansionY = 25.0f;
	Data.option.SenInitWallPaperColor = GetColor(0, 128, 128);
	Data.option.SenTouchWallPaperColor = GetColor(0, 128, 255);
	Data.option.SenPushWallPaperColor = GetColor(0, 128, 170);

	Data.option.SensitivityLineStartX = 125.0f;
	Data.option.SensitivityLineEndX = 1075.0f;
	Data.option.SensitivityXLineY = 62.5f;
	Data.option.SensitivityYLineY = 112.5f;
	Data.option.SensitivityCircleRadius = 10;

	Data.option.SensitivityX = 1.0f;
	Data.option.SensitivityY = 1.0f;
	Data.option.SensitivityFixed = 0.1f;
	Data.option.SensitivitySplit = 12;
	Data.option.Split = 10;
	Data.option.Calculation = pow(10, 2 - 1);

	Data.option.OnSensitivityBotan = VGet(-200, 200, 0);
	Data.option.OffSensitivityBotan = VGet(200, 200, 0);
	Data.option.SensiBotanExpansionX = 200.0f;
	Data.option.SensiBotanExpansionY = 200.0f;
	Data.option.OnSensiBotanWallPaperColor = GetColor(0, 128, 0);
	Data.option.OffSensiBotanWallPaperColor = GetColor(128, 0, 0);
	Data.option.SensiBotanRedWallPaperColor = GetColor(128, 0, 0);
	Data.option.SensiBotanGreenWallPaperColor = GetColor(0, 128, 0);

	Data.option.LineColor = GetColor(255, 255, 255);
	Data.option.CircleColor = GetColor(0, 100, 200);
	//システム関連
	Data.system.SensitivityX = 1;
	Data.system.SensitivityY = 1;
	Data.system.MouseSensitivity = 1;
	Data.system.K = 0;

	Data.option.FontColor = GetColor(255, 255, 255);
	Data.option.FontScale = 30;
	Data.option.FontThick = 3;
	Data.option.ValueScele = 15;
	Data.option.FontHandle = CreateFontToHandle(NULL, Data.option.FontScale, Data.option.FontThick, DX_FONTTYPE_NORMAL);
	//カメラ
	//カメラポジション
	Data.camera.Pos.x = 0.0f;
	Data.camera.Pos.y = 0.0f;
	Data.camera.Pos.z = 0.0f;

	Data.camera.radius = 50.0f;
	Data.camera.Radian = DX_PI_F / 180;
	Data.camera.InitRadian = 30.0f * DX_PI_F / 180;

	Data.camera.MaxDrawingRange = 2000.0f;
	Data.camera.MinDrawingRange = 10.0f;

	//当たり判定関係
	Data.collision.Expansion = 10.0f;

	//フィールドエリア
	//フィールドエリア始点
	Data.field.p = 0;
	Data.field.MaxHundle = 120;

	Data.field.GatePos.x = 0.0f;
	Data.field.GatePos.y = 0.0f;
	Data.field.GatePos.z = 4000.0f;

	Data.field.GatePos2.x = 300.0f;
	Data.field.GatePos2.y = 100.0f;
	Data.field.GatePos2.z = 4000.0f;

	Data.field.StartArea.x = 0;
	Data.field.StartArea.y = 0;
	Data.field.StartArea.z = 0;
	//フィールドエリア終点
	Data.field.EndArea.x = 1000;
	Data.field.EndArea.y = 50;
	Data.field.EndArea.z = 1000;
	//床色
	Data.field.Color = GetColor(255, 255, 200);
	Data.field.NoKickWallColor = GetColor(255, 0, 0);
	Data.field.LeftWallColor = GetColor(200, 200, 200);
	Data.field.RedWallColor = GetColor(100, 0, 0);

	Data.field.pos = VGet(0, 0, 0);
	Data.field.radian = 90.0f * DX_PI_F / 180.0f;
	
	//立方体に必要な値
	//頂点１
	Data.cube.obj1.x = 500.0f;
	Data.cube.obj1.y = 300.0f;
	Data.cube.obj1.z = 100.0f;
	//頂点２
	Data.cube.obj2.x = 450.0f;
	Data.cube.obj2.y = 300.0f;
	Data.cube.obj2.z = 50.0f;
	//表面色
	Data.cube.CubeColorR = 0;
	Data.cube.CubeColorG = 255;
	Data.cube.CubeColorB = 100;

	//線分に必要な値
	//色
	Data.line.ColorR = 0;
	Data.line.ColorG = 0;
	Data.line.ColorB = 0;

	//プレイヤー座標
	Data.wolf.Pos = VGet(200.0f, 100.0f, 0.0f);
	//Data.wolf.Pos = VGet(0.0f, 0.0f, 0.0f);
	Data.wolf.UnderLowwer = -200.0f;
	Data.wolf.InitPos = VGet(200.0f, 100.0f, 0.0f);
	//プレイヤー回転数
	Data.wolf.Angle = 0.0f;
	//アニメーション時間関係
	Data.wolf.PlayTime = 0.0f;
	Data.wolf.AnimTimeSpeed = 30.0f;
	//キャラクターの移動系統値
	Data.wolf.State = 0;
	Data.wolf.Gravity = 0.0f;
	Data.wolf.GravityPlusSpeed = 5.0f;
	Data.wolf.GravityUpperLimit = -6.0f;
	Data.wolf.JumpStock = 1;
	Data.wolf.JumpFloorStock = 2;
	Data.wolf.JumpWallStock = 1;
	Data.wolf.JumpPower = 2.0f;
	Data.wolf.JumpCoolDown = 0.5f;
	Data.wolf.JumpCoolTime = 0.0f;
	Data.wolf.WalkSpeed = 50.0f;
	Data.wolf.MaxWalkSpeed = 100.0f;
	Data.wolf.DashSpeed = 100.0f;
	Data.wolf.MaxDashSpeed = 200.0f;
	Data.wolf.MovingSpeed = 0.0f;
	Data.wolf.DownSpeed = 80.0f;
	//モデル情報
	MV1SetupReferenceMesh(Data.wolf.GraphicHundle, -1, TRUE);
	Data.wolf.Poligon = MV1GetReferenceMesh(Data.wolf.GraphicHundle, -1, TRUE);
	Data.wolf.ModelScale.x = 0.2f;
	Data.wolf.ModelScale.y = 0.2f;
	Data.wolf.ModelScale.z = 0.2f;
	//モデルの回転量
	Data.wolf.RadianZ = DX_PI_F / 2;
	//ゲームとしてのスコア関係値
	Data.wolf.Score = 0;
	Data.wolf.BonusScore = 1000.0f;
	Data.wolf.MscoreZ = 0;
	Data.wolf.ScoreVz = 0;

	Data.wolf.radius = 100.0f;
}
void CONTAINER::loadGraphic() {
	Data.wolf.GraphicHundle = MV1LoadModel("./\\model\\fbx\\Wolf.mv1");
	Data.wolf.AttachAnim = MV1AttachAnim(Data.wolf.GraphicHundle, 0, -1, FALSE);
	Data.field.GraphicHundle = MV1LoadModel("./\\model\\38-floor\\Floor.mv1");

	strcpy_s(Data.gameover.ScoreText, "スコア");
	strcpy_s(Data.gameover.RestartText, "リスタート");
	strcpy_s(Data.gameover.TitleText, "タイトル画面へ");
	strcpy_s(Data.gameover.QuitText, "ゲームを閉じる");

	strcpy_s(Data.option.OnSensitivityBotanText, "マウスによるカメラ操作 ON");
	strcpy_s(Data.option.OffSensitivityBotanText, "マウスによるカメラ操作 OFF");
	strcpy_s(Data.option.BackBotanText, "戻る");
	strcpy_s(Data.option.SensitivityXText, "マウスによるカメラ操作のX軸感度");
	strcpy_s(Data.option.SensitivityYText, "マウスによるカメラ操作のY軸感度");
	
	strcpy_s(Data.field.MapTile, "\
2113\n\
2113\n\
2113\n\
2113\n\
2113");

}