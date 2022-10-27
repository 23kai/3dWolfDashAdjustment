#pragma once
#include "OBJECTS.h"
#include"DxLib.h"

#define PLAYER_ANGLE_SPEED			0.2f		// 角度変化速度
class WOLF :
    public OBJECTS
{
public:
    //ONかOFFか
    enum ONOFF_ID {
        OFF_ID,
        ON_ID
    };
    //オオカミモデルのアニメーション番号
    enum ANIMATION_ID {
        CROUCHING_WALK_ID = 1,//しゃがみ歩き
        STAND_BY_ID,//待機モーション
        RUN_ID,//走る
        SIT_ID,//座る
        WALKING_ID//歩き
    };
    //プレイヤーの状態番号
    enum STATE_ID {
        HIT_FLOOR_ID=1,
        HIT_LEFTWALL_ID,
        HIT_RED_LEFTWALL_ID,
        HIT_RIGHTWALL_ID,
        HIT_RED_RIGHTWALL_ID,
        HIT_STRAGHTWALL_ID,
        HIT_GATE_ID,
        NUM_HITSTATE
    };
    //オオカミモデルのハンドルやアニメーション時間、座標の変数
    struct DATA {
        VECTOR Pos;//座標
        VECTOR MinPoligonPos;//最低座標
        VECTOR MaxPoligonPos;//最高座標
        VECTOR ModelScale;//モデルの大きさ
        MATRIX matrix;
        float UnderLowwer;//Y座標の最低値
        VECTOR InitPos;//位置初期化
        int GraphicHundle;//モデル番号
        VECTOR ModelCenterFrame;
        int AnimHundle;//アニメーション番号
        int AttachAnim;//アタッチするアニメーション
        int TotalTime;//アニメーションの総時間
        float PlayTime;//アニメーションの現時間
        float AnimTimeSpeed;//アニメーションの動く速度
        VECTOR TargetMoveDirection;//キャラクターが向くべき方向

        VECTOR UpMoveVec;//カメラから見て上に移動する値
        VECTOR LeftMoveVec;//カメラから見て左に移動する値
        VECTOR MoveVec;//移動方向値
        float Angle;// モデルが向いている方向の角度
        int AngleState;//回転方向の条件分岐
        float RadianZ;//Z軸の回転
        MATRIX Radian;//回転
        VECTOR RadianTranslation;

        float MovingSpeed;//移動速度
        float WalkSpeed;//歩き速度
        float DashSpeed;//ダッシュスピード
        int MovingCheck;//移動するかしないか
        float DownSpeed;//慣性が働く際のスピードを下げる値
        float MaxWalkSpeed;//移動速度の最大値
        float MaxDashSpeed;//ダッシュの最大速度

        int AirCheck;//空中確認値
        float JumpPower;//ジャンプ力
        float Gravity;//重力
        float GravityPlusSpeed;//重力加速度
        float GravityUpperLimit;//重力速度の上限値
        int JumpStock;//ジャンプ回数
        int JumpFloorStock;//地面についたときのジャンプ回数
        int JumpWallStock;//壁に張り付いた時のジャンプ回数
        float JumpCoolTime;//ジャンプの現再使用時間
        float JumpCoolDown;//ジャンプの再使用時間

        int State;//プレイヤーの状態
        int StateConditions[NUM_HITSTATE];//プレイヤーの重ならない条件の時
        int HitState[NUM_HITSTATE];//プレイヤーの状態を複数判定させる
        VECTOR HitVector;
        float StateTime;//状態の保持時間
        MV1_REF_POLYGONLIST Poligon;//ポリゴン情報
        
        VECTOR CollisionSphere;//当たり判定範囲指定用球体座標
        float radius;//当たり判定範囲指定用球体の半径

        float Score;//進んだ距離に応じたスコア
        float BonusScore;//ボーナススコア加算
        float ScoreVz;//プレイヤーの位置
        float MscoreZ;//プレイヤーが現在進んだ最高位置
    };
private:
    DATA Wolf;
public:
    WOLF(class GAME* game);
    ~WOLF();
    void create();//オブジェクト作成（値取得)
    void init();//初期化
    void update();//更新
    void draw();//描画
    void move();//移動
    void angleProcess();
    void animProcess();
    void attachAnim(enum ANIMATION_ID animId);
    void modelInit();
    void collision();
    float radius() { return Wolf.radius; }
    VECTOR CollisionCircle() { return Wolf.CollisionSphere; }
    VECTOR target() { return Wolf.Pos; }
    int state() { return Wolf.State; }
    int score() { return (int)Wolf.Score; }
};

