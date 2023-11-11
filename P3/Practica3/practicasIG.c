/*	Prácticas de Informática Gráfica

	Grupo C					Curso 2022-23
 	
	Codigo base para la realización de las practicas de IG
	
	Estudiante: 

	Programa principal
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

=======================================================

	practicasIG.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include "practicasIG.h"
#include <iostream>
#include <string.h>
//#include "hiply.h"




/*=================================================*/

/**	int main( int argc, char *argv[] )	
	Programa principal.
	
	Inicializa glut y openGL
	Crea la ventana X
	Inicializa las variables globales
	lanza los gestores de eventos	
**/
using namespace std;

int main (int argc, char *argv[])
{
// Inicializa glu y openGL
  glutInit (&argc, argv);

// Crea una ventana X para la salida grafica en la posicion 0,0 con tamaño 800x800, con colores RGB-alfa, con doble buffer, y 
// buffer de profundidad

  if(argc>1){
    if(strcmp(argv[1],"--help")==0){
      cout<<endl<<endl<<endl<<endl;
      cout<<"La tecla p cambia a modo GL_POINT"<<endl;
      cout<<"La tecla 1 cambia a modo GL_LINE"<<endl;
      cout<<"La tecla f cambia a modo GL_FILL"<<endl;
      cout<<"La tecla i desactiva la iluminación"<<endl;
      cout<<"La tecla q cambia a entre drawSmooth y drawFlat"<<endl;
      exit(0);
    }
  }

  glutInitWindowPosition (0, 0);
  glutInitWindowSize (800, 800);
  glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow ("IG. Curso 2023/24. Autor: DAVID SERRANO DOMINGUEZ");

// Inicializa las variables del modelo
  initModel ();

// Inicializa las funciones de dibujo y cambio de tamanyo de la ventana X
  if(argc==1){
    glutDisplayFunc (Dibuja);
  }else if(strcmp(argv[1],"--spin")==0){
    string argumento(argv[2]);
    cout<<"LEIDOOOOOO"<<argumento<<endl;
    guardarPath(argumento);
    glutDisplayFunc (DibujaSuperficie);
  }else if(strcmp(argv[1],"--load")==0){
    string argumento(argv[2]);
    guardarPath(argumento);
    glutDisplayFunc (DibujaPLY);
  }
  glutReshapeFunc (inicializaVentana);

// FUNCIONES DE INTERACCION
  glutKeyboardFunc (letra);
  glutSpecialFunc (especial);

  glutMouseFunc (clickRaton);
  glutMotionFunc (RatonMovido);

// Funcion de fondo
  glutTimerFunc (30, idle, 0);

// Inicializa parametros de openGL
  glEnable (GL_DEPTH_TEST);
  glEnable (GL_CULL_FACE);
  glEnable (GL_LIGHTING);
  glEnable (GL_LIGHT0);


// Lanza el gestor de eventos de glut
  glutMainLoop ();
  return 0;
}
