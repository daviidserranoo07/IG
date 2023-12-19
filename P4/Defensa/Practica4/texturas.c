#include "texturas.h"
#include "lector-jpg.h"
#include <string>

using namespace std;

Textura::Textura(){

}

Textura::Textura(string pathTextura){
    this->image=LeerArchivoJPEG(pathTextura.c_str(),ancho,alto);
}

void Textura::setTextura(string pathTextura){
    this->image=LeerArchivoJPEG(pathTextura.c_str(),ancho,alto);
}

int Textura::getID(){
    return this->texId;
}

void Textura::draw(){

}

void Textura::cargarTextura(){
    glGenTextures(1,&texId);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,ancho,alto,0,GL_RGB,GL_UNSIGNED_BYTE,image);
}