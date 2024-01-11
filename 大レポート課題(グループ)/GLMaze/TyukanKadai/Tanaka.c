#include <math.h>
#include "Header.h"
#include "Tanaka.h"
#include "GoalAnimation.h"


GLfloat pos0[] = { 20.0, 10.0, 0.0, 1.0 };
GLfloat pos1[] = { 5.0, 0.0, 0.0, 0.0 };
GLfloat red[] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat dark_red[] = { 0.6, 0.1, 0.0, 1.0 };
GLfloat green[] = { 0.0, 1.0, 0.0, 1.0 };
GLfloat blue[] = { 0.0, 0.0, 1.0, 1.0 };
GLfloat light_blue[] = { 0.2, 0.6, 1.0, 1.0 };
GLfloat yellow[] = { 1.0, 1.0, 0.0, 1.0 };
GLfloat brown[] = { 0.5, 0.25, 0.0, 1.0 };
GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat black[] = { .1, .1, .1, 1.0 };
GLdouble vertex[][3] = {
        { 1.0, 1.0, 0.0 },
        { -1.0, 1.0, 0.0 },
        { -1.0, -1.0, 0.0 },
        { 1.0, -1.0, 0.0 }
};
GLdouble centers[3] = {
    0.0, 0.0, 0.0
};
GLdouble norms[3] = {
    {0.0, 0.0, 1.0},
};
GLdouble thickness = 1;
GLdouble distance(GLdouble a[3], GLdouble b[3]){
    GLdouble div[3] = {
        a[0] - b[0],
        a[1] - b[1],
        a[2] - b[2]
    };
    return sqrt(div[0] * div[0] + div[1] * div[1] + div[2] * div[2]);
}

void sponge(GLdouble face[][3], GLdouble thick, GLdouble norm[3]){
    int i, j;
    GLdouble center[3] = {
        (face[0][0] + face[1][0] + face[2][0] + face[3][0])/4,
        (face[0][1] + face[1][1] + face[2][1] + face[3][1])/4,
        (face[0][2] + face[1][2] + face[2][2] + face[3][2])/4
    };
    GLdouble subdiv = 100.0, amp = 0.05, cycle = 0.24;
    GLdouble apex[(int)subdiv * 4][3];
    for (i = 0; i < 4; i++) {
        for (j = 0; j < subdiv; j++) {
            int v_from = i % 4, v_to = (i + 1) % 4;
            GLdouble s_vertex[3] = {
                face[v_from][0] + (face[v_to][0]-face[v_from][0]) * (GLdouble)j / subdiv,
                face[v_from][1] + (face[v_to][1]-face[v_from][1]) * (GLdouble)j / subdiv,
                face[v_from][2] + (face[v_to][2]-face[v_from][2]) * (GLdouble)j / subdiv
            };
            GLdouble wav = amp * sin(((GLdouble)i + (GLdouble)j / subdiv) * 2 * M_PI /cycle);
            GLdouble dist = distance(s_vertex, center);
            for (int k = 0; k < 3; k++){
                s_vertex[k] = center[k] + (dist + wav) / dist * (s_vertex[k] - center[k]);
                apex[i * (int)subdiv + j][k] = s_vertex[k];
            }
        }
    }
    for (i = 0; i < 4; i++) {
        for (j = 0; j < subdiv; j++) {
            int target = i * (int)subdiv + j;
            GLdouble apex1[3] = {
                apex[target][0],
                apex[target][1],
                apex[target][2] + thick / 2
            }, apex2[3] = {
                apex[(target+1) % ((int)subdiv * 4)][0],
                apex[(target+1) % ((int)subdiv * 4)][1],
                apex[(target+1) % ((int)subdiv * 4)][2] + thick / 2
            },_apex1[3] = {
                apex[target][0],
                apex[target][1],
                apex[target][2] - thick / 2
            }, _apex2[3] = {
                apex[(target+1) % ((int)subdiv * 4)][0],
                apex[(target+1) % ((int)subdiv * 4)][1],
                apex[(target+1) % ((int)subdiv * 4)][2] - thick / 2
            };
            GLdouble _norm[3] = {
                norm[0],
                norm[1],
                -norm[2]
            };
            glBegin(GL_TRIANGLES);
            glNormal3dv(norm);
            glVertex3dv(apex1);
            glVertex3dv(apex2);
            glVertex3dv(center);
            glEnd();
            glBegin(GL_TRIANGLES);
            glNormal3dv(_norm);
            glVertex3dv(_apex2);
            glVertex3dv(_apex1);
            glVertex3dv(center);
            glEnd();
            
            GLdouble __center[3] = {
                (apex1[0]+apex2[0]+_apex1[0]+_apex2[0])/4,
                (apex1[1]+apex2[1]+_apex1[1]+_apex2[1])/4,
                (apex1[2]+apex2[2]+_apex1[2]+_apex2[2])/4
            };
            GLdouble dist = distance(__center, center);
            GLdouble __norm[3] = {
                (__center[0] - center[0]) / dist,
                (__center[1] - center[1]) / dist,
                (__center[2] - center[2]) / dist
            };
            glBegin(GL_QUADS);
            glNormal3dv(__norm);
            glVertex3dv(_apex1);
            glVertex3dv(_apex2);
            glVertex3dv(apex2);
            glVertex3dv(apex1);
            glEnd();
        }
    }
}

void mouse(void){
    GLdouble start[3] = {
        -0.5, 0.2, 0.5
    };
    GLdouble end[3] = {
        0.5, 0.2, 0.5
    };
    GLdouble center[3] = {
        0.0, -0.5, 0.5
    };
    GLdouble subdiv = 10.0;
    GLdouble apex[(int)subdiv * 2][3];
    for (int i = 0;i < subdiv; i++){
        GLdouble div = ((GLdouble)i) * ((GLdouble)i - subdiv) / subdiv / subdiv;
        GLdouble vertex[3] = {
            start[0] + (end[0] - start[0]) * (GLdouble)i / subdiv,
            start[1] + (end[1] - start[1]) * (GLdouble)i / subdiv + div,
            start[2] + (end[2] - start[2]) * (GLdouble)i / subdiv
        };
        apex[i][0] = vertex[0];
        apex[i][1] = vertex[1];
        apex[i][2] = vertex[2];
    }
    for (int i = 0;i < subdiv; i++){
        GLdouble div = 4 * ((GLdouble)i) * ((GLdouble)i - subdiv) / subdiv / subdiv;
        GLdouble vertex[3] = {
            end[0] + (start[0] - end[0]) * (GLdouble)i / subdiv,
            end[1] + (start[1] - end[1]) * (GLdouble)i / subdiv + div,
            end[2] + (start[2] - end[2]) * (GLdouble)i / subdiv
        };
        apex[(int)subdiv + i][0] = vertex[0];
        apex[(int)subdiv + i][1] = vertex[1];
        apex[(int)subdiv + i][2] = vertex[2];
    }
    for (int i = 0;i < subdiv * 2; i++){
        int v_from = i % (int)(subdiv * 2), v_to = (i + 1) % (int)(subdiv * 2);
        glBegin(GL_TRIANGLES);
        glNormal3dv(norms);
        glVertex3dv(apex[v_to]);
        glVertex3dv(apex[v_from]);
        glVertex3dv(center);
        glEnd();
    }
}

void necktie(void){
    GLdouble tri[3][3] = {
        {-0.1, -1.0, 0.4},
        {0, -1.15, 0.4},
        {0.1, -1.0, 0.4}
    };
    GLdouble sq[4][3] = {
        {0, -1.0, 0.4},
        {-0.1, -1.3, 0.4},
        {0, -1.4, 0.4},
        {0.1, -1.3, 0.4}
    };
    glBegin(GL_TRIANGLES);
    glNormal3dv(norms);
    for (int i = 0;i < 3; i++){
        glVertex3dv(tri[i]);
    }
    glEnd();
    
    glBegin(GL_QUADS);
    glNormal3dv(norms);
    for (int i = 0;i < 4; i++){
        glVertex3dv(sq[i]);
    }
    glEnd();
}

void drawTanaka(void){
    
    glPushMatrix();
    glTranslatef(first_pos[0], first_pos[1], first_pos[2]);
    glRotatef(90, 1, 0, 0);
    glScaled(0.1, 0.1, 0.1);
    
    glPushMatrix();
    
    glLightfv(GL_LIGHT0, GL_POSITION, pos0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);
    glLightfv(GL_LIGHT0, GL_AMBIENT, white);
    
    glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
    //glMaterialfv(GL_FRONT, GL_AMBIENT, black);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 10.0);
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, yellow);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow);
    sponge(vertex, thickness, norms);
    //glutSolidSphere(1, 30, 30);
    
    glTranslatef(0, -1.3, 0);
    glScalef(2, 0.3, 0.7);
    glMaterialfv(GL_FRONT, GL_AMBIENT, brown);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, brown);
    glutSolidCube(1);
    glMaterialfv(GL_FRONT, GL_AMBIENT, white);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
    glTranslatef(0, 1.0, 0);
    glScalef(1, 1, 1);
    glutSolidCube(1);
    glPopMatrix();
    
    GLdouble i_size = 0.6;
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT, white);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
    glTranslatef(0.3, 0.4, 0.4);
    glScalef(1, 1, 0.5);
    glutSolidSphere(0.3, 30, 30);
    glMaterialfv(GL_FRONT, GL_AMBIENT, light_blue);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, light_blue);
    glTranslatef(-0.03, 0.0, 0.1);
    glScalef(i_size, i_size, 1);
    glutSolidSphere(0.3, 30, 30);
    glMaterialfv(GL_FRONT, GL_AMBIENT, black);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
    glTranslatef(0.0, 0.0, 0.1);
    glScalef(i_size, i_size, 1);
    glutSolidSphere(0.3, 30, 30);
    glMaterialfv(GL_FRONT, GL_AMBIENT, yellow);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow);
    glTranslatef(1.0, -0.5, 0.0);
    glScalef(2, 1.5, 1);
    glutSolidSphere(0.3, 30, 30);
    glMaterialfv(GL_FRONT, GL_AMBIENT, white);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
    glTranslatef(-0.7, -0.5, 0.0);
    glScalef(0.3, 0.4, 0.3);
    glutSolidCube(1);
    glPopMatrix();
    
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT, white);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
    glTranslatef(-0.3, 0.4, 0.4);
    glScalef(1, 1, 0.5);
    glutSolidSphere(0.3, 30, 30);
    glMaterialfv(GL_FRONT, GL_AMBIENT, light_blue);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, light_blue);
    glTranslatef(0.03, 0.0, 0.1);
    glScalef(i_size, i_size, 1);
    glutSolidSphere(0.3, 30, 30);
    glMaterialfv(GL_FRONT, GL_AMBIENT, black);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
    glTranslatef(0.0, 0.0, 0.1);
    glScalef(i_size, i_size, 1);
    glutSolidSphere(0.3, 30, 30);
    glMaterialfv(GL_FRONT, GL_AMBIENT, yellow);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow);
    glTranslatef(-1.0, -0.5, 0.0);
    glScalef(2, 1.5, 1);
    glutSolidSphere(0.3, 30, 30);
    glMaterialfv(GL_FRONT, GL_AMBIENT, white);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
    glTranslatef(0.7, -0.5, 0.0);
    glScalef(0.3, 0.4, 0.3);
    glutSolidCube(1);
    glPopMatrix();
    
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT, dark_red);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, dark_red);
    mouse();
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, red);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
    necktie();
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, yellow);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow);
    glTranslatef(0.0, 0.1, 0.5);
    glScalef(0.3, 0.3, 1);
    glutSolidSphere(0.3, 30, 30);
    glPopMatrix();
    
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT, brown);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, brown);
    glTranslatef(0.5, -1.5, 0.0);
    glScalef(0.5, 0.3, 0.3);
    glutSolidCube(1.0);
    glMaterialfv(GL_FRONT, GL_AMBIENT, yellow);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow);
    glTranslatef(0.0, -1, 0.0);
    glScalef(0.3, 1.0, 0.5);
    glutSolidCube(1.0);
    glMaterialfv(GL_FRONT, GL_AMBIENT, white);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
    glTranslatef(0.0, -0.5, 0.0);
    glScalef(1.1, 0.5, 1.1);
    glutSolidCube(1.0);
    glMaterialfv(GL_FRONT, GL_AMBIENT, black);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
    glTranslatef(0.0, -1.5, 0.8);
    glScalef(2, 2, 3);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT, brown);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, brown);
    glTranslatef(-0.5, -1.5, 0.0);
    glScalef(0.5, 0.3, 0.3);
    glutSolidCube(1.0);
    glMaterialfv(GL_FRONT, GL_AMBIENT, yellow);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow);
    glTranslatef(0.0, -1, 0.0);
    glScalef(0.3, 1.0, 0.5);
    glutSolidCube(1.0);
    glMaterialfv(GL_FRONT, GL_AMBIENT, white);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
    glTranslatef(0.0, -0.5, 0.0);
    glScalef(1.1, 0.5, 1.1);
    glutSolidCube(1.0);
    glMaterialfv(GL_FRONT, GL_AMBIENT, black);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
    glTranslatef(0.0, -1.5, 0.8);
    glScalef(2, 2, 3);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT, white);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
    glTranslatef(1.0, -0.3, 0.0);
    glScalef(0.5, 0.3, 0.3);
    glRotatef(-40, 0.0, 0.0, 1.0);
    glutSolidCube(1.0);
    glMaterialfv(GL_FRONT, GL_AMBIENT, yellow);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow);
    glScalef(3, 0.5, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT, yellow);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow);
    glTranslatef(1.6, -0.6, 0.35);
    glScalef(0.15, 0.15, 1);
    glutSolidCube(1.0);
    glTranslatef(0.1, 1, 1);
    glScalef(1.5, 3, 1);
    glutSolidCube(1.0);
    glTranslatef(0.3, 0.7, 0.0);
    glScalef(0.5, 0.8, 0.3);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT, white);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
    glTranslatef(-1.0, -0.3, 0.0);
    glScalef(0.5, 0.3, 0.3);
    glRotatef(40, 0.0, 0.0, 1.0);
    glutSolidCube(1.0);
    glMaterialfv(GL_FRONT, GL_AMBIENT, yellow);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow);
    glScalef(3, 0.5, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-1.2, -0.9, 0.0);
    glScalef(0.5, 0.3, 0.3);
    glRotatef(-60, 0.0, 0.0, 1.0);
    glScalef(3, 0.5, 0.5);
    glutSolidCube(1.0);
    glTranslatef(0.2, -0.2, 0.0);
    glScalef(0.5, 2, 2);
    glTranslatef(0.2, 0.0, 0.0);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPopMatrix();
}
