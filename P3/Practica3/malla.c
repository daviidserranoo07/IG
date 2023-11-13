#include "malla.h"
#include <math.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "file_ply_stl.h"	

using namespace std;

void Malla::calcularNormales(){
  float normal[3];
  int indice=0;
  for(int i=0;i<caras_ply.size()/3;i++){
    indice=i*3;
    calcularNormal(vertices_ply[caras_ply[indice]*3],vertices_ply[caras_ply[indice]*3+1],vertices_ply[caras_ply[indice]*3+2],
                   vertices_ply[caras_ply[indice+1]*3],vertices_ply[caras_ply[indice+1]*3+1],vertices_ply[caras_ply[indice+1]*3+2],
                   vertices_ply[caras_ply[indice+2]*3],vertices_ply[caras_ply[indice+2]*3+1],vertices_ply[caras_ply[indice+2]*3+2],normal);
    
    for(int j=0;j<3;j++){
      normalesVertice[caras_ply[indice]*3+j]+=normal[j];
      normalesVertice[caras_ply[indice+1]*3+j]+=normal[j];
      normalesVertice[caras_ply[indice+2]*3+j]+=normal[j];
    }
  }
}

void Malla::normalizar(){
  float modulo=0.0;
  int actual=0;
  for(int i=0;i<caras_ply.size();i++){
    actual=caras_ply[i];
    modulo=sqrt(normalesVertice[actual*3]*normalesVertice[actual*3]+normalesVertice[actual*3+1]
               *normalesVertice[actual*3+1]+normalesVertice[actual*3+2]*normalesVertice[actual*3+2]);
    if(modulo>0.0){
       normalesVertice[actual*3]=normalesVertice[actual*3]/modulo;
       normalesVertice[actual*3+1]=normalesVertice[actual*3+1]/modulo;
       normalesVertice[actual*3+2]=normalesVertice[actual*3+2]/modulo;
    }
  }
}

void Malla::drawSmooth(){
  glShadeModel(GL_SMOOTH);
  glBegin(GL_TRIANGLES);
  {
      for(int i=0;i<caras_ply.size()/3;i++){
        int indice=3*i;
        glNormal3f(normalesVertice[caras_ply[indice]*3],normalesVertice[caras_ply[indice]*3+1],normalesVertice[caras_ply[indice]*3+2]);
        glVertex3f(vertices_ply[caras_ply[indice]*3],vertices_ply[caras_ply[indice]*3+1],vertices_ply[caras_ply[indice]*3+2]);
        glNormal3f(normalesVertice[caras_ply[indice+1]*3],normalesVertice[caras_ply[indice+1]*3+1],normalesVertice[caras_ply[indice+1]*3+2]);
        glVertex3f(vertices_ply[caras_ply[indice+1]*3],vertices_ply[caras_ply[indice+1]*3+1],vertices_ply[caras_ply[indice+1]*3+2]);
        glNormal3f(normalesVertice[caras_ply[indice+2]*3],normalesVertice[caras_ply[indice+2]*3+1],normalesVertice[caras_ply[indice+2]*3+2]);
        glVertex3f(vertices_ply[caras_ply[indice+2]*3],vertices_ply[caras_ply[indice+2]*3+1],vertices_ply[caras_ply[indice+2]*3+2]);
      }
  }glEnd();
}

void Malla::drawFlat(){
  glShadeModel(GL_FLAT);
  glBegin(GL_TRIANGLES);
  {
      float x=0.0,y=0.0,z=0.0,modulo=0.0,normal[3];
      for(int i=0;i<caras_ply.size()/3;i++){
        int indice=3*i;
        calcularNormal(vertices_ply[caras_ply[indice]*3],vertices_ply[caras_ply[indice]*3+1],vertices_ply[caras_ply[indice]*3+2],
                   vertices_ply[caras_ply[indice+1]*3],vertices_ply[caras_ply[indice+1]*3+1],vertices_ply[caras_ply[indice+1]*3+2],
                   vertices_ply[caras_ply[indice+2]*3],vertices_ply[caras_ply[indice+2]*3+1],vertices_ply[caras_ply[indice+2]*3+2],normal);
        
        glNormal3f(normal[0],normal[1],normal[2]);
        glVertex3f(vertices_ply[caras_ply[indice]*3],vertices_ply[caras_ply[indice]*3+1],vertices_ply[caras_ply[indice]*3+2]);
        glVertex3f(vertices_ply[caras_ply[indice+1]*3],vertices_ply[caras_ply[indice+1]*3+1],vertices_ply[caras_ply[indice+1]*3+2]);
        glVertex3f(vertices_ply[caras_ply[indice+2]*3],vertices_ply[caras_ply[indice+2]*3+1],vertices_ply[caras_ply[indice+2]*3+2]);
      }
  }glEnd();
}
void Malla::draw(){

}

Malla::Malla(string nombre){
  ply::read(nombre.c_str(),vertices_ply,caras_ply);
  normalesVertice.resize(vertices_ply.size());
  calcularNormales();
  normalizar();
}

Malla::Malla() : Objeto3D(){
}