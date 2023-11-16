#ifndef superficie_h
#define superficie_h
#include "modelo.h"
#include "malla.h"

class Superficie : public Objeto3D{
private:
	int n;
public:
	Superficie();
	Superficie(std::string path,int n);
	void draw();
	void addTapaInferior();
	void addTapaSuperior();
};

#endif