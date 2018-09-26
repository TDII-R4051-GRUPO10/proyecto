/*
 * A4988.c
 *
 *  Created on: 12 de set. de 2018
 *      Author: grama
 */

#include<A4988.h>

void initA4988()
{
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,STEPport,STEPpin);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,DIRport,DIRpin);
}

void doSteps(dira)
{

}
