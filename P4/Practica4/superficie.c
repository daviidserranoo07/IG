#include "superficie.h"
#include <math.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "file_ply_stl.h"	

using namespace std;

Superficie::Superficie() : Objeto3D(){
  
}

Superficie::Superficie(string path,int n) : Superficie(){
  ply::read_vertices(path.c_str(),vertices_ply);
  
  //Añadimos las coordenadas de un vértice en el centro por abajo para tener tapa inferior
  addTapaInferior();

  this->n=n;//Contiene el número de copias que vamos a hacer
  double angulo=0.0,x=0.0,y=0.0,z=0.0;

  //Añadimos las coordenadas de un vértice en el centro por arriba para tener tapa superior
  addTapaSuperior();
  
  int size=vertices_ply.size()/3;//Cada vértice tiene 3 coordenadas x,y,z por ese el tamaño total lo dividimos entre 3

  //Añadimos nuevos vértices calculando el nuevo valor de x y z, a partir de la hipotenusa que
  //es la x y multiplicando por cos y sin con el angulo que forman y que se obtiene como 2PIi/n-1
  //y finalmente añadimos las coordenadas de forma consecutivas al final del vector de vértices
  for(int i=0;i<n;i++){
    for(int j=0;j<size;j++){
      angulo=2*M_PI*(double)i/(n-1);
      x=vertices_ply[j*3]*cos(angulo);
      y=vertices_ply[j*3+1];
      z=-1*vertices_ply[j*3]*sin(angulo);
      vertices_ply.push_back(x);
      vertices_ply.push_back(y);
      vertices_ply.push_back(z);
    }
  }

  //Añadimos indices de las caras a lista de caras
  int k=0;
  for(int i=0;i<n-1;i++){
    for(int j=0;j<size-1;j++){
      k=i*size+j;//Es el indice que indica que el vértice j de la instancia i donde se encontrara en el vector caras_ply
        caras_ply.push_back(k);
        caras_ply.push_back(k+size);
        caras_ply.push_back(k+size+1);

        caras_ply.push_back(k);
        caras_ply.push_back(k+size+1);
        caras_ply.push_back(k+1); 
    }
  }

  //Cerramos la figura
  for (int i = 0; i < size-1; i++) {
        caras_ply.push_back(size*(n-1)+i);
        caras_ply.push_back(size+i);
        caras_ply.push_back(size+i+1); 

        caras_ply.push_back(size+i+1); 
        caras_ply.push_back(size*(n-1)+i+1);
        caras_ply.push_back(size*(n-1)+i);
    }

  normalesVertice.resize(vertices_ply.size());
  calcularNormales();
  normalizar();
}

Superficie::Superficie(string path,int n,Textura* textura) : Superficie(path,n){
  this->textura=textura;
}

void Superficie::draw(){
  if(dibujo){
    drawSmooth();
  }else{
    drawFlat();
  }
  Nodo::draw();
}

void Superficie::addTapaInferior(){
  double tapaInf=vertices_ply[1];
  vertices_ply.insert(vertices_ply.begin(),0);
  vertices_ply.insert(vertices_ply.begin(),tapaInf);
  vertices_ply.insert(vertices_ply.begin(),0);
}

void Superficie::addTapaSuperior(){
  double tapaSup=vertices_ply[vertices_ply.size()-2];
  vertices_ply.push_back(0);
  vertices_ply.push_back(tapaSup);
  vertices_ply.push_back(0);
}