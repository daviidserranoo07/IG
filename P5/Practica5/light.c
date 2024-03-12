#include "light.h"
#include <iostream>
#include <GL/glut.h>
#include <cstring>
#include <string>

using namespace std;

Light::Light(){

}

Light::Light(GLenum luzID,GLfloat* pos, GLfloat* color){
    this->luzID;
    this->pos=pos;
    this->color=color;
}

void Light::setID(GLenum luzID){
    this->luzID=luzID;
}

void Light::activarLuz(){
    glEnable(luzID);
}

void Light::desactivarLuz(){
    glDisable(luzID);
}

void Light::setColor(GLenum tipo,GLfloat* color){
    glLightfv(luzID,tipo,color);
}

void Light::setPos(GLfloat* pos){
    glLightfv(luzID,GL_POSITION,pos);
}