#ifndef traslacion_h
#define traslacion_h

#include "nodo.h"

class Traslacion : public Nodo{
private:
    float translation[3];
public:
    Traslacion();
    Traslacion(float x, float y, float z);
    virtual void apply();
};

#endif