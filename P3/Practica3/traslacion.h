#ifndef traslacion_h
#define traslacion_h

#include "transformacion.h"

class Traslacion : public Transformacion{
private:
    float translation[3];
public:
    Traslacion();
    Traslacion(float x, float y, float z);
    virtual void apply();
};

#endif