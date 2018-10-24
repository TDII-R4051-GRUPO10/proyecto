
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "semphr.h"
#include "header.h"
#include "sensor_color.h"


#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif


#include <cr_section_macros.h>


#include "header.h"
#include <stdlib.h>

void InicializarContador();
void ResetearContador(void);
unsigned int LeerContador(void);

xSemaphoreHandle 	init;
xSemaphoreHandle 	motor1;
xSemaphoreHandle 	motor2;
xSemaphoreHandle 	alarma;
xSemaphoreHandle 	sensor_color;
xSemaphoreHandle 	sd;
xSemaphoreHandle 	motor1_ISR;

xSemaphoreHandle 	init_OK;
xSemaphoreHandle 	motor1_OK;
xSemaphoreHandle 	motor2_OK;
xSemaphoreHandle 	alarma_OK;
xSemaphoreHandle 	sd_OK;

xQueueHandle 		QueueColor;
xQueueHandle 		posicion;
xQueueHandle 		contador;





void initHardware(void)
{
    SystemCoreClockUpdate();

    initDisplay();

    //initMotores();
    InicializarContador();
    init_color_sensor();

    SetPINSEL(ALARM,0);
    SetDIR(ALARM,GPIO_OUTPUT);

}

void InicializarContador(void)
{
	LPC_SYSCTL->PCONP|=1<<23;
	LPC_SYSCTL->PCLKSEL[1]&= ~(1<<15);
	LPC_SYSCTL->PCLKSEL[1]&=  (1<<14);


	//LPC_IOCON->PINSEL[1]|= (0x03<<14); <----ACÁ ESTABA EL PROBLEMA

	SetPINSEL(0,24,3);


	LPC_TIMER3->CTCR = 0x05;

	SetPINMODE(0,24,2);
	ResetearContador();
}

int flag;


void ResetearContador(void)
{
	LPC_TIMER3->TCR = 2;
	LPC_TIMER3->TCR = 1;
}

unsigned int LeerContador(void)
{
	return LPC_TIMER3->TC;

}

static void Tarea_Ppal(void *p)
{

	static int estado_anterior=0;
	static int estado=INICIO;
	static unsigned int data=NON;
	static int cont=0;

	while(1)
	{
		switch(estado)
		{
			case INICIO:

				if(estado_anterior==0)
				{
					estado_anterior=INICIO;
					xSemaphoreGive(init);
				}

				if(xSemaphoreTake(init_OK,DELAY)==pdTRUE)
				{
					estado=LECT_COLOR;


				}

				break;

			case LECT_COLOR:


				if(estado_anterior==INICIO || estado_anterior==MOV_MOTOR1)
				{
					estado_anterior=LECT_COLOR;
					xSemaphoreGive(sensor_color);
				}

				if(xQueueReceive(QueueColor,&data,DELAY)==pdTRUE)
				{
					if(data==NON)
					{
						cont++;

						if(cont==5)
						{
							estado=ALARMA;

							xQueueSend(contador,&data,DELAY);
						}
						else
							estado=MOV_MOTOR1;
					}
					else
					{
						cont=0;

						xQueueSend(contador,&data,DELAY);

						estado=MOV_MOTOR2;

					}
				}

				break;

			case MOV_MOTOR1:

				if(estado_anterior==MOV_MOTOR2 || estado_anterior==ALARMA || estado_anterior==LECT_COLOR)
				{
					estado_anterior=MOV_MOTOR1;
					xSemaphoreGive(motor1);
				}

				if(xSemaphoreTake(motor1_OK,DELAY)==pdTRUE)
					estado=LECT_COLOR;

				break;

			case MOV_MOTOR2:

				if(estado_anterior==LECT_COLOR)
				{
					estado_anterior=MOV_MOTOR2;
					xQueueSend(posicion,&data,DELAY);

				}
				if(xSemaphoreTake(motor2_OK,DELAY)==pdTRUE)
					estado=MOV_MOTOR1;

				break;

			case ALARMA:

				if(estado_anterior==LECT_COLOR)
				{
					estado_anterior=ALARMA;
					Habilitar_Interrupcion(ALARMA);
					xSemaphoreGive(alarma);

				}

				if(xSemaphoreTake(alarma_OK,DELAY)==pdTRUE)
				{
					SetPIN(ALARM,0);
					Deshabilitar_Interrupcion(ALARMA);
					cont=0;
					estado=MOV_MOTOR1;
				}

				break;
		}
	}

	vTaskDelete(NULL);
}

static void Inicializacion (void *p)
{

	while(1)
	{
		if(xSemaphoreTake(init,DELAY)==pdTRUE)
		{
			Habilitar_Interrupcion(MOV_MOTOR1);

			moverM1_360();
		}
	}

	vTaskDelete(NULL);
}

static void Motor1(void *p)
{

	while(1)
	{
		if(xSemaphoreTake(motor1,DELAY)==pdTRUE)
		{
			moverM1_360();

			xSemaphoreGive(motor1_OK);
		}

	}

	vTaskDelete(NULL);
}

static void Motor1_STOP(void *p)
{

	tomar_semaforos();

	while(1)
	{

		if(xSemaphoreTake(motor1_ISR,DELAY)==pdTRUE)		//tomo semáforo de la interrupcion del hall
		{
			pararM1();										//driver de frenado M1

			Deshabilitar_Interrupcion(MOV_MOTOR1);

			Habilitar_Interrupcion(MOV_MOTOR2);

			moverM2(ANTI_HORARIO,(180/PASO_MINIMO));			//muevo el motor2 en un sentido ininterrumpidamente esperando el final de carrera (interrupcion)

		}
	}

	vTaskDelete(NULL);

}

static void Motor2(void *p)
{

	static int pos=NON;
	static int pos_anterior=ROJO;           				//cuando inicializamos el motor2 queda posicionado en el color rojo

	while(1)
	{
		if(xQueueReceive(posicion,&pos,DELAY)==pdTRUE)
		{
			posicionarM2(pos,pos_anterior);					//la funcion necesita saber la posicion del motor y hacia que posicion ir

			xSemaphoreGive(motor2_OK);

			pos_anterior=pos;
		}
	}

	vTaskDelete(NULL);
}

static void Alarma(void *p)
{

	while(1)
	{
		if(xSemaphoreTake(alarma,DELAY)==pdTRUE)
		{

			//refrescarDisplay(DISPLAY_ALARM);

			activar_Alarma();
		}


	}

	vTaskDelete(NULL);
}

void Sensor_Color (void *pvParameters)
{

	unsigned int total;
	int color = NON;
	int porcentaje_rojo;
	int porcentaje_azul;
	int porcentaje_verde;

	int promedio_rojo=0;
	int promedio_azul=0;
	int promedio_verde=0;

	int n;

	unsigned int R, V, A;

	while(1) {

		if(xSemaphoreTake(sensor_color, portMAX_DELAY)==pdTRUE)
		{

			for(n=0;n<10;n++)
			{
				activa_sensor();

				R = sensa_rojo();

				V = sensa_verde();

				A = sensa_azul();

				total=R+V+A;

				porcentaje_rojo=(R*100)/total;
				porcentaje_verde=(V*100)/total;
				porcentaje_azul=(A*100)/total;

				promedio_rojo+=porcentaje_rojo;
				promedio_azul+=porcentaje_verde;
				promedio_verde+=porcentaje_azul;

			}

			promedio_rojo=promedio_rojo/n;
			promedio_verde=promedio_verde/n;
			promedio_azul=promedio_azul/n;


			if(total<300)
				color=NON;
			else{


			if(promedio_rojo>55 && promedio_rojo<61 && promedio_verde >26 && promedio_verde<33 && promedio_azul>17 && promedio_azul<23)
				color=ROJO;
			else if(promedio_rojo>55 && promedio_rojo<66 && promedio_verde >23 && promedio_verde<29 && promedio_azul>17 && promedio_azul<22)
				color=NARANJA;
			else if(promedio_rojo>50 && promedio_rojo<57 && promedio_verde >18 && promedio_verde<24 && promedio_azul>30 && promedio_azul<37)
				color=AMARILLO;
			else if(promedio_rojo>28 && promedio_rojo<35 && promedio_verde >31 && promedio_verde<40 && promedio_azul>36 && promedio_azul<43)
				color=VERDE;
			else if(promedio_rojo>32 && promedio_rojo<39 && promedio_verde >40 && promedio_verde<49 && promedio_azul>24 && promedio_azul<30)
				color=AZUL;
			else
				color=NON;

			}

			xQueueSend( QueueColor, &color, 0 );
		}
	}
}

void SD(void *p)
{

	int cont;

	while(1)
	{
		if(xQueueReceive(contador,&cont,DELAY)==pdTRUE)
		{
			if(cont!=NON)
			{
				escribirSD(cont);
				refrescarDisplay(cont);
			}
			else
				refrescarDisplay(DISPLAY_ALARM);


		}
	}

	vTaskDelete(NULL);
}


int main(void){

	initHardware();

	vSemaphoreCreateBinary(init);
	vSemaphoreCreateBinary(motor1);
	vSemaphoreCreateBinary(motor2);
	vSemaphoreCreateBinary(alarma);
	vSemaphoreCreateBinary(sensor_color);
	vSemaphoreCreateBinary(sd);
	vSemaphoreCreateBinary(motor1_ISR);


	vSemaphoreCreateBinary(init_OK);
	vSemaphoreCreateBinary(motor1_OK);
	vSemaphoreCreateBinary(motor2_OK);
	vSemaphoreCreateBinary(alarma_OK);
	vSemaphoreCreateBinary(sd_OK);


	QueueColor 	= xQueueCreate(1,sizeof(int));
	posicion= xQueueCreate(1,sizeof(int));
	contador= xQueueCreate(1,sizeof(int));


	if(!init || !motor1 || !motor2 || !alarma || ! sensor_color || !sd || !motor1_ISR || !init_OK
			|| !motor1_OK || !motor2_OK || !alarma_OK || !sd_OK || !QueueColor || !posicion  || !contador)

	{
		return 0;
		initHardware();
	}
	else
	{
		if(!xTaskCreate(Tarea_Ppal,(const char *)"tareappal", configMINIMAL_STACK_SIZE*2, NULL, tskIDLE_PRIORITY+1, 0)
		|| !xTaskCreate(Inicializacion,(const char *)"inic",configMINIMAL_STACK_SIZE*2, NULL, tskIDLE_PRIORITY+2,0)
		|| !xTaskCreate(Motor1,(const char *)"motor1",configMINIMAL_STACK_SIZE*2, NULL, tskIDLE_PRIORITY+2,0)
		|| !xTaskCreate(Motor1_STOP,(const char *)"motor1_stop",configMINIMAL_STACK_SIZE*2, NULL, tskIDLE_PRIORITY+3,0)
		|| !xTaskCreate(Motor2,(const char *)"motor2",configMINIMAL_STACK_SIZE*2, NULL, tskIDLE_PRIORITY+2,0)
		|| !xTaskCreate(Alarma,(const char *)"alarm",configMINIMAL_STACK_SIZE*2, NULL, tskIDLE_PRIORITY+2,0)
		|| !xTaskCreate(Sensor_Color,(const char *)"sensor",configMINIMAL_STACK_SIZE*2, NULL, tskIDLE_PRIORITY+2,0)
		|| !xTaskCreate(SD,(const char *)"sd",configMINIMAL_STACK_SIZE*2, NULL, tskIDLE_PRIORITY+1,0) )
		{

			return 0;
		}
		else
			vTaskStartScheduler();
	}


    while(1) {

    }
    return 0 ;
}


void EINT3_IRQHandler()
{
	EXTINT|=(0x01<<3);

	portBASE_TYPE contexto;

	xSemaphoreGiveFromISR(motor1_ISR,&contexto);

	portEND_SWITCHING_ISR(contexto);
}
void EINT2_IRQHandler()
{
	EXTINT|=(0x01<<2);

	portBASE_TYPE contexto;

	xSemaphoreGiveFromISR(alarma_OK,&contexto);

	portEND_SWITCHING_ISR(contexto);

}
void EINT1_IRQHandler()
{
	EXTINT|=(0x01<<1);

	pararM2();

	portBASE_TYPE contexto;

	xSemaphoreGiveFromISR(init_OK,&contexto);

	portEND_SWITCHING_ISR(contexto);

}
void tomar_semaforos()
{
	xSemaphoreTake(init,0);
	xSemaphoreTake(motor1,0);
	xSemaphoreTake(motor2,0);
	xSemaphoreTake(alarma,0);
	xSemaphoreTake(sensor_color,0);
	xSemaphoreTake(sd,0);
	xSemaphoreTake(motor1_ISR,0);

	xSemaphoreTake(init_OK,0);
	xSemaphoreTake(motor1_OK,0);
	xSemaphoreTake(motor2_OK,0);
	xSemaphoreTake(alarma_OK,0);
	xSemaphoreTake(sd_OK,0);
}

