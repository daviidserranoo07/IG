#include "material.h"
#include <GL/glut.h>

Material::Material(){

}

void Material::setAmbiental(float R, float G, float B){
    this->ambiental[0]=R;
    this->ambiental[1]=G;
    this->ambiental[2]=B;
}

void Material::setEspecular(float R, float G, float B){
    this->especular[0]=R;
    this->especular[1]=G;
    this->especular[2]=B;
}

void Material::setDifusa(float R, float G, float B){
    this->difusa[0]=R;
    this->difusa[1]=G;
    this->difusa[2]=B;
}

void Material::setBrillo(float brillo){
    this->brillo=brillo;
}

void Material::aplicarMaterial(){
    glMaterialfv(GL_FRONT,GL_AMBIENT,ambiental);
    glMaterialfv(GL_FRONT,GL_SPECULAR,especular);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,difusa);
    glMaterialf(GL_FRONT,GL_SHININESS,brillo);
}