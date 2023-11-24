#ifndef cubo_h
#define cubo_h

#include "material.h"
#include "modelo.h"


class Cubo : public Objeto3D{
private:
    float lado;
public:
    Cubo(float lado, Material* material);
    virtual void draw();
};

#endif