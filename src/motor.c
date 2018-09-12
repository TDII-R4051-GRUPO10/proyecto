/*
 * motor.c
 *
 *  Created on: 12 de set. de 2018
 *      Author: grama
 */


#include <motor.h>

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
