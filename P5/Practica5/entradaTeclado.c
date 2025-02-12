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
modulo entradaTeclado.c
	Gestion de eventos de teclado
*/

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include "practicasIG.h"
#include "modelo.h"
#include "camara.h"


/** 

Imprime en la consola las instrucciones del programa

**/
void printHelp ()
{

  printf ("\n\n     Prácticas de Informática Gráfica	Curso 2022-2023");
  printf ("\n\n Dpto. Lenguajes y Sistemas Informaticos");
  printf ("\n E.T.S.I. Informatica		Univ. de Granada ");
  printf ("\n");
  printf ("\n Opciones: \n\n");
  printf ("h, H: Imprime informacion de ayuda \n");
  printf ("PgUp, PgDn: avanza y retrocede la cámara \n\n");
  printf ("+,-: avanza y retrocede la cámara \n\n");
  printf ("Teclas de movimiento de cursor: giran la camara\n");
  printf ("p,1,f: Cambia el modo de dibujo\n");
  // Anyade la informacion de las opciones que introduzcas aqui !!       

  printf ("\n Escape: Salir");
  printf ("\n\n\n");
}




/* @teclado ---------------------------------------------------------------- */

/** 		void letra (unsigned char k, int x, int y)

Este procedimiento es llamado por el sistema cuando se pulsa una tecla normal
El codigo k es el ascii de la letra

Para anyadir nuevas ordenes de teclado coloca el correspondiente case.

Parametros de entrada:

k: codigo del caracter pulsado

x:

y:

**/
float rotxCamara = 30, rotyCamara = 45, moverseX=0, moverseZ=0;
float dCamara = 10;


void letra (unsigned char k, int x, int y)
{
  const float velocidadMovimiento=0.2f;
  rotxCamara=getCamara().getView_rotx();
  rotyCamara=getCamara().getView_roty();
  moverseX=getCamara().getX();
  moverseZ=getCamara().getY();
  switch (k)
    {
    case 'h':
    case 'H':
      printHelp ();		// H y h imprimen ayuda
      break;
    case '+':			// acerca la cámara
      dCamara -= 5.0;
      break;
    case '-':			// aleja la cámara
      dCamara += 5.0;
      break;
    case 27:			// Escape  Terminar
      exit (0);
      break;
    case 'p':
      setModo(GL_POINT);
      break;
    case '1':
      setModo(GL_LINE);
      break;
    case 'f':
      setModo(GL_FILL);
      break;
    case 'i':
      entradaTeclado('i');
      break;
    case 'q':
      entradaTeclado('q');
      break;
    case 'C':
      entradaTeclado('C');
      break;
    case 'c':
      entradaTeclado('c');
      break;
    case 'e':
      entradaTeclado('e');
      break;
    case 'E':
      entradaTeclado('E');
      break;
    case 'o':
      entradaTeclado('o');
      break;
    case 'O':
      entradaTeclado('O');
      break;
    case 'n':
      entradaTeclado('n');
      break;
    case 'N':
      entradaTeclado('N');
      break;
    case 'L':
      entradaTeclado('L');
      break;
    case 'l':
      entradaTeclado('l');
      break;
    case 'G':
      entradaTeclado('G');
      break;
    case 'g':
      entradaTeclado('g');
      break;
    case 'A':
      entradaTeclado('A');
      break;
    case '2':
      entradaTeclado('2');
      break;
    case '3':
      entradaTeclado('3');
      break;
    case 'w':
      moverseX-=velocidadMovimiento*sin(rotyCamara*M_PI/180.0);
      moverseZ+=velocidadMovimiento*cos(rotyCamara*M_PI/180.0);
      break;
    case 'a':
      moverseX+=velocidadMovimiento*cos(rotyCamara*M_PI/180.0);
      moverseZ+=velocidadMovimiento*sin(rotyCamara*M_PI/180.0);
      break;
    case 's':
      moverseX+=velocidadMovimiento*sin(rotyCamara*M_PI/180.0);
      moverseZ-=velocidadMovimiento*cos(rotyCamara*M_PI/180.0);
      break;
    case 'd':
      moverseX-=velocidadMovimiento*cos(rotyCamara*M_PI/180.0);
      moverseZ-=velocidadMovimiento*sin(rotyCamara*M_PI/180.0);
      break;
    case 'R':
      moverseX=0;
      moverseZ=0;
      setXY(moverseX,moverseZ);
      break;
    case '4':
      entradaTeclado('4');
      break;
    case '5':
      entradaTeclado('5');
      break;
    case '6':
      entradaTeclado('6');
      break;
    case '7':
      entradaTeclado('7');
      break;
    default:
      entradaTeclado(k);
      return;
    }
  setXY(moverseX,moverseZ);
  setCamara(rotxCamara,rotyCamara,dCamara);
  glutPostRedisplay ();		// Algunas de las opciones cambian paramentros
}				// de la camara. Es necesario actualziar la imagen

/**		void especial(int k, int x, int y)
Este procedimiento es llamado por el sistema cuando se pulsa una tecla
especial. El codigo k esta definido en glut mediante constantes

Parametros de entrada:

k: codigo del caracter pulsado (definido en glut mediante constantes).

x:

y:

**/
void especial (int k, int x, int y)
{

  switch (k)
    {
    case GLUT_KEY_UP:
      rotxCamara += 5.0;	// Cursor arriba + rotacion x
      if (rotxCamara > 360)
	rotxCamara -= 360;
      break;
    case GLUT_KEY_DOWN:
      rotxCamara -= 5.0;
      if (rotxCamara < 0)
	rotxCamara += 360;
      break;
    case GLUT_KEY_LEFT:
      rotyCamara += 5.0;
      if (rotyCamara > 360)
	rotyCamara -= 360;
      break;
    case GLUT_KEY_RIGHT:
      rotyCamara -= 5.0;
      if (rotyCamara < 0)
	rotyCamara += 360;
      break;
    case GLUT_KEY_PAGE_DOWN:	// acerca la cámara
      dCamara -= 5.0;
      break;
    case GLUT_KEY_PAGE_UP:	// aleja la cámara
      dCamara += 5.0;
      break;
    default:
      return;
    }
  setCamara(rotxCamara,rotyCamara,dCamara);
  glutPostRedisplay ();		// Actualiza la imagen (ver proc. letra)
}
