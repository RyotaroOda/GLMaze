#include <stdlib.h>
#include "InputHandler.h"
#include "Header.h"
#include "CameraController.h"
#include "LightController.h"

#include "GoalAnimation.h"

//キーボードを押した時
void keyPush(unsigned char key, int x, int y){
    float r = 1.0;
    switch (key) {
        case '\033'://esc
            exit(0);//終了
            
        case  'g':
            BoxAnimationTrigger(0);
            break;
            //wasdはデバック用
        case 'w':
            mainCameraPosition.y += r;
            break;
        case 'a':
            mainCameraPosition.x -= r;
            break;
        case 'd':
            mainCameraPosition.x += r;
            break;
        case 's':
            mainCameraPosition.y -= r;
            break;
            
        case '1':
            setLight(1);
            break;
        case '2':
            setLight(2);
            break;
        case '3':
            setLight(3);
            break;
        case '4':
            setLight(4);
            break;
            
        default:
            break;
    }
    windowUpdate();
}


//特殊キー
void spKeyPush(int key, int x, int y) {
    if (!animation){
        switch (key){
            case GLUT_KEY_UP:
                moveForward();
                break;
            case GLUT_KEY_LEFT:
                turnSide(false);
                break;
            case GLUT_KEY_RIGHT:
                turnSide(true);
                break;
            case GLUT_KEY_DOWN:
                
                break;
                
            default:
                break;
        }
    }
}
