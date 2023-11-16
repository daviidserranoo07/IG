#include "rotacion.h"
#include <GL/glut.h>
#include <iostream>

using namespace std;

Rotacion::Rotacion() : Transformacion(){

}

Rotacion::Rotacion(float angle, float x, float y, float z){
    this->angle=angle;
    rotation[0]=x;
    rotation[1]=y;
    rotation[2]=z;
}

void Rotacion::draw(){
    glRotatef(angle,rotation[0],rotation[1],rotation[2]);
}

void Rotacion::setRotar(float rotar){
    glRotatef(rotar,rotation[0],rotation[1],rotation[2]);
}