#include "MapWindowController.h"
#include "Header.h"
#include <math.h>
#include <time.h>

GLfloat position[] = { 0.0, 0.0, 100.0, 0.0 };
static GLfloat pos1[] = { 1.5, 1.5, 0.5, 1.0 };

time_t st, ed;

void Maze(void)
{
    glColor3d(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(MAPSIZE, 0.0, 0.0);
    glVertex3d(MAPSIZE, MAPSIZE, 0.0);
    glVertex3d(0.0, MAPSIZE, 0.0);
    glEnd();
}

void Player_Pos(void) {
    glColor3d(1.0, 0.0, 0.0);
    glPushMatrix();
    glutSolidSphere(0.2, 30, 30);
    glPopMatrix();
}

void Direction(void) {
    glColor3d(1.0, 0.0, 0.0);
    switch (playerDirection) {
        case south:
            glPushMatrix();
            glRotatef(-90, 1, 0, 0);
            glTranslatef(0.0, 0.0, 0.1);
            glutSolidCone(0.1 * sqrt(3), 0.3, 30, 30);
            glPopMatrix();
            break;
        case east:
            glPushMatrix();
            glRotatef(90, 0, 1, 0);
            glTranslatef(0.0, 0.0, 0.1);
            glutSolidCone(0.1 * sqrt(3), 0.3, 30, 30);
            glPopMatrix();
            break;
        case north:
            glPushMatrix();
            glRotatef(90, 1, 0, 0);
            glTranslatef(0.0, 0.0, 0.1);
            glutSolidCone(0.1 * sqrt(3), 0.3, 30, 30);
            glPopMatrix();
            break;
        case west:
            glPushMatrix();
            glRotatef(-90, 0, 1, 0);
            glTranslatef(0.0, 0.0, 0.1);
            glutSolidCone(0.1 * sqrt(3), 0.3, 30, 30);
            glPopMatrix();
            break;
        default:
            break;
    }
    windowUpdate();
}

void Timer(int value) {
    glPushAttrib(GL_CURRENT_BIT);
    char* str = "Elapsed Time : ";
    char buffer[8];
    char* str2 = "[s]";
    snprintf(buffer, 8, "%.0f", ( (double)ed - (double)st ));
    glRasterPos3d(0.0, -0.3, 3.0);
    while (*str) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *str++);
    }
    for (int i = 0; i < 8; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, buffer[i]);
    }
    while (*str2) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *str2++);
    }
    glPopAttrib();
    windowUpdate();
    //glutTimerFunc(1000, Timer, value + 1);
}

void mapWindowDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glPushMatrix();
    
    Maze();
    
    glTranslatef(mainCameraPosition.x, mainCameraPosition.y, 0.2);
    Player_Pos();
    Direction();
    
    glPopMatrix();
    
    ed = time(NULL);
//    Timer(0);
    
    glutSwapBuffers();
}

void mapWindowInit(void)
{
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    st = time(NULL);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
            
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_COLOR_MATERIAL);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0, 1, 1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt((double)MAPSIZE /2, (double)MAPSIZE /2, 6.0,
              (double)MAPSIZE /2, (double)MAPSIZE /2, 0.0,
              -1.0, 0.0, 0.0);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, color[WHITE]);
    glLightfv(GL_LIGHT0, GL_AMBIENT, color[WHITE]);
    glLightfv(GL_LIGHT0, GL_SPECULAR, color[WHITE]);
}
