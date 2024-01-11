#include "UIController.h"
#include "Header.h"
#include<string.h>

int list;
char *uiMessage = "";

void UIUpdate(void){
    if (uiMessage) {
        drawText(winWidth/22, winHeight/12.5, uiMessage);//中央に表示
    }
    char buf[12];
    snprintf(buf, 12, "SCORE %d", score);
    drawText(2, 2, buf);

}

// 文字描画
void *font = GLUT_BITMAP_TIMES_ROMAN_24;

void drawString(int x, int y, char *string, void *font){
    int len, i;
    glRasterPos2f(x, y);
    len = (int)strlen(string);
    for (i = 0; i < len; i++){
        glutBitmapCharacter(font, string[i]);
    }
}

void drawText(int x, int y, char *string){
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    
    glPushAttrib(GL_ENABLE_BIT);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 100, 0, 100);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glColor3f(0.0, 0.0, 0.0);
    glCallList(list);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glPopAttrib();
    glMatrixMode(GL_MODELVIEW);
    list = glGenLists(1);
    glNewList(list, GL_COMPILE);
    
    drawString(x, y, string, GLUT_BITMAP_TIMES_ROMAN_24);
    glEndList();
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void deleteMessage(int value){
    uiMessage = "";
}

//一定時間で消える
void showMesage(char *string){
    uiMessage = string;
    glutTimerFunc(3000, deleteMessage, 0);
}

void uiLabel(char *string, int x, int y){
    uiMessage = string;
}
