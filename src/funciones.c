#include "board.h"

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "semphr.h"

#include "main.h"


#include "header.h"

#include <motor.h>

void pararM1()
{
	//ACA LA IDEA ES, SI doSteps() ES UNA TAREA DEL SO, PODER BLOQUEARLA ASI NO PIERDE LOS PASOS QUE LE QUEDAN HACER
	//Y QUE DESPUES PUEDA SEGUIR CON LOS PASOS QUE LE QUEDAN CUANDO SE LA DESBLOQUEA.
}

void posicionarM2(int pos)
{


}

void activar_Alarma()
{


}


void moverM1_360()
{
	//esto es solo una idea
	//los motores son de 48 pasos cada 360°
	doSteps(motor[0], HORARIO, 48);
}

int muestrearColor()
{
	int muestra;

	//codigo

	return muestra;
}

void escribirSD(int* esc)
{



}

void Habilitar_Interrupcion()
{


}
