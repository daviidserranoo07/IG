#ifndef superficie_h
#define superficie_h
#include "modelo.h"
#include "malla.h"
#include "texturas.h"
#include <utility>
#include <vector>

class Superficie : public Objeto3D{
private:
	int n;
	Textura* textura;
	std::vector<std::pair<float,float>> vectorCoordenadas;
public:
	Superficie();
	Superficie(std::string path,int n);
	Superficie(std::string path,int n,Textura* textura);
	void draw();
	void addTapaInferior();
	void addTapaSuperior();
};

#endif