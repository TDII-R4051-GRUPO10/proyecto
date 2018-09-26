#include "header.h"

#include <motor.h>

void pararM1()
{
<<<<<<< HEAD
	 SetPIN(MOTOR,0);
=======
	//ACA LA IDEA ES, SI doSteps() ES UNA TAREA DEL SO, PODER BLOQUEARLA ASI NO PIERDE LOS PASOS QUE LE QUEDAN HACER
	//Y QUE DESPUES PUEDA SEGUIR CON LOS PASOS QUE LE QUEDAN CUANDO SE LA DESBLOQUEA.
>>>>>>> master
}

void posicionarM2(int pos)
{
	apagarLeds();

	vTaskDelay(DELAY);

	prenderLed(pos);

	vTaskDelay(DELAY);

}

void activar_Alarma()
{
	SetPIN(ALARM,1);

}

void apagarLeds()
{
	SetPIN(LED1,0);
	SetPIN(LED2,0);
	SetPIN(LED3,0);
	SetPIN(LED4,0);
	SetPIN(LED5,0);
}

void prenderLed(int pos)
{
		if(pos==1)
			SetPIN(LED1,1);

		if(pos==2)
			SetPIN(LED2,1);

		if(pos==3)
			SetPIN(LED3,1);

		if(pos==4)
			SetPIN(LED4,1);

		if(pos==5)
			SetPIN(LED5,1);
}


void moverM1_360()
{
<<<<<<< HEAD
	SetPIN(MOTOR,1);

	vTaskDelay(DELAY);


	SetPIN(MOTOR,0);

	vTaskDelay(DELAY);

=======
	//esto es solo una idea
	//los motores son de 48 pasos cada 360°
	doSteps(motor[0], HORARIO, 48);
>>>>>>> master
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

void Habilitar_Interrupcion()
{
	SetPINSEL(INTERRUPT1,1);

	EXTMODE|=(0x01<<3);
	EXTPOLAR&=~(0x01<<3);
	ISER0|=(0x01<<21);


}
void Deshabilitar_Interrupcion()
{
	SetPINSEL(INTERRUPT1,0);
	EXTMODE&=~(0x01<<3);
	ISER0&=~(0x01<<21);
}


