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
    //�l�擾
    Wolf = game()->container()->wolf();
}

void WOLF::init()
{
    //������
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
    //�����蔻��
    collision();
    move();
    // �Đ����Ԃ�i�߂�
    Wolf.PlayTime += Wolf.AnimTimeSpeed * game()->DeltaTime;

    // �Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB������Đ����Ԃ��O�ɖ߂�
    if (Wolf.PlayTime >= Wolf.TotalTime && Wolf.AnimHundle != SIT_ID)
    {
        Wolf.PlayTime = 0.0f;
    }

    // �Đ����Ԃ��Z�b�g����
    MV1SetAttachAnimTime(Wolf.GraphicHundle, Wolf.AttachAnim, Wolf.PlayTime);

    Wolf.matrix=MV1GetMatrix(Wolf.GraphicHundle);
}

void WOLF::draw()
{
    MV1SetMatrix(Wolf.GraphicHundle, MMult(MGetScale(Wolf.ModelScale), MMult(Wolf.Radian, MMult(MGetTranslate(Wolf.Pos), MGetTranslate(Wolf.RadianTranslation)))));
    MV1DrawModel(Wolf.GraphicHundle);//���f���̕`��
}

void WOLF::move()
{
    if (Wolf.MscoreZ < Wolf.ScoreVz) {
        Wolf.MscoreZ = Wolf.ScoreVz;
    }
    
    // �����{�^���u���v���������Ƃ��̃v���C���[�̈ړ��x�N�g���̓J�����̎�����������x�����𔲂�������
    Wolf.UpMoveVec = VSub(game()->camera()->target(), game()->camera()->pos());
    Wolf.UpMoveVec.y = 0.0f;
    // �����{�^���u���v���������Ƃ��̃v���C���[�̈ړ��x�N�g���͏���������Ƃ��̕����x�N�g���Ƃx���̃v���X�����̃x�N�g���ɐ����ȕ���
    Wolf.LeftMoveVec = VCross(Wolf.UpMoveVec, VGet(0.0f, 1.0f, 0.0f));

    // �����{�^���u���v�����͂��ꂽ��J�����̌��Ă���������猩�č������Ɉړ�����
    if (game()->system()->CheckKey(KEY_INPUT_A) > 0)
    {
        // �ړ��x�N�g���Ɂu���v�����͂��ꂽ���̈ړ��x�N�g�������Z����
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
        // �����{�^���u���v�����͂��ꂽ��J�����̌��Ă���������猩�ĉE�����Ɉړ�����
        if (game()->system()->CheckKey(KEY_INPUT_D) > 0)
        {
            // �ړ��x�N�g���Ɂu���v�����͂��ꂽ���̈ړ��x�N�g���𔽓]�������̂����Z����
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

    // �����{�^���u���v�����͂��ꂽ��J�����̌��Ă�������Ɉړ�����
    if (game()->system()->CheckKey(KEY_INPUT_W) > 0)
    {
        // �ړ��x�N�g���Ɂu���v�����͂��ꂽ���̈ړ��x�N�g�������Z����
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
        // �����{�^���u���v�����͂��ꂽ��J�����̕����Ɉړ�����
        if (game()->system()->CheckKey(KEY_INPUT_S) > 0)
        {
            // �ړ��x�N�g���Ɂu���v�����͂��ꂽ���̈ړ��x�N�g���𔽓]�������̂����Z����
            Wolf.MoveVec = VAdd(Wolf.MoveVec, VScale(Wolf.UpMoveVec, -1.0f));
            if (Wolf.MovingSpeed < Wolf.MaxWalkSpeed)
                Wolf.MovingSpeed += Wolf.WalkSpeed * game()->DeltaTime;
            Wolf.MovingCheck = WALKING_ID;
            //�_�b�V��
            if (game()->system()->CheckKey(KEY_INPUT_LSHIFT) > 0) {
                if (Wolf.MovingSpeed < Wolf.MaxDashSpeed)
                    Wolf.MovingSpeed += Wolf.DashSpeed * game()->DeltaTime;
                Wolf.MovingCheck = RUN_ID;
            }
        }

    if (Wolf.MovingCheck== WALKING_ID &&Wolf.MaxWalkSpeed < Wolf.MovingSpeed) {
        Wolf.MovingSpeed -= Wolf.DashSpeed*game()->DeltaTime;
    }


    //�󒆊m�F
    if(Wolf.State == 0 ) {
        if(Wolf.Gravity>Wolf.GravityUpperLimit)
            Wolf.Gravity -= Wolf.GravityPlusSpeed*game()->DeltaTime;
        Wolf.AirCheck = ON_ID;
    }
    //�n�ʔ���
    if (Wolf.HitState[HIT_FLOOR_ID]) {
        Wolf.Gravity = 0;
        Wolf.JumpStock = Wolf.JumpFloorStock;
        Wolf.JumpCoolTime = 0;
    }

    //���ǔ���
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

    //�E�ǔ���
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
    //�������ǂ̔���
    if (Wolf.HitState[HIT_GATE_ID]) {
        Wolf.Pos = Wolf.InitPos;
        game()->field()->loop();
        Wolf.MscoreZ = Wolf.Pos.z;
        Wolf.Score += Wolf.BonusScore;
    }
    if (Wolf.StateTime > 0) {
        Wolf.StateTime -= game()->DeltaTime;
    }

    //�W�����v
    if (game()->system()->CheckKey(KEY_INPUT_SPACE) > 0 && Wolf.JumpStock > 0 && Wolf.JumpCoolTime <= 0) {
        --Wolf.JumpStock;
        Wolf.JumpCoolTime = Wolf.JumpCoolDown;
        Wolf.Gravity = 0;
        Wolf.Gravity += Wolf.JumpPower;
    }
    //�W�����v�N�[���^�C��
    if (Wolf.JumpCoolTime > 0) {
        //Wolf.Gravity += Wolf.JumpPower * game()->DeltaTime;
        Wolf.JumpCoolTime -= game()->DeltaTime;
    } 
    //�ړ����邩���Ȃ���
    if (Wolf.MovingCheck) {

        // �ړ��x�N�g���𐳋K���������̂��v���C���[�������ׂ������Ƃ��ĕۑ�
        Wolf.TargetMoveDirection = VNorm(Wolf.MoveVec);

        // �v���C���[�������ׂ������x�N�g�����v���C���[�̃X�s�[�h�{�������̂��ړ��x�N�g���Ƃ���
        Wolf.MoveVec = VScale(Wolf.TargetMoveDirection, Wolf.MovingSpeed*game()->DeltaTime);

        //�����ɂ��v��Ȃ��ړ��x�N�g���̏�����
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
        
        //�x�N�g�����Z
        Wolf.Pos = VAdd(Wolf.Pos, Wolf.MoveVec);
        angleProcess();

    }
    else if(Wolf.MovingSpeed>0) {
        Wolf.MovingSpeed -= Wolf.DownSpeed*game()->DeltaTime;
        // �ړ��x�N�g���𐳋K���������̂��v���C���[�������ׂ������Ƃ��ĕۑ�
        Wolf.TargetMoveDirection = VNorm(Wolf.MoveVec);

        // �v���C���[�������ׂ������x�N�g�����v���C���[�̃X�s�[�h�{�������̂��ړ��x�N�g���Ƃ���
        Wolf.MoveVec = VScale(Wolf.TargetMoveDirection, Wolf.MovingSpeed * game()->DeltaTime);

        //�����ɂ��v��Ȃ��ړ��x�N�g���̏�����
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
{// �v���C���[�̌�����ς��鏈��
        float TargetAngle;			// �ڕW�p�x
        float SaAngle;				// �ڕW�p�x�ƌ��݂̊p�x�Ƃ̍�
        MV1SetRotationXYZ(Wolf.GraphicHundle, VGet(0.0f, 0.0f, 0.0f));
        // �ڕW�̕����x�N�g������p�x�l���Z�o����
        TargetAngle = atan2(Wolf.TargetMoveDirection.x, Wolf.TargetMoveDirection.z);
        // �ڕW�̊p�x�ƌ��݂̊p�x�Ƃ̍�������o��
        {
            // �ŏ��͒P���Ɉ����Z
            SaAngle = TargetAngle - Wolf.Angle;

            // ����������炠������̍����P�W�O�x�ȏ�ɂȂ邱�Ƃ͖����̂�
            // ���̒l���P�W�O�x�ȏ�ɂȂ��Ă�����C������
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

        // �p�x�̍����O�ɋ߂Â���
        if (SaAngle > 0.0f)
        {
            // �����v���X�̏ꍇ�͈���
            SaAngle -= PLAYER_ANGLE_SPEED;
            if (SaAngle < 0.0f)
            {
                SaAngle = 0.0f;
            }
        }
        else
        {
            // �����}�C�i�X�̏ꍇ�͑���
            SaAngle += PLAYER_ANGLE_SPEED;
            if (SaAngle > 0.0f)
            {
                SaAngle = 0.0f;
            }
        }
        // ���f���̊p�x���X�V
        Wolf.Angle = TargetAngle - SaAngle;
        MV1SetRotationXYZ(Wolf.GraphicHundle, VGet(0.0f, Wolf.Angle + DX_PI_F, 0.0f));
        Wolf.Radian = MGetRotY(Wolf.Angle + DX_PI_F);
        Wolf.RadianTranslation = VGet(0, 0, 0);
        //�ǂ𑖂�ۂ̃��f���̌���
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
    //�ړ����[�V����
    if (game()->system()->CheckKey(KEY_INPUT_W) > 0 || game()->system()->CheckKey(KEY_INPUT_S) > 0 ||
        game()->system()->CheckKey(KEY_INPUT_A) > 0 || game()->system()->CheckKey(KEY_INPUT_D) > 0) {//W�L�[�̔���

        if (game()->system()->CheckKey(KEY_INPUT_C) > 0) {//C�L�[�̔���
            if (Wolf.AnimHundle != CROUCHING_WALK_ID)//���̃A�j���[�V���������̃A�j���[�V�����ƈႤ���ǂ���
                attachAnim(CROUCHING_WALK_ID);
            return;
        }
        if (CheckHitKey(KEY_INPUT_LSHIFT) > 0) {
            if (Wolf.AnimHundle != RUN_ID)//���̃A�j���[�V���������̃A�j���[�V�����ƈႤ���ǂ���
                attachAnim(RUN_ID);
            return;
        }
        if (Wolf.AnimHundle != WALKING_ID)//���̃A�j���[�V���������̃A�j���[�V�����ƈႤ���ǂ���
            attachAnim(WALKING_ID);
        return;
    }
    if (CheckHitKey(KEY_INPUT_C) > 0) {//C�L�[�݂̂̔��肩���̃A�j���[�V���������̃A�j���[�V�����ƈႤ���ǂ���
        if (Wolf.AnimHundle != SIT_ID)
            attachAnim(SIT_ID);
        return;
    }
    if (Wolf.AnimHundle != STAND_BY_ID)
        attachAnim(STAND_BY_ID);
}

void WOLF::attachAnim(enum ANIMATION_ID animId)
{
    modelInit();//���f���̏�����
    Wolf.PlayTime = 0.0f;//�Đ����Ԃ��O��
    MV1DetachAnim(Wolf.AnimHundle, Wolf.AttachAnim);//���݂̃A�j���[�V�����̃f�^�b�`
    Wolf.AttachAnim = MV1AttachAnim(Wolf.GraphicHundle, animId, -1, FALSE);//�A�j���[�V�����̃A�^�b�`
    Wolf.TotalTime = MV1GetAttachAnimTotalTime(Wolf.GraphicHundle, Wolf.AttachAnim);//���݂̃A�j���[�V�����̑�����
    Wolf.AnimHundle = animId;//���݂̃A�j���[�V�����ԍ�
    MV1SetPosition(Wolf.GraphicHundle, Wolf.Pos);//���f���̍��W�Z�b�g

}

void WOLF::modelInit()
{
    Wolf.GraphicHundle = MV1DuplicateModel(Wolf.GraphicHundle);//���f���̏�����
    MV1SetScale(Wolf.GraphicHundle, Wolf.ModelScale);//���f���̑傫���̒���
    angleProcess();//��]�p�x
    MV1SetPosition(Wolf.GraphicHundle, Wolf.Pos);//���f���̍��W�Z�b�g
    Wolf.PlayTime = 0.0f;//�Đ����Ԃ��O��

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
                Wolf.HitState[HIT_FLOOR_ID] = ON_ID;//�n�ʂƏՓ˂��Ă���
                Wolf.HitVector = game()->collision()->HitCollision();//�Փˍ��W���o��
                if (Wolf.Pos.y < Wolf.HitVector.y - 0.3f) {
                    Wolf.Pos.y = Wolf.HitVector.y;
                }
            }
        }
        if (game()->collision()->collisionStop(j) == LEFT_WALL_ID) {
            NextFrameHit = game()->collision()->collision(VGet(Wolf.Pos.x + Wolf.MoveVec.x, Wolf.Pos.y + Wolf.Gravity, Wolf.Pos.z + Wolf.MoveVec.z), Wolf.MaxPoligonPos, Wolf.MinPoligonPos, Wolf.matrix, LEFT_WALL_ID);
            if (NextFrameHit == LEFT_WALL_ID) {
                Wolf.HitState[HIT_LEFTWALL_ID] = ON_ID;//���ǂƏՓ˂��Ă���
                Wolf.HitVector = game()->collision()->HitCollision();//�Փˍ��W���o��
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
