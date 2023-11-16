#include "malla.h"
#include <math.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "file_ply_stl.h"	

using namespace std;

void Malla::draw() {
  if(Malla::dibujo){
    drawSmooth();
  }else{
    drawFlat();
  }
}

Malla::Malla(string nombre){
  ply::read(nombre.c_str(),vertices_ply,caras_ply);
  normalesVertice.resize(vertices_ply.size());
  calcularNormales();
  normalizar();
}

Malla::Malla() : Objeto3D(){

}

