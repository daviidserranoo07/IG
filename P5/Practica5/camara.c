#include "camara.h"
#include <GL/glut.h>

Camara::Camara(){

}

Camara::Camara(float view_rotx, float view_roty, float D){
    this->view_rotx=view_rotx;
    this->view_roty=view_roty;
    this->D=D;
}

float Camara::getView_rotx(){
    return this->view_rotx;
}

float Camara::getView_roty(){
    return this->view_roty;
}

float Camara::getDistancia(){
    return this->D;
}

void Camara::setAngulo(float view_rotx, float view_roty){
    this->view_rotx=view_rotx;
    this->view_roty=view_roty;
}

void Camara::setDistancia(float D){
    this->D=D;
}

void Camara::setXY(float x, float y){
    this->moverX=x;
    this->moverY=y;
}

void Camara::aplicarTransformacion(){
    glTranslatef(0,0,-D);
    glRotatef(view_rotx,1.0,0.0,0.0);
    glRotatef(view_roty,0.0,1.0,0.0);
    glTranslatef(moverX,0.0,moverY);
}