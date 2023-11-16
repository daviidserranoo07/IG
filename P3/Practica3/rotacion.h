#ifndef rotacion_h
#define rotacion_h

#include "transformacion.h"

class Rotacion : public Transformacion{
private:
    float rotation[3];
    float angle;
public:
    Rotacion();
    Rotacion(float angle, float x, float y, float z);
    void setRotar(float rotar);
    virtual void draw();
};

#endif