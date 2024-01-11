#include "Header.h"
#include "Calferz.h"
#include "GoalAnimation.h"


GLfloat pos2[] = { 10000.0, -1.0, 10000.0, 1.0 };
GLfloat pink[] = { 1.0, 0.2, 0.4, 1.0 };
GLfloat pink2[] = { 0.81, 0.4, 0.4, 1.0 };
GLfloat darkred1[] = { 0.4, 0.05, 0.05, 1.0 };
GLfloat darkred2[] = { 0.1, 0.05, 0.05, 1.0 };

void Eyes(void) {
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color[BLACK]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, color[BLACK]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
    //右目
    glPushMatrix();
    glRotatef(-20, 0, 1, 0);
    glRotatef(30, 0, 0, 1);
    glRotatef(-3, 1, 0, 0);
    glTranslatef(1, 0, 0);
    glScalef(0.01, 1, 0.35);
    glutSolidSphere(0.27, 30, 30);
    glPopMatrix();
    //左目
    glPushMatrix();
    glRotatef(3, 0, 1, 0);
    glRotatef(25, 0, 0, 1);
    glRotatef(-10, 1, 0, 0);
    glTranslatef(1, 0, 0);
    glScalef(0.01, 1, 0.4);
    glutSolidSphere(0.25, 30, 30);
    glPopMatrix();
}

void inEyes(void) {
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color[WHITE]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, color[WHITE]);
    //右目
    glPushMatrix();
    glRotatef(-20, 0, 1, 0);
    glRotatef(35, 0, 0, 1);
    glRotatef(-3, 1, 0, 0);
    glTranslatef(1.02, 0, 0);
    glScalef(0.01, 1, 0.4);
    glutSolidSphere(0.13, 30, 30);
    glPopMatrix();
    //左目
    glPushMatrix();
    glRotatef(4, 0, 1, 0);
    glRotatef(30, 0, 0, 1);
    glRotatef(-15, 1, 0, 0);
    glTranslatef(1.02, 0, 0);
    glScalef(0.01, 1, 0.5);
    glutSolidSphere(0.12, 30, 30);
    glPopMatrix();
}
void Cheek(void) {
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color[RED]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color[RED]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, pink2);
    //右
    glPushMatrix();
    glRotatef(-40, 0, 1, 0);
    glRotatef(17, 0, 0, 1);
    glTranslatef(1.01, 0, 0);
    glScalef(0.01, 0.6, 1);
    glutSolidSphere(0.15, 30, 30);
    glPopMatrix();
    //左
    glPushMatrix();
    glRotatef(22, 0, 1, 0);
    glRotatef(8, 0, 0, 1);
    glRotatef(-8, 1, 0, 0);
    glTranslatef(1.01, 0, 0);
    glScalef(0.01, 0.45, 1);
    glutSolidSphere(0.19, 30, 30);
    glPopMatrix();
}
void Mouth(void) {
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color[RED]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, color[RED]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, color[RED]);
    glPushMatrix();
    glRotatef(-12, 0, 1, 0);
    glRotatef(-10, 1, 0, 0);
    glRotatef(7, 0, 0, 1);
    glTranslatef(1, 0, 0);
    glScalef(0.01, 1, 0.7);
    glutSolidSphere(0.1, 30, 30);
    glPopMatrix();
}

void Sphere(void) {
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color[RED]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, pink2);
    glMaterialfv(GL_FRONT, GL_SPECULAR, pink);
    glMaterialf(GL_FRONT, GL_SHININESS, 1.0);
    glutSolidSphere(1, 30, 30);
}
void Ellipsoid1(void) {    //右腕
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color[RED]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, pink2);
    glMaterialfv(GL_FRONT, GL_SPECULAR, pink);
    glMaterialf(GL_FRONT, GL_SHININESS, 2.0);
    glPushMatrix();
    glScalef(0.75, 0.75, 1);
    glTranslatef(0.2, 0.2, 1);
    glutSolidSphere(0.45, 30, 30);
    glPopMatrix();
}

void Ellipsoid2(void) {    //左腕
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color[RED]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, pink2);
    glMaterialfv(GL_FRONT, GL_SPECULAR, pink);
    glMaterialf(GL_FRONT, GL_SHININESS, 2.0);
    glPushMatrix();
    glRotatef(57, 0, 1, 0);
    glRotatef(-22, 1, 0, 0);
    glTranslatef(0.9, 0.35, 0.5);
    glScalef(0.5, 0.5, 1);
    glutSolidSphere(0.56, 30, 30);
    glPopMatrix();
}

void Ellipsoid3(void) {    //右足
    glLightfv(GL_LIGHT0, GL_POSITION, pos2); //光源の位置・性質
    glLightfv(GL_LIGHT0, GL_DIFFUSE, color[WHITE]);
    glLightfv(GL_LIGHT0, GL_SPECULAR, color[WHITE]);
    glLightfv(GL_LIGHT0, GL_AMBIENT, color[WHITE]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color[BLACK]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color[BLACK]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, darkred2);
    glMaterialf(GL_FRONT, GL_SHININESS, 0.0);
    glPushMatrix();
    glRotatef(-25, 0, 1, 0);
    glRotatef(45, 1, 0, 0);
    glTranslatef(-0.3, -0.1, 1.25);
    glScalef(0.5, 0.6, 1);
    glutSolidSphere(0.65, 30, 30);
    glPopMatrix();
}

void Ellipsoid4(void) {    //左足
    GLfloat pos1[] = { 20.0, 0.0, 0.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, pos1); //光源の位置・性質
    glLightfv(GL_LIGHT0, GL_DIFFUSE, color[WHITE]);
    glLightfv(GL_LIGHT0, GL_SPECULAR, color[WHITE]);
    glLightfv(GL_LIGHT0, GL_AMBIENT, color[WHITE]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, darkred1);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, darkred1);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color[BLACK]);
    glMaterialf(GL_FRONT, GL_SHININESS, 128);
    glPushMatrix();
    glRotatef(-12, 0, 0, 1);
    glRotatef(10, 0, 1, 0);
    glTranslatef(0.4, -1.0, -0.35);
    glScalef(1, 0.5, 0.6);
    glutSolidSphere(0.65, 30, 30);
    glPopMatrix();
}

void drawCalferz(void){
    GLfloat pos0[] = { 2.0, 1.5, 0.0, 1.0 };
    
    glPushMatrix();
    
    glTranslatef(first_pos[0], first_pos[1], first_pos[2]);
    glRotatef(90, 1, 0, 0);
    glRotatef(80, 0, -1, 0);
    glScaled(0.1, 0.1, 0.1);
    
    glPushMatrix();
    //光源系
    glLightfv(GL_LIGHT0, GL_POSITION, pos0); //光源の位置・性質
    glLightfv(GL_LIGHT0, GL_DIFFUSE, color[WHITE]);
    glLightfv(GL_LIGHT0, GL_SPECULAR, color[WHITE]);
    glLightfv(GL_LIGHT0, GL_AMBIENT, color[WHITE]);

    Ellipsoid1();
    Sphere();
    Ellipsoid2();
    Eyes();
    inEyes();
    Cheek();
    Mouth();
    Ellipsoid3();
    Ellipsoid4();

    glPopMatrix();
    
    glPopMatrix();
}
