#include "superficie.h"
#include <math.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <utility>
#include "file_ply_stl.h"	

using namespace std;

Superficie::Superficie() : Objeto3D(){
  
}

Superficie::Superficie(string path,int n) : Superficie(){
  ply::read_vertices(path.c_str(),vertices_ply);
  
  //Añadimos las coordenadas de un vértice en el centro por abajo para tener tapa inferior
  //addTapaInferior();

  this->n=n;//Contiene el número de copias que vamos a hacer
  double angulo=0.0,x=0.0,y=0.0,z=0.0;

  //Añadimos las coordenadas de un vértice en el centro por arriba para tener tapa superior
  //addTapaSuperior();
  
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

Superficie::Superficie(string path,int n,Textura textura) : Superficie(path,n){
  this->textura=textura;
  calcularCoordenadasTextura();
}

void Superficie::draw(){
  if(dibujo){
    drawSmooth();
  }else{
    drawFlat();
  }
  Nodo::draw();
}

void Superficie::drawTextura(){
  pair<float,float> coordenada;
  glShadeModel(GL_SMOOTH);
  glBegin(GL_TRIANGLES);
  {
      for(int i=0;i<caras_ply.size()/3;i++){
        int indice=3*i;
        glNormal3f(normalesVertice[caras_ply[indice]*3],normalesVertice[caras_ply[indice]*3+1],normalesVertice[caras_ply[indice]*3+2]);
        coordenada=vectorCoordenadas[caras_ply[i]];
        glTexCoord2f(coordenada.first,coordenada.second); 
        glVertex3f(vertices_ply[caras_ply[indice]*3],vertices_ply[caras_ply[indice]*3+1],vertices_ply[caras_ply[indice]*3+2]);
        
        glNormal3f(normalesVertice[caras_ply[indice+1]*3],normalesVertice[caras_ply[indice+1]*3+1],normalesVertice[caras_ply[indice+1]*3+2]);
        coordenada=vectorCoordenadas[caras_ply[i+1]];
        glTexCoord2f(coordenada.first,coordenada.second); 
        glVertex3f(vertices_ply[caras_ply[indice+1]*3],vertices_ply[caras_ply[indice+1]*3+1],vertices_ply[caras_ply[indice+1]*3+2]);
        
        glNormal3f(normalesVertice[caras_ply[indice+2]*3],normalesVertice[caras_ply[indice+2]*3+1],normalesVertice[caras_ply[indice+2]*3+2]);
        coordenada=vectorCoordenadas[caras_ply[i+2]];
        glTexCoord2f(coordenada.first,coordenada.second); 
        glVertex3f(vertices_ply[caras_ply[indice+2]*3],vertices_ply[caras_ply[indice+2]*3+1],vertices_ply[caras_ply[indice+2]*3+2]);
      }
  }glEnd();
}

GLuint Superficie::getIdTextura(){
  return this->textura.getID();
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

void Superficie::calcularCoordenadasTextura() {
    float dmax=0.0, distance=0.0, u=0.0, v=0.0, angulo=0.0, di=0.0;
    vector<float> coordenadasU;
    int size = vertices_ply.size()/3;

    // Calculamos la distancia total dmax del perfil
    for(int i=0;i<size-1;i++) {
        distance=sqrt(pow(vertices_ply[i*3+3]-vertices_ply[i*3],2) +
                      pow(vertices_ply[i*3+4]-vertices_ply[i*3+1],2) +
                      pow(vertices_ply[i*3+5]-vertices_ply[i*3+2],2));
        dmax+=distance;
    }

    // Calcula las coordenadas de textura para cada vértice
    for(int i=0;i<size;i++) {
      // Calcula la distancia desde el inicio del perfil
      di = 0.0;
      distance=0.0;
      for(int k=0;k<i-1;k++){
          distance =sqrt(pow(vertices_ply[k*3+3]-vertices_ply[k*3],2) +
                         pow(vertices_ply[k*3+4]-vertices_ply[k*3+1],2) +
                         pow(vertices_ply[k*3+5]-vertices_ply[k*3+2],2));
          di+=distance;
      }

      // Coordenada v basada en la distancia desde el inicio del perfil y el número de copias
      v=di/dmax;
      pair<float,float> coordenada;
      // Coordenada u basada en el ángulo del perfil (en grados)
      float alpha = 360.0f / (size - 1);
      u = alpha * i;

      // Normalizamos u y v para que estén en el rango 0 a 1
      u /= 360.0f;
      coordenada.first=u;
      coordenada.second=v;

      // Guardar las coordenadas de textura para el vértice i
      vectorCoordenadas.push_back(coordenada);
    }
}    
