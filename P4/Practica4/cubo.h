#ifndef cubo_h
#define cubo_h

#include "material.h"
#include "modelo.h"


class Cubo : public Objeto3D{
private:
    float lado;
    bool materialActivado;
public:
    Cubo(float lado);
    Cubo(float lado, Material* material);
    virtual void draw();
    void drawTextura();
};

#endif