#include "header.h"



void pararM1()
{
	 SetPIN(MOTOR,0);
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
	SetPIN(MOTOR,1);

	vTaskDelay(DELAY);

	SetPIN(MOTOR,0);

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
	int a;
	a=1;
}

