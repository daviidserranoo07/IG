/*	Prácticas de Informática Gráfica

	Grupo C					Curso 2023-24
 	
	Codigo base para la realización de las practicas de IG
	
	Estudiante: David Serrano Domínguez

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
#include <vector>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include "practicasIG.h"
#include "file_ply_stl.h"
#include "superficie.h"
#include "cubo.h"
#include "material.h"

using namespace std;


/**	void initModel()

Inicializa el modelo y de las variables globales

**/
int modo;
bool iluminacion, dibujo, animacion, llegadoMas, llegadoMenos, fin, rapidoTodo, rapidoMovimiento, lentoTodo, lentoMovimiento;
float rotarTorso, mover, moverY, rotarTodo, obtener, aumenta, aumentaMover;
string ruta;

Nodo* padre;
Malla* cuerpo;
Malla* pi;
Malla* pd;
Rotacion* rotacion1;
Rotacion* rotarEjeY;
Rotacion* rotarEjeYTodo;
Traslacion* traslacionZ;
Traslacion* traslacionY;
Escalado* escalar;
Cubo* cubo;
Material* material;

void initModel (){
  //Inicializamos modo
  modo=GL_FILL;

  //Inicializamos la ruta
  ruta="";

  //Inicializamos todos los booleanos
  iluminacion=true, dibujo=false, obtener=false, animacion=false, llegadoMas=false, llegadoMenos=false, fin=false, 
  rotarTorso=false, rapidoTodo=false, rapidoMovimiento=false, lentoTodo=false, lentoMovimiento=false;

  //Inicializamos todos los float
  mover=0.0, moverY=0.0, rotarTodo=0.0, aumenta=1.0, aumentaMover=0.08;

  //Inicializamos todos los nodos que formaran la jerarquia(Práctica 3)
  padre = new Nodo();
  cuerpo = new Malla("./plys/cuerpo.ply");
  pi = new Malla("./plys/pi.ply");
  pd = new Malla("./plys/pd.ply");
  rotacion1 = new Rotacion(-90,1,0,0);
  rotarEjeY = new Rotacion(rotarTorso,0,0,1);
  rotarEjeYTodo = new Rotacion(rotarTodo,0,1,0);
  traslacionZ = new Traslacion(0,0,mover);
  traslacionY = new Traslacion(0,moverY,0);
  escalar = new Escalado(2,2,2);

  //Montamos la jerarquia
  padre->addChild(traslacionY);
  traslacionY->addChild(traslacionZ);
  traslacionZ->addChild(rotarEjeYTodo);
  rotarEjeYTodo->addChild(rotacion1);

  rotacion1->addChild(pi);
  rotacion1->addChild(pd);
  rotacion1->addChild(rotarEjeY);

  rotarEjeY->addChild(cuerpo);

  //Inicilizamos valores necesarios para materiales y texturas(Práctica 4)
  material = new Material();
  material->setAmbiental(0.8,0.8,0.8);
  material->setEspecular(0.5,0.5,0.5);
  material->setDifusa(0.3,0.3,0.3);
  material->setBrillo(0.9);
  cubo = new Cubo(3,material);
}

void entradaTeclado(char c){
  if(c=='C')
    if (rotarTorso<90 && rotarTorso>=-90) rotarTorso+=2;

  if(c=='c')
    if (rotarTorso<=90 && rotarTorso>-90) rotarTorso-=2;

  if(c=='N'){
    if (rotarTodo>360)  rotarTodo-=360;
    rotarTodo+=2;
  }

  if(c=='n'){
    if (rotarTodo<360)  rotarTodo+=360;
    rotarTodo-=2;
  }

  if(c=='s')
    mover+=0.15;

  if(c=='S')
    mover-=0.15;

  if(c=='o')
    moverY+=0.15;

  if(c=='O')
    moverY-=0.15;
  
  if(c=='L'){
    if(rapidoTodo){
      rapidoTodo=false;
    }else{
      rapidoTodo=true;
      lentoTodo=false;
    }
  }

  if(c=='l'){
    if(lentoTodo){
      lentoTodo=false;
    }else{
      lentoTodo=true;
      rapidoTodo=false;
    }
  }

  if(c=='G'){
    if(rapidoMovimiento){
      rapidoMovimiento=false;
    }else{
      rapidoMovimiento=true;
      lentoMovimiento=false;
    }
  }

  if(c=='g'){
    if(lentoMovimiento){
      lentoMovimiento=false;
    }else{
      lentoMovimiento=true;
      rapidoMovimiento=false;
    }
  }

  if(c=='i'){
    if(iluminacion){
      iluminacion=false;
    }else iluminacion=true;
  }


  if(c=='A'){
    if(animacion){
      animacion=false;
    }else{
      animacion=true;
      llegadoMas=false;
      llegadoMenos=false;
      fin=false;
    }
  }
  
  if(c=='q'){
    if(dibujo){
      dibujo=false;
    }else dibujo=true;
  }
}

/**
 * Guardamos la ruta de el archivo que queremos dibujar ya sea revolucion o ply
*/
void guardarPath(string path){
  ruta=path;
}

/**
 * Creamos el objeto revolución con la ruta de path y creamos dicha superficie para devolverla posteriormente
*/
Superficie obtenerSuperficie(){
  Superficie superficie(ruta,10);
  return superficie;
}

/**
 * Creamos el objeto malla con la ruta de path y creamos dicha malla para devolverla posteriormente
*/
Malla obtenerMalla(){
  Malla malla(ruta);
  return malla;
}

bool Objeto3D::dibujo=false;

/**
 *  Calcula la normal de una cara
*/
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

/**
 * Calcula las normales de un conjunto de vértices mediante las normales de cara
*/
void Objeto3D::calcularNormales(){
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

/**
 * Normaliza la normal de cada vértice
*/
void Objeto3D::normalizar(){
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

/**
 * Dibuja en modo smooth un Objeto3D
*/
void Objeto3D::drawSmooth(){
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

/**
 * Dibuja en modo flat un Objeto3D
*/
void Objeto3D::drawFlat(){
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

/**
 * Cambia el valor de la variable estática dibujo
*/
void Objeto3D::changeDraw(bool cambio){
  dibujo=cambio;
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

Ejes ejesCoordenadas;

/**	void Dibuja( void )

Procedimiento de dibujo del modelo. Es llamado por glut cada vez que se debe redibujar.

**/

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

  if(iluminacion){
    glEnable(GL_LIGHTING);
  }else{
    glDisable(GL_LIGHTING);
  }

  cubo->draw();

  // Dibuja el modelo (A rellenar en prácticas 1,2 y 3)

  glPolygonMode(GL_FRONT_AND_BACK,modo);   
  glPopMatrix ();		// Desapila la transformacion geometrica


  glutSwapBuffers ();		// Intercambia el buffer de dibujo y visualizacion
}


void DibujaP3 (void)
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

  if(iluminacion){
    glEnable(GL_LIGHTING);
  }else{
    glDisable(GL_LIGHTING);
  }

  glColor4fv(color);
  padre->draw();
  rotarEjeY->setRotar(rotarTorso);
  rotarEjeYTodo->setRotar(rotarTodo);
  traslacionZ->setTraslacionZ(mover);
  traslacionY->setTraslacionY(moverY);
  cuerpo->changeDraw(dibujo);
  
  
  // Dibuja el modelo (A rellenar en prácticas 1,2 y 3)

  glPolygonMode(GL_FRONT_AND_BACK,modo);   
  glPopMatrix ();		// Desapila la transformacion geometrica


  glutSwapBuffers ();		// Intercambia el buffer de dibujo y visualizacion
}

Superficie superficie;
/**
 * Función que dibuja solo el perfil pasado como argumento cuando hacemos la llamada ./practicaIG --spin /ruta/perfil
*/
void DibujaSuperficie(void)
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

  if(iluminacion){
    glEnable(GL_LIGHTING);
  }else{
    glDisable(GL_LIGHTING);
  }
  
  
  if(!obtener){
    superficie=obtenerSuperficie();
    obtener=true;
  }

  glColor4fv(color);
  superficie.changeDraw(dibujo);
  superficie.draw();
  
  
  // Dibuja el modelo (A rellenar en prácticas 1,2 y 3)

  glPolygonMode(GL_FRONT_AND_BACK,modo);   
  glPopMatrix ();		// Desapila la transformacion geometrica


  glutSwapBuffers ();		// Intercambia el buffer de dibujo y visualizacion
}


Malla malla;
/**
 * Función que dibuja solo el PLY pasado como argumento cuando hacemos la llamada ./practicaIG --load /ruta/ply
*/
void DibujaPLY(void)
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

  if(iluminacion){
    glEnable(GL_LIGHTING);
  }else{
    glDisable(GL_LIGHTING);
  }
  
  glColor4fv(color);
  if(!obtener){
    malla=obtenerMalla();
    obtener=true;
  }
  glRotatef(-90,1,0,0);
  malla.changeDraw(dibujo);
  malla.draw();

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
  if(animacion){
    hacerAnimacion();
  }
  glutPostRedisplay ();		// Redibuja
  glutTimerFunc (30, idle, 0);	// Vuelve a activarse dentro de 30 ms
}

void setModo(int M)
{
  modo=M;
}

void hacerAnimacion(){
    if(rotarTorso<90 && !llegadoMas){
      rotarTorso+=3;
    }else if(rotarTorso>-90 && !llegadoMenos){
      llegadoMas=true;
      rotarTorso-=3; 
    }else if(rotarTorso!=0){
      rotarTorso+=3;
      llegadoMenos=true;
    }else if(rotarTodo<360 && !fin){
      if(rapidoTodo){
        aumenta++;
        rapidoTodo=false;
      }else if(lentoTodo && aumenta>0){
        aumenta--;
        lentoTodo=false;
      }
      rotarTodo+=aumenta;
    }else if(rotarTodo>=360 && moverY<8 && !fin){
      if(rapidoMovimiento){
        aumentaMover+=0.02;
        rapidoMovimiento=false;
      }else if(lentoMovimiento && aumentaMover>0){
        aumentaMover-=0.02;
        lentoMovimiento=false;
      }
      moverY+=aumentaMover;
    }else{
      fin=true;
      rotarTorso=0;
      moverY=0;
      rotarTodo=0;
      animacion=false;
      aumenta=1;
      aumentaMover=0.08;
    }
}

