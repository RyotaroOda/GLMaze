#include "CameraController.h"
#include "Header.h"
#include "CellEventHandler.h"
#include "UIController.h"

static int playerPosX;
static int playerPosY;
static const int frameRate = 10;
static int cameraAngle;
static bool turning = false;

void cameraInit(void){
    //カメラ回転
    switch (playerDirection) {
        case east:
            cameraAngle = 270;
            break;
        case west:
            cameraAngle = 90;
            break;
        case south:
            cameraAngle = 0;
            break;
        case north:
            cameraAngle = 180;
            break;
    }
}

void cameraUpdate(void){
    float forcus = 0.3;
    if(turning){
        glRotated(cameraAngle, 0.0, 1.0, 0.0);
    }
    else{
        //カメラ回転
        switch (playerDirection) {
            case east:
                mainCameraLookAt.x =  mainCameraPosition.x + forcus;
                mainCameraLookAt.y =  mainCameraPosition.y;
                break;
            case west:
                mainCameraLookAt.x = mainCameraPosition.x - forcus;
                mainCameraLookAt.y =  mainCameraPosition.y;
                break;
            case south:
                mainCameraLookAt.y = mainCameraPosition.y + forcus;
                mainCameraLookAt.x =  mainCameraPosition.x;
                break;
            case north:
                mainCameraLookAt.y = mainCameraPosition.y - forcus;
                mainCameraLookAt.x =  mainCameraPosition.x;
                break;
        }
    }
    gluLookAt(mainCameraPosition.x,mainCameraPosition.y, mainCameraPosition.z,
              mainCameraLookAt.x, mainCameraLookAt.y, mainCameraLookAt.z,
              0.0, 0.0, 1.0f);
    
    //デバックログ
    //    printf("x:%f, y:%f, ", mainCameraPosition.x,mainCameraPosition.y);
    //    switch(playerDirection){
    //        case north:
    //            printf("N");
    //            break;
    //        case east:
    //            printf("E");
    //            break;
    //        case west:
    //            printf("W");
    //            break;
    //        case south:
    //            printf("S");
    //            break;
    //    }
    //    printf("\n");
}


void moveAnimation(int value){
    if(value > 0){
        switch(playerDirection){
            case north:
                mainCameraPosition.y -= 1.0 / frameRate;
                break;
                
            case east:
                mainCameraPosition.x += 1.0 / frameRate;
                break;
                
            case south:
                mainCameraPosition.y += 1.0 / frameRate;
                break;
                
            case west:
                mainCameraPosition.x -= 1.0 / frameRate;
                break;
                
            default:
                printf("Directoin Error!");
                break;
        }
        glutTimerFunc(1000 / frameRate, moveAnimation, --value);
    }
    else{
        switch(playerDirection){
            case north:
                mainCameraPosition.y = playerPosY - 0.5;
                break;
                
            case east:
                mainCameraPosition.x = playerPosX + 1.5;
                break;
                
            case south:
                mainCameraPosition.y = playerPosY + 1.5;
                break;
                
            case west:
                mainCameraPosition.x = playerPosX - 0.5;
                break;
                
            default:
                printf("Directoin Error!");
                break;
        }
        animation = false;
        playerPosX = mainCameraPosition.x - 0.5;
        playerPosY = mainCameraPosition.y - 0.5;
        cellEvent(map[playerPosY][playerPosX].type);
    }
}

void failMove(void){
    showMesage("Collision Wall!");
    animation = false;
}

void moveForward(void){
    playerPosX = mainCameraPosition.x - 0.5;//配列番号で使うためvec3ではなくint
    playerPosY = mainCameraPosition.y - 0.5;
    animation = true;
    static const int time = 50; //ミリ秒　アニメーションの全体時間
    
    switch(playerDirection){
        case north:
            if (!map[playerPosY - 1][playerPosX].southWall && !playerPosY - 1 < 0){
                glutTimerFunc(time / frameRate, moveAnimation, frameRate);
            }else{
                failMove();
            }
            break;
            
        case east:
            if(!map[playerPosY][playerPosX].eastWall) {
                glutTimerFunc(time / frameRate, moveAnimation, frameRate);
            }else{
                failMove();
            }
            break;
            
        case south:
            if(!map[playerPosY][playerPosX].southWall) {
                glutTimerFunc(time / frameRate, moveAnimation, frameRate);
            }else{
                failMove();
            }
            break;
            
        case west:
            if(!map[playerPosY][playerPosX - 1].eastWall && !playerPosX - 1 < 0) {
                glutTimerFunc(time / frameRate, moveAnimation, frameRate);
            }else{
                failMove();
            }
            break;
            
        default:
            printf("Directoin Error!");
            animation = false;
            break;
    }
    windowUpdate();
}

void turnAnimation(int value){
    static int r = 10;
    if(value == 0){
        turning = false;
        animation = false;
        cameraAngle = 0;
    }else if (value < 0){
        cameraAngle -= r;
        value += r;
        glutTimerFunc(1000 / frameRate, turnAnimation, value);
    }else{
        cameraAngle += r;
        value -= r;
        glutTimerFunc(1000 / frameRate, turnAnimation, value);
    }
    windowUpdate();
}

void turnSide(bool right){
    turning = true;
    animation = true;
    playerDirection = (playerDirection + ((right)? -1 : 1)) % 4;//0->1->2->3->0->...
    turnAnimation((right) ?  90 : -90);
}

