#ifndef malla_h
#define malla_h
#include "modelo.h"

class Malla : public Objeto3D{
protected:
	bool dibujo;
public:
	Malla(std::string nombre);
	Malla();
	virtual void draw();
	void calcularNormales();
	void drawFlat();
	void changeDraw(bool dibujo);
	void drawSmooth();
	void normalizar();
	bool getDibujo();
};

#endif