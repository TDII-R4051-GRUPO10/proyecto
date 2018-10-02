<<<<<<< HEAD
/*
===============================================================================
 Name        : Proyecto.c
 Author      : Fritzler
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/
=======
/* Copyright 2015, Pablo Ridolfi
 * All rights reserved.
 *
 * This file is part of lpc1769_template.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/** @brief Blinky using FreeRTOS.
 *
 *
 * NOTE: It's interesting to check behavior differences between standard and
 * tickless mode. Set @ref configUSE_TICKLESS_IDLE to 1, increment a counter
 * in @ref vApplicationTickHook and print the counter value every second
 * inside a task. In standard mode the counter will have a value around 1000.
 * In tickless mode, it will be around 25.
 *
 */

/** \addtogroup rtos_blink FreeRTOS blink example
 ** @{ */

/*==================[inclusions]=============================================*/
//bebe bebu
#include "board.h"

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "semphr.h"

#include "main.h"
#include "header.h"

>>>>>>> master

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif


#include <cr_section_macros.h>


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



void initHardware(void)
{
    SystemCoreClockUpdate();

	SetPINSEL(MOTOR,0);
	SetPINSEL(INTERRUPT2,1);
//	SetPINSEL(INTERRUPT3,1);
	SetPINSEL(LED1,0);
	SetPINSEL(LED2,0);
	SetPINSEL(LED3,0);
	SetPINSEL(LED4,0);
	SetPINSEL(LED5,0);


	EXTMODE|=(0x01<<2);
	EXTPOLAR&=~(0x01<<2);
	ISER0|=(0x01<<20);


	SetDIR(MOTOR,GPIO_OUTPUT);
	SetDIR(LED1,GPIO_OUTPUT);
	SetDIR(LED2,GPIO_OUTPUT);
	SetDIR(LED3,GPIO_OUTPUT);
	SetDIR(LED4,GPIO_OUTPUT);
	SetDIR(LED5,GPIO_OUTPUT);
	SetDIR(ALARM,GPIO_OUTPUT);


	SetPIN(LED1,0);
	SetPIN(LED2,0);
	SetPIN(LED3,0);
	SetPIN(LED4,0);
	SetPIN(LED5,0);

	SetPIN(ALARM,0);


}



static void Tarea_Ppal(void *p)
{

	static int estado_anterior=0;
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

