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

=======================================================/
modulo modelo.c
    Representación del modelo
    Funciones de dibujo
    Función Idle

*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include "practicasIG.h"

using namespace std;


/**	void initModel()

Inicializa el modelo y de las variables globales


**/
void
initModel (){
  modo=GL_FILL;
  iluminacion=true;
}

void Objeto3D::calcularNormal(float x1, float y1, float z1, float x2, float y2, float z2,float x3, float y3, float z3, float resultado[3]){
  float a1=x1-x3,
        a2=y1-y3,
        a3=z1-z3,
        b1=x2-x3,
        b2=y2-y3,
        b3=z2-z3,
        longitud=0.0;

  resultado[0]=a2*b3-a3*b2;
  resultado[1]=a3*b1-a1*b3;
  resultado[2]=a1*b2-a2*b1;

  longitud=sqrt(resultado[0]*resultado[0]+resultado[1]*resultado[1]+resultado[2]*resultado[2]);

  resultado[0]=resultado[0]/longitud;
  resultado[1]=resultado[1]/longitud;
  resultado[2]=resultado[2]/longitud;
}




class Ejes:Objeto3D 
{ 
public: 
    float longitud = 30;
// Dibuja el objeto
void draw( )
{
  glDisable (GL_LIGHTING);
  glBegin (GL_LINES);
  {
    glColor3f (0, 1, 0);
    glVertex3f (0, 0, 0);
    glVertex3f (0, longitud, 0);

    glColor3f (1, 0, 0);
    glVertex3f (0, 0, 0);
    glVertex3f (longitud, 0, 0);

    glColor3f (0, 0, 1);
    glVertex3f (0, 0, 0);
    glVertex3f (0, 0, longitud);
  }
  glEnd ();
  glEnable (GL_LIGHTING);

}
} ; 

Cubo::Cubo(float lado){
    this->lado=lado;
}

void Cubo::draw(){
  glPointSize(10);
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

Piramide::Piramide(float lado, float alto){
  this->lado=lado;
  this->alto=alto;
}

void Piramide::draw(){
  float mitadLado=lado/2;
  float normal[3];

  glBegin(GL_QUADS);
  {
    glNormal3f(0,-1,0);
    glVertex3f(0,0,0);
    glVertex3f(lado,0,0);
    glVertex3f(lado,0,lado);
    glVertex3f(0,0,lado);
  }glEnd();
  
  glBegin(GL_TRIANGLES);
  {
    //Triángulo izquierdo
    calcularNormal(mitadLado, alto,mitadLado,0,0,0,0,0,lado,normal);
    glNormal3f(normal[0],normal[1],normal[2]);
    glVertex3f(mitadLado,alto,mitadLado);
    glVertex3f(0,0,0);
    glVertex3f(0,0,lado);

    // Triángulo frontal
    calcularNormal(mitadLado,alto,mitadLado,0,0,lado,lado,0,lado,normal);
    glNormal3f(normal[0],normal[1],normal[2]);
    glVertex3f(mitadLado, alto,mitadLado);
    glVertex3f(0,0,lado);
    glVertex3f(lado,0,lado);
    
    // Triángulo derecho
    calcularNormal(mitadLado,alto,mitadLado,lado,0,lado,lado,0,0,normal);
    glNormal3f(normal[0],normal[1],normal[2]);
    glVertex3f(mitadLado,alto,mitadLado);
    glVertex3f(lado,0,lado);
    glVertex3f(lado,0,0);

    // Triángulo posterior
    calcularNormal(mitadLado, alto,mitadLado,lado,0,0,0,0,0,normal);
    glNormal3f(normal[0],normal[1],normal[2]);
    glVertex3f(mitadLado, alto, mitadLado);
    glVertex3f(lado,0,0);
    glVertex3f(0,0,0);
  }
  glEnd();

}

Octaedro::Octaedro(float lado){
  this->lado=lado;
}

void Octaedro::draw(){
  float normal[3];

  glBegin(GL_TRIANGLES);
  {
    calcularNormal(0,lado,0,0,0,lado,lado,0,0,normal);
    glNormal3f(normal[0],normal[1],normal[2]);
    glVertex3f(0,lado,0);
    glVertex3f(0,0,lado);
    glVertex3f(lado,0,0);

    calcularNormal(0,0,-lado,0,lado,0,lado,0,0,normal);
    glNormal3f(normal[0],normal[1],normal[2]);
    glVertex3f(0,0,-lado);
    glVertex3f(0,lado,0);
    glVertex3f(lado,0,0);
    
    calcularNormal(0,0,lado,0,-lado,0,lado,0,0,normal);
    glNormal3f(normal[0],normal[1],normal[2]);
    glVertex3f(0,0,lado);
    glVertex3f(0,-lado,0);
    glVertex3f(lado,0,0);

    calcularNormal(0,-lado,0,0,0,-lado,lado,0,0,normal);
    glNormal3f(normal[0],normal[1],normal[2]);
    glVertex3f(0,-lado,0);
    glVertex3f(0,0,-lado);
    glVertex3f(lado,0,0);
    
    calcularNormal(-lado,0,0,0,0,lado,0,lado,0,normal);
    glNormal3f(normal[0],normal[1],normal[2]);
    glVertex3f(-lado,0,0);
    glVertex3f(0,0,lado);
    glVertex3f(0,lado,0);
    
    calcularNormal(0,0,-lado,-lado,0,0,0,lado,0,normal);
    glNormal3f(normal[0],normal[1],normal[2]);
    glVertex3f(0,0,-lado);
    glVertex3f(-lado,0,0);
    glVertex3f(0,lado,0);

    calcularNormal(-lado,0,0,0,-lado,0,0,0,lado,normal);
    glNormal3f(normal[0],normal[1],normal[2]);
    glVertex3f(-lado,0,0);
    glVertex3f(0,-lado,0);
    glVertex3f(0,0,lado);

    calcularNormal(0,0,-lado,0,-lado,0,-lado,0,0,normal);
    glNormal3f(normal[0],normal[1],normal[2]);
    glVertex3f(0,0,-lado);
    glVertex3f(0,-lado,0);
    glVertex3f(-lado,0,0); 

  }glEnd();  
}

PiramideTruncada::PiramideTruncada(float lado){
  this->lado=lado;
}

void PiramideTruncada::draw(){
    glBegin (GL_QUADS);
    {
    glNormal3f (0,-1,0);
    glVertex3f (-1,0,-1);
    glVertex3f (lado+1,0,-1); 
    glVertex3f (lado+1,0,lado+1); 
    glVertex3f (-1,0,lado+1);

    glNormal3f (0.0,1.0,0.0);
    glVertex3f (1,lado,1);	
    glVertex3f (1,lado,lado-1);
    glVertex3f (lado-1,lado,lado-1);		
    glVertex3f (lado-1,lado,1);	

    glNormal3f (0.0,0.0,1.0);
    glVertex3f (1,lado,lado-1);	
    glVertex3f (-1,0,lado+1);
    glVertex3f (lado+1,0,lado+1);
    glVertex3f (lado-1,lado,lado-1);			

    glNormal3f (-1.0,0.0,0.0);
    glVertex3f(1,lado,1);
    glVertex3f(-1,0,-1);
    glVertex3f(-1,0,lado+1);
    glVertex3f(1,lado,lado-1);
    
    glNormal3f (1.0, 0.0, 0.0);
    glVertex3f(lado-1,lado,lado-1);
    glVertex3f(lado+1,0,lado+1);
    glVertex3f(lado+1,0,-1);
    glVertex3f(lado-1,lado,1);
    
    glNormal3f (0.0, 0.0,-1.0);
    glVertex3f(-1,0,-1);
    glVertex3f(1,lado,1);
    glVertex3f(lado-1,lado,1);
    glVertex3f(lado+1,0,-1);
    
  }glEnd ();
  
  
}

Ejes ejesCoordenadas;


/**	void Dibuja( void )

Procedimiento de dibujo del modelo. Es llamado por glut cada vez que se debe redibujar.

**/

void Dibuja (void)
{
  static GLfloat  pos[4] = { 5.0, 5.0, 10.0, 0.0 },color2[4]={1.0,0.0,0.5,1},color3[4]={1.0,0.5,0,1},color4[4]={1.0,2,0,1};	// Posicion de la fuente de luz

  float  color[4] = { 0.8, 0.0, 1, 1 };

  glPushMatrix ();		// Apila la transformacion geometrica actual

  glClearColor (0.0, 0.0, 0.0, 1.0);	// Fija el color de fondo a negro

  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Inicializa el buffer de color y el Z-Buffer

  transformacionVisualizacion ();	// Carga transformacion de visualizacion

  glLightfv (GL_LIGHT0, GL_POSITION, pos);	// Declaracion de luz. Colocada aqui esta fija en la escena

  ejesCoordenadas.draw();			// Dibuja los ejes

  glEnable(GL_COLOR_MATERIAL);

  // glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);

  glColor4fv(color);

  if(iluminacion){
    glEnable(GL_LIGHTING);
  }else{
    glDisable(GL_LIGHTING);

  }
  // Dibuja el modelo (A rellenar en prácticas 1,2 y 3)
  Cubo cubo(2);
  Piramide piramide(2,4);
  Octaedro octaedro(1.5);
  PiramideTruncada truncada(3);

  cubo.draw();
  glTranslatef(3,0,0);
  glColor4fv(color2);
  piramide.draw();
  glTranslatef(-1.5,1.5,5);
  glColor4fv(color3);
  octaedro.draw();
  glTranslatef(5,-1.5,-5);
  glColor4fv(color4);
  truncada.draw();
  
  glPolygonMode(GL_FRONT_AND_BACK,modo);   
  glPopMatrix ();		// Desapila la transformacion geometrica


  glutSwapBuffers ();		// Intercambia el buffer de dibujo y visualizacion
}


/**	void idle()

Procedimiento de fondo. Es llamado por glut cuando no hay eventos pendientes.

**/
void idle (int v)
{

  glutPostRedisplay ();		// Redibuja
  glutTimerFunc (30, idle, 0);	// Vuelve a activarse dentro de 30 ms
}

void setModo(int M)
{
  modo=M;
}

void setLuz(){
  if(iluminacion){
    iluminacion=false;
  }else iluminacion=true;
}
