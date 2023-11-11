#ifndef superficie_h
#define superficie_h
#include "modelo.h"
#include "malla.h"

class Superficie : public Malla{
private:
	int n;
public:
	Superficie();
	Superficie(std::string path,int n);
	virtual void draw();
	void addTapaInferior();
	void addTapaSuperior();
};

#endif