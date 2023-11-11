#ifndef escalado_h
#define escalado_h

#include "nodo.h"

class Escalado : public Nodo{
private:
    float scale[3];
public:
    Escalado();
    Escalado(float x, float y, float z);
};

#endif