#include "Header.h"
#include "DungeonController.h"
#include "InputHandler.h"
#include "CameraController.h"
#include "LightController.h"
#include "ScoreManager.h"
#include "UIController.h"
#include "GoalAnimation.h"
#include "MapWindowController.h"
#include "CreateMap.h"

//グローバル変数
GLfloat color[][4] = {
    { 1.0, 1.0, 1.0, 1.0 },
    { 1.0, 0.0, 0.0, 1.0 },
    { 0.0, 1.0, 0.0, 1.0 },
    { 0.0, 0.0, 1.0, 1.0 },
    { 1.0, 1.0, 0.0, 1.0 },
    { 1.0, 0.0, 1.0, 1.0 },
    { 0.0, 1.0, 1.0, 1.0 },
    { 0.7, 0.7, 0.7, 1.0 },
    { 0.0, 0.0, 0.0, 1.0 },
    { 0.8, 0.8, 0.8, 1.0 }
};

cell map[MAPSIZE][MAPSIZE] =
{
    {{true,  false, start, true}, {false, false, normal, true}, {true, false, normal, true}},
    {{true,  false, trap, true}, {true, true, goal, true}, {true, false, normal, true}},
    {{false,  true, normal, true}, {false, true, normal, true}, {true, true, normal, true}}
};


directionType playerDirection  = south;
vec3 startPos = {0.5, 0.5, 0.5};
vec3 mainCameraPosition;
vec3 mainCameraLookAt;
int score = MAPSIZE*MAPSIZE*2;

bool animation = false;
int Window[2];

//初期化
void init(void){
    mainCameraPosition = startPos;
    mainCameraLookAt = startPos;
    
    glClearColor(135/255.0, 206/255.0, 250/255.0, 0.0);//背景の色（空色）
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_LIGHTING);
    
    cameraInit();
    lightInit();
    scoreInit();
    goalInit();
    dungeonInit();
    
//    createMap();
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// 画面をクリア
    glLoadIdentity();//モデルビュー変換行列の初期化
    
    cameraUpdate();
    dungeonUpdate();
    lightUpdate();
    UIUpdate();
    goalAnimation();
    
    glFlush();
    glutSwapBuffers();
    
}

void windowUpdate(void){
    glutSetWindow(Window[0]);
    glutPostRedisplay();
    glutSetWindow(Window[1]);
    glutPostRedisplay();
}

void setWindow(int n){
    glutSetWindow(Window[n]);
}

void resize(int w, int h){
    glViewport(0, 0, w, h);// ウィンドウ全体をビューポートにする
    
    // 透視変換行列
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //カメラの画角
    gluPerspective(60.0, (double)w / (double)h, 00.1 , 100.0);
    
    glMatrixMode(GL_MODELVIEW);// モデルビュー変換行列の指定
}

void idle(void){
//    windowUpdate();
}

int main(int argc, char *argv[]){
    //メインウィンドウ
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);//ウィンドウ
    glutInitWindowSize(winWidth, winHeight);
    
    Window[0] = glutCreateWindow("Maze");//TODO:ゲームタイトル
    glutDisplayFunc(display);
    init();
    
    glutReshapeFunc(resize);

    Window[1] = glutCreateSubWindow(Window[0],0,0,200,200);
    glutDisplayFunc(mapWindowDisplay);
    mapWindowInit();
    
    //入力
    glutKeyboardFunc(keyPush);
    glutSpecialFunc(spKeyPush);
    
    glutIdleFunc(idle);
    
    glutMainLoop();
    return 0;
}
