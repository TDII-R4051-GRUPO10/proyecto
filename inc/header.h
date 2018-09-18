/*
 * header.h
 *
 *  Created on: Sep 15, 2018
 *      Author: pablodfritzler
 */

#ifndef EXAMPLES_FREERTOS_BLINKY_INC_HEADER_H_
#define EXAMPLES_FREERTOS_BLINKY_INC_HEADER_H_



#endif /* EXAMPLES_FREERTOS_BLINKY_INC_HEADER_H_ */

#define INICIO		1
#define LECT_COLOR  2
#define MOV_MOTOR1  3
#define MOV_MOTOR2  4
#define ALARMA		5


#define DELAY   	300
#define NON			0


#define ROJO		1
#define AZUL		2
#define AMARILLO	3
#define VERDE		4
#define NARANJA		5



void pararM1();
void posicionarM2(int);
void activar_Alarma();
void moverM1_360();
int muestrearColor();
void escribirSD(int*);
void Habilitar_Interrupcion();

