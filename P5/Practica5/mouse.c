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
	modulo mouse.c
	Gestion de eventos de raton

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include <iostream>
#include "practicasIG.h"
#include "visual.h"
#include "camara.h"
#include <string>

using namespace std;

/**	 void clickRaton( int boton, int estado, int x, int y )

Procedimiento para gestionar los eventos de pulsacion de los botones del raton.

Argumentos:

boton: Codigo glut del boton que ha manipulado el usuario.

estado: Estado en el que esta el boton que se ha pulsado.

x,y: Posicion, en coordenadas de pantalla, en que se encuantra el cursor.

**/

bool MOVIENDO_CAMARA = false;
int x_ant = 0;
int y_ant = 0;
float camaraDistancia = getCamara().getDistancia();
float camaraAnguloX = getCamara().getView_rotx(); // Ángulo horizontal inicial
float camaraAnguloY = getCamara().getView_roty(); // Ángulo vertical inicial
float camaraPosX = getCamara().getX();   // Posición inicial X de la cámara
float camaraPosY = getCamara().getY();    // Posición inicial Y de la cámara
float camaraPosZ = 5.0;      // Posición inicial Z de la cámara

void clickRaton (int boton, int estado, int x, int y){
	if(boton==GLUT_MIDDLE_BUTTON){
		if(estado==GLUT_DOWN){
			MOVIENDO_CAMARA=true;
			x_ant=x;
			y_ant=y;
		}else{
			MOVIENDO_CAMARA=false;
		}
	}else if(boton==GLUT_LEFT_BUTTON){
		if(estado==GLUT_DOWN){
			int objetoSeleccionado=0;
			seleccionarObjeto(x,y,&objetoSeleccionado);
			cout<<"Identificador del objeto seleccionado: "<<objetoSeleccionado<<endl;
		}

	}
}


/**	void RatonMovido( int x, int y )

Procedimiento para gestionar los eventos de movimiento del raton.

Argumentos:

x,y: Posicion, en coordenadas de pantalla, en que se encuantra el cursor.

**/

void RatonMovido (int x, int y){
	if(MOVIENDO_CAMARA){
		int deltaX=x-x_ant;
		int deltaY=y-y_ant;

		camaraAnguloX-=deltaY*0.5;
		camaraAnguloY-=deltaX*0.5;

		if(camaraAnguloY>89.0) camaraAnguloY=89.0;
		if(camaraAnguloY<-89.0) camaraAnguloY=-89;

		if(camaraAnguloX>89.0) camaraAnguloX=89.0;
		if(camaraAnguloX<-89.0) camaraAnguloX=-89;

		camaraPosY = camaraDistancia * cos(camaraAnguloY * M_PI / 180.0) * sin(camaraAnguloX * M_PI / 180.0);
        camaraPosX = camaraDistancia * sin(camaraAnguloY * M_PI / 180.0);

		setAngulo(camaraAnguloX,camaraAnguloY);

		x_ant=x;
		y_ant=y;

		glutPostRedisplay();
	}
}
