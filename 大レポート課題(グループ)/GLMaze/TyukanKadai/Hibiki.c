#include "Header.h"
#include "Hibiki.h"
#include "GoalAnimation.h"

void Kirby(void) {
    
    GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat black[] = { .1, .1, .1, 1.0 };
    GLfloat pink[] = { 0.92, 0.57, 0.60, 1.0 };
    GLfloat darkpink[] = { 0.75, 0.335, 0.45, 1.0 };
    GLfloat salmonpink[] = { 0.85, 0.25, 0.40 };
    GLfloat green[] = { 0.10, 0.80, 0.20 };

    glPushMatrix();
    
    glTranslatef(first_pos[0], first_pos[1], first_pos[2]);
    glRotatef(90, 1, 0, 0);
    glScaled(0.1, 0.1, 0.1);
    //胴体
    glMaterialfv(GL_FRONT, GL_DIFFUSE, pink);
    glMaterialfv(GL_FRONT, GL_AMBIENT, darkpink);
    glMaterialfv(GL_FRONT, GL_SPECULAR, pink);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0);
    glutSolidSphere(1, 30, 30);

    //目
    //右
    //黒
    
    glPushMatrix();
    
    glRotatef(-40, 1, 0, 0);
    glTranslatef(0.3, 0.0, 1);
    glScalef(1.0f, 1.8f, 1.0f);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
    glMaterialfv(GL_FRONT, GL_AMBIENT, black);
    glMaterialfv(GL_FRONT, GL_SPECULAR, black);
    glMaterialf(GL_FRONT, GL_SHININESS, 10.0);
    glutSolidSphere(0.13, 30, 30);
    glPopMatrix();
    //白
    glPushMatrix();
    glRotatef(-41, 1, 0, 0);
    glTranslatef(0.3, 0.0, 1);
    glScalef(0.9f, 1.51f, 1.1f);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
    glMaterialfv(GL_FRONT, GL_AMBIENT, white);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 10.0);
    glutSolidSphere(0.13, 30, 30);
    glPopMatrix();
    //左
    //黒
    glPushMatrix();
    glRotatef(-40, 1, 0, 0);
    glTranslatef(-0.3, 0.0, 1.0);
    glScalef(1.0f, 1.8f, 1.0f);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
    glMaterialfv(GL_FRONT, GL_AMBIENT, black);
    glMaterialfv(GL_FRONT, GL_SPECULAR, black);
    glMaterialf(GL_FRONT, GL_SHININESS, 10.0);
    glutSolidSphere(0.13, 30, 30);
    glPopMatrix();
    //白
    glPushMatrix();
    glRotatef(-41, 1, 0, 0);
    glTranslatef(-0.3, 0.0, 1.0);
    glScalef(0.9f, 1.51f, 1.1f);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
    glMaterialfv(GL_FRONT, GL_AMBIENT, white);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 10.0);
    glutSolidSphere(0.13, 30, 30);
    glPopMatrix();

    //口
    glPushMatrix();
    glRotatef(-5, 1, 0, 0);
    glTranslatef(0, 0.0, 1.0);
    glScalef(2.0f, 2.0f, 1.0f);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
    glMaterialfv(GL_FRONT, GL_AMBIENT, black);
    glMaterialfv(GL_FRONT, GL_SPECULAR, black);
    glMaterialf(GL_FRONT, GL_SHININESS, 128.0);
    glutSolidSphere(0.13, 30, 30);
    glPopMatrix();

    //手
    //右
    glPushMatrix();
    glRotatef(20, 0, 1, 0);
    glTranslatef(1.1, 0, 0);
    glScalef(1.5f, 1.0f, 1.0f);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, pink);
    glMaterialfv(GL_FRONT, GL_AMBIENT, darkpink);
    glMaterialfv(GL_FRONT, GL_SPECULAR, pink);
    glMaterialf(GL_FRONT, GL_SHININESS, 280.0);
    glutSolidSphere(0.3, 30, 30);
    glPopMatrix();
    //左
    glPushMatrix();
    glRotatef(-20, 0, 1, 0);
    glTranslatef(-1.1, 0, 0);
    glScalef(1.5f, 1.0f, 1.0f);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, pink);
    glMaterialfv(GL_FRONT, GL_AMBIENT, darkpink);
    glMaterialfv(GL_FRONT, GL_SPECULAR, pink);
    glMaterialf(GL_FRONT, GL_SHININESS, 280.0);
    glutSolidSphere(0.3, 30, 30);
    glPopMatrix();

    //足
    //右
    glPushMatrix();
    glTranslatef(0.6, -1, 0);
    glScalef(1.5f, 0.8f, 1.2f);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, salmonpink);
    glMaterialfv(GL_FRONT, GL_AMBIENT, salmonpink);
    glMaterialfv(GL_FRONT, GL_SPECULAR, salmonpink);
    glMaterialf(GL_FRONT, GL_SHININESS, 1.0);
    glutSolidSphere(0.4, 30, 30);
    glPopMatrix();
    //左
    glPushMatrix();
    glTranslatef(-0.6, -1, 0);
    glScalef(1.5f, 0.8f, 1.2f);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, salmonpink);
    glMaterialfv(GL_FRONT, GL_AMBIENT, salmonpink);
    glMaterialfv(GL_FRONT, GL_SPECULAR, salmonpink);
    glMaterialf(GL_FRONT, GL_SHININESS, 1.0);
    glutSolidSphere(0.4, 30, 30);
    glPopMatrix();
    
    glPopMatrix();
}
