#include "sensor_color.h"
#include "GPIO.h"

void ResetearContador(void);
long LeerContador(void);

void init_color_sensor() {

	Chip_GPIO_SetPinDIROutput(LPC_GPIO, gpioSensor[S0].port, gpioSensor[S0].pin); //S0
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, gpioSensor[S1].port, gpioSensor[S1].pin); //S1
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, gpioSensor[S2].port, gpioSensor[S2].pin); //S2
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, gpioSensor[S3].port, gpioSensor[S3].pin); //S3

	Chip_GPIO_SetPinDIRInput(LPC_GPIO, gpioSensor[OUT].port, gpioSensor[OUT].pin); //Output

	SetPINMODE(2,10,2);

	disable_sensor();
}


void disable_sensor() {
	Chip_GPIO_SetPinState(LPC_GPIO, gpioSensor[S0].port, gpioSensor[S0].pin, 0);
	Chip_GPIO_SetPinState(LPC_GPIO, gpioSensor[S1].port, gpioSensor[S1].pin, 0);
	//vTaskDelay(1/portTICK_RATE_MS);

	return;
}

void activa_sensor() {
	Chip_GPIO_SetPinState(LPC_GPIO, gpioSensor[S0].port, gpioSensor[S0].pin, 0);
	Chip_GPIO_SetPinState(LPC_GPIO, gpioSensor[S1].port, gpioSensor[S1].pin, 1);
}

unsigned int sensa_rojo() {
	Chip_GPIO_SetPinState(LPC_GPIO, gpioSensor[S2].port, gpioSensor[S2].pin, 0);
	Chip_GPIO_SetPinState(LPC_GPIO, gpioSensor[S3].port, gpioSensor[S3].pin, 0);
	vTaskDelay(1/portTICK_RATE_MS);

	return lee_sensor();
}

unsigned int sensa_verde() {
	Chip_GPIO_SetPinState(LPC_GPIO, gpioSensor[S2].port, gpioSensor[S2].pin, 1);
	Chip_GPIO_SetPinState(LPC_GPIO, gpioSensor[S3].port, gpioSensor[S3].pin, 1);
	vTaskDelay(1/portTICK_RATE_MS);

	return lee_sensor();
}

unsigned int sensa_azul() {
	Chip_GPIO_SetPinState(LPC_GPIO, gpioSensor[S2].port, gpioSensor[S2].pin, 0);
	Chip_GPIO_SetPinState(LPC_GPIO, gpioSensor[S3].port, gpioSensor[S3].pin, 1);
	vTaskDelay(1/portTICK_RATE_MS);

	return lee_sensor();
}

unsigned int lee_sensor(){

	ResetearContador();
	vTaskDelay(1);

	return LeerContador();

}

/*
long lee_sensor() {
	portTickType inicio, fin;

	//Espero por termino de pulso anterior
	while(Chip_GPIO_GetPinState(LPC_GPIO, gpioSensor[OUT].port, gpioSensor[OUT].pin));

	//Espero por el comienzo del pulso
	while(!Chip_GPIO_GetPinState(LPC_GPIO, gpioSensor[OUT].port, gpioSensor[OUT].pin));

	//Cuento hasta fin de pulso
	inicio = xTaskGetTickCount();

	while(Chip_GPIO_GetPinState(LPC_GPIO, gpioSensor[OUT].port, gpioSensor[OUT].pin));
	while(!Chip_GPIO_GetPinState(LPC_GPIO, gpioSensor[OUT].port, gpioSensor[OUT].pin));
	while(Chip_GPIO_GetPinState(LPC_GPIO, gpioSensor[OUT].port, gpioSensor[OUT].pin));
	while(!Chip_GPIO_GetPinState(LPC_GPIO, gpioSensor[OUT].port, gpioSensor[OUT].pin));
	while(Chip_GPIO_GetPinState(LPC_GPIO, gpioSensor[OUT].port, gpioSensor[OUT].pin));
	while(!Chip_GPIO_GetPinState(LPC_GPIO, gpioSensor[OUT].port, gpioSensor[OUT].pin));
	while(Chip_GPIO_GetPinState(LPC_GPIO, gpioSensor[OUT].port, gpioSensor[OUT].pin));
	while(!Chip_GPIO_GetPinState(LPC_GPIO, gpioSensor[OUT].port, gpioSensor[OUT].pin));
	while(Chip_GPIO_GetPinState(LPC_GPIO, gpioSensor[OUT].port, gpioSensor[OUT].pin));
	while(!Chip_GPIO_GetPinState(LPC_GPIO, gpioSensor[OUT].port, gpioSensor[OUT].pin));
	while(Chip_GPIO_GetPinState(LPC_GPIO, gpioSensor[OUT].port, gpioSensor[OUT].pin));
	while(!Chip_GPIO_GetPinState(LPC_GPIO, gpioSensor[OUT].port, gpioSensor[OUT].pin));
	while(Chip_GPIO_GetPinState(LPC_GPIO, gpioSensor[OUT].port, gpioSensor[OUT].pin));
	while(!Chip_GPIO_GetPinState(LPC_GPIO, gpioSensor[OUT].port, gpioSensor[OUT].pin));
	while(Chip_GPIO_GetPinState(LPC_GPIO, gpioSensor[OUT].port, gpioSensor[OUT].pin));
	while(!Chip_GPIO_GetPinState(LPC_GPIO, gpioSensor[OUT].port, gpioSensor[OUT].pin));
	while(Chip_GPIO_GetPinState(LPC_GPIO, gpioSensor[OUT].port, gpioSensor[OUT].pin));
	while(!Chip_GPIO_GetPinState(LPC_GPIO, gpioSensor[OUT].port, gpioSensor[OUT].pin));
	while(Chip_GPIO_GetPinState(LPC_GPIO, gpioSensor[OUT].port, gpioSensor[OUT].pin));
	while(!Chip_GPIO_GetPinState(LPC_GPIO, gpioSensor[OUT].port, gpioSensor[OUT].pin));
	while(Chip_GPIO_GetPinState(LPC_GPIO, gpioSensor[OUT].port, gpioSensor[OUT].pin));
	while(!Chip_GPIO_GetPinState(LPC_GPIO, gpioSensor[OUT].port, gpioSensor[OUT].pin));
	while(Chip_GPIO_GetPinState(LPC_GPIO, gpioSensor[OUT].port, gpioSensor[OUT].pin));
	while(!Chip_GPIO_GetPinState(LPC_GPIO, gpioSensor[OUT].port, gpioSensor[OUT].pin));
	while(Chip_GPIO_GetPinState(LPC_GPIO, gpioSensor[OUT].port, gpioSensor[OUT].pin));
	while(!Chip_GPIO_GetPinState(LPC_GPIO, gpioSensor[OUT].port, gpioSensor[OUT].pin));
	while(Chip_GPIO_GetPinState(LPC_GPIO, gpioSensor[OUT].port, gpioSensor[OUT].pin));
	while(!Chip_GPIO_GetPinState(LPC_GPIO, gpioSensor[OUT].port, gpioSensor[OUT].pin));
	while(Chip_GPIO_GetPinState(LPC_GPIO, gpioSensor[OUT].port, gpioSensor[OUT].pin));
	while(!Chip_GPIO_GetPinState(LPC_GPIO, gpioSensor[OUT].port, gpioSensor[OUT].pin));
	while(Chip_GPIO_GetPinState(LPC_GPIO, gpioSensor[OUT].port, gpioSensor[OUT].pin));
	while(!Chip_GPIO_GetPinState(LPC_GPIO, gpioSensor[OUT].port, gpioSensor[OUT].pin));
	while(Chip_GPIO_GetPinState(LPC_GPIO, gpioSensor[OUT].port, gpioSensor[OUT].pin));
	while(!Chip_GPIO_GetPinState(LPC_GPIO, gpioSensor[OUT].port, gpioSensor[OUT].pin));
	while(Chip_GPIO_GetPinState(LPC_GPIO, gpioSensor[OUT].port, gpioSensor[OUT].pin));
	while(!Chip_GPIO_GetPinState(LPC_GPIO, gpioSensor[OUT].port, gpioSensor[OUT].pin));
	while(Chip_GPIO_GetPinState(LPC_GPIO, gpioSensor[OUT].port, gpioSensor[OUT].pin));
	while(!Chip_GPIO_GetPinState(LPC_GPIO, gpioSensor[OUT].port, gpioSensor[OUT].pin));
	while(Chip_GPIO_GetPinState(LPC_GPIO, gpioSensor[OUT].port, gpioSensor[OUT].pin));
	while(!Chip_GPIO_GetPinState(LPC_GPIO, gpioSensor[OUT].port, gpioSensor[OUT].pin));
	while(Chip_GPIO_GetPinState(LPC_GPIO, gpioSensor[OUT].port, gpioSensor[OUT].pin));
	while(!Chip_GPIO_GetPinState(LPC_GPIO, gpioSensor[OUT].port, gpioSensor[OUT].pin));
	while(Chip_GPIO_GetPinState(LPC_GPIO, gpioSensor[OUT].port, gpioSensor[OUT].pin));
	while(!Chip_GPIO_GetPinState(LPC_GPIO, gpioSensor[OUT].port, gpioSensor[OUT].pin));
	while(Chip_GPIO_GetPinState(LPC_GPIO, gpioSensor[OUT].port, gpioSensor[OUT].pin));
	while(!Chip_GPIO_GetPinState(LPC_GPIO, gpioSensor[OUT].port, gpioSensor[OUT].pin));
	while(Chip_GPIO_GetPinState(LPC_GPIO, gpioSensor[OUT].port, gpioSensor[OUT].pin));
	while(!Chip_GPIO_GetPinState(LPC_GPIO, gpioSensor[OUT].port, gpioSensor[OUT].pin));



	fin = xTaskGetTickCount();

	//return (int)((fin-inicio)*portTICK_RATE_MS/1000);

	return ((fin-inicio));
}
*/
