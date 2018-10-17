/*
 * motor.h
 *
 *  Created on: 12 de set. de 2018
 *      Author: grama
 */
/*


#ifndef PROJECTS_PROYECTO_INC_MOTOR_H_
#define PROJECTS_PROYECTO_INC_MOTOR_H_

#define CANTvASOS	5
#define NmOTORES	2


//MODIFICAR ESTOS DEFINES PARA ASIGNAR LOS PINES DEL MICRO A USAR POR LOS MOTORES
#define M0STEPport	0
#define M0STEPin	22

#define M0DIRport	0
#define M0DIRpin	23


#define M1STEPport	1
#define M1STEPpin	22

#define M1DIRport	1
#define M1DIRpin	23

enum {AMARILLO = 0, ROJO, AZUL, MARRON, VERDE};
enum {HORARIO = 0, ANTIHORARIO};

typedef struct
{
	int stepPort;
	int stepPin;
	int dirPort;
	int dirPin;
} typedef_motor;

typedef struct
{
	int grados;
	int dir;
} typedef_posicionObjeto;

typedef_posicionObjeto vaso[CANTvASOS];
typedef_posicionObjeto sensor;

typedef_motor motor[NmOTORES];

void initMotores(void);

void doSteps(typedef_motor m, int dir, int n);

//FUNCIONES PARA EL MOTOR QUE REPARTE EN VASOS

void configVaso(int vasoColor, int grados, int dir);
void moverAvaso(int vasoColor);

//FUNCIONES PARA EL MOTOR QUE SENSA PASTILLAS

void configPosSensor(int grados, int dir);
void moverAsensor();

#endif  PROJECTS_PROYECTO_INC_MOTOR_H_


*/
