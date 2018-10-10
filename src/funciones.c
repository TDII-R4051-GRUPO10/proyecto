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

int muestrearColor()
{
	static int muestra;

	muestra=ROJO;

	return muestra;
}

void escribirSD(int esc)
{



}

void refrescarDisplay(int col)
{
	unsigned int pines;
	unsigned int i;
	unsigned int e;

	int aux=0;

	static int contador[5]={0,0,0,0,0};

	contador[col-1]++;

	char frase[7][16]={

			"CANTIDAD DE",
			"PASTILLAS ",
			"ROJO: ",
			"AZUL: ",
			"AMARILLO: ",
			"VERDE: ",
			"NARANJA: "

	};

	char cantRojo[10];
	char cantAzul[10];
	char cantAmarillo[10];
	char cantVerde[10];
	char cantNaranja[10];

	itoa(contador[0],cantRojo,10);
	itoa(contador[1],cantAzul,10);
	itoa(contador[2],cantAmarillo,10);
	itoa(contador[3],cantVerde,10);
	itoa(contador[4],cantNaranja,10);

	strcat(frase[2],cantRojo);
	strcat(frase[3],cantAzul);
	strcat(frase[4],cantAmarillo);
	strcat(frase[5],cantVerde);
	strcat(frase[6],cantNaranja);


	for(e=0; e<7 ; e++)
    {
		if(e%2==0)
		{
			pines=0x01;

			Send(pines);

			SetPIN(ENA,1);

			SetPIN(ENA,0);

		}

		for(i=0; frase[e][i]!='\0' ;i++)
		{
			pines=0x080;

			if((e%2)==0)
				pines|=i;
			else
				pines|=(i+40);

			Send(pines);

			if(e%2==0)
			{	while(aux<1000)
				{aux++;}
			}
			aux=0;

//			vTaskDelay(1);

			SetPIN(ENA,1);

			while(aux<5)
				aux++;

			aux=0;

//			vTaskDelay(1);

			SetPIN(ENA,0);

			pines=0x0200;

			pines|=frase[e][i];

			Send(pines);

			while(aux<10)
				aux++;

			aux=0;

//			vTaskDelay(1);

			SetPIN(ENA,1);


			while(aux<10)
				aux++;

			aux=0;
//			vTaskDelay(1);

			SetPIN(ENA,0);

		}

		if(e%2 || e==6)
			vTaskDelay(300);


	}
}

void initDisplay()
{

	SetPINSEL(RS,0);
	SetPINSEL(RorW,0);
	SetPINSEL(ENA,0);
	SetPINSEL(DB0,0);
	SetPINSEL(DB1,0);
	SetPINSEL(DB2,0);
	SetPINSEL(DB3,0);
	SetPINSEL(DB4,0);
	SetPINSEL(DB5,0);
	SetPINSEL(DB6,0);
	SetPINSEL(DB7,0);


	SetDIR(RS,GPIO_OUTPUT);
	SetDIR(RorW,GPIO_OUTPUT);
	SetDIR(ENA,GPIO_OUTPUT);
	SetDIR(DB0,GPIO_OUTPUT);
	SetDIR(DB1,GPIO_OUTPUT);
	SetDIR(DB2,GPIO_OUTPUT);
	SetDIR(DB3,GPIO_OUTPUT);
	SetDIR(DB4,GPIO_OUTPUT);
	SetDIR(DB5,GPIO_OUTPUT);
	SetDIR(DB6,GPIO_OUTPUT);
	SetDIR(DB7,GPIO_OUTPUT);


	SetPIN(RS,0);
	SetPIN(RorW,0);
	SetPIN(DB7,0);
	SetPIN(DB6,0);
	SetPIN(DB5,0);
	SetPIN(DB4,0);
	SetPIN(DB3,0);
	SetPIN(DB2,0);
	SetPIN(DB1,0);
	SetPIN(DB0,0);


	int i;

	//SetFunc

	SetPIN(RS,0);
	SetPIN(RorW,0);
	SetPIN(DB7,0);
	SetPIN(DB6,0);
	SetPIN(DB5,1);
	SetPIN(DB4,1);
	SetPIN(DB3,1);
	SetPIN(DB2,1);
	SetPIN(DB1,1);
	SetPIN(DB0,1);


	for(i=0;i<10000;i++)
	{}


	SetPIN(ENA,1);

	for(i=0;i<10000;i++)
	{}


	SetPIN(ENA,0);

	//Display ON

	SetPIN(RS,0);
	SetPIN(RorW,0);
	SetPIN(DB7,0);
	SetPIN(DB6,0);
	SetPIN(DB5,0);
	SetPIN(DB4,0);
	SetPIN(DB3,1);
	SetPIN(DB2,1);
	SetPIN(DB1,0);
	SetPIN(DB0,0);

	for(i=0;i<10000;i++)
	{}


	SetPIN(ENA,1);

	for(i=0;i<10000;i++)
	{}

	SetPIN(ENA,0);

	//Display Clear

	SetPIN(RS,0);
	SetPIN(RorW,0);
	SetPIN(DB7,0);
	SetPIN(DB6,0);
	SetPIN(DB5,0);
	SetPIN(DB4,0);
	SetPIN(DB3,0);
	SetPIN(DB2,0);
	SetPIN(DB1,0);
	SetPIN(DB0,1);

	for(i=0;i<10000;i++)
	{}

	SetPIN(ENA,1);

	for(i=0;i<10000;i++)
	{}

	SetPIN(ENA,0);

	//Entry mode

	SetPIN(RS,0);
	SetPIN(RorW,0);
	SetPIN(DB7,0);
	SetPIN(DB6,0);
	SetPIN(DB5,0);
	SetPIN(DB4,0);
	SetPIN(DB3,0);
	SetPIN(DB2,1);
	SetPIN(DB1,0);
	SetPIN(DB0,0);

	for(i=0;i<10000;i++)
	{}

	SetPIN(ENA,1);

	for(i=0;i<10000;i++)
	{}

	SetPIN(ENA,0);


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


void Send(int pines)
{

	if(pines & 0x01)
		SetPIN(DB0,1);
	else
		SetPIN(DB0,0);

	if((pines>>1) & 0x01)
		SetPIN(DB1,1);
	else
		SetPIN(DB1,0);

	if((pines>>2) & 0x01)
		SetPIN(DB2,1);
	else
		SetPIN(DB2,0);

	if((pines>>3) & 0x01)
		SetPIN(DB3,1);
	else
		SetPIN(DB3,0);

	if((pines>>4) & 0x01)
		SetPIN(DB4,1);
	else
		SetPIN(DB4,0);

	if((pines>>5) & 0x01)
		SetPIN(DB5,1);
	else
		SetPIN(DB5,0);

	if((pines>>6) & 0x01)
		SetPIN(DB6,1);
	else
		SetPIN(DB6,0);

	if((pines>>7) & 0x01)
		SetPIN(DB7,1);
	else
		SetPIN(DB7,0);

	if((pines>>8) & 0x01)
		SetPIN(RorW,1);
	else
		SetPIN(RorW,0);

	if((pines>>9) & 0x01)
		SetPIN(RS,1);
	else
		SetPIN(RS,0);

}


