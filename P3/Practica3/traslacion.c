#include "traslacion.h"
#include <GL/glut.h>

using namespace std;

Traslacion::Traslacion() : Transformacion(){

}

Traslacion::Traslacion(float x, float y, float z){
    translation[0]=x;
    translation[1]=y;
    translation[2]=z;
}

void Traslacion::draw(){
    glTranslatef(translation[0],translation[1],translation[2]);
}

void Traslacion::setTraslacion(float traslacion){
    glTranslatef(translation[0],traslacion,translation[2]);
}