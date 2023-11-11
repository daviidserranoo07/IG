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
void initModel (){

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
  if(longitud>0.0){
    resultado[0]=resultado[0]/longitud;
    resultado[1]=resultado[1]/longitud;
    resultado[2]=resultado[2]/longitud;
  }
  
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

Malla::Malla(bool dibujo,string nombre){
  ply::read(nombre.c_str(),vertices_ply,caras_ply);
  normalesVertice.resize(vertices_ply.size());
  calcularNormales();
  normalizar();
  this->dibujo=dibujo;
}

Malla::Malla(){
  dibujo=false;
}

Superficie::Superficie(string path,int n,bool dibujo){
  Malla();
  ply::read_vertices(path.c_str(),vertices_ply);
  
  //Añadimos las coordenadas de un vértice en el centro por abajo para tener tapa inferior
  addTapaInferior();

  this->n=n;//Contiene el número de copias que vamos a hacer
  this->dibujo=dibujo;//Booleao para saber si dibujamos en modo smooth o flat
  double angulo=0.0,x=0.0,y=0.0,z=0.0;

  //Añadimos las coordenadas de un vértice en el centro por arriba para tener tapa superior
  addTapaSuperior();
  
  int size=vertices_ply.size()/3;//Cada vértice tiene 3 coordenadas x,y,z por ese el tamaño total lo dividimos entre 3

  //Añadimos nuevos vértices calculando el nuevo valor de x y z, a partir de la hipotenusa que
  //es la x y multiplicando por cos y sin con el angulo que forman y que se obtiene como 2PIi/n-1
  //y finalmente añadimos las coordenadas de forma consecutivas al final del vector de vértices
  for(int i=1;i<n;i++){
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
  normalesVertice.resize(vertices_ply.size());
  calcularNormales();
  normalizar();
}

void Superficie::draw(){
  if(dibujo) drawSmooth();
  else drawFlat();
}

void Superficie::drawSmooth(){
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

void Superficie::drawFlat(){
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


Ejes ejesCoordenadas;

/**	void Dibuja( void )

Procedimiento de dibujo del modelo. Es llamado por glut cada vez que se debe redibujar.

**/

Malla mallaPLY1(true,"./plys/beethoven.ply");
Malla mallaPLY2(false,"./plys/big_dodge.ply");
Malla mallaPLY3(true,"./plys/footbones.ply");
Superficie superficie("./plys/perfil.ply",10,false);
Superficie superficie2("./plys/perfilCilindro.ply",100,true);
Superficie superficie3("./plys/perfilCono.ply",100,false);

void Dibuja (void)
{
  static GLfloat  pos[4] = { 5.0, 5.0, 10.0, 0.0 },color2[4]={1,0.05,0.052,1},color3[4]={1.0,0.5,0,1},color4[4]={1.0,0.8,0.3,1};	// Posicion de la fuente de luz

  float  color[4] = { 0.8, 0.0, 1, 1 };

  glPushMatrix ();		// Apila la transformacion geometrica actual

  glClearColor (0.0, 0.0, 0.0, 1.0);	// Fija el color de fondo a negro

  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Inicializa el buffer de color y el Z-Buffer

  transformacionVisualizacion ();	// Carga transformacion de visualizacion

  glLightfv (GL_LIGHT0, GL_POSITION, pos);	// Declaracion de luz. Colocada aqui esta fija en la escena
  ejesCoordenadas.draw();			// Dibuja los ejes
  glEnable(GL_COLOR_MATERIAL);
  glPointSize(5);

  if(iluminacio){
    glEnable(GL_LIGHTING);
  }else{
    glDisable(GL_LIGHTING);
  }
  
  glColor4fv(color);
  glTranslatef(-10,0,0);
  mallaPLY1.draw();
  glColor4fv(color2);
  glTranslatef(25,0,0);
  mallaPLY2.draw();
  glColor4fv(color3);
  glTranslatef(0,0,10);
  mallaPLY3.draw();
  glColor4fv(color);
  glTranslatef(-15,0,-10);
  glColor4fv(color4);
  glTranslatef(0,0,0); 
  superficie.draw();
  glTranslatef(-10,0,10);
  superficie2.draw();
  glTranslatef(0,0,10);
  superficie3.draw();
  
  // Dibuja el modelo (A rellenar en prácticas 1,2 y 3)

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

void Objeto3D::setModo(int M)
{
  modo=M;
}

void Objeto3D::setLuz(){
  if(iluminacion){
    iluminacion=false;
  }else iluminacion=true;
}
