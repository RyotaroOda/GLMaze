#include "TrapAnimation.h"
#include "Header.h"
#include "LightController.h"

static float trapTimer = 0;

///トラップタイルの描写
void drawTrapTile(void) {
    
    GLdouble radius = 0.15;
    GLdouble height = 0.5;
    GLdouble slice = 8;
    
    glPushMatrix();
    int t;
    int i;
    for (t = 0; t < 3; t++) {
        for (i = 0; i < 3; i++) {
            glPushMatrix();
            glMaterialfv(GL_FRONT, GL_DIFFUSE, color[GRAY]);
            glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
            glMaterialfv(GL_FRONT, GL_SPECULAR, color[GRAY]);
            glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
            glTranslatef(0.2 + (0.30 * i), 0.2 + (0.30 * t), (-0.45 + trapTimer < 0) ? -0.48 + trapTimer : 0);
            //glutSolidCone(半径,高さ,    xy平面の分割数,z軸の分割数);
            glutSolidCone(radius, height, slice, slice);
            glPopMatrix();
        }
    }
    
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
    glPopMatrix();
}

void setDeathLight(void) {
    
    GLfloat lightPosition[4] = { mainCameraPosition.x , mainCameraPosition.y , 10.0, 1.0 };
    GLfloat lightDiffuse[3] = { 0.7 * trapTimer,   0.0, 0.0 }; //
    GLfloat lightAmbient[3] = { 0.25, 0.25, 0.25 }; //
    GLfloat lightSpecular[3] = { 0.7 * trapTimer,   0.0, 0.0 }; //
    
    glLightfv(GL_LIGHT2, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT2, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT2, GL_SPECULAR, lightSpecular);
    
    glEnable(GL_LIGHT2);
}

void trapAnimation(int value) {
    animation = true;
    if (value){
        lightColorChange(RED);
    }
    if (trapTimer < 0.6 && !value) {
        trapTimer += 0.05f;
        glutTimerFunc(10, trapAnimation, 0);
    }
    else if (trapTimer > 0) {
        trapTimer -= 0.02f;
        glutTimerFunc(10, trapAnimation, 1);
    }
    else {
        lightColorChange(WHITE);
        animation = false;
        trapTimer = 0;
    }
}
