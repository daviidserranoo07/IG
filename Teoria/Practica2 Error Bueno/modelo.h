/*	Prácticas de Informática Gráfica

	Grupo C					Curso 2022-23
 	
	Codigo base para la realización de las practicas de IG
	
	Estudiante: 

=======================================================
	G. Arroyo, J.C. Torres 
	Dpto. Lenguajes y Sistemas Informticos
	(Univ. de Granada)

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details 
 http://www.gnu.org/copyleft/gpl.html

=======================================================

	 modelo.h
*/

#include<vector>
#include<string>

/**
	Funcion de redibujado. Se ejecuta con los eventos postRedisplay
**/
void Dibuja (void);

/**
	Funcion de fondo
**/
void idle (int v);

/**
	Funcion de inicializacion del modelo y de las variables globales
**/
void initModel ();

/*Variable para cambiar el modo de dibujo*/
const int maxVer=10,maxTri=10;

/*Función para editar modo de visualización*/
void setModo(int M);

void setLuz();

void setDibujo();

void setModoVisualizacion(int n);

class Objeto3D {
protected:
	std::vector<float> vertices_ply;
	std::vector<int> caras_ply;
	std::vector<float> normalesVertice;	
public:
	void calcularNormal(float x1, float y1, float z1, float x2, float y2, float z2,float x3, float y3, float z3,float resultado[3]);
	virtual void draw(bool dibujo) = 0; // Dibuja el objeto
} ; 

class Malla : public Objeto3D{
public:
	Malla(std::string nombre);
	virtual void draw(bool dibujo);
	void calcularNormales();
	void drawFlat();
	void drawSmooth();
	void normalizar();
	bool getDibujo();
};

class Superficie : public Malla{
private:
	int n;
public:
	Superficie(std::string path,int n);
	virtual void draw(bool dibujo);
	void cerrarFigura();
	// void drawFlat();
	// void drawSmooth();
	void addTapaInferior();
	void addTapaSuperior();

};





