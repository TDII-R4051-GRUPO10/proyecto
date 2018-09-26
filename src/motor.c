/*
 * motor.c
 *
 *  Created on: 12 de set. de 2018
 *      Author: grama
 */


#include <motor.h>

void initMotores()
{
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,M1STEPport,M1STEPin);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,M1DIRport,M1DIRpin);

	Chip_GPIO_SetPinDIROutput(LPC_GPIO,M2STEPport,M2STEPin);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,M2DIRport,M2DIRpin);
}

//ACA TE DAS CUENTA QUE ES MEJOR USAR UNA ESTRUCTURA DE PINES STEP Y DIR DE MOTOR
//PARA HACER UNA SOLA FUNCION DOSTEPS QUE LE MANDAS EL MOTOR QUE QUERES QUE SE MUEVA. SALU2
//MAS ADELANTE BORRAR A4988 PORQUE ESTAN AL PEDO ESOS ARCHIVOS
void doSteps(int dir, int n)
{
	Chip_GPIO_SetPinState(LPC_GPIO);

	Chip_GPIO_SetPinOutHigh();

	Chip_GPIO_SetPinOutLow();
}

//IMPLEMENTACIÓN DE FUNCIONES PARA EL MOTOR QUE REPARTE EN VASOS

void configVaso(int vasoColor, int grados, int dir)
{
	vaso[vasoColor].grados = grados;
	vaso[vasoColor].dir = dir;
}

void moverAvaso(int vasoColor)
{

}

//IMPLEMENTACIÓN DE FUNCIONES PARA EL MOTOR QUE SENSA PASTILLAS

void configPosSensor(int grados, int dir)
{
	sensor.grados = grados;
	sensor.dir = dir;
}

void moverAsensor()
{

}
