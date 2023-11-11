#ifndef rotacion_h
#define rotacion_h

#include "nodo.h"

class Rotacion : public Nodo{
private:
    float rotation[3];
    float angle;
public:
    Rotacion();
    Rotacion(float angle, float x, float y, float z);
    virtual void apply();
};

#endif