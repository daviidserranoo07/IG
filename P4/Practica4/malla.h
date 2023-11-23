#ifndef malla_h
#define malla_h
#include "modelo.h"

class Malla : public Objeto3D{
protected:
	
public:
	Malla(std::string nombre);
	Malla();
	virtual void draw();
	bool getDibujo();
};

#endif