#include "escalado.h"
#include <GL/glut.h>

using namespace std;

Escalado::Escalado(){

}

Escalado::Escalado(float x, float y, float z){
        scale[0]=x;
        scale[1]=y;
        scale[2]=z;
}

void Escalado::apply(){
        glScalef(scale[0],scale[1],scale[2]);
}