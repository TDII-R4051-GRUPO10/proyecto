#include "display.h"


void refrescarDisplay(int col)
{
	unsigned int pines;
	unsigned int i;
	unsigned int e;
	unsigned int cantDeFilas;

	static int contador[5]={0,0,0,0,0};

	char frase[7][16]={

			"CANTIDAD DE ",
			"PASTILLAS",
			"ROJO: ",
			"AZUL: ",
			"AMARILLO: ",
			"VERDE   : ",
			"NARANJA: "

	};

	char frase_alarma[2][16]={

			"FALTAN PASTILLAS",
			"ALARMA ACTIVADA"
	};

	char cantRojo[10];
	char cantAzul[10];
	char cantAmarillo[10];
	char cantVerde[10];
	char cantNaranja[10];

	if(col!=DISPLAY_ALARM)
	{
		contador[col-1]++;

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

		cantDeFilas=7;
	}
	else
		cantDeFilas=2;

	for(e=0; e<cantDeFilas ; e++)
    {
		if(e%2==0)
		{
			pines=0x01;

			Send(pines);

			vTaskDelay(1);
		}

		if(col!=DISPLAY_ALARM)
		{
			for(i=0; frase[e][i]!='\0' ;i++)
			{

				pines=0x080;

				if((e%2)==0)
					pines|=i;
				else
					pines|=(i+40);

				Send(pines);

				pines=0x0200;

				pines|=frase[e][i];

				Send(pines);

			}
    	}
		else
		{
			for(i=0; frase_alarma[e][i]!='\0' ;i++)
			{

				pines=0x080;

				if((e%2)==0)
					pines|=i;
				else
					pines|=(i+40);

				Send(pines);

				pines=0x0200;

				pines|=frase_alarma[e][i];

				Send(pines);

			}
		}

		if(e%2 || e==6)
			vTaskDelay(100);


	}
}

void initDisplay()
{

	SetPINSEL(RS,0);
	SetPINSEL(RorW,0);
	SetPINSEL(ENA,0);
	SetPINSEL(DB4,0);
	SetPINSEL(DB5,0);
	SetPINSEL(DB6,0);
	SetPINSEL(DB7,0);

	SetDIR(RS,GPIO_OUTPUT);
	SetDIR(RorW,GPIO_OUTPUT);
	SetDIR(ENA,GPIO_OUTPUT);
	SetDIR(DB4,GPIO_OUTPUT);
	SetDIR(DB5,GPIO_OUTPUT);
	SetDIR(DB6,GPIO_OUTPUT);
	SetDIR(DB7,GPIO_OUTPUT);

	//FUNCTION SET

	SetPIN(DB4,0);
	SetPIN(DB5,1);
	SetPIN(DB6,0);
	SetPIN(DB7,0);
	SetPIN(RorW,0);
	SetPIN(RS,0);

	EnaDelay(INIT_DELAY);

	SetPIN(DB4,0);
	SetPIN(DB5,1);
	SetPIN(DB6,0);
	SetPIN(DB7,0);
	SetPIN(RorW,0);
	SetPIN(RS,0);

	EnaDelay(INIT_DELAY);

	SetPIN(DB4,0);
	SetPIN(DB5,0);
	SetPIN(DB6,1);
	SetPIN(DB7,1);
	SetPIN(RorW,0);
	SetPIN(RS,0);


	//DISPLAY ON

	EnaDelay(INIT_DELAY);

	SetPIN(DB4,0);
	SetPIN(DB5,0);
	SetPIN(DB6,0);
	SetPIN(DB7,0);
	SetPIN(RorW,0);
	SetPIN(RS,0);

	EnaDelay(INIT_DELAY);

	SetPIN(DB4,0);
	SetPIN(DB5,0);
	SetPIN(DB6,1);
	SetPIN(DB7,1);
	SetPIN(RorW,0);
	SetPIN(RS,0);

	EnaDelay(INIT_DELAY);


	//DISPLAY CLEAR

	SetPIN(DB4,0);
	SetPIN(DB5,0);
	SetPIN(DB6,0);
	SetPIN(DB7,0);
	SetPIN(RorW,0);
	SetPIN(RS,0);

	EnaDelay(INIT_DELAY);

	SetPIN(DB4,1);
	SetPIN(DB5,0);
	SetPIN(DB6,0);
	SetPIN(DB7,0);
	SetPIN(RorW,0);
	SetPIN(RS,0);

	EnaDelay(INIT_DELAY);

	//ENTRY MODE SET

	SetPIN(DB4,0);
	SetPIN(DB5,0);
	SetPIN(DB6,0);
	SetPIN(DB7,0);
	SetPIN(RorW,0);
	SetPIN(RS,0);

	EnaDelay(INIT_DELAY);

	SetPIN(DB4,0);
	SetPIN(DB5,0);
	SetPIN(DB6,1);
	SetPIN(DB7,0);
	SetPIN(RorW,0);
	SetPIN(RS,0);

	EnaDelay(INIT_DELAY);

}

void EnaDelay(int delay)
{
	int i;

	for(i=0;i<delay;i++)
	{}

	SetPIN(ENA,1);

	for(i=0;i<delay;i++)
	{}

	SetPIN(ENA,0);

}



void Send(int pines)
{
	SetPIN(DB4,(pines>>4) & 0x01);
	SetPIN(DB5,(pines>>5) & 0x01);
	SetPIN(DB6,(pines>>6) & 0x01);
	SetPIN(DB7,(pines>>7) & 0x01);
	SetPIN(RorW,(pines>>8) & 0x01);
	SetPIN(RS,(pines>>9) & 0x01);

	EnaDelay(WRITE_DELAY);

	SetPIN(DB4,(pines>>0) & 0x01);
	SetPIN(DB5,(pines>>1) & 0x01);
	SetPIN(DB6,(pines>>2) & 0x01);
	SetPIN(DB7,(pines>>3) & 0x01);

	EnaDelay(WRITE_DELAY);

}
