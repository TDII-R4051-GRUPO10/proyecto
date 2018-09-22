/*
===============================================================================
 Name        : Proyecto.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif


#include <cr_section_macros.h>

#include "board.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "FW_GPIO.h"
#include "Parcial.h"
#include "header.h"
#include <stdlib.h>


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

xQueueHandle 		color;
xQueueHandle 		posicion;
xQueueHandle 		contador;


static void initHardware(void);



static void initHardware(void)
{
    SystemCoreClockUpdate();


    SetPINSEL(MOTOR,0);

    SetDIR(MOTOR,0);


}



static void Tarea_Ppal(void *p)
{
	static int estado=INICIO;
	static int data=NON;
	static int cont=0;
	static int i;

	static int colores[5];

	for(i=0;i<5;i++)
		colores[i]=0;

	while(1)
	{
		switch(estado)
		{
			case INICIO:

				xSemaphoreGive(init);

				if(xSemaphoreTake(init_OK,DELAY)==pdTRUE)
					estado=LECT_COLOR;

			case LECT_COLOR:

				xSemaphoreGive(sensor_color);

				if(xQueueReceive(color,&data,DELAY)==pdTRUE)
				{
					if(data==NON)
					{
						cont++;

						if(cont==5)
							estado=ALARMA;
						else
							estado=MOV_MOTOR1;
					}
					else
					{
						cont=0;

						colores[data-1]++;

						xQueueSend(contador,&colores,DELAY);

						estado=MOV_MOTOR2;

					}
				}

			case MOV_MOTOR1:

				xSemaphoreGive(motor1);

				if(xSemaphoreTake(motor1_OK,DELAY)==pdTRUE)
					estado=LECT_COLOR;

			case MOV_MOTOR2:

				xQueueSend(posicion,&data,DELAY);

				if(xSemaphoreTake(motor2_OK,DELAY)==pdTRUE)
					estado=MOV_MOTOR1;

			case ALARMA:

				xSemaphoreGive(alarma);

				if(xSemaphoreTake(alarma_OK,DELAY)==pdTRUE)
				{

					cont=0;
					estado=MOV_MOTOR1;

				}
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
			Habilitar_Interrupcion();

			xSemaphoreGive(motor1);
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
			moverM1_360();									//driver de giro de 360 grados
		}

	}

	vTaskDelete(NULL);
}

static void Motor1_STOP(void *p)
{

	while(1)
	{
		if(xSemaphoreTake(motor1_ISR,DELAY)==pdTRUE)		//tomo semáforo de la interrupcion ef hall
		{
			pararM1();										//driver de frenado M1

			xSemaphoreGive(init_OK);
		}
	}

	vTaskDelete(NULL);

}

static void Motor2(void *p)
{

	static int pos=NON;

	while(1)
	{
		if(xQueueReceive(posicion,&pos,DELAY)==pdTRUE)
		{
			posicionarM2(pos);

			xSemaphoreGive(motor2_OK);
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
			activar_Alarma();
		}
	}

	vTaskDelete(NULL);
}

static void Sensor_Color(void *p)
{

	static int dato;

	while(1)
	{
		if(xSemaphoreTake(sensor_color,DELAY)==pdTRUE)
		{
			dato=muestrearColor();

			xQueueSend(color,&dato,DELAY);
		}
	}

	vTaskDelete(NULL);
}

static void SD(void *p)
{

	int cont[5];

	while(1)
	{
		if(xQueueReceive(contador,&cont,DELAY)==pdTRUE)
		{
			escribirSD(cont);

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


	color 	= xQueueCreate(1,sizeof(int));
	posicion= xQueueCreate(1,sizeof(int));
	contador= xQueueCreate(5,sizeof(int));


	if(!init || !motor1 || !motor2 || !alarma || ! sensor_color || !sd || !motor1_ISR || !init_OK
			|| !motor1_OK || !motor2_OK || !alarma_OK || !sd_OK || !color || !posicion  || !contador)

	{
		return 0;
	}
	else
	{
		if(!xTaskCreate(Tarea_Ppal,(const char *)"tareappal", configMINIMAL_STACK_SIZE*2, NULL, tskIDLE_PRIORITY+1, 0)
		|| !xTaskCreate(Inicializacion,(const char *)"inic",configMINIMAL_STACK_SIZE*2, NULL, tskIDLE_PRIORITY+2,0)
		|| !xTaskCreate(Motor1,(const char *)"motor1",configMINIMAL_STACK_SIZE*2, NULL, tskIDLE_PRIORITY+2,0)
		|| !xTaskCreate(Motor1_STOP,(const char *)"motor1",configMINIMAL_STACK_SIZE*2, NULL, tskIDLE_PRIORITY+3,0)
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

