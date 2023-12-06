#ifndef cubo_h
#define cubo_h

#include "material.h"
#include "modelo.h"
#include "texturas.h"


class Cubo : public Objeto3D{
private:
    float lado;
    bool materialActivado;
    Textura textura;
public:
    Cubo(float lado);
    virtual void draw();
    void drawTextura();
    void addMaterial(Material material);
    void addTextura(Textura textura);
    GLuint getIdTextura();
};

#endif