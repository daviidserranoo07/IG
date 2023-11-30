#ifndef texturas_h
#define texturas_h

#include "modelo.h"
#include <GL/glut.h>
#include <string>

class Textura : public Objeto3D{
private:
    unsigned char * image; //Array que contiene la textura
    GLuint texId; //Indentificador de la textura
    unsigned ancho, alto; //Almacena el alto y ancho de la textura
public:
    Textura();
    Textura(std::string pathTextura);
    void setTextura(std::string pathTextura);
    virtual void draw();
    void cargarTextura();
    int getID();
};

#endif