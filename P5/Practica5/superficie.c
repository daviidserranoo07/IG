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
  vector<float> vertices_ply,normalesVertice;
  vector<int> caras_ply;
  ply::read_vertices(path.c_str(),vertices_ply);
  this->mesh.setVertices(vertices_ply);
  
  //Añadimos las coordenadas de un vértice en el centro por abajo para tener tapa inferior
  addTapaInferior();
  vertices_ply=this->mesh.getVertices();
     
  this->n=n;//Contiene el número de copias que vamos a hacer
  double angulo=0.0,x=0.0,y=0.0,z=0.0;

  //Añadimos las coordenadas de un vértice en el centro por arriba para tener tapa superior
  addTapaSuperior();
  vertices_ply=this->mesh.getVertices();
  
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
  for(int i=0;i<n;i++){
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
  this->mesh.setVertices(vertices_ply);
  this->mesh.setCaras(caras_ply);
  this->mesh.setNormalesVertice(normalesVertice);
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
  vector<float> vertices_ply=this->mesh.getVertices(),normalesVertice=this->mesh.getNormalesVertice();
  vector<int> caras_ply=this->mesh.getCaras();
  glShadeModel(GL_SMOOTH);
  glBegin(GL_TRIANGLES);{   
    int size = caras_ply.size()/3;
    for(int i=0;i<size;i++) {
      int v0, v1, v2;
      int indice = i * 3;
      v0 = caras_ply[indice + 0];
      v1 = caras_ply[indice + 1];
      v2 = caras_ply[indice + 2];

      glNormal3f(normalesVertice[caras_ply[indice]*3],normalesVertice[caras_ply[indice]*3+1],normalesVertice[caras_ply[indice]*3+2]);
      glTexCoord2f(vectorCoordenadas[v0].first, vectorCoordenadas[v0].second);
      glVertex3f(vertices_ply[v0*3],vertices_ply[v0*3+1],vertices_ply[v0*3+2]);

      glNormal3f(normalesVertice[caras_ply[indice+1]*3],normalesVertice[caras_ply[indice+1]*3+1],normalesVertice[caras_ply[indice+1]*3+2]);
      glTexCoord2f(vectorCoordenadas[v1].first, vectorCoordenadas[v1].second);
      glVertex3f(vertices_ply[v1*3],vertices_ply[v1*3+1],vertices_ply[v1*3+2]);

      glNormal3f(normalesVertice[caras_ply[indice+2]*3],normalesVertice[caras_ply[indice+2]*3+1],normalesVertice[caras_ply[indice+2]*3+2]);
      glTexCoord2f(vectorCoordenadas[v2].first, vectorCoordenadas[v2].second);
      glVertex3f(vertices_ply[v2*3],vertices_ply[v2*3+1],vertices_ply[v2*3+2]);
    }
  }glEnd();
}

GLuint Superficie::getIdTextura(){
  return this->textura.getID();
}

void Superficie::addTapaInferior(){
  vector<float> vertices_ply=this->mesh.getVertices();
  
  double tapaInf=vertices_ply[1];
  vertices_ply.insert(vertices_ply.begin(),0);
  vertices_ply.insert(vertices_ply.begin(),tapaInf);
  vertices_ply.insert(vertices_ply.begin(),0);

  this->mesh.setVertices(vertices_ply);
}

void Superficie::addTapaSuperior(){
  vector<float> vertices_ply=this->mesh.getVertices();
  double tapaSup=vertices_ply[vertices_ply.size()-2];
  vertices_ply.push_back(0);
  vertices_ply.push_back(tapaSup);
  vertices_ply.push_back(0);

  this->mesh.setVertices(vertices_ply);
}

void Superficie::calcularCoordenadasTextura() {
    float dmax=0.0, distance=0.0, u=0.0, v=0.0, angulo=0.0, di=0.0,v0=0.0, v1=0.0, v2=0.0, u0=0.0, u1=0.0, u2=0.0;
    vector<float>vertices_ply=this->mesh.getVertices();
    int size = (vertices_ply.size()/3)/(n+1),base0=0,base1=0,indice=0;
    pair<float,float> coordenada;
    vector<float>auxiliar(size,0);
    

    // Calculamos la longitud total del perfil (dmax)
    for (int i=size-2;i> 0;i--) {
        base0 = i * 3;
        base1 = (i - 1) * 3;

        v0 = vertices_ply[base0 + 0];
        v1 = vertices_ply[base0 + 1];
        v2 = vertices_ply[base0 + 2];

        u0 = vertices_ply[base1 + 0];
        u1 = vertices_ply[base1 + 1];
        u2 = vertices_ply[base1 + 2];

        dmax += sqrt((pow(u0-v0,2) + pow(u1-v1,2) + pow(u2-v2,2)));

        auxiliar[i] = (dmax);
    }

    // Calcula las coordenadas de textura para cada vértice
    for(int i=0;i<vertices_ply.size()/3;i++) {
      indice=i*3;
      v = auxiliar[i%size]/dmax;
      angulo=atan2((-vertices_ply[indice+2]),(vertices_ply[indice]));
      if (angulo < 0) angulo = (2*M_PI)+angulo;
      if (i > 2*size && angulo < M_PI/n) angulo = 2*M_PI;

      u = angulo/(2*M_PI);
      coordenada.first=u;
      coordenada.second=v;

      // Guardar las coordenadas de textura para el vértice i
      vectorCoordenadas.push_back(coordenada);
    }
}    
