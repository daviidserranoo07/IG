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
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include "practicasIG.h"
#include "file_ply_stl.h"
#include "superficie.h"


using namespace std;


/**	void initModel()

Inicializa el modelo y de las variables globales

**/
int modo;
bool iluminacion, dibujo, animacion, llegadoMas, llegadoMenos, fin;
float rotarTorso, mover, moverY, rotarTodo, obtener;
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

void initModel (){
  modo=GL_FILL;
  iluminacion=true;
  ruta="";
  dibujo=false, obtener=false, animacion=false, llegadoMas=false, llegadoMenos=false, fin=false, rotarTorso=0;
  mover=0, moverY=0, rotarTodo=0;

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
  
  rotacion1->addChild(rotarEjeY);
  rotacion1->addChild(pi);
  rotacion1->addChild(pd);

  rotarEjeY->addChild(cuerpo);
  
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

  padre->draw();
  rotarEjeY->setRotar(rotarTorso);
  rotarEjeYTodo->setRotar(rotarTodo);
  traslacionZ->setTraslacionZ(mover);
  traslacionY->setTraslacionY(moverY);
  cuerpo->changeDraw(dibujo);
  glColor4fv(color);
  
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
  
  
  glColor4fv(color);
  if(!obtener){
    superficie=obtenerSuperficie();
    obtener=true;
  }

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

void setLuz(){
  if(iluminacion){
    iluminacion=false;
  }else iluminacion=true;
}

void setAnimacion(){
  if(animacion){
    animacion=false;
  }else animacion=true;
}

void setDraw(){
  if(dibujo){
    dibujo=false;
  }else dibujo=true;
}

void setRotarIzquierda(){
  if (rotarTorso<90 && rotarTorso>=-90) rotarTorso+=2;
}

void setRotarDerecha(){
  if (rotarTorso<=90 && rotarTorso>-90) rotarTorso-=2;
}

void setRotarTodoIzquierda(){
  rotarTodo+=2;
  if (rotarTodo>360)  rotarTodo-=360;
}

void setRotarTodoDerecha(){
  if (rotarTodo<360)  rotarTodo+=360;
  rotarTodo-=2;
}

void setMoverAdelante(){
  mover+=0.15;
}

void setMoverAtras(){
  mover-=0.15;
}

void setMoverArriba(){
  moverY+=0.15;
}

void setMoverAbajo(){
  moverY-=0.15;
}

void hacerAnimacion(){
    if(rotarTorso<90 && !llegadoMas){
      rotarTorso+=2;
    }else if(rotarTorso>-90 && !llegadoMenos){
      llegadoMas=true;
      rotarTorso-=2; 
    }else if(rotarTorso!=0){
      rotarTorso+=2;
      llegadoMenos=true;
    }else if(rotarTodo<270){
      rotarTodo+=2;
    }else if(rotarTodo==270 && moverY<3 && !fin){
      moverY+=0.04;
    }else{
      fin=true;
      rotarTorso=0;
      moverY=0;
    }
}

