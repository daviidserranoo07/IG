#ifndef transformacion_h
#define transformacion_h

#include "nodo.h"

class Transformacion : public Nodo{
private:

public:
    Transformacion();
    virtual void draw( ) = 0; // Dibuja el objeto
};

#endif