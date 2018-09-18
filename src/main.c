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

#include "board.h"

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "semphr.h"

#include "main.h"
#include "header.h"


xSemaphoreHandle init;
xSemaphoreHandle motor1;
xSemaphoreHandle motor2;
xSemaphoreHandle alarma;
xSemaphoreHandle sensor_color;
xSemaphoreHandle sd;
xSemaphoreHandle motor1_ISR;


xSemaphoreHandle init_OK;
xSemaphoreHandle motor1_OK;
xSemaphoreHandle motor2_OK;
xSemaphoreHandle alarma_OK;
xSemaphoreHandle sd_OK;

xQueueHandle color;
xQueueHandle posicion;
xQueueHandle contador;

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/** @brief hardware initialization function
 *	@return none
 */
static void initHardware(void);

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

static void initHardware(void)
{
    SystemCoreClockUpdate();

    Board_Init();

    Board_LED_Set(0, false);
}



static void Inicializacion ()
{

	while(1)
	{
		if(xSemaphoreTake(init,DELAY)==pdTRUE)
		{
			Habilitar_Interrupcion();

			xSemaphoreGive(motor1);
		}
	}
}

static void Motor1()
{

	while(1)
	{
		if(xSemaphoreTake(motor1,DELAY)==pdTRUE)
		{
			moverM1_360();									//driver de giro de 360 grados
		}

	}
}

static void Motor1_STOP()
{
	while(1)
	{
		if(xSemaphoreTake(motor1_ISR,DELAY)==pdTRUE)		//tomo semáforo de la interrupcion ef hall
		{
			pararM1();										//driver de frenado M1

			xSemaphoreGive(init_OK);
		}
	}

}


static void Motor2()
{

	int pos=NON;

	while(1)
	{
		if(xQueueReceive(posicion,&pos,DELAY)==pdTRUE)
		{
			posicionarM2(pos);

			xSemaphoreGive(motor2_OK);
		}
	}
}

static void Alarma()
{
	while(1)
	{
		if(xSemaphoreTake(alarma,DELAY)==pdTRUE)
		{
			activar_Alarma();
		}
	}
}

static void Sensor_Color()
{
	int dato;

	while(1)
	{
		if(xSemaphoreTake(sensor_color,DELAY)==pdTRUE)
		{
			dato=muestrearColor();

			xQueueSend(color,&dato,DELAY);
		}
	}
}

static void SD()
{
	int cont[5];

	while(1)
	{
		if(xQueueReceive(contador,&cont,DELAY)==pdTRUE)
		{
			escribirSD(cont);

		}
	}
}

static void Tarea_Ppal()
{
	int estado=INICIO;
	int data=NON;
	int cont=0;
	int i;

	int colores[5];

	for(i=0;i<5;i++)
		colores[i]=0;

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

					colores[i]++;

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
				estado=MOV_MOTOR1;
	}

}




/*==================[external functions definition]==========================*/

int main(void)
{
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


	xTaskCreate(Tarea_Ppal, (const char *)"tareappal", configMINIMAL_STACK_SIZE*2, NULL, tskIDLE_PRIORITY+1, 0);
	xTaskCreate(Inicializacion,(const char *)"inic",configMINIMAL_STACK_SIZE*2, NULL, tskIDLE_PRIORITY+2,0);
	xTaskCreate(Motor1,(const char *)"motor1",configMINIMAL_STACK_SIZE*2, NULL, tskIDLE_PRIORITY+2,0);
	xTaskCreate(Motor1_STOP,(const char *)"motor1",configMINIMAL_STACK_SIZE*2, NULL, tskIDLE_PRIORITY+3,0);
	xTaskCreate(Motor2,(const char *)"motor2",configMINIMAL_STACK_SIZE*2, NULL, tskIDLE_PRIORITY+2,0);
	xTaskCreate(Alarma,(const char *)"alarm",configMINIMAL_STACK_SIZE*2, NULL, tskIDLE_PRIORITY+2,0);
	xTaskCreate(Sensor_Color,(const char *)"sensor",configMINIMAL_STACK_SIZE*2, NULL, tskIDLE_PRIORITY+2,0);
	xTaskCreate(SD,(const char *)"sd",configMINIMAL_STACK_SIZE*2, NULL, tskIDLE_PRIORITY+1,0);


	vTaskStartScheduler();

	while (1) {
	}
}

