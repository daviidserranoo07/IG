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
#include "file_ply_stl.h"


using namespace std;


/**	void initModel()

Inicializa el modelo y de las variables globales


**/
void
initModel (){
  mod=GL_FILL;
  iluminacio=true;
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

  for(int i=0;i<3;i++) resultado[i]=resultado[i]/longitud;
}

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
    if(modulo>0){
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
        x=normalesVertice[caras_ply[indice]*3]+normalesVertice[caras_ply[indice+1]*3]+normalesVertice[caras_ply[indice+2]*3];
        y=normalesVertice[caras_ply[indice]*3+1]+normalesVertice[caras_ply[indice+1]*3+1]+normalesVertice[caras_ply[indice+2]*3+1];
        z=normalesVertice[caras_ply[indice]*3+2]+normalesVertice[caras_ply[indice+1]*3+2]+normalesVertice[caras_ply[indice+2]*3+2];
        modulo=sqrt(x*x+y*y+z*z);
        normal[0]=x/modulo;
        normal[1]=y/modulo;
        normal[2]=z/modulo;
        glNormal3f(normal[0],normal[1],normal[2]);
        glVertex3f(vertices_ply[caras_ply[indice]*3],vertices_ply[caras_ply[indice]*3+1],vertices_ply[caras_ply[indice]*3+2]);
        glVertex3f(vertices_ply[caras_ply[indice+1]*3],vertices_ply[caras_ply[indice+1]*3+1],vertices_ply[caras_ply[indice+1]*3+2]);
        glVertex3f(vertices_ply[caras_ply[indice+2]*3],vertices_ply[caras_ply[indice+2]*3+1],vertices_ply[caras_ply[indice+2]*3+2]);
      }
  }glEnd();
}



class Ejes:Objeto3D { 
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
};

void Malla::draw(){
  if(dibujo) drawSmooth();
  else drawFlat();
}

void Superficie::draw(){

}

Malla::Malla(bool dibujo,string nombre){
  ply::read(nombre.c_str(),vertices_ply,caras_ply);
  normalesVertice.resize(vertices_ply.size());
  calcularNormales();
  normalizar();
  this->dibujo=dibujo;
}

Superficie::Superficie(string path){
  ply::read_vertices(path.c_str(),vertices_ply);
}

Ejes ejesCoordenadas;

/**	void Dibuja( void )

Procedimiento de dibujo del modelo. Es llamado por glut cada vez que se debe redibujar.

**/

Malla mallaPLY1(true,"./plys/beethoven.ply");
Malla mallaPLY2(false,"./plys/big_dodge.ply");
Superficie superficie("./plys/perfil.ply");

void Dibuja (void)
{
  static GLfloat  pos[4] = { 5.0, 5.0, 10.0, 0.0 },color2[4]={1,0.05,0.052,1},color3[4]={1.0,0.5,0,1};	// Posicion de la fuente de luz

  float  color[4] = { 0.8, 0.0, 1, 1 };

  glPushMatrix ();		// Apila la transformacion geometrica actual

  glClearColor (0.0, 0.0, 0.0, 1.0);	// Fija el color de fondo a negro

  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Inicializa el buffer de color y el Z-Buffer

  transformacionVisualizacion ();	// Carga transformacion de visualizacion

  glLightfv (GL_LIGHT0, GL_POSITION, pos);	// Declaracion de luz. Colocada aqui esta fija en la escena
  ejesCoordenadas.draw();			// Dibuja los ejes
  

  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
  glTranslatef(-10,0,0);
  mallaPLY1.draw();
  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color2);
  glTranslatef(25,0,0);
  mallaPLY2.draw();
      

  if(iluminacio){
    glEnable(GL_LIGHTING);
  }else{
    glDisable(GL_LIGHTING);

  }
  // Dibuja el modelo (A rellenar en prácticas 1,2 y 3)


  glPolygonMode(GL_FRONT_AND_BACK,mod);   
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
  mod=M;
}

void setLuz(){
  if(iluminacio){
    iluminacio=false;
  }else iluminacio=true;
}
