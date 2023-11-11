#include "rotacion.h"
#include <GL/glut.h>

using namespace std;

Rotacion::Rotacion(){

}

Rotacion::Rotacion(float angle, float x, float y, float z){
    this->angle=angle;
    rotation[0]=x;
    rotation[1]=y;
    rotation[2]=z;
}

void Rotacion::apply(){
    glRotatef(angle,rotation[0],rotation[1],rotation[2]);
}