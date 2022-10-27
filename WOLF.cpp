#include "WOLF.h"
#include"GAME.h"
WOLF::WOLF(GAME* game) :
    OBJECTS(game)
{
}

WOLF::~WOLF()
{
    MV1DeleteModel(Wolf.GraphicHundle);
}

void WOLF::create()
{
    //値取得
    Wolf = game()->container()->wolf();
}

void WOLF::init()
{
    //初期化
    Wolf.AngleState = 0;
    Wolf.MovingCheck = 0;
    Wolf.State = 0;
    MV1SetScale(Wolf.GraphicHundle, Wolf.ModelScale);
    for (int i = 0; i < NUM_HITSTATE; i++) {
        Wolf.HitState[i] = 0;
        Wolf.StateConditions[i] = 0;
    }
    
    Wolf.ModelCenterFrame = MV1GetFramePosition(Wolf.GraphicHundle, 0);
    Wolf.MaxPoligonPos = Wolf.Poligon.MaxPosition;
    Wolf.MinPoligonPos = Wolf.Poligon.MinPosition;

}

void WOLF::update()
{
    init();
    animProcess();
    //当たり判定
    collision();
    move();
    // 再生時間を進める
    Wolf.PlayTime += Wolf.AnimTimeSpeed * game()->DeltaTime;

    // 再生時間がアニメーションの総再生時間に達したら再生時間を０に戻す
    if (Wolf.PlayTime >= Wolf.TotalTime && Wolf.AnimHundle != SIT_ID)
    {
        Wolf.PlayTime = 0.0f;
    }

    // 再生時間をセットする
    MV1SetAttachAnimTime(Wolf.GraphicHundle, Wolf.AttachAnim, Wolf.PlayTime);

    Wolf.matrix=MV1GetMatrix(Wolf.GraphicHundle);
}

void WOLF::draw()
{
    MV1SetMatrix(Wolf.GraphicHundle, MMult(MGetScale(Wolf.ModelScale), MMult(Wolf.Radian, MMult(MGetTranslate(Wolf.Pos), MGetTranslate(Wolf.RadianTranslation)))));
    MV1DrawModel(Wolf.GraphicHundle);//モデルの描画
}

void WOLF::move()
{
    if (Wolf.MscoreZ < Wolf.ScoreVz) {
        Wolf.MscoreZ = Wolf.ScoreVz;
    }
    
    // 方向ボタン「↑」を押したときのプレイヤーの移動ベクトルはカメラの視線方向からＹ成分を抜いたもの
    Wolf.UpMoveVec = VSub(game()->camera()->target(), game()->camera()->pos());
    Wolf.UpMoveVec.y = 0.0f;
    // 方向ボタン「←」を押したときのプレイヤーの移動ベクトルは上を押したときの方向ベクトルとＹ軸のプラス方向のベクトルに垂直な方向
    Wolf.LeftMoveVec = VCross(Wolf.UpMoveVec, VGet(0.0f, 1.0f, 0.0f));

    // 方向ボタン「←」が入力されたらカメラの見ている方向から見て左方向に移動する
    if (game()->system()->CheckKey(KEY_INPUT_A) > 0)
    {
        // 移動ベクトルに「←」が入力された時の移動ベクトルを加算する
        Wolf.MoveVec = VAdd(Wolf.MoveVec, Wolf.LeftMoveVec);
        if (Wolf.MovingSpeed < Wolf.MaxWalkSpeed)
            Wolf.MovingSpeed += Wolf.WalkSpeed * game()->DeltaTime;
        Wolf.MovingCheck = WALKING_ID;
        if (game()->system()->CheckKey(KEY_INPUT_LSHIFT) > 0) {
            if (Wolf.MovingSpeed < Wolf.MaxDashSpeed)
                Wolf.MovingSpeed += Wolf.DashSpeed * game()->DeltaTime;
            Wolf.MovingCheck = RUN_ID;
        }
    }
    else
        // 方向ボタン「→」が入力されたらカメラの見ている方向から見て右方向に移動する
        if (game()->system()->CheckKey(KEY_INPUT_D) > 0)
        {
            // 移動ベクトルに「←」が入力された時の移動ベクトルを反転したものを加算する
            Wolf.MoveVec = VAdd(Wolf.MoveVec, VScale(Wolf.LeftMoveVec, -1.0f));
            if (Wolf.MovingSpeed < Wolf.MaxWalkSpeed)
                Wolf.MovingSpeed += Wolf.WalkSpeed * game()->DeltaTime;
            Wolf.MovingCheck = WALKING_ID;
            if (game()->system()->CheckKey(KEY_INPUT_LSHIFT) > 0) {
                if (Wolf.MovingSpeed < Wolf.MaxDashSpeed)
                    Wolf.MovingSpeed += Wolf.DashSpeed * game()->DeltaTime;
                Wolf.MovingCheck = RUN_ID;
            }
        }

    // 方向ボタン「↑」が入力されたらカメラの見ている方向に移動する
    if (game()->system()->CheckKey(KEY_INPUT_W) > 0)
    {
        // 移動ベクトルに「↑」が入力された時の移動ベクトルを加算する
        Wolf.MoveVec = VAdd(Wolf.MoveVec, Wolf.UpMoveVec);
        if (Wolf.MovingSpeed < Wolf.MaxWalkSpeed)
            Wolf.MovingSpeed += Wolf.WalkSpeed * game()->DeltaTime;
        Wolf.MovingCheck = WALKING_ID;
        if (game()->system()->CheckKey(KEY_INPUT_LSHIFT) > 0) {
            if (Wolf.MovingSpeed < Wolf.MaxDashSpeed)
                Wolf.MovingSpeed += Wolf.DashSpeed * game()->DeltaTime;
            Wolf.MovingCheck = RUN_ID;
        }
    }
    else
        // 方向ボタン「↓」が入力されたらカメラの方向に移動する
        if (game()->system()->CheckKey(KEY_INPUT_S) > 0)
        {
            // 移動ベクトルに「↑」が入力された時の移動ベクトルを反転したものを加算する
            Wolf.MoveVec = VAdd(Wolf.MoveVec, VScale(Wolf.UpMoveVec, -1.0f));
            if (Wolf.MovingSpeed < Wolf.MaxWalkSpeed)
                Wolf.MovingSpeed += Wolf.WalkSpeed * game()->DeltaTime;
            Wolf.MovingCheck = WALKING_ID;
            //ダッシュ
            if (game()->system()->CheckKey(KEY_INPUT_LSHIFT) > 0) {
                if (Wolf.MovingSpeed < Wolf.MaxDashSpeed)
                    Wolf.MovingSpeed += Wolf.DashSpeed * game()->DeltaTime;
                Wolf.MovingCheck = RUN_ID;
            }
        }

    if (Wolf.MovingCheck== WALKING_ID &&Wolf.MaxWalkSpeed < Wolf.MovingSpeed) {
        Wolf.MovingSpeed -= Wolf.DashSpeed*game()->DeltaTime;
    }


    //空中確認
    if(Wolf.State == 0 ) {
        if(Wolf.Gravity>Wolf.GravityUpperLimit)
            Wolf.Gravity -= Wolf.GravityPlusSpeed*game()->DeltaTime;
        Wolf.AirCheck = ON_ID;
    }
    //地面判定
    if (Wolf.HitState[HIT_FLOOR_ID]) {
        Wolf.Gravity = 0;
        Wolf.JumpStock = Wolf.JumpFloorStock;
        Wolf.JumpCoolTime = 0;
    }

    //左壁判定
    if (Wolf.HitState[HIT_LEFTWALL_ID]) {
        Wolf.State = HIT_LEFTWALL_ID;
        if (Wolf.MovingSpeed > Wolf.MaxWalkSpeed && Wolf.MoveVec.x < 0) {
            //Wolf.Gravity = 0;
            Wolf.Gravity = -Wolf.MoveVec.x * game()->DeltaTime;
            Wolf.JumpStock = Wolf.JumpWallStock;
            Wolf.AngleState = LEFT_WALL_ID;
        }

    }
    if (Wolf.HitState[HIT_RED_LEFTWALL_ID]) {
        Wolf.State = HIT_RED_LEFTWALL_ID;
    }

    //右壁判定
    if (Wolf.HitState[HIT_RIGHTWALL_ID]) {
        Wolf.State = HIT_RIGHTWALL_ID;
        if (Wolf.MovingSpeed >= Wolf.MaxWalkSpeed && Wolf.MoveVec.x > 0) {
            //Wolf.Gravity = 0;
            Wolf.Gravity = Wolf.MoveVec.x * game()->DeltaTime;
            Wolf.JumpStock = Wolf.JumpWallStock;
            Wolf.AngleState = RIGHT_WALL_ID;
        }
    }
    if (Wolf.HitState[HIT_RED_RIGHTWALL_ID]) {
        Wolf.State = HIT_RED_RIGHTWALL_ID;
    }
    //一周する壁の判定
    if (Wolf.HitState[HIT_GATE_ID]) {
        Wolf.Pos = Wolf.InitPos;
        game()->field()->loop();
        Wolf.MscoreZ = Wolf.Pos.z;
        Wolf.Score += Wolf.BonusScore;
    }
    if (Wolf.StateTime > 0) {
        Wolf.StateTime -= game()->DeltaTime;
    }

    //ジャンプ
    if (game()->system()->CheckKey(KEY_INPUT_SPACE) > 0 && Wolf.JumpStock > 0 && Wolf.JumpCoolTime <= 0) {
        --Wolf.JumpStock;
        Wolf.JumpCoolTime = Wolf.JumpCoolDown;
        Wolf.Gravity = 0;
        Wolf.Gravity += Wolf.JumpPower;
    }
    //ジャンプクールタイム
    if (Wolf.JumpCoolTime > 0) {
        //Wolf.Gravity += Wolf.JumpPower * game()->DeltaTime;
        Wolf.JumpCoolTime -= game()->DeltaTime;
    } 
    //移動するかしないか
    if (Wolf.MovingCheck) {

        // 移動ベクトルを正規化したものをプレイヤーが向くべき方向として保存
        Wolf.TargetMoveDirection = VNorm(Wolf.MoveVec);

        // プレイヤーが向くべき方向ベクトルをプレイヤーのスピード倍したものを移動ベクトルとする
        Wolf.MoveVec = VScale(Wolf.TargetMoveDirection, Wolf.MovingSpeed*game()->DeltaTime);

        //条件により要らない移動ベクトルの初期化
        if (Wolf.HitState[HIT_LEFTWALL_ID] && Wolf.MoveVec.x < 0) {
            Wolf.MoveVec.x = 0;
        }
        if (Wolf.HitState[HIT_RED_LEFTWALL_ID] && Wolf.MoveVec.x > 0) {
            Wolf.MoveVec.x = 0;
        }
        if (Wolf.HitState[HIT_RIGHTWALL_ID] && Wolf.MoveVec.x > 0) {
            Wolf.MoveVec.x = 0;
        }
        if (Wolf.HitState[HIT_RED_RIGHTWALL_ID] && Wolf.MoveVec.x < 0) {
            Wolf.MoveVec.x = 0;
            
        }
        
        //ベクトル加算
        Wolf.Pos = VAdd(Wolf.Pos, Wolf.MoveVec);
        angleProcess();

    }
    else if(Wolf.MovingSpeed>0) {
        Wolf.MovingSpeed -= Wolf.DownSpeed*game()->DeltaTime;
        // 移動ベクトルを正規化したものをプレイヤーが向くべき方向として保存
        Wolf.TargetMoveDirection = VNorm(Wolf.MoveVec);

        // プレイヤーが向くべき方向ベクトルをプレイヤーのスピード倍したものを移動ベクトルとする
        Wolf.MoveVec = VScale(Wolf.TargetMoveDirection, Wolf.MovingSpeed * game()->DeltaTime);

        //条件により要らない移動ベクトルの初期化
        if (Wolf.HitState[HIT_FLOOR_ID]) {
            Wolf.MoveVec.y = 0;
            //Wolf.Gravity = 0;
        }
        if (Wolf.HitState[HIT_LEFTWALL_ID] && Wolf.MoveVec.x < 0) {
            Wolf.MoveVec.x = 0;
            Wolf.MoveVec.y = 0;
            Wolf.MoveVec.z = 0;
        }
        if (Wolf.HitState[HIT_RED_LEFTWALL_ID] && Wolf.MoveVec.x > 0) {
            Wolf.MoveVec.x = 0;
            Wolf.MoveVec.y = 0;
            Wolf.MoveVec.z = 0;
        }
        if (Wolf.HitState[HIT_RIGHTWALL_ID] && Wolf.MoveVec.x > 0) {
            Wolf.MoveVec.x = 0;
            Wolf.MoveVec.y = 0;
            Wolf.MoveVec.z = 0;
        }
        if (Wolf.HitState[HIT_RED_RIGHTWALL_ID] && Wolf.MoveVec.x < 0) {
            Wolf.MoveVec.x = 0;
            Wolf.MoveVec.y = 0;
            Wolf.MoveVec.z = 0;
        }
        Wolf.Pos = VAdd(Wolf.Pos, Wolf.MoveVec);
        angleProcess();
    }
    if (Wolf.AirCheck) {
        Wolf.Pos = VAdd(Wolf.Pos,VGet(0,Wolf.Gravity, 0));
        Wolf.AirCheck = 0;
    }
    if (Wolf.Pos.y <= Wolf.UnderLowwer) {
        Wolf.State = 1;
    }
    Wolf.ScoreVz = Wolf.Pos.z;
    if (Wolf.MscoreZ < Wolf.ScoreVz) {
            Wolf.Score += Wolf.ScoreVz - Wolf.MscoreZ;
    }
    //DrawFormatString(0, 100, GetColor(255, 255, 255), "Score=%f", Wolf.Score);

}

void WOLF::angleProcess()
{// プレイヤーの向きを変える処理
        float TargetAngle;			// 目標角度
        float SaAngle;				// 目標角度と現在の角度との差
        MV1SetRotationXYZ(Wolf.GraphicHundle, VGet(0.0f, 0.0f, 0.0f));
        // 目標の方向ベクトルから角度値を算出する
        TargetAngle = atan2(Wolf.TargetMoveDirection.x, Wolf.TargetMoveDirection.z);
        // 目標の角度と現在の角度との差を割り出す
        {
            // 最初は単純に引き算
            SaAngle = TargetAngle - Wolf.Angle;

            // ある方向からある方向の差が１８０度以上になることは無いので
            // 差の値が１８０度以上になっていたら修正する
            if (SaAngle < -DX_PI_F)
            {
                SaAngle += DX_TWO_PI_F;
            }
            else
                if (SaAngle > DX_PI_F)
                {
                    SaAngle -= DX_TWO_PI_F;
                }
        }

        // 角度の差が０に近づける
        if (SaAngle > 0.0f)
        {
            // 差がプラスの場合は引く
            SaAngle -= PLAYER_ANGLE_SPEED;
            if (SaAngle < 0.0f)
            {
                SaAngle = 0.0f;
            }
        }
        else
        {
            // 差がマイナスの場合は足す
            SaAngle += PLAYER_ANGLE_SPEED;
            if (SaAngle > 0.0f)
            {
                SaAngle = 0.0f;
            }
        }
        // モデルの角度を更新
        Wolf.Angle = TargetAngle - SaAngle;
        MV1SetRotationXYZ(Wolf.GraphicHundle, VGet(0.0f, Wolf.Angle + DX_PI_F, 0.0f));
        Wolf.Radian = MGetRotY(Wolf.Angle + DX_PI_F);
        Wolf.RadianTranslation = VGet(0, 0, 0);
        //壁を走る際のモデルの向き
        if (Wolf.AngleState == LEFT_WALL_ID) {
            Wolf.Radian = MMult(MGetRotY(Wolf.Angle + DX_PI_F), MGetRotZ(-Wolf.RadianZ));
            Wolf.RadianTranslation = VGet(Wolf.MinPoligonPos.z * Wolf.ModelScale.z, 0, 0);
        }
        else if (Wolf.AngleState == RIGHT_WALL_ID) {
            Wolf.Radian = MMult(MGetRotY(Wolf.Angle + DX_PI_F), MGetRotZ(Wolf.RadianZ));
            Wolf.RadianTranslation = VGet(-Wolf.MinPoligonPos.z * Wolf.ModelScale.z, 0, 0);
        }
}

void WOLF::animProcess()
{
    //移動モーション
    if (game()->system()->CheckKey(KEY_INPUT_W) > 0 || game()->system()->CheckKey(KEY_INPUT_S) > 0 ||
        game()->system()->CheckKey(KEY_INPUT_A) > 0 || game()->system()->CheckKey(KEY_INPUT_D) > 0) {//Wキーの判定

        if (game()->system()->CheckKey(KEY_INPUT_C) > 0) {//Cキーの判定
            if (Wolf.AnimHundle != CROUCHING_WALK_ID)//今のアニメーションが次のアニメーションと違うかどうか
                attachAnim(CROUCHING_WALK_ID);
            return;
        }
        if (CheckHitKey(KEY_INPUT_LSHIFT) > 0) {
            if (Wolf.AnimHundle != RUN_ID)//今のアニメーションが次のアニメーションと違うかどうか
                attachAnim(RUN_ID);
            return;
        }
        if (Wolf.AnimHundle != WALKING_ID)//今のアニメーションが次のアニメーションと違うかどうか
            attachAnim(WALKING_ID);
        return;
    }
    if (CheckHitKey(KEY_INPUT_C) > 0) {//Cキーのみの判定かつ今のアニメーションが次のアニメーションと違うかどうか
        if (Wolf.AnimHundle != SIT_ID)
            attachAnim(SIT_ID);
        return;
    }
    if (Wolf.AnimHundle != STAND_BY_ID)
        attachAnim(STAND_BY_ID);
}

void WOLF::attachAnim(enum ANIMATION_ID animId)
{
    modelInit();//モデルの初期化
    Wolf.PlayTime = 0.0f;//再生時間を０に
    MV1DetachAnim(Wolf.AnimHundle, Wolf.AttachAnim);//現在のアニメーションのデタッチ
    Wolf.AttachAnim = MV1AttachAnim(Wolf.GraphicHundle, animId, -1, FALSE);//アニメーションのアタッチ
    Wolf.TotalTime = MV1GetAttachAnimTotalTime(Wolf.GraphicHundle, Wolf.AttachAnim);//現在のアニメーションの総時間
    Wolf.AnimHundle = animId;//現在のアニメーション番号
    MV1SetPosition(Wolf.GraphicHundle, Wolf.Pos);//モデルの座標セット

}

void WOLF::modelInit()
{
    Wolf.GraphicHundle = MV1DuplicateModel(Wolf.GraphicHundle);//モデルの初期化
    MV1SetScale(Wolf.GraphicHundle, Wolf.ModelScale);//モデルの大きさの調整
    angleProcess();//回転角度
    MV1SetPosition(Wolf.GraphicHundle, Wolf.Pos);//モデルの座標セット
    Wolf.PlayTime = 0.0f;//再生時間を０に

}

void WOLF::collision()
{
    Wolf.CollisionSphere = Wolf.Pos;
    int Hit=0,NextFrameHit=0;
    //game()->collision()->HitCollision(Wolf.Pos, Wolf.radius);
    for (int j = 0; game()->collision()->collisionStop(j) != 0; j++) {
        if (game()->collision()->collisionStop(j) == FLOOR_ID) {
            NextFrameHit = game()->collision()->collision(VGet(Wolf.Pos.x,Wolf.Pos.y+Wolf.Gravity,Wolf.Pos.z), Wolf.MaxPoligonPos, Wolf.MinPoligonPos, Wolf.matrix, FLOOR_ID);
            if (NextFrameHit == FLOOR_ID) {
                Wolf.HitState[HIT_FLOOR_ID] = ON_ID;//地面と衝突している
                Wolf.HitVector = game()->collision()->HitCollision();//衝突座標取り出し
                if (Wolf.Pos.y < Wolf.HitVector.y - 0.3f) {
                    Wolf.Pos.y = Wolf.HitVector.y;
                }
            }
        }
        if (game()->collision()->collisionStop(j) == LEFT_WALL_ID) {
            NextFrameHit = game()->collision()->collision(VGet(Wolf.Pos.x + Wolf.MoveVec.x, Wolf.Pos.y + Wolf.Gravity, Wolf.Pos.z + Wolf.MoveVec.z), Wolf.MaxPoligonPos, Wolf.MinPoligonPos, Wolf.matrix, LEFT_WALL_ID);
            if (NextFrameHit == LEFT_WALL_ID) {
                Wolf.HitState[HIT_LEFTWALL_ID] = ON_ID;//左壁と衝突している
                Wolf.HitVector = game()->collision()->HitCollision();//衝突座標取り出し
                if (Wolf.MinPoligonPos.z * Wolf.matrix.m[0][2] < Wolf.HitVector.x && Wolf.MinPoligonPos.z * Wolf.matrix.m[0][2] > 0) { //
                    Wolf.Pos.x = Wolf.HitVector.x+Wolf.MinPoligonPos.z * Wolf.matrix.m[0][2];
                    if (Wolf.MoveVec.x < 0) {
                        Wolf.StateConditions[HIT_LEFTWALL_ID] = ON_ID;
                    }
                }
            }
        }
        if (game()->collision()->collisionStop(j) == RED_LEFT_WALL_ID) {
            NextFrameHit = game()->collision()->collision(VGet(Wolf.Pos.x + Wolf.MoveVec.x, Wolf.Pos.y + Wolf.Gravity, Wolf.Pos.z + Wolf.MoveVec.z), Wolf.MaxPoligonPos, Wolf.MinPoligonPos, Wolf.matrix, RED_LEFT_WALL_ID);
            if (NextFrameHit == RED_LEFT_WALL_ID) {
                Wolf.HitState[HIT_RED_LEFTWALL_ID] = ON_ID;
                Wolf.HitVector = game()->collision()->HitCollision();
                if (Wolf.MaxPoligonPos.z * Wolf.matrix.m[0][2] < Wolf.HitVector.x && Wolf.MaxPoligonPos.z * Wolf.matrix.m[0][2] > 0 && !Wolf.StateConditions[HIT_LEFTWALL_ID]) {
                    Wolf.Pos.x = Wolf.HitVector.x - Wolf.MaxPoligonPos.z * Wolf.matrix.m[0][2];
                }
            }
        }
        if (game()->collision()->collisionStop(j) == RIGHT_WALL_ID) {
            NextFrameHit = game()->collision()->collision(VGet(Wolf.Pos.x + Wolf.MoveVec.x, Wolf.Pos.y + Wolf.Gravity, Wolf.Pos.z + Wolf.MoveVec.z), Wolf.MaxPoligonPos, Wolf.MinPoligonPos, Wolf.matrix, RIGHT_WALL_ID);
            if (NextFrameHit == RIGHT_WALL_ID) {
                Wolf.HitState[HIT_RIGHTWALL_ID] = ON_ID;
                Wolf.HitVector = game()->collision()->HitCollision();
                if (Wolf.MaxPoligonPos.z * Wolf.matrix.m[0][2] < Wolf.HitVector.x && Wolf.MaxPoligonPos.z * Wolf.matrix.m[0][2] > 0) {
                    Wolf.Pos.x = Wolf.HitVector.x + Wolf.MinPoligonPos.z * Wolf.matrix.m[0][2];
                    if (Wolf.MoveVec.x > 0) {
                        Wolf.StateConditions[HIT_RIGHTWALL_ID] = ON_ID;
                    }
                }
            }
        }
        if (game()->collision()->collisionStop(j) == RED_RIGHT_WALL_ID) {
            NextFrameHit = game()->collision()->collision(VGet(Wolf.Pos.x + Wolf.MoveVec.x, Wolf.Pos.y + Wolf.Gravity, Wolf.Pos.z + Wolf.MoveVec.z), Wolf.MaxPoligonPos, Wolf.MinPoligonPos, Wolf.matrix, RED_RIGHT_WALL_ID);
            if (NextFrameHit == RED_RIGHT_WALL_ID) {
                Wolf.HitState[HIT_RED_RIGHTWALL_ID] = ON_ID;
                Wolf.HitVector = game()->collision()->HitCollision();
                if (Wolf.MinPoligonPos.z * Wolf.matrix.m[0][2] < Wolf.HitVector.x && Wolf.MinPoligonPos.z * Wolf.matrix.m[0][2] > 0 && !Wolf.StateConditions[HIT_RIGHTWALL_ID]) {
                    Wolf.Pos.x = Wolf.HitVector.x + Wolf.MinPoligonPos.z * Wolf.matrix.m[0][2];
                }
            }
        }
        if (game()->collision()->collisionStop(j) == STRAGHT_WALL_ID) {
            NextFrameHit = game()->collision()->collision(VGet(Wolf.Pos.x + Wolf.MoveVec.x, Wolf.Pos.y + Wolf.Gravity, Wolf.Pos.z + Wolf.MoveVec.z), Wolf.MaxPoligonPos, Wolf.MinPoligonPos, Wolf.matrix, STRAGHT_WALL_ID);
            if (NextFrameHit == STRAGHT_WALL_ID) {
                Wolf.HitState[HIT_STRAGHTWALL_ID] = ON_ID;
                Wolf.HitVector = game()->collision()->HitCollision();
                if (Wolf.MinPoligonPos.x * Wolf.matrix.m[0][0] < Wolf.HitVector.z && Wolf.MinPoligonPos.x * Wolf.matrix.m[0][0] > 0 ) {
                    Wolf.Pos.z = Wolf.HitVector.z + Wolf.MinPoligonPos.x * Wolf.matrix.m[0][0];
                }
            }
        }
        if (game()->collision()->collisionStop(j) == GATE_ID) {
            NextFrameHit = game()->collision()->collision(VGet(Wolf.Pos.x + Wolf.MoveVec.x, Wolf.Pos.y + Wolf.Gravity, Wolf.Pos.z + Wolf.MoveVec.z), Wolf.MaxPoligonPos, Wolf.MinPoligonPos, Wolf.matrix, GATE_ID);
            if (NextFrameHit == GATE_ID) {
                Wolf.HitState[HIT_GATE_ID] = ON_ID;
            }
        }
        game()->collision()->collisionNext();
    }

}
