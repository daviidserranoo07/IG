#include "traslacion.h"
#include <GL/glut.h>

using namespace std;

Traslacion::Traslacion(){

}

Traslacion::Traslacion(float x, float y, float z){
    translation[0]=x;
    translation[1]=y;
    translation[2]=z;
}

void Traslacion::apply(){
    glTranslatef(translation[0],translation[1],translation[2]);
}