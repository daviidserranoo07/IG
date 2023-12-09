/*	Prácticas de Informática Gráfica

	Grupo C					Curso 2023-24
 	
	Codigo base para la realización de las practicas de IG
	
	Estudiante: David Serrano Domínguez

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
    if(strcmp(argv[1],"--help")!=0 && strcmp(argv[1],"--load")!=0 && strcmp(argv[1],"--spin")!=0 && strcmp(argv[1],"--practica3")!=0){
      cout<<"La opción pasada es incorrecta, solo existe --help, --load, --spin, --practica3"<<endl;
      exit(0);
    }else if(strcmp(argv[1],"--help")==0){
      cout<<"-------------MODOS-------------"<<endl;
      cout<<"La tecla p cambia a modo GL_POINT"<<endl;
      cout<<"La tecla 1 cambia a modo GL_LINE"<<endl;
      cout<<"La tecla f cambia a modo GL_FILL"<<endl;
      cout<<endl;
      cout<<"-------------ILUMINACIÓN-------------"<<endl;
      cout<<"La tecla i desactiva la iluminación"<<endl;
      cout<<"La tecla 2 para activar y desactivar la iluminacion 1"<<endl;
      cout<<"La tecla 3 para activar y desactivar la iluminacion 3"<<endl;
      cout<<endl;
      cout<<"-------------MODO DIBUJO-------------"<<endl;
      cout<<"La tecla q cambia a entre drawSmooth y drawFlat"<<endl;
      cout<<endl;
      cout<<"-------------MOVIMIENTO ROBOT-------------"<<endl;
      cout<<"La tecla s mueve el robot hacia delante"<<endl;
      cout<<"La tecla S mueve el robot hacia atras"<<endl;
      cout<<"La tecla o mueve el robot hacia arriba"<<endl;
      cout<<"La tecla O mueve el robot hacia abajo"<<endl;
      cout<<"-------------GIROS ROBOT-------------"<<endl;
      cout<<endl;
      cout<<"La tecla C gira el torso del robot hacia la izquierda"<<endl;
      cout<<"La tecla c gira el torso del robot hacia la derecha"<<endl;
      cout<<"La tecla N gira el robot hacia la izquierda"<<endl;
      cout<<"La tecla n gira el robot hacia la derecha"<<endl;
      cout<<endl;
      cout<<"-------------ANIMACIÓN-------------"<<endl;
      cout<<"La tecla A para activar y desactivar animación"<<endl;
      cout<<"La tecla L aumenta velocidad de giro de todo el robot"<<endl;
      cout<<"La tecla l disminuye velocidad de giro de todo el robot"<<endl;
      cout<<"La tecla G aumenta velocidad de movimiento hacia arriba del robot"<<endl;
      cout<<"La tecla g disminuye velocidad de movimiento hacia arriba del robot"<<endl;
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
    if(argc<3){
      cout<<"No has pasado ninguna ruta"<<endl;
      exit(0);
    }
    string argumento(argv[2]);
    guardarPath(argumento);
    glutDisplayFunc (DibujaSuperficie);
  }else if(strcmp(argv[1],"--load")==0){
    if(argc<3){
      cout<<"No has pasado ninguna ruta"<<endl;
      exit(0);
    }
    string argumento(argv[2]);
    guardarPath(argumento);
    glutDisplayFunc (DibujaPLY);
  }else if(strcmp(argv[1],"--practica3")==0){
    glutDisplayFunc (DibujaP3);
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
