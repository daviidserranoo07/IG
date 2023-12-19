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
	Textura textura;
	std::vector<std::pair<float,float>> vectorCoordenadas;
public:
	Superficie();
	Superficie(std::string path,int n);
	Superficie(std::string path,int n,Textura textura);
	void draw();
	void drawTextura();
	void addMaterial(Material material);
	GLuint getIdTextura();
	void addTapaInferior();
	void addTapaSuperior();
	void calcularCoordenadasTextura();
	float distancia (float x0, float y0, float z0, float x1, float y1, float z1);
};

#endif