#ifndef traslacion_h
#define traslacion_h

#include "transformacion.h"

class Traslacion : public Transformacion{
private:
    float translation[3];
public:
    Traslacion();
    Traslacion(float x, float y, float z);
    virtual void draw();
    void setTraslacionX(float traslacion);
    void setTraslacionZ(float traslacion);
    void setTraslacionY(float traslacion);
};

#endif