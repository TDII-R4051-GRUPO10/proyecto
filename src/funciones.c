#include "header.h"

#include <motor.h>

void pararM1()
{

	//ACA LA IDEA ES, SI doSteps() ES UNA TAREA DEL SO, PODER BLOQUEARLA ASI NO PIERDE LOS PASOS QUE LE QUEDAN HACER
	//Y QUE DESPUES PUEDA SEGUIR CON LOS PASOS QUE LE QUEDAN CUANDO SE LA DESBLOQUEA.

}
void moverM2()
{
	//muevo ininterrumpidamente paso a paso el motor 2 en un sentido de giro esperando la interrupcion del final de carrera

}
void pararM2()
{
	//paro el motor2
}
void posicionarM2(int pos)
{


}

void activar_Alarma()
{
	SetPIN(ALARM,1);

}

void moverM1_360()
{
	//esto es solo una idea
	//los motores son de 48 pasos cada 360°
	doSteps(motor[0], HORARIO, 48);
}

int muestrearColor()
{
	static int muestra;

	muestra=NON;

	return muestra;
}

void escribirSD(int* esc)
{



}

void Habilitar_Interrupcion(int e)
{
	switch(e)
	{
		case MOV_MOTOR1:

			SetPINSEL(INTERRUPT_M1,1);

			EXTMODE|=(0x01<<3);
			EXTPOLAR&=~(0x01<<3);
			ISER0|=(0x01<<21);

			break;


		case MOV_MOTOR2:

			SetPINSEL(INTERRUPT_M2,1);

			EXTMODE|=(0x01<<1);
			EXTPOLAR&=~(0x01<<1);
			ISER0|=(0x01<<19);

			break;

		case ALARMA:

			SetPINSEL(INTERRUPT_A,1);

			EXTMODE|=(0x01<<2);
			EXTPOLAR&=~(0x01<<2);
			ISER0|=(0x01<<20);

			break;

	}

}
void Deshabilitar_Interrupcion(int e)
{
	switch(e)
	{
		case MOV_MOTOR1:

			SetPINSEL(INTERRUPT_M1,0);
			EXTMODE&=~(0x01<<3);
			ISER0&=~(0x01<<21);

			break;


		case MOV_MOTOR2:

			SetPINSEL(INTERRUPT_M2,0);
			EXTMODE&=~(0x01<<1);
			ISER0&=~(0x01<<19);


			break;

		case ALARMA:

			SetPINSEL(INTERRUPT_A,0);
			EXTMODE&=~(0x01<<2);
			ISER0&=~(0x01<<20);


			break;

	}
}

