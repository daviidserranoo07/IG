#ifndef escalado_h
#define escalado_h

#include "transformacion.h"

class Escalado : public Transformacion{
private:
    float scale[3];
public:
    Escalado();
    Escalado(float x, float y, float z);
    virtual void draw();
};

#endif