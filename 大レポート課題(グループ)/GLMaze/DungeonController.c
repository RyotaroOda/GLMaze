#include "DungeonController.h"
#include "Header.h"
#include "TrapAnimation.h"
#include <stdlib.h>

GLfloat wallColor[MAPSIZE][MAPSIZE][5][2][4];

void dungeonInit(void){
    for (int x = 0; x < MAPSIZE; x++) {
        for (int y = 0; y < MAPSIZE; y++) {
            for (int z = 0; z < 5; z++) {
                for (int i = 0; i < 2; i++) {
                    for (int j = 0; j < 3; j++) {
                        float r = rand() % 255;
                        wallColor[x][y][z][i][j] = r / 255;
                    }
                    wallColor[x][y][i][z][3] = 1;
                }
            }
        }
    }
}

//スタートするタイルの描写
void drawStartTile(void) {
    
    glPushMatrix();
    glBegin(GL_QUADS);
    glNormal3d(0, 0, 1);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color[BLUE]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLUE]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, color[BLUE]);
    glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
    glVertex3d(1.0, 1.0, 0.0);
    glVertex3d(0.0, 1.0, 0.0);
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(1.0, 0.0, 0.0);
    glEnd();
    
    glPopMatrix();
}

//ゴールタイルの描写
void drawGoalTile(void) {
    
    glPushMatrix();
    glBegin(GL_QUADS);
    glNormal3d(0, 0, 1);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color[RED]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, color[RED]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, color[RED]);
    glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
    glVertex3d(1.0, 1.0, 0.0);
    glVertex3d(0.0, 1.0, 0.0);
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(1.0, 0.0, 0.0);
    glEnd();
    
    glPopMatrix();
}

//普通のタイルの描写
void drawNomalTile(void) {
    
    glPushMatrix();
    glBegin(GL_QUADS);
    glNormal3d(0, 0, 1);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color[LIGHTGRAY]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
    glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
    glVertex3d(1.0, 1.0, 0.0);
    glVertex3d(0.0, 1.0, 0.0);
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(1.0, 0.0, 0.0);
    glEnd();
    
    glBegin(GL_QUADS);
    glNormal3d(0, 0, 1);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color[GRAY]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
    glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
    glVertex3d(0.9, 0.9, 0.01);
    glVertex3d(0.1, 0.9, 0.01);
    glVertex3d(0.1, 0.1, 0.01);
    glVertex3d(0.9, 0.1, 0.01);
    glEnd();
    
    glPopMatrix();
}

//mapのtypeによってタイルを描画する関数を実行
void drawFloor(void) {
    int x, y;
    
    for (x = 0; x < MAPSIZE; x++) {
        for (y = 0; y < MAPSIZE; y++) {
            glPushMatrix();
            glTranslatef(x, y, 0);
            switch (map[y][x].type) {
                    
                case normal:
                    drawNomalTile();
                    break;
                    
                case start:
                    drawStartTile();
                    break;
                    
                case goal:
                    drawGoalTile();
                    break;
                    
                case trap:
                    drawTrapTile();
                    break;
                    
                default:
                    printf("CellType ERROR!");
                    break;
            }
            glPopMatrix();
        }
    }
}

void drawVY(int i,int j)
{
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
    glMaterialf(GL_FRONT, GL_SHININESS, 100);
    glBegin(GL_QUADS);
    
    double L = 0.25;
    
    for (int k = 0; k < 4; k++) {
        for (int t = 0; t < 4; t++)
        {
            glMaterialfv(GL_FRONT, GL_DIFFUSE, wallColor[i][j][0][0]);
            GLdouble v[4][3];
            if (!((k ^ t) & 1))continue;
            v[0][0] = j + 1;
            v[0][1] = i + (k + 0) * L;
            v[0][2] = (t + 0) * L;
            v[1][0] = j + 1;
            v[1][1] = i + (k + 1) * L;
            v[1][2] = (t + 0) * L;
            v[2][0] = j + 1;
            v[2][1] = i + (k + 1) * L;
            v[2][2] = (t + 1) * L;
            v[3][0] = j + 1;
            v[3][1] = i + (k + 0) * L;
            v[3][2] = (t + 1) * L;
            glVertex3dv(v[0]);
            glVertex3dv(v[1]);
            glVertex3dv(v[2]);
            glVertex3dv(v[3]);
            glVertex3dv(v[0]);
            glVertex3dv(v[3]);
            glVertex3dv(v[2]);
            glVertex3dv(v[1]);
        }
    }
    glEnd();
    
    glPopMatrix();
}

void drawVB(int i, int j)
{
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
    glMaterialf(GL_FRONT, GL_SHININESS, 100);
    glBegin(GL_QUADS);
    
    double L = 0.25;
    
    for (int k = 0; k < 4; k++) {
        for (int t = 0; t < 4; t++)
        {
            glMaterialfv(GL_FRONT, GL_DIFFUSE, wallColor[i][j][1][1]);
            GLdouble v[4][3];
            if (((k ^ t) & 1))continue;
            v[0][0] = j + 1;
            v[0][1] = i + (k + 0) * L;
            v[0][2] = (t + 0) * L;
            v[1][0] = j + 1;
            v[1][1] = i + (k + 1) * L;
            v[1][2] = (t + 0) * L;
            v[2][0] = j + 1;
            v[2][1] = i + (k + 1) * L;
            v[2][2] = (t + 1) * L;
            v[3][0] = j + 1;
            v[3][1] = i + (k + 0) * L;
            v[3][2] = (t + 1) * L;
            glVertex3dv(v[0]);
            glVertex3dv(v[1]);
            glVertex3dv(v[2]);
            glVertex3dv(v[3]);
            glVertex3dv(v[0]);
            glVertex3dv(v[3]);
            glVertex3dv(v[2]);
            glVertex3dv(v[1]);
        }
    }
    glEnd();
    
    glPopMatrix();
}

void drawHY(int i,int j)
{
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
    glMaterialf(GL_FRONT, GL_SHININESS, 100);
    glBegin(GL_QUADS);
    
    double L = 0.25;
    
    for (int k = 0; k < 4; k++) {
        for (int t = 0; t < 4; t++)
        {
            glMaterialfv(GL_FRONT, GL_DIFFUSE, wallColor[i][j][2][0]);
            GLdouble v[4][3];
            if (!((k ^ t) & 1))continue;
            v[0][0] = j+(k + 0) * L;
            v[0][1] = i + 1;
            v[0][2] = (t + 0) * L;
            v[1][0] = j+(k + 1) * L;
            v[1][1] = i + 1;
            v[1][2] = (t + 0) * L;
            v[2][0] = j+(k + 1) * L;
            v[2][1] = i + 1;
            v[2][2] = (t + 1) * L;
            v[3][0] = j+(k + 0) * L;
            v[3][1] = i + 1;
            v[3][2] = (t + 1) * L;
            glVertex3dv(v[0]);
            glVertex3dv(v[1]);
            glVertex3dv(v[2]);
            glVertex3dv(v[3]);
            glVertex3dv(v[0]);
            glVertex3dv(v[3]);
            glVertex3dv(v[2]);
            glVertex3dv(v[1]);
        }
    }
    glEnd();
    
    glPopMatrix();
}

void drawHB(int i,int j)
{
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
    glMaterialf(GL_FRONT, GL_SHININESS, 100);
    glBegin(GL_QUADS);
    
    double L = 0.25;
    
    for (int k = 0; k < 4; k++) {
        for (int t = 0; t < 4; t++)
        {
            glMaterialfv(GL_FRONT, GL_DIFFUSE, wallColor[i][j][3][1]);
            GLdouble v[4][3];
            if (((k ^ t) & 1))continue;
            v[0][0] = j+(k + 0) * L;
            v[0][1] = i + 1;
            v[0][2] = (t + 0) * L;
            v[1][0] = j+(k + 1) * L;
            v[1][1] = i + 1;
            v[1][2] = (t + 0) * L;
            v[2][0] = j+(k + 1) * L;
            v[2][1] = i + 1;
            v[2][2] = (t + 1) * L;
            v[3][0] = j+(k + 0) * L;
            v[3][1] = i + 1;
            v[3][2] = (t + 1) * L;
            glVertex3dv(v[0]);
            glVertex3dv(v[1]);
            glVertex3dv(v[2]);
            glVertex3dv(v[3]);
            glVertex3dv(v[0]);
            glVertex3dv(v[3]);
            glVertex3dv(v[2]);
            glVertex3dv(v[1]);
        }
    }
    glEnd();
    
    glPopMatrix();
}

void drawRY(int i, int j) {
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
    glMaterialf(GL_FRONT, GL_SHININESS, 100);
    glBegin(GL_QUADS);
    
    double L = 0.25;
    
    for (int k = 0; k < 4; k++) {
        for (int t = 0; t < 4; t++)
        {
            glMaterialfv(GL_FRONT, GL_DIFFUSE, wallColor[i][j][4][0]);
            GLdouble v[4][3];
            if (((k ^ t) & 1))continue;
            v[0][0] = i + k * L;
            v[0][1] = j + t * L;
            v[0][2] = HEIGHT;
            v[1][0] = i + (k + 1) * L;
            v[1][1] = j + t * L;
            v[1][2] = HEIGHT;
            v[2][0] = i + (k + 1) * L;
            v[2][1] = j + (t + 1) * L;
            v[2][2] = HEIGHT;
            v[3][0] = i + k * L;
            v[3][1] = j + (t + 1) * L;
            v[3][2] = HEIGHT;
            glVertex3dv(v[0]);
            glVertex3dv(v[1]);
            glVertex3dv(v[2]);
            glVertex3dv(v[3]);
            glVertex3dv(v[0]);
            glVertex3dv(v[3]);
            glVertex3dv(v[2]);
            glVertex3dv(v[1]);
        }
    }
    glEnd();
    
    glPopMatrix();
}

void drawRB(int i, int j) {
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
    glMaterialf(GL_FRONT, GL_SHININESS, 100);
    glBegin(GL_QUADS);
    
    double L = 0.25;
    
    for (int k = 0; k < 4; k++) {
        for (int t = 0; t < 4; t++)
        {
            glMaterialfv(GL_FRONT, GL_DIFFUSE, wallColor[i][j][4][1]);
            GLdouble v[4][3];
            if (!((k ^ t) & 1))continue;
            v[0][0] = i + k * L;
            v[0][1] = j + t * L;
            v[0][2] = HEIGHT;
            v[1][0] = i + (k + 1) * L;
            v[1][1] = j + t * L;
            v[1][2] = HEIGHT;
            v[2][0] = i + (k + 1) * L;
            v[2][1] = j + (t + 1) * L;
            v[2][2] = HEIGHT;
            v[3][0] = i + k * L;
            v[3][1] = j + (t + 1) * L;
            v[3][2] = HEIGHT;
            glVertex3dv(v[0]);
            glVertex3dv(v[1]);
            glVertex3dv(v[2]);
            glVertex3dv(v[3]);
            glVertex3dv(v[0]);
            glVertex3dv(v[3]);
            glVertex3dv(v[2]);
            glVertex3dv(v[1]);
        }
    }
    glEnd();
    
    glPopMatrix();
}

void drawGround(void)
{
    glPushMatrix();
    
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color[GRAY]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
    glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
    glBegin(GL_QUADS);
    
    //    glVertex3d(0, 0, 0);        //ground
    //    glVertex3d(XG, 0, 0);
    //    glVertex3d(XG, YG, 0);
    //    glVertex3d(0, YG, 0);
    //
    //    glVertex3d(0, 0, ZG);        //roof
    //    glVertex3d(0, YG, ZG);
    //    glVertex3d(XG, YG, ZG);
    //    glVertex3d(XG, 0, ZG);
    
    for (int i = 0; i < 3; i++)
    {
        drawHY(-1, i);           //north outer wall
        drawHB(-1, i);
    }
    for (int i = 0; i < 3; i++)
    {
        drawVY(i, -1);           //west outer wall
        drawVB(i, -1);
    }
}

void drawWall(void){
    for (int i = 0; i < MAPSIZE; i++){
        for (int j = 0; j < MAPSIZE; j++){
            if (map[i][j].eastWall == true){
                drawVY(i,j);
                drawVB(i,j);
            }
            
            if (map[i][j].southWall == true){
                drawHY(i,j);
                drawHB(i,j);
            }
            drawRY(i, j);
            drawRB(i, j);
        }
    }
    glEnd();
    
    glPopMatrix();
}

//オブジェクトの配置
void dungeonUpdate(void)
{
    drawGround();
    drawFloor();
    drawWall();
}
