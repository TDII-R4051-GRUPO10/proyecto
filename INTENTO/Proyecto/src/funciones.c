#include "header.h"


#include <motor.h>

void pararM1()
{

	//ACA LA IDEA ES, SI doSteps() ES UNA TAREA DEL SO, PODER BLOQUEARLA ASI NO PIERDE LOS PASOS QUE LE QUEDAN HACER
	//Y QUE DESPUES PUEDA SEGUIR CON LOS PASOS QUE LE QUEDAN CUANDO SE LA DESBLOQUEA.

}
void moverM2(int sentido,int pasos)
{
	//muevo MOTOR 2 en un sentido una cantidad de pasos
}


void pararM2()
{

	//paro el motor2
}

//IMPORTANTE: Los depositos de colores están separados a 30 grados entre si


void posicionarM2(int pos, int pos_anterior)
{
	if((pos_anterior-pos)<0)
	{
		moverM2(HORARIO,(pos-pos_anterior)*(30/PASO_MINIMO));

	}
	else if((pos_anterior-pos)>0)
	{
		moverM2(ANTI_HORARIO,(pos_anterior-pos)*(30/PASO_MINIMO));

	}

	//Si es 0 no realiza ninguna accion (no es necesario mover el motor)

}

void activar_Alarma()
{
	SetPIN(ALARM,1);

}

void moverM1_360()
{
	//esto es solo una idea
	//los motores son de 48 pasos cada 360°
//	doSteps(motor[0], HORARIO, 48);
}


void escribirSD(int esc)
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



