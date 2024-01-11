#ifndef Header_h
#define Header_h

#include <stdio.h>
//#include <stdlib.h>
#include <stdbool.h>
//#include <math.h>
//#include <time.h>

// #include <GL/glut.h>
#include <GLUT/GLUT.h>
//#include<OpenGL/OpenGL.h>

//ウィンドサイズ
#define winWidth 1000
#define winHeight 600

//マップサイズ
#define MAPSIZE 3
#define HEIGHT 1

#define PI (3.14159)

//色の宣言
typedef enum  {
    WHITE, RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN, GRAY, BLACK, LIGHTGRAY
}COLOR;

extern GLfloat color[][4];

//マスの種類
typedef enum {
    normal, start, goal, trap
}cellType;


//方角（右回り）
typedef  enum{
    north, east, south, west
}directionType;

//一マスの情報
//座標は二次元配列の挿入位置で管理
typedef struct {
    bool eastWall;  //東壁
    bool southWall; //南壁
    cellType type;
    bool correctRoute;
} cell;

//3次元ベクトル
typedef struct{
    GLfloat x;
    GLfloat y;
    GLfloat z;
}vec3;

//2次元ベクトル
typedef struct{
    GLfloat x;
    GLfloat y;
    GLfloat z;
}vec2;

extern cell map[MAPSIZE][MAPSIZE];
//┏━━┯━━━━━━┓
//┃s ┃      ┃
//┃  ┃_g_┃  ┃
//┃         ┃
//┗━━━━━━━━━┛

extern directionType playerDirection;
//メインカメラ （プレイヤー視点） 初期値
extern vec3 startPos;
extern vec3 mainCameraPosition;
extern vec3 mainCameraLookAt;
extern int score;

extern bool animation;

void windowUpdate(void);
void setWindow(int);

#endif /* Header_h */
