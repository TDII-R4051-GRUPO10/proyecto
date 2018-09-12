/*
 * motor.h
 *
 *  Created on: 12 de set. de 2018
 *      Author: grama
 */

#ifndef PROJECTS_PROYECTO_INC_MOTOR_H_
#define PROJECTS_PROYECTO_INC_MOTOR_H_

#define CANTvASOS	5

enum {AMARILLO = 0, ROJO, AZUL, MARRON, VERDE};

typedef struct
{
	int grados;
	int dir;
} typedef_posicionObjeto;

typedef_posicionObjeto vaso[CANTvASOS];
typedef_posicionObjeto sensor;

//FUNCIONES PARA EL MOTOR QUE REPARTE EN VASOS

void configVaso(int vasoColor, int grados, int dir);
void moverAvaso(int vasoColor);

//FUNCIONES PARA EL MOTOR QUE SENSA PASTILLAS

void configPosSensor(int grados, int dir);
void moverAsensor();

#endif /* PROJECTS_PROYECTO_INC_MOTOR_H_ */
