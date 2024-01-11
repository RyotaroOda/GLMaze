#include "LightController.h"
#include "Header.h"

void lightInit(void){
    //光源
    static GLfloat lightDiffuse[3]  = { 1.0,   1.0, 1.0  }; //拡散光
    static GLfloat lightAmbient[3]  = { 0.25, 0.25, 0.25 }; //環境光
    static GLfloat lightSpecular[3] = { 1.0,   1.0, 1.0  }; //鏡面光
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  lightDiffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  lightAmbient);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    
    glEnable(GL_LIGHT0);
}

void lightUpdate(void){
    GLfloat pos0[] = { mainCameraPosition.x, mainCameraPosition.y, mainCameraPosition.z+1, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, pos0);
}

void lightColorChange(COLOR col){
    setWindow(0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, color[col]);
    windowUpdate();
}

void setLight(int lightNum){
    //    GLenum light = GL_LIGHT0 + lightNum;//光源のポインタを指定
    //    GLfloat lightPosition[4] = {
    //        mainCameraPosition.x, mainCameraPosition.y, 10.0, 1.0
    //
    //    }; //光源の位置
    //    glLightfv(light, GL_POSITION, lightPosition);
}
