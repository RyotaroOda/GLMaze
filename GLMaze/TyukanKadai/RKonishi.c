#include "Header.h"
#include "RKonishi.h"
#include "GoalAnimation.h"

//--------------------------------------
//構想：はやぶさ2。アンテナ面・太陽光パネル面がz=0平面で、ボディのz=0面の中心点の座標が(0,0,0)。


int face[][4] = {
        { 0, 1, 2, 3 },
        { 3, 2, 6, 7 },
        { 7, 6, 5, 4 },
        { 4, 5, 1, 0 },
        { 0, 3, 7, 4 },
        { 2, 1, 5, 6 }
};

GLdouble norm[][3] = {
        { 0.0, 0.0, 1.0 },
        { 0.0, -1.0, 0.0 },
        { 0.0, 0.0, -1.0 },
        { 0.0, 1.0, 0.0 },
        { 1.0, 0.0, 0.0 },
        { -1.0, 0.0, 0.0 }
};


void cube(GLdouble xx[8][3])
{
    int i;
    int j;

    for (j = 0; j < 6; j++) {
            glBegin(GL_QUADS);
            glNormal3dv(norm[j]);
            for (i = 0; i < 4; i++) {
                glVertex3dv(xx[face[j][i]]);
            }
            glEnd();
    }
}

void xyzcube(double x,double y,double z, double lx, double ly, double lz, GLdouble a[8][3])
{
    
    int q[8][3] = {
        {1,1,1},
        {-1,1,1},
        {-1,-1,1},
        {1,-1,1},
        {1,1,0},
        {-1,1,0},
        {-1,-1,0},
        {1,-1,0}
    };
    
    for (int l=0; l<8; l++) {
        a[l][0] = x + q[l][0] * lx / 2;
        a[l][1] = y + q[l][1] * ly / 2;
        a[l][2] = z + q[l][2] * lz / 2;
    }
    
    cube(a);
}

void wing(void)
{
    GLdouble pole1[8][3];
    GLdouble pole2[8][3];
    GLdouble pole3[8][3];
    GLdouble pole4[8][3];
    GLdouble pole5[8][3];
    GLdouble pole6[8][3];
    GLdouble pole7[8][3];
    GLdouble pole8[8][3];
    GLdouble panel1[8][3];
    GLdouble panel2[8][3];
    GLdouble panel3[8][3];
    GLdouble panel4[8][3];
    GLdouble panel5[8][3];
    GLdouble panel6[8][3];
    
    xyzcube(0.0, 3.0, -1.5, 50.0, 1.0, 1.0, pole1);
    xyzcube(0.0, -3.0, -1.5, 50.0, 1.0, 1.0, pole2);
    xyzcube(11.0, 0.0, -1.5, 1.0, 6.0, 1.0, pole3);
    xyzcube(-11.0, 0.0, -1.5, 1.0, 6.0, 1.0, pole4);
    xyzcube(18.0, 0.0, -1.25, 0.5, 44.0, 0.5, pole5);
    xyzcube(22.0, 0.0, -1.25, 0.5, 44.0, 0.5, pole6);
    xyzcube(-18.0, 0.0, -1.25, 0.5, 44.0, 0.5, pole7);
    xyzcube(-22.0, 0.0, -1.25, 0.5, 44.0, 0.5, pole8);
    xyzcube(20.0, 0.0, -0.5, 10.0, 14.0, 1.0, panel1);
    xyzcube(20.0, 15.0, -0.5, 10.0, 14.0, 1.0, panel2);
    xyzcube(20.0, -15.0, -0.5, 10.0, 14.0, 1.0, panel3);
    xyzcube(-20.0, 0.0, -0.5, 10.0, 14.0, 1.0, panel4);
    xyzcube(-20.0, 15.0, -0.5, 10.0, 14.0, 1.0, panel5);
    xyzcube(-20.0, -15.0, -0.5, 10.0, 14.0, 1.0, panel6);
    gluCylinder(1, 1, 1, 1, 1, 1);
}

//--------------------------------------
void drawKonishi(void){
    GLfloat pos0[] = { 10.0, 10.0, 10.0, 1.0 };
    GLfloat pos1[] = { 5.0, 0.0, 0.0, 0.0 };
    GLdouble vertex[][3] = {
            { 5.0, 8.0, 0.0 },
            { -5.0, 8.0, 0.0 },
            { -5.0, -8.0, 0.0 },
            { 5.0, -8.0, 0.0 },
            { 5.0, 8.0, -12.5 },
            { -5.0, 8.0, -12.5 },
            { -5.0, -8.0, -12.5 },
            { 5.0, -8.0, -12.5 }
    };
    
    glPushMatrix();
    
    glTranslatef(first_pos[0], first_pos[1], first_pos[2]);
    glRotatef(90, 1, 0, 0);
    glScaled(0.01, 0.01, 0.01);
    
    glLightfv(GL_LIGHT0, GL_POSITION, pos0);
    //glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    //glLightfv(GL_LIGHT0, GL_SPECULAR, white);
    //glLightfv(GL_LIGHT0, GL_AMBIENT, white);
    
    //glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
    //glMaterialfv(GL_FRONT, GL_AMBIENT, green);
    //glMaterialfv(GL_FRONT, GL_AMBIENT, black);
    //glMaterialfv(GL_FRONT, GL_SPECULAR, blue);
    //glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
    //glutSolidSphere(1, 30, 30);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color[YELLOW]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, color[YELLOW]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, color[YELLOW]);
    cube(vertex);
    GLdouble pole1[8][3];
    GLdouble pole2[8][3];
    GLdouble pole3[8][3];
    GLdouble pole4[8][3];
    GLdouble pole5[8][3];
    GLdouble pole6[8][3];
    GLdouble pole7[8][3];
    GLdouble pole8[8][3];
    GLdouble panel1[8][3];
    GLdouble panel2[8][3];
    GLdouble panel3[8][3];
    GLdouble panel4[8][3];
    GLdouble panel5[8][3];
    GLdouble panel6[8][3];
    
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color[BLACK]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, color[BLACK]);
    xyzcube(0.0, 3.0, -1.5, 50.0, 1.0, 1.0, pole1);
    xyzcube(0.0, -3.0, -1.5, 50.0, 1.0, 1.0, pole2);
    xyzcube(11.0, 0.0, -1.5, 1.0, 6.0, 1.0, pole3);
    xyzcube(-11.0, 0.0, -1.5, 1.0, 6.0, 1.0, pole4);
    xyzcube(18.0, 0.0, -1.25, 0.5, 44.0, 0.5, pole5);
    xyzcube(22.0, 0.0, -1.25, 0.5, 44.0, 0.5, pole6);
    xyzcube(-18.0, 0.0, -1.25, 0.5, 44.0, 0.5, pole7);
    xyzcube(-22.0, 0.0, -1.25, 0.5, 44.0, 0.5, pole8);
    
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color[BLUE]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLUE]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, color[BLUE]);
    xyzcube(20.0, 0.0, -0.5, 10.0, 14.0, 1.0, panel1);
    xyzcube(20.0, 15.0, -0.5, 10.0, 14.0, 1.0, panel2);
    xyzcube(20.0, -15.0, -0.5, 10.0, 14.0, 1.0, panel3);
    xyzcube(-20.0, 0.0, -0.5, 10.0, 14.0, 1.0, panel4);
    xyzcube(-20.0, 15.0, -0.5, 10.0, 14.0, 1.0, panel5);
    xyzcube(-20.0, -15.0, -0.5, 10.0, 14.0, 1.0, panel6);
    glPopMatrix();
}
