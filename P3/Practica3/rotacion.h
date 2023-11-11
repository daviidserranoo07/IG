#ifndef rotacion_h
#define rotacion_h

#include "nodo.h"

class Rotacion : public Nodo{
private:
    float rotation[3];
public:
    Rotacion();
    virtual void apply();
};

#endif