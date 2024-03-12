#include "cubo.h"
#include "GL/glut.h"
#include "material.h"

Cubo::Cubo(float lado){
    this->lado=lado;
    this->materialActivado=false;
}

void Cubo::addMaterial(Material material){
  this->material=material;
  this->materialActivado=true;
}

void Cubo::draw(){
  if(materialActivado){
      material.aplicarMaterial();
  }
  glBegin (GL_QUAD_STRIP);
  {
    glNormal3f (0.0, 0.0, 1.0);	/*Vertical delantera */
    glVertex3f (lado, lado, lado);
    glVertex3f (0, lado, lado);
    glVertex3f (lado, 0, lado);
    glVertex3f (0, 0, lado);
    glNormal3f (0.0, -1.0, 0.0);	/*Inferior */
    glVertex3f (lado, 0, 0);
    glVertex3f (0, 0, 0);
    glNormal3f (0.0, 0.0, -1.0);	/* Vertical hacia atras */
    glVertex3f (lado, lado, 0);
    glVertex3f (0, lado, 0);
    glNormal3f (0.0, 1.0, 0.0);	/* Superior, horizontal */
    glVertex3f (lado, lado, lado);
    glVertex3f (0, lado, lado);
  }
  glEnd ();
  glBegin (GL_QUADS);
  {
    glNormal3f (1.0, 0.0, 0.0);
    glVertex3f (lado, 0, 0);
    glVertex3f (lado, lado, 0);
    glVertex3f (lado, lado, lado);
    glVertex3f (lado, 0, lado);
    glNormal3f (-1.0, 0.0, 0.0);
    glVertex3f (0, 0, 0);
    glVertex3f (0, 0, lado);
    glVertex3f (0, lado, lado);
    glVertex3f (0, lado, 0);
  }glEnd ();
}

void Cubo::drawTextura(){
  glBegin (GL_QUADS);
  {
    glNormal3f (0.0, 0.0, 1.0);	/*Vertical delantera */
    glTexCoord2f(0.5,0.75);  
    glVertex3f (lado, 0, lado);

    glTexCoord2f(0.5,0.5); 
    glVertex3f (lado, lado, lado);

    glTexCoord2f(0.75,0.5); 
    glVertex3f (0, lado, lado);

    glTexCoord2f(0.75,0.75); 
    glVertex3f (0, 0, lado);

    glNormal3f (0.0, -1.0, 0.0);	/*Inferior */
    glTexCoord2f(1,0.5);
    glVertex3f (lado, 0, 0);

    glTexCoord2f(0.75,0.5);
    glVertex3f (lado, 0, lado);

    glTexCoord2f(0.75,0.75);  
    glVertex3f (0, 0, lado);

    glTexCoord2f(1,0.75);  
    glVertex3f (0, 0, 0);

    glNormal3f (0.0, 0.0, -1.0);	/* Vertical hacia atras */
    glTexCoord2f(0.0,0.5);  
    glVertex3f (0, 0, 0);

    glTexCoord2f(0.0,0.75);  
    glVertex3f (0, lado, 0);

    glTexCoord2f(0.25,0.75);
    glVertex3f (lado, lado, 0);

    glTexCoord2f(0.25,0.5); 
    glVertex3f (lado, 0, 0);

    glNormal3f (0.0, 1.0, 0.0);	/* Superior, horizontal */
    glTexCoord2f(0.25,0.5);
    glVertex3f (lado, lado, lado);

    glTexCoord2f(0.5,0.5);
    glVertex3f (lado, lado, 0);

    glTexCoord2f(0.5,0.75);
    glVertex3f (0, lado, 0);

    glTexCoord2f(0.25,0.75); 
    glVertex3f (0, lado, lado);

    glNormal3f (1.0, 0.0, 0.0);//Lado derecho
    glTexCoord2f(0.5,0.25); 
    glVertex3f (lado, 0, 0);

    glTexCoord2f(0.75,0.25);  
    glVertex3f (lado, lado, 0);

    glTexCoord2f(0.75,0.5); 
    glVertex3f (lado, lado, lado);
    
    glTexCoord2f(0.5,0.5); 
    glVertex3f (lado, 0, lado);

    glNormal3f (-1.0, 0.0, 0.0);//Lado izquierdo
    glTexCoord2f(0.75,1);  
    glVertex3f (0, 0, 0);

    glTexCoord2f(0.5,1);  
    glVertex3f (0, 0, lado);

    glTexCoord2f(0.5,0.75);  
    glVertex3f (0, lado, lado);

    glTexCoord2f(0.75,0.75);  
    glVertex3f (0, lado, 0);
  }glEnd ();
}

 void Cubo::addTextura(Textura textura){
  this->textura=textura;
 }

GLuint Cubo::getIdTextura(){
  return this->textura.getID();
}