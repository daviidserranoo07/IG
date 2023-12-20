#include "malla.h"
#include <math.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "file_ply_stl.h"	

using namespace std;

Malla::Malla() : Objeto3D(){

}

Malla::Malla(string nombre) : Malla(){
  vector<float> vertices_ply,normalesVertice;
  vector<int> caras_ply;
  ply::read(nombre.c_str(),vertices_ply,caras_ply);
  this->mesh.setVertices(vertices_ply);
  normalesVertice.resize(vertices_ply.size());
  this->mesh.setCaras(caras_ply);
  this->mesh.setNormalesVertice(normalesVertice);
  calcularNormales();
  normalizar();
}

Malla::Malla(string nombre,Textura* textura) : Malla(nombre){
    this->textura=textura;
}

void Malla::draw() {
  if(Malla::dibujo){
    drawSmooth();
  }else{
    drawFlat();
  }
  Nodo::draw();
}