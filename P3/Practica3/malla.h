#ifndef malla_h
#define malla_h
#include "modelo.h"

class Malla : public Objeto3D{
protected:
	static bool dibujo;
public:
	Malla(std::string nombre);
	Malla();
	virtual void draw();
	void calcularNormales();
	void drawFlat();
	static void changeDraw(bool cambio);
	void drawSmooth();
	void normalizar();
	bool getDibujo();
};

#endif