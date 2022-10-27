#if 1
#include"DxLib.h"
#include"GAME.h"
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    ChangeWindowMode(true);
    SetGraphMode(1280, 720, 32);
    //SetGraphMode(1920, 1080, 32);
    SetBackgroundColor(128, 128, 128);
    if (DxLib_Init() == -1)    // �c�w���C�u��������������
    {
        return -1;    // �G���[���N�����璼���ɏI��
    }
    GAME game;
    game.run();
    DxLib_End();        // �c�w���C�u�����g�p�̏I������

    return 0;        // �\�t�g�̏I��
}
#endif
#if 0
#include <math.h>
#include <DxLib.h>

static const float ROTATE_SPEED = DX_PI_F / 90;//��]�X�s�[�h

// (x,y)�̓_��(mx,my)�𒆐S��ang�p��]����
void rotate(float* x, float* y, const float ang, const float mx, const float my) {
    const float ox = *x - mx, oy = *y - my;
    *x = ox * cos(ang) + oy * sin(ang);
    *y = -ox * sin(ang) + oy * cos(ang);
    *x += mx;
    *y += my;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);

    float cameraX = 0,cameraY=0, cameraZ = -20;    //�J�����̍��W
    const float targetX = 0,targetY=10.0f, targetZ = 0;//�J�����̎����̐�^�[�Q�b�g�̍��W

    //�n��
    float angleX=100, angleY=cos(90), xz=sin(90), yz=cos(90);

    //3D���f���̓ǂݍ���
    int ModelHandle = MV1LoadModel("C:/Users/yurek/Downloads/3Dsample (1)/3Dsample/dat/Lat���~�N/Lat���~�NVer2.3_Normal.pmd");

    //���s0.1�`1000�܂ł��J�����̕`��͈͂Ƃ���
    SetCameraNearFar(0.1f, 1000.0f);

    while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen()) {

        if (CheckHitKey(KEY_INPUT_LEFT) > 0) {//���L�[��������Ă�����
            rotate(&cameraX, &cameraZ, +ROTATE_SPEED, targetX, targetZ);//��]
        }
        if (CheckHitKey(KEY_INPUT_RIGHT) > 0) {//�E�L�[��������Ă�����
            rotate(&cameraX, &cameraZ, -ROTATE_SPEED, targetX, targetZ);//��]
        }
        if (CheckHitKey(KEY_INPUT_UP) > 0) {
            rotate(&cameraY,&cameraZ, -ROTATE_SPEED, targetY,targetZ);
        }
        if (CheckHitKey(KEY_INPUT_DOWN) > 0) {
            rotate(&cameraY, &cameraZ, +ROTATE_SPEED, targetY, targetZ);
        }
        //�������̎��_����������̃^�[�Q�b�g������p�x�ɃJ������ݒu
        SetCameraPositionAndTarget_UpVecY(VGet(cameraX, cameraY, cameraZ), VGet(targetX, targetY, targetZ));

        // �R�c���f���̕`��
        DrawTriangle3D(
            VGet(angleX,angleY,0.0f),
            VGet(angleX, angleY, 0.0f),
            VGet(angleX, 250.0f, 100.0f), GetColor(255, 255, 255), true);
        DrawTriangle3D(
            VGet(100.0f, 100.0f, 0.0f),
            VGet(200.0f, 200.0f, 0.0f),
            VGet(200.0f, 250.0f, 100.0f), GetColor(255, 255, 255), true);
        MV1DrawModel(ModelHandle);

    }

    DxLib_End();
    return 0;
}
#endif
#if 0
#include <DxLib.h>
#include<math.h>
static const float ROTATE_SPEED = DX_PI_F / 90;

void rotate(float* x, float* y, const float ang, const float mx, const float my) {
    const float ox = *x - mx, oy = *y - my;
    *x = ox * cos(ang) + oy * sin(ang);
    *y = -ox * sin(ang) + oy * cos(ang);
    *x += mx;
    *y += my;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
    int Cr = GetColor(255, 255, 255);
    float x=0.0f, y=200.0f, z=0.0f;
    float x2 = 200.0f, y2 = 200.0f, z2 = 0.0f;
    float x1 = 200.0f, y1 = 0.0f, z1 = 0.0f;//�����_�i��j
    float x3 = 200.0f, y3 = 0.0f, z3 = 100.0f;//�����_�Q
    VECTOR cameraPos;
    cameraPos.x = 200.0f, cameraPos.y = 200.0f, cameraPos.z = -500.0f;
    VECTOR CenterPos;
    float r = 20.0f;
    int DivNum = 64;
    SetUseZBuffer3D(TRUE);
    SetWriteZBuffer3D(TRUE);
    while (!ScreenFlip() && !ProcessMessage() &&
        !ClearDrawScreen() && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {

        SetCameraPositionAndTarget_UpVecY(cameraPos, VGet(x2, y2, z2));
        if (CheckHitKey(KEY_INPUT_RIGHT) > 0) {
            rotate(&cameraPos.x, &cameraPos.z, ROTATE_SPEED, x2, z2);
        }
        if (CheckHitKey(KEY_INPUT_LEFT) > 0) {
            rotate(&cameraPos.x, &cameraPos.z, -ROTATE_SPEED, x2, z2);
        }
        
        DrawTriangle3D(
            VGet(x, y, z),
            VGet(x1, y1, z1),
            VGet(x2, y2, z2), GetColor(255, 255, 255), TRUE);//����
        DrawTriangle3D(
            VGet(x, y, z),
            VGet(x3, y3, z3),
            VGet(x2, y2, z2), GetColor(255, 0,0 ), TRUE);//�Ԗ�
        DrawTriangle3D(
            VGet(x1, y1, z1),
            VGet(x3, y3, z3),
            VGet(x2, y2, z2), GetColor(0, 0, 255), TRUE);//��
        DrawTriangle3D(
            VGet(x1, y1, z1),
            VGet(x3, y3, z3),
            VGet(x, y, z), GetColor(255, 0, 255), TRUE);//�s���N��

        rotate(&y1, &z1, ROTATE_SPEED, y2, z2);
        rotate(&y3, &z3, ROTATE_SPEED, y2, z2);

        DrawFormatString(0, 0, Cr,"%d", (int)cameraPos.z);
        CenterPos.x = x1, CenterPos.y = y1, CenterPos.z = z1;
        DrawSphere3D(CenterPos, r, DivNum, GetColor(0, 255, 255), GetColor(255, 0, 0),TRUE);
    }
    
    DxLib_End();
    return 0;
}
#endif