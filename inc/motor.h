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
} typedef_posicionVaso;

typedef_posicionVaso vaso[CANTvASOS];

void configVaso(typedef_posicionVaso vaso);
void moverAvaso(typedef_posicionVaso vaso);

#endif /* PROJECTS_PROYECTO_INC_MOTOR_H_ */
