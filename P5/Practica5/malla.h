#ifndef malla_h
#define malla_h
#include "modelo.h"
#include "texturas.h"
#include <utility>
#include <vector>

class Malla : public Objeto3D{
protected:
	Textura* textura;
	std::vector<std::pair<float,float>> vectorCoordenadas;
public:
	Malla();
	Malla(std::string nombre);
	Malla(std::string nombre,Textura* textura);
	virtual void draw();
	bool getDibujo();
};

#endif